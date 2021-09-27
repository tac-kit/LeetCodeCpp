/*
Solution 1: DP
*/

#include<iostream>
#include<vector>

using namespace std;

class Solution {
public:
    int coinChange(const vector<int>& coins, int amount) {
        vector<int> dp(amount+1, 0);
        for (int idx=1; idx<=amount; ++idx) {
            int minCnt = INT_MAX;
            for (auto coin: coins) {
                if (coin <= idx && dp[idx-coin] < minCnt)
                    minCnt = dp[idx-coin] + 1;
            }
            dp[idx] = minCnt;
        }
        return dp[amount] == INT_MAX ? -1 : dp[amount];
    }
};

int main() {
    Solution s;
    cout << s.coinChange(vector<int>{1,2,5}, 11) << endl;
}