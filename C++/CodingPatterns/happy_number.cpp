#include <iostream>
#include <map>
#include <cmath>

using namespace std;

int getDigitSquareSum(int n){
    int squareSum = 0, digit;

    while(n>0){
        digit = n % 10;
        squareSum += pow(digit, 2);
        n /= 10;
    }

    return squareSum;
}

bool isHappy(int n) {
    map<int, bool> recordedSums = {};

    int slow=n, fast=n;
    while(fast != 1){
        slow = getDigitSquareSum(slow);
        fast = getDigitSquareSum(getDigitSquareSum(fast));

        if(slow == fast && slow != 1){
            return false;
        }
    }

    return true;
}

int main(){
    int n;
    cin >> n;

    cout << isHappy(n) << endl;

    return 0;
}
