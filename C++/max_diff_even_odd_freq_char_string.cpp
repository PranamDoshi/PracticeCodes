/*
https://leetcode.com/problems/maximum-difference-between-even-and-odd-frequency-i/description/?envType=daily-question&envId=2025-06-12
*/
#include<iostream>
#include<map>
#include<vector>
#include<tuple>
#include<algorithm>
#include<climits>

using std::cout;
using std::endl;
using std::string;
using std::map;
using std::vector;
using std::tuple;

map<char, int> increameMapValue(map<char, int> mapping, char ch){
    if(mapping.find(ch) != mapping.end()){
        mapping[ch]++;
    }
    else{
        mapping[ch] = 1;
    }
    return mapping;
}

vector<int> getDifferences(vector<tuple<int, int>> pairs){
    vector<int> diffs(pairs.size());
    for(int i=0;i<pairs.size();i++){
        diffs[i] = std::get<0>(pairs[i]) - std::get<1>(pairs[i]);
    }
    return diffs;
}

vector<tuple<int, int>> crossProduct(vector<int> v1, vector<int> v2){
    vector<tuple<int, int>> cross_product;

    for(int i=0;i<v1.size();i++){
        for(int j=0;j<v2.size();j++){
            cross_product.push_back(std::make_tuple(v1[i], v2[j]));
        }
    }

    return cross_product;
}

int maxDifference(string s) {
    map<char, int> charCount;
    vector<int> oddFreqs, evenFreqs;
    for(int i=0;i<s.length();i++){
        charCount = increameMapValue(charCount, s[i]);
    }

    for(auto map:charCount){
        if(map.second % 2 == 0){
            evenFreqs.push_back(map.second);
        }
        else{
            oddFreqs.push_back(map.second);
        }
    }

    vector<int> diffs = getDifferences(crossProduct(oddFreqs, evenFreqs));
    return *std::max_element(diffs.begin(), diffs.end());   
}

int maxDifference_optimized(string s) {
    map<char, int> charCount;
    vector<int> oddFreqs, evenFreqs;
    for(int i=0;i<s.length();i++){
        charCount = increameMapValue(charCount, s[i]);
    }

    for(auto map:charCount){
        if(map.second % 2 == 0){
            evenFreqs.push_back(map.second);
        }
        else{
            oddFreqs.push_back(map.second);
        }
    }

    int maxDiff = INT_MIN;
    int temp;
    for(auto oddFreq: oddFreqs){
        for(auto evenFreq: evenFreqs){
            temp = oddFreq - evenFreq;
            if(temp > maxDiff){
                maxDiff = temp;
            }
        }
    }

    return maxDiff;
}

int main(){
    string str = "aaaaabbc";
    cout << str << endl;
    cout << maxDifference(str) << endl;

    str = "mmsmsym";
    cout << str << endl;
    cout << maxDifference(str) << endl;

    return 0;
}
