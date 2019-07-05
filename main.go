package main

import (
	"os"

	"github.com/radlinskii/dotenv"
	"github.com/radlinskii/wasm/server"
)

func main() {
	s := server.GetServer()

	err := dotenv.SetEnv()
	if err != nil {
		s.Err.Fatalln(err)
	}

	port := os.Getenv("PORT")
	if port == "" {
		s.Err.Fatalln("PORT is not specified")
	}

	s.Info.Println("Starting the server")

	s.Listen(port)
}
