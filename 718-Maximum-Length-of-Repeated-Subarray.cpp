/*
Solution 1: DP+状态压缩，dp[i][j]表示以nums1[i]和nums2[j]结尾的重复子串长度
*/

#include<iostream>
#include<vector>

using namespace std;

class Solution {
public:
    int findLength(const vector<int>& nums1, const vector<int>& nums2) {
        vector<int> dp(nums1.size()+1, 0);
        int maxLen = 0;
        for (auto num2: nums2) {
            vector<int> newDp(nums1.size()+1, 0);
            for (int idx=0; idx<nums1.size(); ++idx) {
                if (num2 == nums1[idx]) {
                    newDp[idx+1] = dp[idx] + 1;
                    if (newDp[idx+1] > maxLen)
                        maxLen = newDp[idx+1];
                }
            }
            dp = newDp;
        }
        return maxLen;
    }
};

int main() {
    Solution s;
    cout << s.findLength(vector<int>{1,2,3,2,1}, vector<int>{3,2,1,4,7}) << endl;
    cout << s.findLength(vector<int>{0,0,0,0,0}, vector<int>{0,0,0,0,0}) << endl;
}