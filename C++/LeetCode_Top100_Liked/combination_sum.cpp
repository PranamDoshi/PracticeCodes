/*
https://leetcode.com/problems/combination-sum/description/?envType=study-plan-v2&envId=top-100-liked
*/
#include<iostream>

using std::vector;
using std::cout;

class Solution {
public:
    void printVector(vector<int>& vec){
        for(int v:vec){
            cout << v << "-";
        }
        cout << std::endl;
    }

    int calculateSum(vector<int>& combination){
        int sum = 0;
        for(int cand:combination){
            sum += cand;
        }
        return sum;
    }
    
    void recursivelyCombine(vector<vector<int>>& combinations, vector<int>& combination, vector<int>& candidates, int target, int pos){
        // printVector(combination);
        int currentSum = calculateSum(combination);
        // cout << "Depth: " << depth << ", Current Target: " << target << ", Current sum: " << currentSum << std::endl;
        
        for(int i=pos;i<candidates.size();i++){
            // cout << "Parsiing " << cand << ", sum will be " << currentSum+cand << std::endl;
            if(currentSum + candidates[i] == target){
                combination.push_back(candidates[i]);
                combinations.emplace_back(combination);
                combination.pop_back();
            }
            else if(currentSum + candidates[i] < target){
                combination.push_back(candidates[i]);
                recursivelyCombine(combinations, combination, candidates, target, i);
                combination.pop_back();
            }
        }
    }

    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> combinations;
        vector<int> combination;

        recursivelyCombine(combinations, combination, candidates, target, 0);

        return combinations;
    }
};

int main(){
    Solution sol;

    vector<int> candidates = {2, 3, 6, 7};
    int target = 8;

    for(auto vec:sol.combinationSum(candidates, target)){
        for(int cand:vec){
            cout << cand << "-";
        }
        cout << std::endl;
    }

    return 0;
}
