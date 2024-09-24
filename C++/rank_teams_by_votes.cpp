/*
https://leetcode.com/problems/rank-teams-by-votes/description/
*/
#include<iostream>
#include<vector>
#include<algorithm>
#include<map>
#include<stdexcept>
#include<set>
#include<unordered_map>

using std::cout;
using std::string;
using std::endl;
using std::vector;

// typedef std::unordered_map<string, std::unordered_map<string, int>> MapStringToMap;

class Solution {
public:
    vector<std::pair<char, int>> sortMap(std::map<char,int>& mapToSort){
        vector<std::pair<char, int>> tempVec(mapToSort.begin(), mapToSort.end());
        std::sort(tempVec.begin(), tempVec.end(), [](const std::pair<char, int>& a, const std::pair<char, int>& b) {
            // cout << "Sorting " << a.first << " = " << a.second << " by comparing with " << b.first << "=" << b.second << endl;
            if(a.second == b.second){
                return int(a.first) <= int(b.first);
            }
            else{
                return a.second > b.second;
            }
        });
        return tempVec;
    }

    int customCondition(const std::map<int, int>& a , const std::map<int, int>& b, const int& totalCandidates){
        for(int i=0;i<totalCandidates;i++){
            if((a.find(i+1) == a.end()) && (b.find(i+1) == b.end())){
                continue;
            }
            else if((a.find(i+1) == a.end()) && (b.find(i+1) != b.end())){
                return 0;
            }
            else if((a.find(i+1) != a.end()) && (b.find(i+1) == b.end())){
                return 1;
            }
            else{
                if(a.at(i+1) == b.at(i+1)){
                    continue;
                }
                else{
                    if(a.at(i+1) > b.at(i+1)){
                        return 1;
                    }
                    else{
                        return 0;
                    }
                }
            }
        }
        return -1;
    };

    void printResult(std::map<char, std::map<int, int>>& results){
        cout << "----------------------------------------" << endl;
        for(const auto& outerpair: results){
            cout << outerpair.first << endl;
            for(const auto& innerpair: outerpair.second){
                cout << innerpair.second << " voted as preference position " << innerpair.first << endl;
            }
        }
    }

    void printResultVectorPair(vector<std::pair<char, std::map<int, int>>>& pairVector){
        cout << "---------------------------------------" << endl;
        for(const auto& pair: pairVector){
            cout << pair.first << endl;
            for(const auto& innerPair: pair.second){
                cout << innerPair.second << " voted as preference position " << innerPair.first << endl;
            }
        }
    }

    string customSort(std::map<char, std::map<int, int>>& results, const int& totalCandidates){

        printResult(results);
        vector<std::pair<char, std::map<int, int>>> tempVec(results.begin(), results.end());

        std::sort(tempVec.begin(), tempVec.end(), [this, totalCandidates](
            const std::pair<char, std::map<int, int>>& a, const std::pair<char, std::map<int, int>>& b 
        ){
            int positionComparison = this->customCondition(a.second, b.second, totalCandidates);
            if(positionComparison == -1){
                return int(a.first) < int(b.first);
            }
            else if(positionComparison == 1){
                return true;
            }
            else{
                return false;
            }
        });
        printResultVectorPair(tempVec);        

        string winners = "";
        for(const std::pair<char, std::map<int, int>> p:tempVec){
            winners += p.first;
        }

        return winners;
    }
 
