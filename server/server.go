package server

import (
	"encoding/json"
	"errors"
	"fmt"
	"log"
	"net/http"
	"os"

	"github.com/gorilla/websocket"
)

type agentRequest struct {
	AgentID    int        `json:"agentId"`
	Population population `json:"population"`
}

func (a agentRequest) String() string {
	return fmt.Sprintf("agentId: %d, population: %v", a.AgentID, a.Population)
}

type agentResponse struct {
	Population population `json:"population"`
	Func       string     `json:"function"`
	Dimensions int        `json:"dimensions"`
	MinValue   float64    `json:"minValue"`
	MaxValue   float64    `json:"maxValue"`
	AgentID    int        `json:"agentId"`
	CR         float64    `json:"paramCR"`
	F          float64    `json:"paramF"`
}

func (a agentResponse) String() string {
	return fmt.Sprintf("population: %v, function: %q, dimensions: %v, minValue: %f, maxValue: %f, agentId: %d, CR: %f, F: %f", a.Population, a.Func, a.Dimensions, a.MinValue, a.MaxValue, a.AgentID, a.CR, a.F)
}

type agent struct {
	ID               int           `json:"id"`
	AgentResponse    agentResponse `json:"data"`
	GenerationNumber int           `json:"generationNumber"`
}

func (a agent) String() string {
	return fmt.Sprintf("id: %v, agentResponse: %v, generationNumber: %d", a.ID, a.AgentResponse, a.GenerationNumber)
}

// Server type combines std output and std error loggers
type Server struct {
	Err  *log.Logger
	Info *log.Logger
}

var upgrader = websocket.Upgrader{
	ReadBufferSize:  1024,
	WriteBufferSize: 1024,
}

var agentsMap = make(map[int]agent)
var agentCount = 0

// GetServer is creating new server
func GetServer() *Server {
	return &Server{
		Err:  log.New(os.Stderr, "ERROR: ", log.Ldate|log.Ltime|log.Lshortfile),
		Info: log.New(os.Stdout, "INFO: ", log.Ldate|log.Ltime|log.Lshortfile)}
}

func (s *Server) handleWebSocket(w http.ResponseWriter, r *http.Request) {
	upgrader.CheckOrigin = func(r *http.Request) bool { return true }

	ws, err := upgrader.Upgrade(w, r, nil)
	if err != nil {
		s.Err.Println(err)
	}

	// helpful log statement to show connections
	s.Info.Println("Client Connected")

	population := populate(populationLength, fitnessFunc)

	resp := agentResponse{
		Population: population,
		Func:       fitnessFunc.ID.String(),
		Dimensions: fitnessFunc.Dimensions,
		MinValue:   fitnessFunc.MinValue,
		MaxValue:   fitnessFunc.MaxValue,
		AgentID:    agentCount,
		CR:         getCR(),
		F:          getF(),
	}
	agentsMap[agentCount] = agent{ID: agentCount, AgentResponse: resp, GenerationNumber: 1}
	currentAgentCount := agentCount

	agentCount++

	data, err := json.Marshal(resp)
	if err != nil {
		s.Err.Println(err)
	}

	err = ws.WriteMessage(1, data)
	if err != nil {
		s.Err.Println(err)
	}

	ws.SetCloseHandler(func(code int, reason string) error {
		if _, ok := agentsMap[currentAgentCount]; ok {
			delete(agentsMap, currentAgentCount)
		}

		return errors.New("Client closed connection")
	})

	s.listenOnWebSocket(ws)
}

func (s *Server) listenOnWebSocket(conn *websocket.Conn) {
	for {
		messageType, msg, err := conn.ReadMessage()
		if err != nil {
			conn.Close()
			s.Err.Println(err)
			return
		}

		var req agentRequest
		err = json.Unmarshal(msg, &req)
		if err != nil {
			conn.Close()
			s.Err.Println(err)
		}

		a := agentsMap[req.AgentID]

		if a.GenerationNumber >= maxNumOfGenerations {
			s.handleExceedingMaxNumOfGenerations(a, conn)
			return
		}
		a.GenerationNumber++
		agentsMap[a.ID] = a

		setNewPopulationToRandomAgent(req.Population)

		// s.Info.Println(agentsMap)

		data, err := json.Marshal(a.AgentResponse)
		if err != nil {
			conn.Close()
			s.Err.Println(err)
		}

		if err := conn.WriteMessage(messageType, data); err != nil {
			conn.Close()
			s.Err.Println(err)
			return
		}
	}
}

func setNewPopulationToRandomAgent(population population) {
	randomAgentID := getRandomAgentID()
	randomAgent := agentsMap[randomAgentID]
	randomAgent.AgentResponse.Population = population
	agentsMap[randomAgentID] = randomAgent
}

func getRandomAgentID() int {
	keys := make([]int, len(agentsMap))

	i := 0
	for k := range agentsMap {
		keys[i] = k
		i++
	}

	return keys[getRandInt(0, i)]
}

func (s *Server) handleExceedingMaxNumOfGenerations(a agent, conn *websocket.Conn) {
	finishMsg := fmt.Sprintf("achieved max number of generations - %d", a.GenerationNumber)

	if _, ok := agentsMap[a.ID]; ok {
		delete(agentsMap, a.ID)
	}

	if err := conn.WriteMessage(websocket.CloseMessage, websocket.FormatCloseMessage(websocket.CloseNormalClosure, finishMsg)); err != nil {
		conn.Close()
		s.Err.Println(err)
		return
	}

	s.Info.Println(finishMsg)
	conn.Close()
}

// Listen runs the server on a given port
func (s *Server) Listen(port string) {
	http.Handle("/", http.FileServer(http.Dir("public")))
	http.HandleFunc("/ws", s.handleWebSocket)

	s.Info.Printf("Server running on PORT: %s\n", port)

	s.Err.Fatal(http.ListenAndServe(":"+port, nil))
}
