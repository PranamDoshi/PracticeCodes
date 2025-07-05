package main

import (
	"net/http"

	"github.com/gomarkdown/markdown"
	"github.com/gomarkdown/markdown/html"
	"github.com/gomarkdown/markdown/parser"

	"fmt"
	"log"
	"os"
)

func mdToHTML(md []byte) []byte {
	// create markdown parser with extensions
	extensions := parser.CommonExtensions | parser.AutoHeadingIDs | parser.NoEmptyLineBeforeBlock
	fmt.Println("Using extensions:", extensions)
	p := parser.NewWithExtensions(extensions)
	doc := p.Parse(md)

	// create HTML renderer with extensions
	htmlFlags := html.CommonFlags | html.HrefTargetBlank
	opts := html.RendererOptions{Flags: htmlFlags}
	renderer := html.NewRenderer(opts)

	return markdown.Render(doc, renderer)
}

func read_markdown_file(filename string) ([]byte, error) {
	data, err := os.ReadFile(filename)
	if err != nil {
		return nil, fmt.Errorf("error reading file %s: %w", filename, err)
	}
	return data, nil
}

func ConvertMarkdownToHTML(filename string) ([]byte, error) {
	md, err := read_markdown_file(filename)
	if err != nil {
		fmt.Fprintf(os.Stderr, "Error reading markdown file: %v\n", err)
		return nil, err
	}

	html := mdToHTML(md)
	return html, nil
}

func getCwd() string {
	dir, err := os.Getwd()
	if err != nil {
		log.Fatalf("Error getting current working directory: %v", err)
	}
	return dir
}

func ConvertMarkdownToHTMLHandler(w http.ResponseWriter, r *http.Request) {
	log.Printf("Received request to convert markdown to HTML: %s - %s", r.URL.Path, r.Method)
	filename := r.URL.Query().Get("filename")
	if filename == "" {
		http.Error(w, "filename query parameter is required", http.StatusBadRequest)
		return
	}
	log.Printf("Current working directory: %s", getCwd())

	html, err := ConvertMarkdownToHTML(fmt.Sprintf("static/%s.md", filename))
	if err != nil {
		http.Error(w, fmt.Sprintf("Error converting markdown to HTML: %v", err), http.StatusInternalServerError)
		return
	}

	_, err = w.Write(html)
	if err != nil {
		http.Error(w, fmt.Sprintf("Error writing response: %v", err), http.StatusInternalServerError)
		return
	}
}

func main() {
	// muaxHandler := mux.NewRouter()
	// // muaxHandler.HandleFunc("/convert_md_to_html", ConvertMarkdownToHTMLHandler).Methods("GET")

	http.HandleFunc("/convert_md_to_html", ConvertMarkdownToHTMLHandler)

	log.Println("Starting server on port 8080...")
	if err := http.ListenAndServe(":8080", nil); err != nil {
		log.Fatal("Error starting server:", err)
		os.Exit(1)
	} else {
		log.Println("Server started on port 8080")
	}
}
