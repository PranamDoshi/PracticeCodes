/*
https://leetcode.com/problems/maximum-difference-between-adjacent-elements-in-a-circular-array/?envType=daily-question&envId=2025-06-12
*/
#include<vector>
#include<iostream>
#include<deque>

using std::cout;
using std::endl;
using std::vector;

void printArray(vector<int> array){
    for(int element:array){
        cout << element << " ";
    }
    cout << endl;
}

int getArraySize(vector<int> array){
    return array.size();
}

int getMod(int value, int MOD){
    return value % MOD;
}

int findMaxAdjecentDifference(vector<int> circular_array){
    int maxDiff = 0;
    int arrayLength = getArraySize(circular_array);
    int tempDiff;
    for(int i=0;i < arrayLength;i++){
        tempDiff = std::abs(circular_array[getMod(i+1, arrayLength)] - circular_array[i]);
        // cout << circular_array[getMod(i+1, arrayLength)] << " - " << circular_array[i] << " = " << tempDiff << endl;
        if(tempDiff > maxDiff){
            maxDiff = tempDiff;
        }
    }

    return maxDiff;
}

int main(){
    std::vector<int> circular_array;
    circular_array = {
        1, 2, 4
    };
    // printArray(circular_array);

    cout << findMaxAdjecentDifference(circular_array);

    return 0;
}
