/*
https://leetcode.com/problems/largest-subarray-length-k/

Given an array of positive numbers and a positive number ‘k’ , find the maximum sum of any
contiguous subarray of size ‘k’ .
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

class Solution {
public:
    int max_sub_array_sum(vector<int>& nums, int k) {
        int left = 0, sum = 0, maxSum = -1;

        for(int right=0;right<nums.size();right++){
            sum += nums[right];
            if(right >= k-1){
                if(maxSum == -1){
                    maxSum = sum;
                } else {
                    maxSum = max(sum, maxSum);
                }
                sum -= nums[left];
                left++;
            }
        }

        if(maxSum == -1 && k > nums.size()){
            return sum;
        }

        return maxSum;
    }
};

// Function to compute expected result (reference solution)
int expected_max_sub_array_sum(vector<int>& arr, int k) {
    if (arr.empty() || k <= 0 || k > (int)arr.size()) return 0;
    int window_sum = accumulate(arr.begin(), arr.begin() + k, 0);
    int max_sum = window_sum;
    for (int i = k; i < (int)arr.size(); ++i) {
        window_sum += arr[i] - arr[i - k];
        max_sum = max(max_sum, window_sum);
    }
    return max_sum;
}

void print_vector(const vector<int>& arr) {
    cout << "[";
    for (size_t i = 0; i < arr.size(); ++i) {
        cout << arr[i];
        if (i != arr.size() - 1) cout << ", ";
    }
    cout << "]";
}

int main() {
    srand((unsigned) time(nullptr));
    Solution sol;

    vector<pair<vector<int>, int>> tests;

    // --- Fixed edge cases ---
    tests.push_back({{2, 1, 5, 1, 3, 2}, 3});
    tests.push_back({{2, 3, 4, 1, 5}, 2});
    tests.push_back({{1, 1, 1, 1}, 2});
    tests.push_back({{10}, 1});
    tests.push_back({{4, 2}, 2});
    tests.push_back({{100, 200, 300, 400}, 4});
    tests.push_back({{5, 5, 5, 5, 5}, 3});
    tests.push_back({{2, 1, 5, 1, 3, 2}, 6});
    tests.push_back({{2, 1, 5, 1, 3, 2}, 1});

    // --- Random tests ---
    for (int t = 0; t < 5; ++t) {
        int size = rand() % 11 + 5; // [5,15]
        int k = rand() % size + 1;
        vector<int> arr(size);
        for (int i = 0; i < size; ++i)
            arr[i] = rand() % 20 + 1;
        tests.push_back({arr, k});
    }

    cout << "Running tests...\n\n";

    int passed = 0;
    for (size_t i = 0; i < tests.size(); ++i) {
        auto& arr = tests[i].first;
        int k = tests[i].second;

        int expected = expected_max_sub_array_sum(arr, k);
        int result;
        bool error = false;

        try {
            result = sol.max_sub_array_sum(arr, k);
        } catch (...) {
            cout << "❌ Test " << i + 1 << ": Exception occurred for arr=";
            print_vector(arr);
            cout << ", k=" << k << "\n";
            error = true;
        }

        if (!error) {
            if (result == expected) {
                cout << "✅ Test " << i + 1 << ": Passed | arr=";
                print_vector(arr);
                cout << ", k=" << k << ", sum=" << result << "\n";
                ++passed;
            } else {
                cout << "❌ Test " << i + 1 << ": Failed | arr=";
                print_vector(arr);
                cout << ", k=" << k << ", expected=" << expected << ", got=" << result << "\n";
            }
        }
    }

    cout << "\nSummary: " << passed << "/" << tests.size() << " tests passed.\n";
    return 0;
}