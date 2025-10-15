#include <iostream>
#include <vector>
#include <random>
#include <limits>
#include <algorithm>

#include "utils.h"

using std::vector;
using std::cout;

// ==================== Vector Utilities ====================
vector<int> generateRandomNumsArray(int size, int min, int max){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);

    vector<int> randomVector(size);
    for(int i = 0; i < size; i++){
        randomVector[i] = dis(gen);
    }
    return randomVector;
}

vector<vector<int>> generateRandomNums2DArray(int width, int height, int min, int max){
    vector<vector<int>> random2DVector;
    for(int w = 0; w < width; w++){
        random2DVector.push_back(generateRandomNumsArray(height, min, max));
    }
    return random2DVector;
}

void printArray(vector<int> arr){
    for(int a : arr){
        cout << a << ", ";
    }
    cout << std::endl;
}

void mergeSortMerge(vector<int>& arr, int left, int mid, int right){
    int a1 = mid - left + 1, a2 = right - mid;

    vector<int> L(a1), R(a2);

    for(int i = 0; i < a1; i++){
        L[i] = arr[left+i];
    }
    for(int j = 0; j < a2; j++){
        R[j] = arr[mid+j+1];
    }

    int i = 0, j = 0, k = left;

    while(i < a1 && j < a2){
        if(L[i] <= R[j]){
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }

    while(i < a1) arr[k++] = L[i++];
    while(j < a2) arr[k++] = R[j++];
}

void mergeSort(vector<int>& arr, int left, int right){
    if(left >= right) return;

    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    mergeSortMerge(arr, left, mid, right);
}

vector<int> sortVector(vector<int> nums, bool ascending){
    if(ascending)
        std::sort(nums.begin(), nums.end());
    else
        std::sort(nums.begin(), nums.end(), std::greater<int>());
    return nums;
}

// ==================== Random Number Utility ====================
int generateRandomNumber(int min, int max){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

// ==================== Linked List Utilities ====================
ListNode* generateRandomNumsLinkedList(int size, int min, int max){
    if(size <= 0) return nullptr;

    ListNode* head = new ListNode(generateRandomNumber(min, max));
    ListNode* temp = head;

    for(int i = 1; i < size; i++){
        temp->next = new ListNode(generateRandomNumber(min, max));
        temp = temp->next;
    }

    return head;
}

ListNode* generateRandomNumsSortedLinkedList(int size, int min, int max){
    ListNode* head = generateRandomNumsLinkedList(size, min, max);
    return sortLinkedList(head);
}

ListNode* createLinkedList(vector<int> nums){
    ListNode* head = nullptr;
    ListNode* tmp = nullptr;
    for(int val : nums){
        if(!head){
            head = new ListNode(val);
            tmp = head;
        } else {
            tmp->next = new ListNode(val);
            tmp = tmp->next;
        }
    }
    return head;
}

ListNode* sortLinkedList(ListNode* head, bool ascending){
    if(!head || !head->next) return head;

    vector<int> values;
    ListNode* current = head;

    while(current){
        values.push_back(current->val);
        current = current->next;
    }

    values = sortVector(values, ascending);

    current = head;
    for(int val : values){
        current->val = val;
        current = current->next;
    }

    return head;
}

void printLinkedList(ListNode* head){
    ListNode* temp = head;
    while(temp){
        cout << temp->val << ", ";
        temp = temp->next;
    }
    cout << std::endl;
}
