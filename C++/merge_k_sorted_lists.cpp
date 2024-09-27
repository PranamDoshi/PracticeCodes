/*
https://leetcode.com/problems/merge-k-sorted-lists/description/
*/

#include<iostream>
#include<vector>
#include<map>
#include<deque>

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

        void heapify(std::deque<ListNode*>& tempList){
            int index = tempList.size()-1;
            int parentIndex = (index-1)/2;
            int temp;
            while(index >= 0 && parentIndex >= 0 && tempList[index]->val < tempList[parentIndex]->val){
                temp = tempList[parentIndex]->val;
                tempList[parentIndex]->val = tempList[index]->val;
                tempList[index]->val = temp;
                index = parentIndex;
                parentIndex = (index-1)/2;
            }
        }

        void printHeap(std::deque<ListNode*> heap){
            for(const auto& node:heap){
                if(node){
                    std::cout << node->val << " , ";
                }
                else{
                    std::cout << "null , ";
                }
            }
            std::cout << "\n";
        }

        ListNode* popRoot(std::deque<ListNode*>& minHeap, int index=0){
            // printHeap(minHeap);
            // std::cout << "Popping index " << index << " from above heap\n";
            ListNode* temp;
            if(index >= minHeap.size()){
                return nullptr;
            }
            ListNode* lastRoot = minHeap[index];
            int leftIndex, rightIndex;

            if(minHeap[index] != nullptr){
                // std::cout << "Value at index " << index << " is " << lastRoot->val << "\n";
                leftIndex = (2*index)+1;
                rightIndex = leftIndex+1;

                if(leftIndex < minHeap.size() && minHeap[leftIndex] != nullptr && rightIndex < minHeap.size() && minHeap[rightIndex] != nullptr){
                    // std::cout << "Comparing " << minHeap[leftIndex]->val << " and " << minHeap[rightIndex]->val << "\n";
                    if(minHeap[leftIndex]->val <= minHeap[rightIndex]->val){
                        minHeap[index] = popRoot(minHeap, leftIndex);
                    }
                    else{
                        minHeap[index] = popRoot(minHeap, rightIndex);
                    }
                    return lastRoot;
                }
                else if(leftIndex < minHeap.size() && minHeap[leftIndex] == nullptr && rightIndex < minHeap.size() && minHeap[rightIndex] == nullptr){
                    // std::cout << "This Node has no childs!\n";
                    minHeap[index] = nullptr;
                    return lastRoot;
                }
                else if(leftIndex < minHeap.size()){
                    if(minHeap[leftIndex] == nullptr){
                        // std::cout << "Left child at index " << rightIndex << " is null\n";
                        minHeap[index] = popRoot(minHeap, rightIndex);
                    }
                    else{
                        // std::cout << "Left child at index " << rightIndex << " is not null\n";
                        minHeap[index] = popRoot(minHeap, leftIndex);
                    }
                    return lastRoot;
                }
                else if(rightIndex < minHeap.size()){
                    if(minHeap[rightIndex] == nullptr){
                        // std::cout << "Right child at index " << leftIndex << " is null\n";
                        minHeap[index] = popRoot(minHeap, leftIndex);
                    }
                    else{
                        // std::cout << "Right child at index " << rightIndex << " is not null\n";
                        minHeap[index] = popRoot(minHeap, rightIndex);
                    }
                    return lastRoot;
                }
                else{
                    minHeap[index] = nullptr;
                    return lastRoot;
                }
            }
            else{
                return nullptr;
            }

        }

        ListNode* mergeKLists(vector<ListNode*>& lists){
            if(lists.size() == 0){
                return nullptr;
            }
            else if(lists.size() == 1){
                return lists[0];
            }

            /*Approach 1: Time Complexity: O(n^3)*/
            // ListNode* reference_node = nullptr;
            // ListNode* newHead = nullptr;
            // int globalMinimum;
            // int i;
            // for(i = 0;i<lists.size();i++){
            //     if(lists[i]){
            //         reference_node = lists[i];
            //         newHead = reference_node;
            //         globalMinimum = newHead->val;
            //         break;
            //     }
            // }
            // if(reference_node == nullptr){
            //     return nullptr;
            // }

            // for(int j=i+1;j<lists.size();j++){
            //     reference_node = newHead;
            //     ListNode* tempNode = lists[j];
            //     ListNode* prevNode = nullptr;
            //     while(tempNode && reference_node){
            //         // printLinkeList(newHead);
            //         // while(reference_node && reference_node->next && reference_node->val == reference_node->next->val){
            //         //     reference_node = reference_node->next;
            //         // }

            //         // cout << "Comparing " << reference_node->val << " with " << tempNode->val << endl;
            //         if (reference_node->val < tempNode->val){
            //             prevNode = reference_node;
            //             reference_node = reference_node->next;
            //         }
            //         else if(reference_node->val == tempNode->val){
            //             ListNode* temp = reference_node->next;
            //             ListNode* temp2 = tempNode->next;
            //             reference_node->next = tempNode;
            //             reference_node->next->next = temp;
            //             tempNode = temp2;
            //             prevNode = reference_node;
            //             reference_node = reference_node->next;  
            //         }
            //         else{
            //             ListNode* temp = tempNode->next;
            //             tempNode->next = reference_node;
            //             if(tempNode->val < newHead->val){
            //                 newHead = tempNode;
            //                 globalMinimum = newHead->val;
            //             }
            //             if(prevNode){
            //                 prevNode->next = tempNode;
            //                 prevNode = prevNode->next;
            //             }
            //             else{
            //                 prevNode = tempNode;
            //             }
            //             tempNode = temp;
            //         }
            //     }
            //     if(tempNode){
            //         if(prevNode){
            //             prevNode->next = tempNode;
            //         }
            //     }
            // }

            // return newHead;

            /*Approach 2: Use min heap to reduce the time complexity */
            ListNode* temp;
            std::deque<ListNode*> minHeap = {};

            for(int i=0;i<lists.size();i++){
                if(!lists[i]){
                    continue;
                }
                else{
                    temp = lists[i];
                    while(temp){
                        minHeap.push_back(temp);
                        heapify(minHeap);
                        temp = temp->next;
                        // printHeap(minHeap);
                    }
                }
            }

            // printHeap(minHeap);
            ListNode* newHead = nullptr;
            ListNode* prev = nullptr;

            while(true){
                temp = popRoot(minHeap);
                if(!temp){
                    break;
                }
                temp->next = nullptr;
                // std::cout << "Popped from the heep: " << temp->val << "\n";
                if(!newHead){
                    newHead = temp;
                    prev = newHead;
                }
                else{
                    prev->next=temp;
                    prev=prev->next;
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
    /*Create first linked list*/
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

    // lists = {head1, head2, head3};
    // newHead = sol.mergeKLists(lists);
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

    /*Test Case 4*/
    ListNode* head4 = new ListNode(-2);
    ListNode* list4_node2 = new ListNode(-1);
    head4->next=list4_node2;
    ListNode* list4_node3 = new ListNode(-1);
    list4_node2->next=list4_node3;
    ListNode* list4_node4 = new ListNode(-1);
    list4_node3->next=list4_node4;

    sol.printLinkeList(head4);

    lists = {head4, nullptr};
    newHead = sol.mergeKLists(lists);
    sol.printLinkeList(newHead);
}
