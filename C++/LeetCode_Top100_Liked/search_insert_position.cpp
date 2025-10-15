/*
https://leetcode.com/problems/search-insert-position/?envType=study-plan-v2&envId=top-100-liked

To run this file:
bash run.sh LeetCode_Top100_Liked/search_insert_position.cpp LeetCode_Top100_Liked/utils.cpp
*/
#include <iostream>
#include <vector>
#include "utils.h"

using std::vector;
using std::cout;

class Solution {
public:
    int search_using_binary_search(vector<int>& nums, int left, int right, int target){
        /*
        Given a sorted array of distinct integers and a target value, return the index if the target is found. If not, return the index where it would be if it were inserted in order.
        */
        int mid;
        cout << left << " - " << right << std::endl;

        if(nums[left] > target){
            // if(left > 0){
            //     return left-1;
            // }
            return left;
        }
        else if(nums[right] < target){
            if(right < nums.size()){
                return right+1;
            }
            return right;
        }

       if(left <= right){
            mid = (left+right)/2;
            cout << "Mid: " << mid << std::endl;

            if(nums[mid] == target){
                return mid;
            }
            else if(nums[mid] > target){
                // right = mid-1;
                return search_using_binary_search(nums, left, mid-1, target);
            }
            else{
                // left = mid+1;
                return search_using_binary_search(nums, mid+1, right, target);
            }
       }
       return -1;
    }

    int searchInsert(vector<int>& nums, int target) {
        return search_using_binary_search(nums, 0, nums.size()-1, target);
    }
};

int main(){
    Solution sol;
    vector<int> arr;
    int toFind;

    // for(int i=0;i<5;i++){
    //     arr = generateRandomNumsArray(5, 0, 99);
    //     printArray(arr);

    //     mergeSort(arr, 0, arr.size()-1);
    //     printArray(arr);

    //     toFind = generateRandomNumber(0, 99);
    //     cout << "To Find: " << toFind << " Result: " << std::endl << sol.searchInsert(arr, toFind) << std::endl;
    //     cout << "-------------------" << std::endl;
    // }

    arr = {1, 3};
    printArray(arr);
    toFind = 2;
    cout << "To Find: " << toFind << " Result: " << std::endl << sol.searchInsert(arr, toFind) << std::endl;

    return 0;
}
