package main

import (
	"fmt"
	"os"

	"github.com/radlinskii/wasm/server"
)

func main() {
	logger := server.GetLoggers()

	logger.Info.Println("Starting the server")

	port := os.Getenv("PORT")
	if port == "" {
		err := fmt.Errorf("PORT is not specified")
		logger.Err.Fatalln(err)
	}

	server.Run(port, logger)
}
