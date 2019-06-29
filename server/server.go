package server

import (
	"fmt"
	"log"
	"net/http"
	"os"

	"github.com/gorilla/websocket"
)

// Logger combines std output and std error loggers
type Logger struct {
	Err  *log.Logger
	Info *log.Logger
}

// GetLoggers is initializing the loggers
func GetLoggers() *Logger {
	return &Logger{
		Err:  log.New(os.Stderr, "ERROR: ", log.Ldate|log.Ltime|log.Lshortfile),
		Info: log.New(os.Stdout, "INFO: ", log.Ldate|log.Ltime|log.Lshortfile)}
}

var upgrader = websocket.Upgrader{
	ReadBufferSize:  1024,
	WriteBufferSize: 1024,
}

func homePage(w http.ResponseWriter, r *http.Request) {
	fmt.Fprintf(w, "Home Page")
}

func wsEndpoint(w http.ResponseWriter, r *http.Request) {
	upgrader.CheckOrigin = func(r *http.Request) bool { return true }

	ws, err := upgrader.Upgrade(w, r, nil)
	if err != nil {
		log.Println(err)
	}

	// helpful log statement to show connections
	log.Println("Client Connected")
	err = ws.WriteMessage(1, []byte("Hi Client!"))
	if err != nil {
		log.Println(err)
	}
	// listen indefinitely for new messages coming
	// through on our WebSocket connection
	reader(ws)
}

func reader(conn *websocket.Conn) {
	for {
		// read in a message
		messageType, p, err := conn.ReadMessage()
		if err != nil {
			log.Println(err)
			return
		}
		// print out that message for clarity
		fmt.Println(string(p))

		if err := conn.WriteMessage(messageType, []byte("did you just say \""+string(p)+"\"?")); err != nil {
			log.Println(err)
			return
		}

	}
}

// Run runs the server
func Run(port string, logger *Logger) {
	http.Handle("/", http.FileServer(http.Dir("public")))
	http.HandleFunc("/ws", wsEndpoint)

	logger.Info.Printf("Server running on PORT: %s\n", port)

	logger.Err.Fatal(http.ListenAndServe(":"+port, nil))
}
