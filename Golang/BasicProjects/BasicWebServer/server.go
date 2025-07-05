package main

import (
	"fmt"
	"log"
	"net/http"
)

func WelcomeHandler(w http.ResponseWriter, r *http.Request) {
	log.Printf("Received request: %s - %s", r.Method, r.URL.Path)
	w.Write([]byte("Welcome to the Basic Web Server!"))
}

func WelcomeHandlerPost(w http.ResponseWriter, r *http.Request) {
	log.Printf("Received request: %s - %s", r.Method, r.URL.Path)
	w.Write([]byte("Welcome to the Basic Web Server! You made a POST request."))
}

func FormHandler(w http.ResponseWriter, r *http.Request) {
	log.Printf("Received request: %s - %s", r.Method, r.URL.Path)
	if r.Method == http.MethodPost {
		if err := r.ParseForm(); err != nil {
			log.Fatalf("An error occured when parsing the request form: ", err)
			http.Error(w, fmt.Sprintf("%s", err), http.StatusBadRequest)
		}
		name := r.FormValue("name")
		addr := r.FormValue("address")

		log.Printf("Name: %s, Address: %s", name, addr)
	} else {
		http.Error(w, fmt.Sprintf("%s is not alloed", r.Method), http.StatusNotFound)
	}
}

func main() {

	// muaxHandler := mux.NewRouter()
	// muaxHandler.HandleFunc("/", WelcomeHandler).Methods("GET")
	// muaxHandler.HandleFunc("/", WelcomeHandlerPost).Methods("POST")

	// muaxHandler.HandleFunc("/form", FormHandler).Methods("GET", "POST")

	/* Used by default when handler given to http.ListenAndServe is nil */
	// http.HandleFunc("/", func(w http.ResponseWriter, r *http.Request) {
	// 	log.Printf("Received request: %s - %s", r.Method, r.URL.Path)
	// 	w.Write([]byte("Hello, World!"))
	// })
	fileServer := http.FileServer(http.Dir("./static"))
	http.Handle("/", fileServer)
	http.HandleFunc("/form", FormHandler)

	fmt.Println("Starting web server on :8080")
	if err := http.ListenAndServe(":8080", nil); err != nil {
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
