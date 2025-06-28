package main

import "fmt"

func sum(nums ...int) int {
	sum := 0
	for _, num := range nums {
		sum += num
	}
	return sum
}

func printStrings(strings ...string) {
	for _, str := range strings {
		fmt.Println(str)
	}
}

func main() {
	total := sum(1, 2, 3)
	fmt.Println(total)

	input_strings := []string{"Hello", "World", "from", "Go"}
	printStrings(input_strings...)
}
