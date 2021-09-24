/*
Solution 1: DP
*/

#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

using namespace std;

class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        vector<vector<int>> dp(text2.length()+1, vector<int>(text1.length()+1, 0));
        for (int idx2=0; idx2<text2.length(); ++idx2) {
            for (int idx1=0; idx1<text1.length(); ++idx1) {
                if (text1[idx1] == text2[idx2]) {
                    dp[idx2+1][idx1+1] = dp[idx2][idx1] + 1;
                }else {
                    dp[idx2+1][idx1+1] = max({dp[idx2][idx1+1], dp[idx2][idx1], dp[idx2+1][idx1]});
                }
            }
        }
        return dp[text2.length()][text1.length()];
    }
};

int main() {
    Solution s;
    cout << s.longestCommonSubsequence("abcde", "ace") << endl;
    cout << s.longestCommonSubsequence("abc", "abc") << endl;
    cout << s.longestCommonSubsequence("abc", "def") << endl;
}