/* 
https://leetcode.com/problems/trapping-rain-water/description/
This is a Hard problem on Leetcode.
*/

#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::endl;

class Solution {
public:
    void log(vector<int> height, int left, int right, int max_left, int max_right, int water_trapped){
        for(int h: height){
            cout << h << ",";
        }
        cout << endl;
        cout << "Left: " << left << ", Right: " << right << ", Max Left: " << max_left << ", Max Right: " << max_right << ", Water Traped: " << water_trapped << endl;
    }

    int trap(vector<int> height, bool log_it = false) {
        int left = 0;
        int right = height.size()-1;
        int water_trapped = 0;
        int max_left = height[left];
        int max_right = height[right];
        int temp = 0;
        while(max_left == 0 && left < right){
            left++;
            max_left = height[left];
        }
        // log(height, left, right, max_left, max_right, water_trapped);
        while(max_right == 0 && right > left){
            right--;
            max_right = height[right];
        }
        if(log_it){log(height, left, right, max_left, max_right, water_trapped);};

        while(left < right-1){ 
            if(log_it){cout << "Iteration" << endl;};

            // while(true){
            if(max_left <= max_right){
                if(height[left+1] <= max_left){
                    temp = std::min(max_left, max_right) - height[left+1];
                    if(temp>0){water_trapped += temp;};
                    left++;
                }
                else{
                    max_left = height[++left];
                }
                if(log_it){log(height, left, right, max_left, max_right, water_trapped);};
                // }

                while(left < right and max_left < height[left+1]){
                    max_left = height[++left];
                }

            }

                // if(left >= right-1){
                //     break;
                // }
            else{
                // while(true){
                if(height[right-1] <= max_right){
                    temp = std::min(max_left, max_right) - height[right-1];
                    if(temp>0){water_trapped += temp;};
                    right--;
                }
                else{
                    max_right = height[--right];
                }
                if(log_it){log(height, left, right, max_left, max_right, water_trapped);};
                // }

                // log(height, left, right, max_left, max_right, water_trapped);
                while(left < right && max_right < height[right-1]){
                    max_right = height[--right];
                }

                // if(left >= right-1){
                //     break;
                // }
            }
        }

        return water_trapped;
    }
};

int main(){
    Solution sol = Solution();

    vector<int> height = {0,1,0,2,1,0,1,3,2,1,2,1};
    int water_trapped = sol.trap(height, false);
    cout << water_trapped << endl;
    // Expected: 6

    height = {4,2,0,3,2,5};
    water_trapped = sol.trap(height, false);
    cout << water_trapped << endl;
    // Expected: 9

    height = {5,4,1,2};
    water_trapped = sol.trap(height, false);
    cout << water_trapped << endl;
    // Expected: 1

    height = {5,5,1,7,1,1,5,2,7,6};
    water_trapped = sol.trap(height, false);
    cout << water_trapped << endl;
    // Expected: 23

    height = {6,4,2,0,3,2,0,3,1,4,5,3,2,7,5,3,0,1,2,1,3,4,6,8,1,3};
    water_trapped = sol.trap(height, false);
    cout << water_trapped << endl;
    // Expected: 83

    return 0;
}
