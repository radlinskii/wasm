package server

import (
	"encoding/json"
	"net/http"
	"net/http/httptest"
	"strings"
	"testing"

	"github.com/gorilla/websocket"
)

func TestWsEndpoint(t *testing.T) {
	fitnessFunc = fitnessFunction{ID: beale, Dimensions: 5, MinValue: 1, MaxValue: 5}

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

	// check connection response
	_, got, err := ws.ReadMessage()
	if err != nil {
		t.Fatalf("could not send message over ws connection %v", err)
	}

	var testResp connectionResponse
	err = json.Unmarshal(got, &testResp)
	if err != nil {
		t.Fatalf("could not unmarshal server response")
	}

	if fitnessFunc.MinValue != testResp.MinValue {
		t.Fatalf("invalid MinValue - got: %f, expected: %f", fitnessFunc.MinValue, testResp.MinValue)
	}
	if fitnessFunc.MaxValue != testResp.MaxValue {
		t.Fatalf("invalid MaxValue - got: %f, expected: %f", fitnessFunc.MaxValue, testResp.MaxValue)
	}
	if fitnessFunc.Dimensions != testResp.Dimensions {
		t.Fatalf("invalid Dimensions - got: %d, expected: %d", fitnessFunc.Dimensions, testResp.Dimensions)
	}
	if fitnessFunc.ID.String() != testResp.Func {
		t.Fatalf("invalid Func Type - got: %q, expected: %q", fitnessFunc.ID.String(), testResp.Func)
	}

	// TODO check response after sending a request from client
	// // Send message to server, read response and check to see if it's what we expect.
	// msg := "hello"

	// if err := ws.WriteMessage(websocket.TextMessage, []byte(msg)); err != nil {
	// 	t.Fatalf("could not open a ws connection on %s %v", u, err)
	// }
	// _, got, err = ws.ReadMessage()
	// if err != nil {
	// 	t.Fatalf("could not send message over ws connection %v", err)
	// }
	// if expected := "did you just say \"" + msg + "\"?"; string(got) != "did you just say \""+msg+"\"?" {
	// 	t.Fatalf("invalid message - got: %q, expected: %q", string(got), expected)
	// }
}
