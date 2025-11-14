/*
https://leetcode.com/problems/longest-substring-with-at-most-two-distinct-characters/

Given a string, find the length of the longest substring in it with at most two distinct chatacters.
*/

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <cstdlib>
#include <ctime>
using namespace std;

// ---------------------------------------------------------------
// Solution Class (skeleton only)
// ---------------------------------------------------------------
class Solution {
public:
    int lengthOfLongestSubstringTwoDistinct(const string& s) {
        int start = 0, maxLength = 0, length = 0, maxUniqueChars = 2;
        unordered_map<char, int> freqMap = {};

        for(int right=0;right<s.size();right++){
            if(freqMap.count(s[right]) == 0){
                freqMap[s[right]] = 0;
            }
            freqMap[s[right]]++;
            length++;

            while(freqMap.size() > maxUniqueChars){
                freqMap[s[start]]--;
                length--;
                if(freqMap[s[start]] <= 0){
                    freqMap.erase(s[start]);
                }
                start++;
            }
            if(length > maxLength){
                maxLength = length;
            }
        }
        return maxLength;
    }
};

// ---------------------------------------------------------------
// Reference implementation (ground truth)
// ---------------------------------------------------------------
int expected_lengthOfLongestSubstringTwoDistinct(const string& s) {
    int n = s.size();
    if (n == 0) return 0;

    unordered_map<char, int> freq;
    int left = 0, max_len = 0;

    for (int right = 0; right < n; ++right) {
        freq[s[right]]++;
        while (freq.size() > 2) {
            freq[s[left]]--;
            if (freq[s[left]] == 0)
                freq.erase(s[left]);
            left++;
        }
        max_len = max(max_len, right - left + 1);
    }
    return max_len;
}

// ---------------------------------------------------------------
// Utility function to print test summary
// ---------------------------------------------------------------
void print_test_result(const string& input, int expected, int got, int test_num) {
    cout << "Test " << test_num << ": ";
    if (expected == got) {
        cout << "✅ PASS";
    } else {
        cout << "❌ FAIL";
    }
    cout << "\n   Input: \"" << input << "\""
         << "\n   Expected: " << expected
         << "\n   Got: " << got << "\n";
}

// ---------------------------------------------------------------
// Random string generator
// ---------------------------------------------------------------
string generate_random_string(int length) {
    string chars = "abcdefghijklmnopqrstuvwxyz";
    string s;
    for (int i = 0; i < length; ++i)
        s += chars[rand() % chars.size()];
    return s;
}

// ---------------------------------------------------------------
// Main test harness
// ---------------------------------------------------------------
int main() {
    srand((unsigned)time(0));
    Solution sol;

    vector<string> fixed_tests = {
        "",                  // empty string
        "a",                 // single character
        "aaaaa",             // all same characters
        "abc",               // 3 distinct
        "eceba",             // example case
        "ccaabbb",           // mixed repeating
        "ababffzzeee"        // alternating pattern
    };

    cout << "Running fixed tests...\n";
    int test_num = 1;
    for (const auto& s : fixed_tests) {
        int expected = expected_lengthOfLongestSubstringTwoDistinct(s);
        int got = sol.lengthOfLongestSubstringTwoDistinct(s);
        print_test_result(s, expected, got, test_num++);
    }

    cout << "\nRunning random tests...\n";
    for (int i = 0; i < 5; ++i) {
        string s = generate_random_string(10 + rand() % 10);
        int expected = expected_lengthOfLongestSubstringTwoDistinct(s);
        int got = sol.lengthOfLongestSubstringTwoDistinct(s);
        print_test_result(s, expected, got, test_num++);
    }

    cout << "\nAll tests completed.\n";
    return 0;
}