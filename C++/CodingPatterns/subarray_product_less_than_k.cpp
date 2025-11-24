/*
https://leetcode.com/problems/subarray-product-less-than-k/
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cstdlib>
#include <ctime>

using namespace std;

class Solution {
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        // Cause 1 <= nums[i] <= 1000
        if(k <= 1){
            return 0;
        }

        int left = 0, right = 0, counter = 0;
        int product = 1;

        while(right < nums.size()){
            product *= nums[right];
            while(product >= k){
                product /= nums[left++];
            }
            if(product < k){counter += (right-left)+1;}
            right++;

            cout << nums[left] << "(" << left << ")" << "," << nums[right] << "(" << right << ")" << " ==> " << product << " -- " << counter << endl;
        }

        return counter;
    }
};

// Reference implementation to compute expected results
int expected_numSubarrayProductLessThanK(vector<int>& nums, int k) {
    if (k <= 1) return 0;

    int count = 0;
    int left = 0;
    long long product = 1;

    for (int right = 0; right < nums.size(); right++) {
        product *= nums[right];

        while (product >= k && left <= right) {
            product /= nums[left];
            left++;
        }

        // All subarrays ending at right with start positions from left to right
        count += (right - left + 1);
    }

    return count;
}

// Helper function to print vectors
void print_vector(const vector<int>& vec) {
    cout << "[";
    for (size_t i = 0; i < vec.size(); i++) {
        cout << vec[i];
        if (i < vec.size() - 1) cout << ", ";
    }
    cout << "]";
}

int main() {
    srand(time(0));

    Solution solution;
    int total_tests = 0;
    int passed_tests = 0;

    // Test case 1: Example 1
    {
        vector<int> nums = {10, 5, 2, 6};
        int k = 100;
        int expected = expected_numSubarrayProductLessThanK(nums, k);
        int result = solution.numSubarrayProductLessThanK(nums, k);

        total_tests++;
        cout << "Test " << total_tests << ": ";
        print_vector(nums);
        cout << ", k = " << k << endl;
        cout << "Expected: " << expected << ", Got: " << result;

        if (result == expected) {
            cout << " -> PASS" << endl;
            passed_tests++;
        } else {
            cout << " -> FAIL" << endl;
        }
        cout << endl;
    }

    // Test case 2: Example 2
    {
        vector<int> nums = {1, 2, 3};
        int k = 0;
        int expected = expected_numSubarrayProductLessThanK(nums, k);
        int result = solution.numSubarrayProductLessThanK(nums, k);

        total_tests++;
        cout << "Test " << total_tests << ": ";
        print_vector(nums);
        cout << ", k = " << k << endl;
        cout << "Expected: " << expected << ", Got: " << result;

        if (result == expected) {
            cout << " -> PASS" << endl;
            passed_tests++;
        } else {
            cout << " -> FAIL" << endl;
        }
        cout << endl;
    }

    // Test case 3: k = 1 (edge case)
    {
        vector<int> nums = {1, 1, 1};
        int k = 1;
        int expected = expected_numSubarrayProductLessThanK(nums, k);
        int result = solution.numSubarrayProductLessThanK(nums, k);

        total_tests++;
        cout << "Test " << total_tests << ": ";
        print_vector(nums);
        cout << ", k = " << k << endl;
        cout << "Expected: " << expected << ", Got: " << result;

        if (result == expected) {
            cout << " -> PASS" << endl;
            passed_tests++;
        } else {
            cout << " -> FAIL" << endl;
        }
        cout << endl;
    }

    // Test case 4: Single element array
    {
        vector<int> nums = {5};
        int k = 10;
        int expected = expected_numSubarrayProductLessThanK(nums, k);
        int result = solution.numSubarrayProductLessThanK(nums, k);

        total_tests++;
        cout << "Test " << total_tests << ": ";
        print_vector(nums);
        cout << ", k = " << k << endl;
        cout << "Expected: " << expected << ", Got: " << result;

        if (result == expected) {
            cout << " -> PASS" << endl;
            passed_tests++;
        } else {
            cout << " -> FAIL" << endl;
        }
        cout << endl;
    }

    // Test case 5: All products exceed k
    {
        vector<int> nums = {100, 200, 300};
        int k = 50;
        int expected = expected_numSubarrayProductLessThanK(nums, k);
        int result = solution.numSubarrayProductLessThanK(nums, k);

        total_tests++;
        cout << "Test " << total_tests << ": ";
        print_vector(nums);
        cout << ", k = " << k << endl;
        cout << "Expected: " << expected << ", Got: " << result;

        if (result == expected) {
            cout << " -> PASS" << endl;
            passed_tests++;
        } else {
            cout << " -> FAIL" << endl;
        }
        cout << endl;
    }

    // Random test cases
    for (int test = 1; test <= 5; test++) {
        int size = 5 + rand() % 10;  // Random size between 5 and 14
        vector<int> nums(size);

        for (int i = 0; i < size; i++) {
            nums[i] = 1 + rand() % 20;  // Random values between 1 and 20
        }

        int k = 10 + rand() % 500;  // Random k between 10 and 509

        int expected = expected_numSubarrayProductLessThanK(nums, k);
        int result = solution.numSubarrayProductLessThanK(nums, k);

        total_tests++;
        cout << "Test " << total_tests << " (Random): ";
        print_vector(nums);
        cout << ", k = " << k << endl;
        cout << "Expected: " << expected << ", Got: " << result;

        if (result == expected) {
            cout << " -> PASS" << endl;
            passed_tests++;
        } else {
            cout << " -> FAIL" << endl;
        }
        cout << endl;
    }

    // Summary
    cout << "======================================" << endl;
    cout << "Test Results: " << passed_tests << "/" << total_tests << " passed" << endl;
    if (passed_tests == total_tests) {
        cout << "All tests PASSED! ✓" << endl;
    } else {
        cout << "Some tests FAILED! ✗" << endl;
    }
    cout << "======================================" << endl;

    return 0;
}
