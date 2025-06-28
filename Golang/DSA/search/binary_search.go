package search

import (
	"DSA/sort"
	"fmt"
	"math/rand"
	"time"
)

func BinarySearch(arr []int, target int) bool {
	left, right := 0, len(arr)-1

	for left <= right {
		mid := left + (right-left)/2

		if arr[mid] == target {
			return true
		} else if arr[mid] < target {
			left = mid + 1
		} else {
			right = mid - 1
		}
	}

	return false
}

func generateArray(length int) []int {
	arr := make([]int, length)
	for i := 0; i < length; i++ {
		arr[i] = rand.Int()
	}
	return arr
}

func get_current_timestamp() int64 {
	return time.Now().UnixNano()
}

func Test_binarySearch(arr_length int) {
	arr := generateArray(arr_length)
	target := arr[rand.Intn(len(arr))]
	fmt.Printf("Testing binary search on an array of length %d with target %d.\n", arr_length, target)

	var start, end int64

	start = get_current_timestamp()
	arr = sort.MergeSort(arr)
	end = get_current_timestamp()
	fmt.Printf("Array sorted in %d nano-seconds.\n", end-start)

	start = get_current_timestamp()
	found := BinarySearch(arr, target)
	end = get_current_timestamp()
	fmt.Printf("Binary search completed in %d nano-seconds.\n", end-start)
	if found {
		fmt.Printf("Target %d found in the array.\n", target)
	} else {
		fmt.Printf("Target %d not found in the array.\n", target)
	}
	fmt.Println("--------------------------------------------------")
}
