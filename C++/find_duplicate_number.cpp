/*
https://leetcode.com/problems/find-the-duplicate-number/description/
*/
#include <iostream>
#include<vector>
// #include<unordered_set>

using std::cout;
using std::endl;
using std::vector;

class Solution{
    public:
        int findDuplicate(vector<int>& nums) {
            // std::unordered_set<int> uniqueNums;
            // for(int num:nums){
            //     if(uniqueNums.find(num) != uniqueNums.end()){
            //         return num;
            //     }
            //     else{
            //         uniqueNums.insert(num);
            //     }
            // }

            for(int i=0;i<nums.size();i++){
                int temp = abs(nums[i]);
                if(nums[temp] < 0){
                    return temp;
                }
                else{
                    nums[temp] *= -1;
                }
            }
            return -1;
        }
};

int main(){
    vector<int> nums = {1,2,3,4,2};
    Solution sol = Solution();
    for(int num: nums){
        cout << num << "-";
    }
    cout << endl << sol.findDuplicate(nums);
    return 0;
}