    string rankTeams(vector<string>& votes) {
        /* --- Approach 1- Doesn't work in all cases ---
        try{
            if(votes.size() == 0){
                return "";
            }

            string winners = "";
            std::map<char, int> results;
            for(size_t i=0;i<votes.size();i++){
                cout << votes[i] << endl;
                for(size_t j=0;j<votes[i].length();j++){
                    char candidate = votes[i].at(j);
                    try{
                        if(results.find(candidate) == results.end()){
                            results[candidate] = 0;
                        }
                        results[candidate] += j+1;
                        // if(candidate == 'R'){
                        //     cout << "For V: Added " << j+1 << endl;
                        // }
                    }
                    catch(const std::runtime_error& e){
                        std::cerr << "Caught an exeption: " << e.what() << endl;
                        continue;
                    }
                }
            }

            cout << "Results Dict:- " << endl;
            for(auto it=results.begin(); it!=results.end();++it){
                std::pair<const char, int>* ptr = &(*it);
                cout << "Key: " << ptr->first << ", Value: " << ptr->second << endl;
            }

            vector<std::pair<char, int>> tempVec = sortMap(results);
            for(const auto& pair: tempVec){
                winners += pair.first;
            }

            return winners;
        }
        catch(const std::runtime_error& e){
            std::cerr << "Caught an exception: " << e.what() << endl;
            return "";
        }
        */

       /* ---- Approach 2- Works in all cases, but very slow and inefficient ----
       if(votes.size() == 0){
            return "";
       }

       string winners = "";
       std::map<char, std::map<int, int>> results;
       int totalCandidates = votes[0].length();
       std::set<char> tiedCandidates;

        // Parses over all the voters one preference at a time
       for(size_t i = 0;i < totalCandidates; i++){

            // Parses over all the votes for a given preference
            for(size_t j=0; j < votes.size(); j++){
                char candidate = votes[j].at(i);

                // Check if a necessary keys exists in the result, create them if they do not exist and increament the value
                if(results.find(candidate) == results.end()){
                    results[candidate] = {};
                }
                if(results[candidate].find(i+1) == results[candidate].end()){
                    results[candidate][i+1] = 0;
                }
                results[candidate][i+1]++;
            }
       }

        // Now, sort the results using a custom function
        return customSort(results, totalCandidates);
        */

       /* ---- Approach 3 - Found from Solutions, works for all cases and more efficiant then approach 2 */
        std::unordered_map<char, vector<int>> count;

        // Initialize the count for each team
        for (const string& vote : votes) {
            for (int i = 0; i < vote.size(); ++i) {
                count[vote[i]].resize(vote.size(), 0);
                count[vote[i]][i]++; // Increment the count for the position
            }
        }

        // Create a vector of teams
        vector<char> teams;
        for (const auto& pair : count) {
            teams.push_back(pair.first);
        }

        // Sort teams based on the voting criteria
        sort(teams.begin(), teams.end(), [&count](char a, char b) {
            return count[a] > count[b] || (count[a] == count[b] && a < b);
        });

        // Construct the result string
        string result;
        for (char team : teams) {
            result += team;
        }

        return result;
    }
};

int main(){
    Solution sol = Solution();
    vector<string> input;

    input = {
        "ABC","ACB","ABC","ACB","ACB"
    };
    cout << sol.rankTeams(input) << endl; // Expected: ACB

    input = {
        "WXYZ","XYZW"
    };
    cout << sol.rankTeams(input) << endl; // Expected: XWYZ

    input = {
        "ZMNAGUEDSJYLBOPHRQICWFXTVK"
    };
    cout << sol.rankTeams(input) << endl; // Expected: ZMNAGUEDSJYLBOPHRQICWFXTVK

    input = {
        "FVSHJIEMNGYPTQOURLWCZKAX","AITFQORCEHPVJMXGKSLNZWUY","OTERVXFZUMHNIYSCQAWGPKJL","VMSERIJYLZNWCPQTOKFUHAXG","VNHOZWKQCEFYPSGLAMXJIUTR","ANPHQIJMXCWOSKTYGULFVERZ","RFYUXJEWCKQOMGATHZVILNSP","SCPYUMQJTVEXKRNLIOWGHAFZ","VIKTSJCEYQGLOMPZWAHFXURN","SVJICLXKHQZTFWNPYRGMEUAO","JRCTHYKIGSXPOZLUQAVNEWFM","NGMSWJITREHFZVQCUKXYAPOL","WUXJOQKGNSYLHEZAFIPMRCVT","PKYQIOLXFCRGHZNAMJVUTWES","FERSGNMJVZXWAYLIKCPUQHTO","HPLRIUQMTSGYJVAXWNOCZEKF","JUVWPTEGCOFYSKXNRMHQALIZ","MWPIAZCNSLEYRTHFKQXUOVGJ","EZXLUNFVCMORSIWKTYHJAQPG","HRQNLTKJFIEGMCSXAZPYOVUW","LOHXVYGWRIJMCPSQENUAKTZF","XKUTWPRGHOAQFLVYMJSNEIZC","WTCRQMVKPHOSLGAXZUEFYNJI"
    };
    cout << sol.rankTeams(input) << endl; // Expected: VWFHSJARNPEMOXLTUKICZGYQ

    return 0;
}
