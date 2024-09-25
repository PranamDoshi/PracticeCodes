/*
https://leetcode.com/problems/merge-k-sorted-lists/description/
*/

#include<iostream>
#include<vector>
#include<map>

using std::cout;
using std::vector;
using std::string;
using std::endl;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution{
    public:
        void printLinkeList(ListNode* head){
            while(head){
                cout << head->val << "->";
                head = head->next;
            }
            cout << endl;
        }

        ListNode* mergeKLists(vector<ListNode*>& lists){
            if(lists.size() == 0){
                return nullptr;
            }
            else if(lists.size() == 1){
                return lists[0];
            }

            /*Approach 1: Time Complexity: O(n^3)*/
            ListNode* reference_node = nullptr;
            ListNode* newHead = nullptr;
            int globalMinimum;
            int i;
            for(i = 0;i<lists.size();i++){
                if(lists[i]){
                    reference_node = lists[i];
                    newHead = reference_node;
                    globalMinimum = newHead->val;
                    break;
                }
            }
            if(reference_node == nullptr){
                return nullptr;
            }

            for(int j=i+1;j<lists.size();j++){
                reference_node = newHead;
                ListNode* tempNode = lists[j];
                ListNode* prevNode = nullptr;
                while(tempNode && reference_node){
                    // printLinkeList(newHead);
                    // while(reference_node && reference_node->next && reference_node->val == reference_node->next->val){
                    //     reference_node = reference_node->next;
                    // }

                    // cout << "Comparing " << reference_node->val << " with " << tempNode->val << endl;
                    if (reference_node->val < tempNode->val){
                        prevNode = reference_node;
                        reference_node = reference_node->next;
                    }
                    else if(reference_node->val == tempNode->val){
                        ListNode* temp = reference_node->next;
                        ListNode* temp2 = tempNode->next;
                        reference_node->next = tempNode;
                        reference_node->next->next = temp;
                        tempNode = temp2;
                        prevNode = reference_node;
                        reference_node = reference_node->next;  
                    }
                    else{
                        ListNode* temp = tempNode->next;
                        tempNode->next = reference_node;
                        if(tempNode->val < newHead->val){
                            newHead = tempNode;
                            globalMinimum = newHead->val;
                        }
                        if(prevNode){
                            prevNode->next = tempNode;
                            prevNode = prevNode->next;
                        }
                        else{
                            prevNode = tempNode;
                        }
                        tempNode = temp;
                    }
                }
                if(tempNode){
                    if(prevNode){
                        prevNode->next = tempNode;
                    }
                }
            }

            return newHead;
        }
};

int main(){
    Solution sol = Solution();
    ListNode* newHead;
    vector<ListNode*> lists;

    /*Test Case 1*/
    // /*Create first linked list*/
    // ListNode* head1 = new ListNode(1);
    // ListNode* list1_node2 = new ListNode(4);
    // head1->next = list1_node2;
    // ListNode* list1_node3 = new ListNode(5);
    // list1_node2->next = list1_node3;

    // sol.printLinkeList(head1);

    // /*Create second linked list*/
    // ListNode* head2 = new ListNode(1);
    // ListNode* list2_node2 = new ListNode(3);
    // head2->next = list2_node2;
    // ListNode* list2_node3 = new ListNode(4);
    // list2_node2->next = list2_node3;

    // sol.printLinkeList(head2);

    // /*Create Third List*/
    // ListNode* head3 = new ListNode(2);
    // ListNode* list3_node2 = new ListNode(6);
    // head3->next = list3_node2;

    // sol.printLinkeList(head3);

    // vector<ListNode*> lists = {head1, head2, head3};
    // ListNode* newHead = sol.mergeKLists(lists);
    // sol.printLinkeList(newHead);

    /*Test Case 2*/
    ListNode* head = new ListNode(1);
    lists = {nullptr, head};
    newHead = sol.mergeKLists(lists);
    sol.printLinkeList(newHead);

    /*Test Case 3*/
    /*Create first linked list*/
    ListNode* head1 = new ListNode(-1);
    ListNode* list1_node2 = new ListNode(1);
    head1->next = list1_node2;

    sol.printLinkeList(head1);

    /*Create second linked list*/
    ListNode* head2 = new ListNode(-3);
    ListNode* list2_node2 = new ListNode(1);
    head2->next = list2_node2;
    ListNode* list2_node3 = new ListNode(4);
    list2_node2->next = list2_node3;

    sol.printLinkeList(head2);

    /*Create Third List*/
    ListNode* head3 = new ListNode(-2);
    ListNode* list3_node2 = new ListNode(-1);
    head3->next = list3_node2;
    ListNode* list3_node3 = new ListNode(0);
    list3_node2->next = list3_node3;
    ListNode* list3_node4 = new ListNode(2);
    list3_node3->next = list3_node4;

    sol.printLinkeList(head3);

    lists = {head1, head2, head3};
    newHead = sol.mergeKLists(lists);
    sol.printLinkeList(newHead);
}
