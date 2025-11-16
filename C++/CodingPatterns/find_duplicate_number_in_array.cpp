/*
https://leetcode.com/problems/find-the-duplicate-number/
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cstdlib>
#include <ctime>
#include <random>
using namespace std;

// -----------------------------------------------------------------------------
// Solution under test
// -----------------------------------------------------------------------------
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int slow = nums[0];
        int fast = nums[0];

        // Phase 1: Detect cycle meeting point
        do {
            slow = nums[slow];
            fast = nums[nums[fast]];
        } while (slow != fast);

        // Phase 2: Find cycle start (duplicate)
        slow = nums[0];
        while (slow != fast) {
            slow = nums[slow];
            fast = nums[fast];
        }
        return slow;
    }
};

// -----------------------------------------------------------------------------
// Reference implementation (ground truth)
// -----------------------------------------------------------------------------
int expected_findDuplicate(const vector<int>& nums) {
    vector<int> freq(nums.size() + 1, 0);
    for (int v : nums) {
        if (++freq[v] > 1) return v;
    }
    return -1;
}

// -----------------------------------------------------------------------------
// Helper: print vector
// -----------------------------------------------------------------------------
void print_vector(const vector<int>& v) {
    cout << "[";
    for (int i = 0; i < (int)v.size(); i++) {
        cout << v[i];
        if (i + 1 < (int)v.size()) cout << ", ";
    }
    cout << "]";
}

// -----------------------------------------------------------------------------
// Main Test Harness
// -----------------------------------------------------------------------------
int main() {
    srand(time(nullptr));
    Solution sol;

    // Proper random generator for shuffle
    random_device rd;
    mt19937 gen(rd());

    vector<pair<string, vector<int>>> fixed_tests = {
        { "Example", {2,5,9,6,9,3,8,9,7,1} },
        {"Example 1", {1,3,4,2,2}},
        {"Example 2", {3,1,3,4,2}},
        {"Example 3", {3,3,3,3,3}},
        {"Small edge case", {1,1}},
        {"Another case", {2,1,4,3,2}}
    };

    cout << "Running fixed test cases...\n\n";
    for (auto& tc : fixed_tests) {
        auto nums = tc.second;

        int expected = expected_findDuplicate(nums);
        int got = sol.findDuplicate(nums);

        cout << tc.first << ":\n";
        cout << "  nums = ";
        print_vector(nums);
        cout << "\n  Expected = " << expected << "\n";
        cout << "  Got      = " << got << "\n";

        if (expected == got)
            cout << "  Result: PASS\n\n";
        else
            cout << "  Result: FAIL\n\n";
    }

    // ---------------------------------------------------------
    // Random tests
    // ---------------------------------------------------------
    cout << "Running random test cases...\n\n";

    for (int t = 1; t <= 5; t++) {
        int n = 5 + rand() % 10;
        vector<int> nums;

        int dup = 1 + rand() % n;

        for (int i = 1; i <= n; i++) nums.push_back(i);
        nums.push_back(dup);

        shuffle(nums.begin(), nums.end(), gen);

        int expected = expected_findDuplicate(nums);
        int got = sol.findDuplicate(nums);

        cout << "Random Test " << t << ":\n";
        cout << "  nums = ";
        print_vector(nums);
        cout << "\n  Expected = " << expected << "\n";
        cout << "  Got      = " << got << "\n";

        if (expected == got)
            cout << "  Result: PASS\n\n";
        else
            cout << "  Result: FAIL\n\n";
    }

    return 0;
}