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

// Server type combines std output and std error loggers
type Server struct {
	Err  *log.Logger
	Info *log.Logger
}

var upgrader = websocket.Upgrader{
	ReadBufferSize:  1024,
	WriteBufferSize: 1024,
}

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
		Population:          population,
		Func:                fitnessFunc.ID.String(),
		Dimensions:          fitnessFunc.Dimensions,
		MinValue:            fitnessFunc.MinValue,
		MaxValue:            fitnessFunc.MaxValue,
		AgentID:             agentCount,
		CR:                  getCR(),
		F:                   getF(),
		MaxNumOfGenerations: agentPopulationsCount,
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

		mutatePopulationWithRandomAgent(req.Population)
		a.AgentResponse.Population = req.Population

		agentsMap[a.ID] = a

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

func (s *Server) handleExceedingMaxNumOfGenerations(a agent, conn *websocket.Conn) {
	finishMsg := fmt.Sprintf("achieved max number of generations - %d", a.GenerationNumber)
	fmt.Println(a.AgentResponse.Population[0])

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
