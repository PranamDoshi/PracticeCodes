/*
https://leetcode.com/problems/linked-list-cycle/
*/
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    bool hasCycle(ListNode *head) {
        if(!head || !head->next){
            return false;
        }

        ListNode *slow=head, *fast=head;
        while(fast && fast -> next){
            slow = slow->next;
            fast = fast->next->next;
            if(slow == fast){
                return true;
            }
        }

        return false;
    }
};

// Reference implementation using Floyd's Cycle Detection Algorithm
bool expected_hasCycle(ListNode *head) {
    if (!head || !head->next) {
        return false;
    }
    ListNode *slow = head;
    ListNode *fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            return true;
        }
    }
    return false;
}

// Helper function to create a linked list with/without cycle
// If pos >= 0, create a cycle connecting tail to node at position 'pos'
ListNode* createLinkedList(const vector<int>& values, int pos) {
    if (values.empty()) {
        return nullptr;
    }

    vector<ListNode*> nodes;
    for (int val : values) {
        nodes.push_back(new ListNode(val));
    }

    for (size_t i = 0; i < nodes.size() - 1; ++i) {
        nodes[i]->next = nodes[i + 1];
    }

    if (pos >= 0 && pos < static_cast<int>(nodes.size())) {
        nodes.back()->next = nodes[pos];
    }

    return nodes[0];
}

// Helper to safely delete linked list (only works for acyclic lists)
// For cyclic lists in tests, we don't delete to avoid infinite loops
void cleanupLinkedList(ListNode* head, bool hasCycle) {
    if (hasCycle || !head) return;
    ListNode* curr = head;
    while (curr) {
        ListNode* next = curr->next;
        delete curr;
        curr = next;
    }
}

void runTest(const vector<int>& values, int pos, int testNum) {
    ListNode* head = createLinkedList(values, pos);
    bool expected = (pos >= 0); // If pos >= 0, there's a cycle
    bool actual = Solution().hasCycle(head);
    bool passed = (actual == expected);

    cout << "Test " << testNum << ": " << (passed ? "PASSED" : "FAILED") << endl;
    cout << "  Input: values = [";
    for (size_t i = 0; i < values.size(); ++i) {
        cout << values[i];
        if (i < values.size() - 1) cout << ", ";
    }
    cout << "], pos = " << pos << endl;
    cout << "  Expected: " << (expected ? "true" : "false") << endl;
    cout << "  Got: " << (actual ? "true" : "false") << endl;
    cout << endl;

    // Cleanup (only for acyclic to avoid infinite loops)
    cleanupLinkedList(head, pos >= 0);
}

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    cout << "Running LeetCode Problem: Linked List Cycle\n" << endl;

    // Fixed test cases from examples
    runTest({3, 2, 0, -4}, 1, 1);
    runTest({1, 2}, 0, 2);
    runTest({1}, -1, 3);

    // Additional fixed test cases
    runTest({}, -1, 4); // Empty list
    runTest({1}, 0, 5); // Single node cycle
    runTest({1, 2, 3, 4, 5}, -1, 6); // No cycle, multiple nodes
    runTest({1, 2, 3, 4, 5}, 2, 7); // Cycle to middle node

    // Random test cases
    cout << "Random test cases:\n" << endl;
    for (int i = 8; i <= 12; ++i) {
        int size = rand() % 10 + 1; // 1 to 10 nodes
        vector<int> values;
        for (int j = 0; j < size; ++j) {
            values.push_back(rand() % 201 - 100); // -100 to 100
        }

        // Randomly decide if there's a cycle (50% chance)
        int pos = (rand() % 2 == 0) ? (rand() % size) : -1;
        runTest(values, pos, i);
    }

    cout << "Verification complete.\n";
    return 0;
}
