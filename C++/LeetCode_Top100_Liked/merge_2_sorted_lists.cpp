/*
To run this file:
bash run.sh LeetCode_Top100_Liked/merge_2_sorted_lists.cpp LeetCode_Top100_Liked/utils.cpp
*/

#include <iostream>
#include <vector>
#include "utils.h"

using std::cout;

class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode *head = nullptr, *tmp = nullptr, *tmp_1 = nullptr;

        while(list1 != nullptr){
            if(head == nullptr){
                head = new ListNode(list1->val);
                tmp = head;
            }
            else{
                tmp->next = new ListNode(list1->val);
                tmp = tmp->next;
            }
            list1 = list1->next;
        }

        if (head == nullptr) {
            while (list2 != nullptr) {
                if (head == nullptr) {
                    head = new ListNode(list2->val);
                    tmp = head;
                } else {
                    tmp->next = new ListNode(list2->val);
                    tmp = tmp->next;
                }
                list2 = list2->next;
            }
            return head;
        }

        tmp = head;
        ListNode *prev = nullptr, *tmp_2 = nullptr;
        while(list2 != nullptr){

            while (tmp != nullptr && tmp->val < list2->val) {
                prev = tmp;
                tmp = tmp->next;
            }

            ListNode* newNode = new ListNode(list2->val);

            if (prev == nullptr) {
                // Insert at head
                newNode->next = head;
                head = newNode;
            } else {
                // Insert in the middle or end
                newNode->next = prev->next;
                prev->next = newNode;
            }

            // Reset traversal pointers
            prev = nullptr;
            tmp = head;

            list2 = list2->next;
        }

        return head;
    }
};

int main(){
    Solution sol;

    int size1 = 4;
    int size2 = 5;

    ListNode *lst1 = nullptr, *lst2 = nullptr, *lst = nullptr;

    lst1 = generateRandomNumsSortedLinkedList(size1, 0, 99);
    lst2 = generateRandomNumsSortedLinkedList(size2, 0, 99);

    printLinkedList(lst1);
    printLinkedList(lst2);

    lst = sol.mergeTwoLists(lst1, lst2);

    printLinkedList(lst);

    cout << std::endl;

    std::vector<int> nums1 = {1, 2, 4};
    std::vector<int> nums2 = {1, 3, 4};
    lst1 = createLinkedList(nums1);
    lst2 = createLinkedList(nums2);

    printLinkedList(lst1);
    printLinkedList(lst2);

    lst = sol.mergeTwoLists(lst1, lst2);

    printLinkedList(lst);

    return 0;
}
