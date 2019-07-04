package server

import (
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
	err = ws.WriteMessage(1, []byte("Hi Client!"))
	if err != nil {
		s.Err.Println(err)
	}
	// listen indefinitely for new messages coming
	// through on our WebSocket connection
	s.listenOnWebSocket(ws)
}

func (s *Server) listenOnWebSocket(conn *websocket.Conn) {
	for {
		// read in a message
		messageType, p, err := conn.ReadMessage()
		if err != nil {
			s.Err.Println(err)
			return
		}
		// print out that message for clarity
		s.Info.Println(string(p))

		if err := conn.WriteMessage(messageType, []byte("did you just say \""+string(p)+"\"?")); err != nil {
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
