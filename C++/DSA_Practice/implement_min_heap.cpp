#include<iostream>
#include<vector>
#include<random>
#include<deque>

using std::vector;
using std::string;

struct TreeNode
{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode* parent;
    TreeNode() : val(0),left(nullptr),right(nullptr),parent(nullptr) {}
    TreeNode(int& val) : val(val),left(nullptr),right(nullptr),parent(nullptr) {}
    TreeNode(int& val, TreeNode* parent) : val(val),left(nullptr),right(nullptr),parent(parent) {}
    TreeNode(int& val, TreeNode*& left, TreeNode*& right, TreeNode* parent) : val(val),left(left),right(right),parent(parent) {}
};


vector<int> generateRandomVector(int size, int min, int max){
    std::random_device rd;
    std::mt19937 gen(rd());
    
    std::uniform_int_distribution<> dis(min, max);

    vector<int> randomVector(size);
    for(int i=0;i<size;i++){
        randomVector[i] = dis(gen);
    }
    return randomVector;
}

void inOrderTraversal(TreeNode*& root){
    if(root != nullptr){
        inOrderTraversal(root->left);
        std::cout << root->val << "-";
        inOrderTraversal(root->right);
    }
}

void preOrderTraversal(TreeNode*& root){
    if(root != nullptr){
        std::cout << root->val << "-";
        preOrderTraversal(root->left);
        preOrderTraversal(root->right);
    }
}

void levelOrderTraversal(TreeNode*& root){
    std::deque<TreeNode*> tempQueue = {root};
    TreeNode* temp;
    while(tempQueue.size()>0){
        temp = tempQueue.front();
        tempQueue.pop_front();
        if(temp->left){
            tempQueue.push_back(temp->left);
        }
        if(temp->right){
            tempQueue.push_back(temp->right);
        }
        std::cout << temp->val << "-";
    }
}

TreeNode* popRoot(TreeNode*& root){
    TreeNode* temp;
    if(root){
        if(!root->left && !root->right){
            return nullptr;
        }
        else if(!root->left){
            return root->right;
        }
        else if(!root->right){
            return root->left;
        }
        else{
            if(root->left->val <= root->right->val){
                temp = root->left;
                temp->left = popRoot(temp);
                temp->right = root->right;
                return temp;
            }
            else{
                temp = root->right;
                temp->right = popRoot(temp);
                temp->left = root->left;
                return temp;
            }
        }
    }
    else{
        return nullptr;
    }
}

void sortedTraversal(TreeNode*& root){
    while(root){
        std::cout << root->val << "-";
        root = popRoot(root);
    }
}

void heapifyUp(TreeNode*& node){
    int temp;
    while(node && node->parent && node->parent->val > node->val){
        temp=node->parent->val;
        node->parent->val=node->val;
        node->val=temp;
        node=node->parent;
    }
}

void insertIntoHeap(int& val, TreeNode*& root){
    TreeNode* node = new TreeNode(val);
    std::deque<TreeNode*> tempVec = {root};
    TreeNode* temp;
    while(tempVec.size() > 0){
        temp = tempVec.front();
        tempVec.pop_front();

        if(temp->left){
            tempVec.push_back(temp->left);
        }
        else{
            node->parent = temp;
            temp->left = node;
            break;
        }

        if(temp->right){
            tempVec.push_back(temp->right);
        }
        else{
            node->parent = temp;
            temp->right = node;
            break;
        }
    }
    heapifyUp(node);
}

TreeNode* minHeapify(vector<int>& input){
    if(input.size() == 0){
        return new TreeNode();
    }
    TreeNode* root = new TreeNode(input[0]);
    for(int i=1;i<input.size();i++){
        insertIntoHeap(input[i], root);
    }

    return root;
}

int main(){
    vector<int> inputArray = generateRandomVector(10, 1, 1000);
    for(const auto& value:inputArray){
        std::cout << value << "-";
    }
    std::cout << '\n';

    TreeNode* root = minHeapify(inputArray);
    sortedTraversal(root);

    return 0;
}
