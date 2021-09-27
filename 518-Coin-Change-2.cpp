/*
Solution 1: DP，每一步两种选择：使用当前硬币，不使用当前硬币。例如对于change(5, [1,2,5])，
使用当前硬币（硬币1）是change(5-1, [1,2,5])，不使用当前硬币是change(5, [2,5])
*/

#include<iostream>
#include<vector>

using namespace std;

class Solution {
public:
    int change(int amount, const vector<int>& coins) {
        vector<int> dp(amount+1, 0);
        dp[0] = 1;
        for (auto coin: coins) {
            vector<int> newDp(amount+1, 0);
            for (int idx=0; idx<=amount; ++idx) {
                // 不使用当前硬币 + 使用当前硬币
                newDp[idx] = dp[idx] + (idx >= coin ? newDp[idx-coin] : 0);
            }
            dp = newDp;
        }
        return dp[amount];
    }
};

int main() {
    Solution s;
    cout << s.change(5, vector<int>{1,2,5}) << endl;
}