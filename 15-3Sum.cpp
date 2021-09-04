/*
Solution 1: 三指针。
*/

#include<iostream>
#include<vector>
#include<algorithm>
#include<cassert>

using namespace std;

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> resList;
        if (nums.size() < 3)
            return resList;
        sort(nums.begin(), nums.end());
        for (int idx1=0; idx1<nums.size()-2; ++idx1) {
            if (nums[idx1] > 0)
                break;
            // 跳过重复数字
            if (idx1>0 && nums[idx1] == nums[idx1-1])
                continue;
            int idx2=idx1+1, idx3=nums.size()-1;
            while (idx2<idx3) {
                int tempSum = nums[idx1] + nums[idx2] + nums[idx3];
                if (tempSum > 0) {
                    idx3--;
                    while (idx2<idx3 && nums[idx3]==nums[idx3+1]) idx3--;
                }else if (tempSum < 0) {
                    idx2++;
                    while (idx2<idx3 && nums[idx2]==nums[idx2-1]) idx2++;
                }else {
                    resList.push_back(vector<int>{nums[idx1], nums[idx2], nums[idx3]});
                    idx2++;
                    while (idx2<idx3 && nums[idx2]==nums[idx2-1]) idx2++;
                    idx3--;
                    while (idx2<idx3 && nums[idx3]==nums[idx3+1]) idx3--;
                }
            }
        }
        return resList;
    }
};

void printMatrix(vector<vector<int>> matrix) {
    for (const vector<int>& line: matrix) {
        for (const int& num: line) {
            cout << num << " ";
        }
        cout << endl;
    }
}

int main() {
    Solution s;
    vector<int> myVec{-1,0,1,2,-1,-4};
    vector<vector<int>> resMatrix = s.threeSum(myVec);
    printMatrix(resMatrix);
}