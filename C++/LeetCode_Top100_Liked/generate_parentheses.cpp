/*
https://leetcode.com/problems/generate-parentheses/description/?envType=study-plan-v2&envId=top-100-liked

n = 4
()()()()

(())(())
(())()()
()(())()
()()(())

(()())()
()(()())
(()()())

((()))()
()((()))

((())())
(()(()))

(((())))
*/
#include<iostream>
#include<vector>

using std::vector;
using std::string;
using std::cout;

class Solution {
public:
    void recursivelyGenerateParenthesis(vector<string>& parenthesis, string& combination, int size, int num_of_opening_brackets, int num_of_closing_brackets){
        string temp;
        // cout << combination << " --> " << num_of_opening_brackets << "(, " << num_of_closing_brackets << ")" << std::endl;

        if(combination.size() == size*2){
            // cout << "Appending " << combination << std::endl;
            parenthesis.emplace_back(combination);
            return;
        }

        if(num_of_opening_brackets == num_of_closing_brackets){
            temp = combination + "(";
            recursivelyGenerateParenthesis(parenthesis, temp, size, num_of_opening_brackets-1, num_of_closing_brackets);
        }
        else{
            // if(num_of_closing_brackets > num_of_opening_brackets){
            //     cout << "Adding ( into: " << combination << std::endl;
            //     temp = combination + ")";
            //     recursivelyGenerateParenthesis(parenthesis, temp, size, num_of_opening_brackets, --num_of_closing_brackets, ++counter);
            // }
            // else{
            // }

            if(num_of_opening_brackets > 0){
                // cout << "Adding ( into: " << combination << std::endl;
                temp = combination + "(";
                recursivelyGenerateParenthesis(parenthesis, temp, size, num_of_opening_brackets-1, num_of_closing_brackets);
            }
            if(num_of_closing_brackets > 0){
                // cout << "Adding ) into: " << combination << std::endl;
                temp = combination + ")";
                recursivelyGenerateParenthesis(parenthesis, temp, size, num_of_opening_brackets, num_of_closing_brackets-1);
            }
        }
    }

    vector<string> generateParenthesis(int n) {
        vector<string> parenthesis;
        string temp("(");

        recursivelyGenerateParenthesis(parenthesis, temp, n, n-1, n);

        return parenthesis;
    }
};

int main(){
    int n = 8;
    Solution sol;

    for(string s:sol.generateParenthesis(n)){
        cout << s << std::endl;
    }

    return 0;
}
