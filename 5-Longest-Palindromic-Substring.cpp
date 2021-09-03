/*
Solution 1: 动态规划，空间复杂度高。
Solution 1.1: 中心扩展，将BFS改为DFS，减少内存占用，减少内存申请释放开销。
*/

#include<iostream>
#include<string>
#include<vector>
#include<cassert>

using namespace std;

class Solution {
public:
    // Solution 1
    // string longestPalindrome(string s) {
    //     vector<pair<int, int>> dp;
    //     pair<int, int> res{0,0};
    //     int res_len = 1;
    //     // 长度为1
    //     for (int i=0; i<s.size(); ++i){
    //         dp.emplace_back(i, i);
    //     }
    //     // 长度为2
    //     for (int i=1; i<s.size(); ++i){
    //         if (s[i] == s[i-1]){
    //             dp.emplace_back(i-1, i);
    //             res.first = i-1;
    //             res.second = i;
    //             res_len = 2;
    //         }
    //     }

    //     // 扩展
    //     while (!dp.empty()){
    //         vector<pair<int, int>> new_dp;
    //         for (auto p: dp){
    //             pair<int, int> new_p{p.first-1, p.second+1};
    //             if (new_p.first>=0 && new_p.second<s.size() && s[new_p.first] == s[new_p.second]){
    //                 new_dp.push_back(new_p);
    //                 if (new_p.second-new_p.first+1 > res_len){
    //                     res = new_p;
    //                     res_len = new_p.second-new_p.first+1;
    //                 }
    //             }
    //         }
    //         // NOTE: 调用拷贝运算符
    //         dp = new_dp;
    //         // dp.clear();
    //         // NOTE: 需要加上back_inserter
    //         // copy(new_dp.begin(), new_dp.end(), back_inserter(dp));
    //     }
    //     return string(s.begin()+res.first, s.begin()+res.second+1);
    // }

    // Solution 1.1
    string longestPalindrome(string s){
        int res_left=0, res_right=0;
        for (int center=0; center<s.size(); ++center){
            // 长度为1
            int left=center, right=center;
            while (left>=0 && right<s.size() && s[left]==s[right]){
                left--;
                right++;
            }
            if (right-left-1 > res_right-res_left+1){
                res_left = left+1;
                res_right = right-1;
            }
            // 长度为2
            left=center;
            right=center+1;
            while (left>=0 && right<s.size() && s[left]==s[right]){
                left--;
                right++;
            }
            if (s[left+1]==s[right-1] && right-left-1 > res_right-res_left+1){
                res_left = left+1;
                res_right = right-1;
            }
        }
        return string(s.begin()+res_left, s.begin()+res_right+1);
    }
};

int main(){
    Solution s;
    string res = s.longestPalindrome("babad");
    string ans = "bab";
    assert(res == ans);
    res = s.longestPalindrome("aaaaa");
}