/*
https://leetcode.com/problems/longest-substring-with-at-most-k-distinct-characters/

Given a string, find the length of the longest substring in it with no more than K distinct characters.
You can assume that K is less than or equal to the length of the given string.
*/

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <set>
using namespace std;

// -----------------------------------------------------------------------------
// Solution class (User implementation placeholder)
// -----------------------------------------------------------------------------
class Solution {
public:
    char findMinimumIndexChar(std::unordered_map<char, int> map){
        int min = -1;
        char c;
        for(auto m:map){
            if (min == -1){
                min = m.second;
                c = m.first;
            } else if(m.second < min){
                min = m.second;
                c = m.first;
            }
        }
        return c;
    }

    int lengthOfLongestSubstringKDistinct(const string& s, int k) {
        std::unordered_map<char, int> charactersByIndex;
        int left = 0, longestSubString = 0;
        char minIndexChar;
        std::vector<char> tmp;

        for(int right=0;right<s.size();right++){
            if(charactersByIndex.size() < k){
                charactersByIndex[s[right]] = right;
                if(right-left+1 > longestSubString){
                    longestSubString = right-left+1;
                }
            } else {
                if(charactersByIndex.count(s[right]) == 1){
                    charactersByIndex[s[right]] = right;
                    if(right-left+1 > longestSubString){
                        longestSubString = right-left+1;
                    }
                } else {
                    minIndexChar = findMinimumIndexChar(charactersByIndex);
                    left = charactersByIndex[minIndexChar]+1;
                    charactersByIndex.erase(minIndexChar);
                    charactersByIndex[s[right]] = right;
                    
                    // Remove all the characters from the mapping where last seen index is less than the value of left to reset the window starting point.
                    tmp = {};
                    for(auto charInd: charactersByIndex){
                        if(charInd.second < left){
                            tmp.push_back(charInd.first);
                        }
                    }
                    for(char c: tmp){
                        charactersByIndex.erase(c);
                    }
                }
            }
        }

        return longestSubString;
    }
};

// -----------------------------------------------------------------------------
// Reference implementation for verification
// -----------------------------------------------------------------------------
int expected_lengthOfLongestSubstringKDistinct(const string& s, int k) {
    if (s.empty() || k == 0) return 0;
    unordered_map<char, int> freq;
    int left = 0, maxLen = 0;

    for (int right = 0; right < (int)s.size(); ++right) {
        freq[s[right]]++;
        while ((int)freq.size() > k) {
            freq[s[left]]--;
            if (freq[s[left]] == 0)
                freq.erase(s[left]);
            left++;
        }
        maxLen = max(maxLen, right - left + 1);
    }
    return maxLen;
}

// -----------------------------------------------------------------------------
// Helper utilities
// -----------------------------------------------------------------------------
void print_result_summary(const string& s, int k, int expected, int got) {
    cout << "Input: s = \"" << s << "\", k = " << k << endl;
    cout << "Expected: " << expected << ", Got: " << got << " --> ";
    if (expected == got) cout << "[PASS ✅]";
    else cout << "[FAIL ❌]";
    cout << "\n-------------------------------------------\n";
}

string random_string(int length) {
    string s;
    for (int i = 0; i < length; ++i) {
        s.push_back('a' + rand() % 5); // only a–e to create collisions
    }
    return s;
}

// -----------------------------------------------------------------------------
// Main test harness
// -----------------------------------------------------------------------------
int main() {
    srand((unsigned) time(0));
    Solution sol;

    vector<pair<string, int>> test_cases = {
        {"eceba", 2},
        {"aa", 1},
        {"abcadcacacaca", 3},
        {"", 1},
        {"aabbcc", 2},
        {"aabbcc", 3}
    };

    // Add some random cases
    for (int i = 0; i < 5; ++i) {
        string s = random_string(8 + rand() % 5);
        int k = 1 + rand() % max(1, (int)s.size());
        test_cases.push_back({s, k});
    }

    cout << "Running tests for: lengthOfLongestSubstringKDistinct\n";
    cout << "===========================================\n";

    string s;
    int k;
    for (auto& tc : test_cases) {
        s = tc.first;
        k = tc.second;

        int expected = expected_lengthOfLongestSubstringKDistinct(s, k);
        int got = sol.lengthOfLongestSubstringKDistinct(s, k);
        print_result_summary(s, k, expected, got);
    }

    cout << "All tests completed.\n";
    return 0;
}