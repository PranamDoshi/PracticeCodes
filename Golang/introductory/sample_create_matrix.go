package main

import "fmt"

func createMatrix(rows, cols int) [][]int {
	matrix := make([][]int, rows)
	createRow := func(row_num, cols int) []int {
		row := make([]int, cols)
		for i := 0; i < len(row); i++ {
			row[i] = i * row_num
		}
		return row
	}

	for i := 0; i < rows; i++ {
		matrix[i] = createRow(i, cols)
	}

	return matrix
}

func main() {
	matrix := createMatrix(3, 4)
	for _, row := range matrix {
		fmt.Println(row)
	}
}
