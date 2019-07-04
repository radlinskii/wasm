package server

import (
	"net/http"
	"net/http/httptest"
	"strings"
	"testing"

	"github.com/gorilla/websocket"
)

func TestWsEndpoint(t *testing.T) {
	server := GetServer()
	// Create test server from handler
	s := httptest.NewServer(http.HandlerFunc(server.handleWebSocket))
	defer s.Close()

	// Convert http://127.0.0.1 to ws://127.0.0.1
	u := "ws" + strings.TrimPrefix(s.URL, "http")

	// Connect to the server
	ws, _, err := websocket.DefaultDialer.Dial(u, nil)
	if err != nil {
		t.Fatalf("%v", err)
	}
	defer ws.Close()

	// Send message to server, read response and check to see if it's what we expect.
	msg := "hello"

	if err := ws.WriteMessage(websocket.TextMessage, []byte(msg)); err != nil {
		t.Fatalf("could not open a ws connection on %s %v", u, err)
	}

	_, got, err := ws.ReadMessage()
	if err != nil {
		t.Fatalf("could not send message over ws connection %v", err)
	}
	if expected := "Hi Client!"; string(got) != expected {
		t.Fatalf("bad message - got: %q, expected: %q", string(got), expected)
	}

	_, got, err = ws.ReadMessage()
	if err != nil {
		t.Fatalf("could not send message over ws connection %v", err)
	}
	if expected := "did you just say \"" + msg + "\"?"; string(got) != "did you just say \""+msg+"\"?" {
		t.Fatalf("bad message - got: %q, expected: %q", string(got), expected)
	}
}
