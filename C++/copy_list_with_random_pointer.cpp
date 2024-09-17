/*
https://leetcode.com/problems/copy-list-with-random-pointer/
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <tuple>

// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = nullptr;
        random = nullptr;
    }
};

typedef std::unordered_map<Node*, Node*> nodeMap;
using std::cout;
using std::endl;

class Solution {
public:
    void print_linked_list_with_random_pointer(Node* head){
        while(head){
            cout << "New Node: " << endl;
            cout << head->val << " -> " << endl;
            if(head->next){
                cout << head->next->val << endl;
            }
            else{
                cout << "No next Node!" << endl;
            }
            if(head->random){
                cout << head->random->val << endl;
            }
            else{
                cout << "No random Node!" << endl;
            }
            head = head->next;
        }
        cout << endl;
    }

    Node* createACopy(Node* node){
        // Node* new_node = new Node(node->val);
        // new_node->next = node->next;
        // new_node->random = node->random;
        // return new_node;
        if(not node){
            return nullptr;
        }
        else{
            cout << "Creating a new node with value: " << node->val << endl;
            return new Node(node->val);
        }
    }

    struct customReturnType{
        Node* node_attr;
        nodeMap nodeMap_attr;
    };

    customReturnType recursivelyCopyRandomList(Node* head, nodeMap old_to_new_node_map = {}){
        if(not head){
            return {nullptr, old_to_new_node_map};
        }

        customReturnType customResult;

        if(old_to_new_node_map.find(head) == old_to_new_node_map.end()){
            old_to_new_node_map[head] = createACopy(head);
            customResult = recursivelyCopyRandomList(head->next, old_to_new_node_map);
            old_to_new_node_map = customResult.nodeMap_attr;
            old_to_new_node_map[head]->next = customResult.node_attr;

            // cout << "Mapping size reached: " <<  old_to_new_node_map.size() << endl;
            // print_linked_list_with_random_pointer(old_to_new_node_map[head]);
            customResult = recursivelyCopyRandomList(head->random, old_to_new_node_map);
            old_to_new_node_map = customResult.nodeMap_attr;
            old_to_new_node_map[head]->random = customResult.node_attr;

        }

        return {old_to_new_node_map[head], old_to_new_node_map};
    }

    Node* copyRandomList(Node* head) {
        /*
        nodeMap old_to_new_node_map;

        Node* new_head = createACopy(head);
        old_to_new_node_map[head] = new_head;

        Node* temp_head = head;
        Node* new_head = nullptr;
        Node* temp_new_head = nullptr;
        while(head){
            if(new_head){
                temp_new_head = createACopy(head);
            }
            else{
                new_head = createACopy(head);
                temp_new_head = new_head;
            }

            if(head->random){
                if(old_to_new_node_map.find(head->random) == old_to_new_node_map.end()){
                    old_to_new_node_map[head->random] = createACopy(head->random);
                }
                temp_new_head->random = old_to_new_node_map[head->random];
            }
            temp_new_head = temp_new_head->next;
            head = head->next;
        }

        return new_head;
        */
        customReturnType customResult = recursivelyCopyRandomList(head);
        return customResult.node_attr;
    }
};

int main(){
    Node* head = new Node(7);
    Node* node_2 = new Node(13);
    head->next = node_2;
    Node* node_3 = new Node(11);
    node_2->next = node_3;
    Node* node_4 = new Node(10);
    node_3->next = node_4;
    Node* node_5 = new Node(1);
    node_4->next = node_5;

    node_2->random = head;
    node_3->random = node_5;
    node_4->random = node_3;
    node_5->random = head;

    Solution sol = Solution();

    sol.print_linked_list_with_random_pointer(head);

    Node* new_head = sol.copyRandomList(head);

    sol.print_linked_list_with_random_pointer(new_head);

    return 0;
}
