package main

import (
	"fmt"
	"time"
)

func concurrentFib(n int) {
	ch := make(chan int)
	go func() {
		fibonacci(n, ch)
	}()
	for i := range ch {
		fmt.Println(i)
	}
}

func fibonacci(n int, ch chan int) {
	x, y := 0, 1
	for i := 0; i < n; i++ {
		ch <- x
		x, y = y, x+y
		time.Sleep(time.Microsecond * 10)
	}
	// Need to close the channel as the user of this function is going to range over this channel
	close(ch)
}

func test(n int) {
	fmt.Printf("Printing %v numbers\n", n)
	concurrentFib(n)
	fmt.Println("============================")
}

func main() {
	test(10)
}
