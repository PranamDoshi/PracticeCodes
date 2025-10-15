#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <limits>

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// ==================== Vector Utilities ====================
std::vector<int> generateRandomNumsArray(int size, int min = 0, int max = std::numeric_limits<int>::max());
std::vector<std::vector<int>> generateRandomNums2DArray(int width, int height, int min = 0, int max = std::numeric_limits<int>::max());
void mergeSort(std::vector<int>& arr, int left, int right);
std::vector<int> sortVector(std::vector<int> nums, bool ascending = true);
void printArray(std::vector<int> arr);

// ==================== Linked List Utilities ====================
ListNode* generateRandomNumsLinkedList(int size, int min = 0, int max = std::numeric_limits<int>::max());
ListNode* generateRandomNumsSortedLinkedList(int size, int min = 0, int max = std::numeric_limits<int>::max());
ListNode* createLinkedList(std::vector<int> nums);
ListNode* sortLinkedList(ListNode* head, bool ascending = true);
void printLinkedList(ListNode* head);

// ==================== Random Number Utility ====================
int generateRandomNumber(int min = 0, int max = std::numeric_limits<int>::max());

#endif
