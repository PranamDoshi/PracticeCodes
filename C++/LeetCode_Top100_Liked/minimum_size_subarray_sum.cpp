/*
https://leetcode.com/problems/minimum-size-subarray-sum/submissions/1822713666/

209. Minimum Size Subarray Sum

Given an array of positive integers nums and a positive integer target, return the minimal length of a subarray whose sum is greater than or equal to target. 
If there is no such subarray, return 0 instead.

Example 1:

Input: target = 7, nums = [2,3,1,2,4,3]
Output: 2
Explanation: The subarray [4,3] has the minimal length under the problem constraint.
Example 2:

Input: target = 4, nums = [1,4,4]
Output: 1
Example 3:

Input: target = 11, nums = [1,1,1,1,1,1,1,1]
Output: 0

Constraints:

1 <= target <= 109
1 <= nums.length <= 105
1 <= nums[i] <= 104
*/

#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <cstdlib>
#include <ctime>
using namespace std;

/*
Problem:
Given an array of positive integers nums and a positive integer target,
return the minimal length of a subarray whose sum is >= target.
If there is no such subarray, return 0.
*/

// --------------------------- USER SOLUTION ---------------------------
class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int sum = 0, minLength = nums.size(), tmp;
        int left = 0, right = 0;
        bool flag = false;

        while(left <= right && right <= nums.size()){
            std::cout << left << "-" << right << "-->" << sum << std::endl;
            if (sum >= target){
                flag = true;
                tmp = right-left;
                if(tmp < minLength){
                    minLength = tmp;
                }
                sum -= nums[left];
                left++;
            } else {
                if(right < nums.size()){
                    while(sum < target && right < nums.size()){
                        sum += nums[right];
                        if(right < nums.size()){
                            right++;
                        }
                    }
                } else {
                    break;
                }
            }
        }

        if(flag == true){
            return minLength;
        } else {
            return 0;
        }
    }
};

// --------------------------- REFERENCE IMPLEMENTATION ---------------------------
int expected_min_subarray_len(int target, const vector<int>& nums) {
    int n = nums.size();
    int minLen = n + 1;
    for (int i = 0; i < n; ++i) {
        int sum = 0;
        for (int j = i; j < n; ++j) {
            sum += nums[j];
            if (sum >= target) {
                minLen = min(minLen, j - i + 1);
                break; // no need to continue
            }
        }
    }
    return (minLen == n + 1) ? 0 : minLen;
}

// --------------------------- HELPER FUNCTIONS ---------------------------
void print_vector(const vector<int>& arr) {
    cout << "[";
    for (size_t i = 0; i < arr.size(); ++i) {
        cout << arr[i];
        if (i + 1 < arr.size()) cout << ", ";
    }
    cout << "]";
}

vector<int> generate_random_array(int size, int minVal, int maxVal) {
    vector<int> arr(size);
    for (int i = 0; i < size; ++i)
        arr[i] = minVal + rand() % (maxVal - minVal + 1);
    return arr;
}

// --------------------------- MAIN TEST HARNESS ---------------------------
int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    Solution sol;
    int passed = 0, total = 0;

    struct TestCase {
        int target;
        vector<int> nums;
    };

    vector<TestCase> tests = {
        {7, {2,3,1,2,4,3}},
        {4, {1,4,4}},
        {11, {1,1,1,1,1,1,1,1}},
        {15, {5,1,3,5,10,7,4,9,2,8}},
        {3, {3}},
        {10, {2,2,2,2,2}},
        {9, {1,2,3,4,5}},
        {20, {1,2,3,4,5}},
        {6, {6,1,1,1,1,1}},
        {1, {1,1,1,1,1}}
    };

    // Add some random test cases
    for (int i = 0; i < 5; ++i) {
        int n = 5 + rand() % 10;
        int target = 5 + rand() % 30;
        vector<int> arr = generate_random_array(n, 1, 10);
        tests.push_back({target, arr});
    }

    for (size_t i = 0; i < tests.size(); ++i) {
        total++;
        int expected = expected_min_subarray_len(tests[i].target, tests[i].nums);
        int got = sol.minSubArrayLen(tests[i].target, const_cast<vector<int>&>(tests[i].nums));

        bool ok = (expected == got);
        if (ok) {
            cout << "✅ Test " << total << ": Passed | nums=";
        } else {
            cout << "❌ Test " << total << ": Failed | nums=";
        }
        print_vector(tests[i].nums);
        cout << ", target=" << tests[i].target;
        cout << ", expected=" << expected << ", got=" << got << endl;

        if (ok) passed++;
    }

    cout << "Summary: " << passed << "/" << total << " tests passed." << endl;
    return 0;
}