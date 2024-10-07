/*
https://leetcode.com/problems/longest-valid-parentheses/description/
*/

#include<iostream>
#include<vector>
#include<deque>
#include<tuple>
#include<stack>

using namespace std;

class Solution {
public:
    bool isValidParenthesesClosing(std::tuple<int, char>& t1, std::tuple<int, char>& t2){
        if(std::get<1>(t1) == '(' && std::get<1>(t2) == ')'){
            return true;
        }

        return false;
    }

    void printStack(std::deque<std::tuple<int, char>>& stack){
        std::cout << "-------------\n";
        for(auto& tuple: stack){
            std::cout << std::get<0>(tuple) << " -- " << std::get<1>(tuple) << "\n";
        }
    }

    // int longestValidParentheses(std::string& s) {
    //     std::deque<std::tuple<int, char>> stack = {};
    //     int maxLength = 0, lengthAtLastPop = 0;
    //     int tempLength = 0;
    //     std::tuple<int, char> lastValidStackPop = {};
    //     std::tuple<int, char> currentChar = {}, stackTop = {};

    //     for(int i=0;i<s.length();i++){

    //         currentChar = {i, s.at(i)};

    //         if(stack.empty()){
    //             if(std::get<1>(currentChar) == '('){
    //                 stack.push_back(currentChar);
    //             }
    //         }

    //         else{
    //             stackTop = stack.at(stack.size()-1);
    //             if(isValidParenthesesClosing(stackTop, currentChar)){
    //                 tempLength = (std::get<0>(currentChar) - std::get<0>(stackTop)) + 1;

    //                 if(std::tuple_size<decltype(lastValidStackPop)>::value != 0){
    //                     if(std::get<0>(lastValidStackPop) + 1 == std::get<0>(stackTop)){
    //                         tempLength += lengthAtLastPop;
    //                     }
    //                     // else if(std::get<0>(lastValidStackPop) + 1 == std::get<0>(currentChar)){
    //                     //     tempLength += lengthAtLastPop;
    //                     // }
    //                 }

    //                 if(tempLength > maxLength){
    //                     maxLength = tempLength;
    //                 }
    //                 lengthAtLastPop = tempLength;

    //                 lastValidStackPop = currentChar;
    //                 stack.pop_back();
    //             }

    //             else if(std::get<1>(currentChar) == ')'){
    //                 lengthAtLastPop = 0;
    //                 lastValidStackPop = {};
    //             }

    //             else{
    //                 stack.push_back(currentChar);
    //             }

    //             // if(stack.size() == 0){
    //             //     lastValidStackPop = {};
    //             // }

    //         }

    //         printStack(stack);
    //         std::cout << "lastValidStackPop:- " << std::get<0>(lastValidStackPop) << " -- " << std::get<1>(lastValidStackPop) << "\n";
    //     }

    //     return maxLength;
    // }

    int longestValidParentheses(string s) {
        int longest = 0;
        stack<int> st;

        //initially push -1 so that ')' is singly present ,push index into st
        st.push(-1);

        for(int i = 0 ; i< s.size() ; i++){
            if(s[i] == '('){
                st.push(i);
            }
            else{
                st.pop(); //at ')' pop
            }

            if(!st.empty()){  //after popping -1 is present, find longest
                longest = max(longest,i-st.top()); 
            }
            else{
                st.push(i); //stack is empty ,push ')' || '('
            }

            // for(auto& entry: st){
            //     std::cout << entry << "\n";
            // }

        }
      return longest;
    }
};

int main(){
    Solution sol = Solution();
    std::string input;
    
    input = "(()()";
    std::cout << "\n-----------------" << input << "----------------------\n";

    std::cout << sol.longestValidParentheses(input); // Expected: 4

    input = "(()";
    std::cout << "\n-----------------" << input << "----------------------\n";

    std::cout << sol.longestValidParentheses(input); // Expected: 2

    input = "()(())";
    std::cout << "\n-----------------" << input << "----------------------\n";

    std::cout << sol.longestValidParentheses(input); // Expected: 6

    input = "(()())";
    std::cout << "\n-----------------" << input << "----------------------\n";

    std::cout << sol.longestValidParentheses(input); // Expected: 6

    input = ")()())";
    std::cout << "\n-----------------" << input << "----------------------\n";

    std::cout << sol.longestValidParentheses(input); // Expected: 4

    return 0;
}
