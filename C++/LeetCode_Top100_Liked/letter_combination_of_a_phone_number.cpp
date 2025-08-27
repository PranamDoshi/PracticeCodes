/*
https://leetcode.com/problems/letter-combinations-of-a-phone-number/?envType=study-plan-v2&envId=top-100-liked
*/
#include<iostream>
#include<vector>
#include<map>

using std::cout;
using std::vector;
using std::string;

class Solution {
private:
    std::map<char, vector<char>> number_to_character_map = {
        {'2', {'a', 'b', 'c'}},
        {'3', {'d', 'e', 'f'}},
        {'4', {'g', 'h', 'i'}},
        {'5', {'j', 'k', 'l'}},
        {'6', {'m', 'n', 'o'}},
        {'7', {'p', 'q', 'r', 's'}},
        {'8', {'t', 'u', 'v'}},
        {'9', {'w', 'x', 'y', 'z'}},
    };

public:

    vector<string> crossProductVectors(vector<string>& v1, vector<char>& v2){
        vector<string> v_cp;
        for(string c1: v1){
            for(char c2: v2){
                v_cp.push_back(c1+c2);
            }
        }

        return v_cp;
    }

    vector<string> charVectorToStringVector(vector<char>& v_char){
        vector<string> v_string;
        for(char c: v_char){
            v_string.push_back(string(1, c));
        }
        return v_string;
    }

    vector<string> generateCombinations(vector<vector<char>>& alphabets_to_available_use) {
        vector<string> combinations, v_cp;

        v_cp = charVectorToStringVector(alphabets_to_available_use.at(0));
        if(alphabets_to_available_use.size() <= 1){
            return v_cp;
        }

        v_cp = crossProductVectors(v_cp, alphabets_to_available_use.at(1));
        for(int i=2;i<alphabets_to_available_use.size();i++){
            v_cp = crossProductVectors(v_cp, alphabets_to_available_use.at(i));
        }

        for(string comb: v_cp){
            combinations.push_back(comb);
        }

        return combinations;
    }

    vector<string> letterCombinations(string digits) {
        vector<vector<char>> alphabets_to_available_use;

        if(digits.size() == 0){
            return {};
        }

        for(char c: digits){
            alphabets_to_available_use.push_back(number_to_character_map.at(c));
            for(char c: alphabets_to_available_use.at(alphabets_to_available_use.size()-1)){
                cout << c << std::endl;
            }
            cout << "---------" << std::endl;
        }

        return generateCombinations(alphabets_to_available_use);
    }
};

int main() {
    Solution sol;
    for(string s: sol.letterCombinations("234")){
        cout << s << std::endl;
    }
    return 0;
}
