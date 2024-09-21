/*
https://leetcode.com/problems/palindrome-partitioning/description/
*/
#include <iostream>
#include <vector>

using std::string;
using std::vector;
using std::cout;
using std::endl;
typedef std::vector<std::vector<string>> vectorList;


class Solution{
    public:
        vectorList all_partitions;
        void recursivelyCreatePalindromePartitions(string s, vector<string> partitions, string prevSubString = ""){
            // cout << "Recursively partitioning " << s << " prevSubString: " << prevSubString << endl;
            if(prevSubString.size() != 0){
                partitions.push_back(prevSubString);
            }
            if(s.size() <= 1){
                if(s.size() == 1){
                    partitions.push_back(s);
                }
                // printVector(partitions);
                all_partitions.push_back(partitions);
                // printResult(all_partitions);
            }
            else{
                // printVector(partitions);
                for(int numElements=1;numElements<=s.size();numElements++){
                    // cout << "Reading substring from 0 to " << numElements << endl;
                    string tempSubString = s.substr(0, numElements);
                    if(isPalindrom(tempSubString)){
                        // cout << tempSubString << " is a palindrom! Now checking further checking substring starting from " << numElements << " to " << s.size()-numElements << endl;
                        // partitions.push_back(tempSubString);
                        recursivelyCreatePalindromePartitions(s.substr(numElements, s.size()-numElements), partitions, tempSubString);
                    }
                }
            }
        }

        bool isPalindrom(string s){
            // cout << "Checking if " << s << " is a palindrom" << endl;
            int leftIndex = 0;
            int rightIndex = s.size()-1;
            while(leftIndex < rightIndex){
                if(s.at(leftIndex) != s.at(rightIndex)){
                    // cout << s.at(leftIndex) << " != " << s.at(rightIndex) << endl;
                    return false;
                }
                leftIndex++;
                rightIndex--;
            }

            return true;
        }

        vectorList partition(string s) {
            all_partitions = {};
            recursivelyCreatePalindromePartitions(s, {});
            return all_partitions;
        }

        void printResult(vectorList all_partitions){
            cout << "Result: " << endl;
            for(vector<string> partitions:all_partitions){
                for(string subString: partitions){
                    cout << subString << "-";
                }
                cout << endl;
            }
        }

        void printVector(vector<string> list){
            for(string str:list){
                cout << str << "-";
            }
            cout << endl;
        }
};

int main(){
    Solution sol = Solution();
    sol.printResult(sol.partition("bcbc"));
    sol.printResult(sol.partition("aab"));
    sol.printResult(sol.partition("a"));
    return 0;
}
