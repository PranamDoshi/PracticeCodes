/*
https://leetcode.com/problems/search-a-2d-matrix/description/?envType=study-plan-v2&envId=top-100-liked

To run this: 
bash run.sh LeetCode_Top100_Liked/search_2D_matrix.cpp LeetCode_Top100_Liked/utils.cpp
*/
#include <iostream>
#include <vector>
#include "utils.h"

using std::vector;
using std::cout;
using std::endl;

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int left, mid, right;
        int y_axis = -1;
        int size = matrix.size();
        // First find the x-axis where the target exist.
        left = 0;
        right = size-1;
        while(left <= right){
            // cout << left << " , " << right << endl;
            if(left == right){
                if(matrix[left][0] == target){
                    return true;
                }
                else if(matrix[left][0] > target && left > 0){
                    y_axis = left-1;
                }
                else{
                    y_axis = left;
                    break;
                }
            }

            else if(matrix[left][0] > target){
                right = left-1;
                continue;
            }

            mid = (left+right)/2;
            // cout << left << " + " << right << " = " << mid << endl;
            if(matrix[mid][0] == target){
                return true;
            }
            else if(matrix[mid][0] < target){
                left = mid+1;
            }
            else{
                right = mid-1;
            }
        }
        if(y_axis == -1){
            y_axis = right;
        }

        // if the target was already found in first column, this logic won't get executed.
        // if the target was no found in the first column, we assume that y_axis variable has the row number where the element should exist.
        if(y_axis == -1){
            // cout << "Couldn't find the y_axis where the target might belong." << endl;
            return false;
        }
        // cout << "y_axis = " << y_axis << endl;
        
        // Now let's perform binary search over the selected y_axis.
        left = 0;
        right = matrix[y_axis].size()-1;
        while(left <= right){
            // cout << left << " , " << right << endl;
            mid = (left+right)/2;
            // cout << left << " + " << right << " = " << mid << endl;
            if(matrix[y_axis][mid] == target){
                return true;
            }
            else if(matrix[y_axis][mid] < target){
                left = mid+1;
            }
            else{
                right = mid-1;
            }
        }

        return false;
    }
};

int main(){
    Solution sol;

    // int m=4, n=3;
    // vector<vector<int>> arr_2d = generateRandomNums2DArray(m, n, 0, 99);
    // for(vector<int> v: arr_2d){
    //     printArray(v);
    // }
    // arr_2d[0][0] = 3;
    // for(vector<int> v: arr_2d){
    //     printArray(v);
    // }
    // int target = generateRandomNumber(0, 99);

    vector<vector<int>> arr_2d = {
        {1, 3, 5, 7},
        {10, 11, 16, 20},
        {23, 30, 34, 60}
    };
    for(vector<int> v: arr_2d){
        printArray(v);
    }
    cout << endl;
    int target, result;

    target = 3;
    cout << "To find: " << target << endl;
    result = sol.searchMatrix(arr_2d, target);
    cout << "Result: " << result << endl; // true
    cout << endl;

    target = 16;
    cout << "To find: " << target << endl;
    result = sol.searchMatrix(arr_2d, target);
    cout << "Result: " << result << endl; // true
    cout << endl;

    target = 15;
    cout << "To find: " << target << endl;
    result = sol.searchMatrix(arr_2d, target);
    cout << "Result: " << result << endl; // false
    cout << endl;

    target = 60;
    cout << "To find: " << target << endl;
    result = sol.searchMatrix(arr_2d, target);
    cout << "Result: " << result << endl; // true
    cout << endl;

    target = 61;
    cout << "To find: " << target << endl;
    result = sol.searchMatrix(arr_2d, target);
    cout << "Result: " << result << endl; // false
    cout << endl;

    arr_2d = {{-10,-8},{-6,-5},{-2,-2},{-1,0},{3,4},{7,7},{8,9},{10,10},{11,11},{12,14},{15,16},{17,19},{20,21},{22,22},{25,27},{28,30},{32,32},{35,36}};
    for(vector<int> v: arr_2d){
        printArray(v);
    }
    cout << endl;

    target = 16;
    cout << "To find: " << target << endl;
    result = sol.searchMatrix(arr_2d, target);
    cout << "Result: " << result << endl; // true
    cout << endl;

    return 0;
}
