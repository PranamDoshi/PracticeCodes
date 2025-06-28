package main

import (
	"fmt"
	"math"
	"strings"
)

type Vertex struct {
	X, Y float64
}

func (v Vertex) Abs() float64 {
	return math.Sqrt(v.X*v.X + v.Y*v.Y)
}

func (v Vertex) Scale(f float64) Vertex {
	v.X = v.X * f
	fmt.Println(v.X)
	v.Y = v.Y * f
	fmt.Println(v.Y)
	return v
}

// VS

func (v *Vertex) Scale_onPointer(f float64) {
	v.X = v.X * f
	v.Y = v.Y * f
}

func monthlyBillIncrease(costPerSend, numLastMonth, numThisMonth int) int {
	var lastMonthBill int
	var thisMonthBill int
	getBillForMonth(&lastMonthBill, costPerSend, numLastMonth)
	getBillForMonth(&thisMonthBill, costPerSend, numThisMonth)
	return thisMonthBill - lastMonthBill
}

func getBillForMonth(bill *int, costPerSend, messagesSent int) {
	*bill = costPerSend * messagesSent
}

func replaceAllExample(message *string) {
	if message == nil {
		return
	}
	messageVal := *message
	bad_words := []string{"dang", "darn", "drat"}
	for _, bad_word := range bad_words {
		messageVal = strings.ReplaceAll(messageVal, bad_word, "****")
	}
	*message = messageVal
}

func main() {
	/*
		Example of using pointers in Go.
		var p *int
		i := 42
		p = &i

		// "dereferencing" or "indirecting"
		fmt.Println(*p) // read i through the pointer p
		*p = 21         // set i through the pointer p
		fmt.Println(i)
	*/

	/*
		Example of using a switch statement in Go.
		switch os := runtime.GOOS; os {
		case "darwin":
			fmt.Println("macOS.")
		case "linux":
			fmt.Println("Linux.")
		default:
			// freebsd, openbsd,
			// plan9, windows...
			fmt.Printf("%s!", os)
		}
	*/

	/*
		Demonstration of methods in Go.
		v := Vertex{3, 4}
		v.Scale(10)
		fmt.Println(v)
		fmt.Println(v.Abs())

		v1 := Vertex{3, 4}
		v1.Scale_onPointer(10)
		fmt.Println(v1)
		fmt.Println(v1.Abs())
	*/

	// fmt.Println(utf8.RuneCountInString("Hello, 世界")) // Count runes in a string

	/*
		Example of using strings.ReplaceAll in Go.
	*/
	message := "This is a dang test with darn and drat words."
	replaceAllExample(&message)
	fmt.Println(message)

}
