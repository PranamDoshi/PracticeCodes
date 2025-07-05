package main

import (
	"fmt"
	"log"
	"net/http"

	"github.com/gorilla/mux"
)

func WelcomeHandler(w http.ResponseWriter, r *http.Request) {
	log.Printf("Received request: %s - %s", r.Method, r.URL.Path)
	w.Write([]byte("Welcome to the Basic Web Server!"))
}

func WelcomeHandlerPost(w http.ResponseWriter, r *http.Request) {
	log.Printf("Received request: %s - %s", r.Method, r.URL.Path)
	w.Write([]byte("Welcome to the Basic Web Server! You made a POST request."))
}

func main() {

	muaxHandler := mux.NewRouter()
	muaxHandler.HandleFunc("/", WelcomeHandler).Methods("GET")
	muaxHandler.HandleFunc("/", WelcomeHandlerPost).Methods("POST")

	/* Used by default when handler given to http.ListenAndServe is nil */
	// http.HandleFunc("/", func(w http.ResponseWriter, r *http.Request) {
	// 	log.Printf("Received request: %s - %s", r.Method, r.URL.Path)
	// 	w.Write([]byte("Hello, World!"))
	// })

	// http.HandleFunc("/fevicon.ico", func(w http.ResponseWriter, r *http.Request) {
	// 	log.Printf("Received request: %s - %s", r.Method, r.URL.Path)
	// 	w.Write([]byte("Hello, World!"))
	// })

	fmt.Println("Starting web server on :8080")
	if err := http.ListenAndServe(":8080", muaxHandler); err != nil {
		log.Fatal("Error starting server:", err)
	}

	// Code below this does not run because ListenAndServe blocks
	resp, err := http.Post("http://localhost:8080/", "application/json", nil)
	if err != nil {
		log.Fatal("Error making POST request:", err)
	}
	defer resp.Body.Close()
	responseBody := make([]byte, 0)
	_, err = resp.Body.Read(responseBody)
	if err != nil {
		log.Fatal("Error reading response body:", err)
	}
	log.Printf("POST request response status: %s - %s", resp.Status, responseBody)
}
