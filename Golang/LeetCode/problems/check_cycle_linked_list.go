/*
https://leetcode.com/problems/linked-list-cycle/description/
*/
package problems

import (
	"LeetCode/utils"
	"fmt"
)

var (
	start, end int64
)

type ListNode struct {
	Val  int
	Next *ListNode
}

func printLinkedList(head *ListNode) {
	temp := head
	for temp != nil {
		fmt.Printf("%v -> ", temp.Val)
		temp = temp.Next
	}
	fmt.Println("nil")
}

func hasCycle(head *ListNode) bool {
	if head == nil || head.Next == nil {
		return false
	}

	ptrMap, temp := make([*ListNode]int, 0), head
	for temp != nil {
		val, exists := ptrMap[temp]
		if exists {
			return true // Cycle detected
		}
		ptrMap[temp] = 1 // Mark this node as visited
		temp = temp.Next
	}

	return false
}

func TestCheckCycleInLinkedList() {
	var has_cycle bool

	head := &ListNode{Val: 3}
	head.Next = &ListNode{Val: 2}
	head.Next.Next = &ListNode{Val: 0}
	head.Next.Next.Next = &ListNode{Val: -4}
	head.Next.Next.Next.Next = head.Next // Creating a cycle

	start = utils.GetCurrentTimeStamp()
	has_cycle = hasCycle(head)
	fmt.Println(has_cycle) // Should return true
	if !has_cycle {
		printLinkedList(head) // Print the linked list if no cycle is detected
	}
	end = utils.GetCurrentTimeStamp()
	fmt.Printf("Time taken: %d ms\n", end-start)

	// Test with no cycle
	head2 := &ListNode{Val: 1}
	head2.Next = &ListNode{Val: 2}

	start = utils.GetCurrentTimeStamp()
	has_cycle = hasCycle(head)
	fmt.Println(has_cycle) // Should return false
	if !has_cycle {
		printLinkedList(head) // Print the linked list if no cycle is detected
	}
	end = utils.GetCurrentTimeStamp()
	fmt.Printf("Time taken: %d ms\n", end-start)
}
