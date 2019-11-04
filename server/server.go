package server

import (
	"encoding/json"
	"fmt"
	"log"
	"net/http"
	"os"

	"github.com/gorilla/websocket"
)

// connectionResponse is the initial json response send by WebSocket when client gets connected.
type connectionResponse struct {
	Population population `json:"population"`
	Func       string     `json:"function"`
	Dimensions int        `json:"dimensions"`
	MinValue   float64    `json:"minValue"`
	MaxValue   float64    `json:"maxValue"`
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
	resp := connectionResponse{population, fitnessFunc.ID.String(), fitnessFunc.Dimensions, fitnessFunc.MinValue, fitnessFunc.MaxValue}

	data, err := json.Marshal(resp)
	if err != nil {
		s.Err.Println(err)
	}

	err = ws.WriteMessage(1, data)
	if err != nil {
		s.Err.Println(err)
	}

	// listen indefinitely for new messages coming
	// through on our WebSocket connection
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

		var newGeneration population
		err = json.Unmarshal(msg, &newGeneration)

		if genCount >= maxNumOfGenerations {
			finishMsg := fmt.Sprintf("achieved max number of generations - %d", genCount)

			if err := conn.WriteMessage(websocket.CloseMessage, websocket.FormatCloseMessage(websocket.CloseNormalClosure, finishMsg)); err != nil {
				conn.Close()
				s.Err.Println(err)
				return
			}

			s.Info.Println(finishMsg)
			conn.Close()
			return
		}

		genCount++
		s.Info.Printf("geneneration number: %d\n", genCount)
		s.Info.Println(newGeneration)

		resp := connectionResponse{newGeneration, fitnessFunc.ID.String(), fitnessFunc.Dimensions, fitnessFunc.MinValue, fitnessFunc.MaxValue}

		data, err := json.Marshal(resp)
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

// Listen runs the server on a given port
func (s *Server) Listen(port string) {
	http.Handle("/", http.FileServer(http.Dir("public")))
	http.HandleFunc("/ws", s.handleWebSocket)

	s.Info.Printf("Server running on PORT: %s\n", port)

	s.Err.Fatal(http.ListenAndServe(":"+port, nil))
}
