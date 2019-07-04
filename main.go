package main

import (
	"fmt"
	"os"

	"github.com/radlinskii/wasm/server"
)

func main() {
	s := server.GetServer()

	s.Info.Println("Starting the server")

	port := os.Getenv("PORT")
	if port == "" {
		err := fmt.Errorf("PORT is not specified")
		s.Err.Fatalln(err)
	}

	s.Listen(port)
}
