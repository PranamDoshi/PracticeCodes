package main

import "fmt"

func fibonacci() func() int {
	num_1, num_2 := -1, -1

	add := func(a, b int) int {
		sum := 0
		if a != -1 {
			sum += a
		}
		if b != -1 {
			sum += b
		}
		return sum
	}
	var num int

	return func() int {
		if num_1 == -1 {
			num_1 = 0
			num = add(num_1, num_2)
		} else if num_2 == -1 {
			num_2 = 1
			num = add(num_1, num_2)
		} else {
			num = add(num_1, num_2)
			num_1, num_2 = num_2, num
		}

		return num
	}
}

func main() {
	f := fibonacci()
	for i := 0; i < 10; i++ {
		fmt.Println(f())
	}
}
