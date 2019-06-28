package main

import (
	"fmt"
	"log"
	"net/http"
	"os"

	"github.com/gorilla/websocket"
)

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

func getLoggers() (info *log.Logger, err *log.Logger) {
	err = log.New(os.Stderr, "ERROR: ", log.Ldate|log.Ltime|log.Lshortfile)
	info = log.New(os.Stdout, "INFO: ", log.Ldate|log.Ltime|log.Lshortfile)

	return
}

func main() {
	infoLogger, errLogger := getLoggers()

	infoLogger.Println("Starting the server")

	port := os.Getenv("PORT")
	if port == "" {
		err := fmt.Errorf("PORT is not specified")
		errLogger.Fatalln(err)
	}

	infoLogger.Printf("Server running on PORT: %s\n", port)

	http.Handle("/", http.FileServer(http.Dir("public")))
	http.HandleFunc("/ws", wsEndpoint)

	errLogger.Fatal(http.ListenAndServe(":"+port, nil))
}
