/*
Solution 1: 栈（单调栈）
*/

#include<iostream>
#include<vector>
#include<string>
#include<unordered_set>

using namespace std;

class Solution {
public:
    string removeDuplicateLetters(string s) {
        vector<int> remainCnt(256, 0);
        for (auto c: s) {
            remainCnt[c]++;
        }
        vector<char> res;
        unordered_set<char> visited;
        for (int idx=0; idx<s.size(); ++idx) {
            remainCnt[s[idx]]--;
            if (visited.find(s[idx]) == visited.end()) {
                while (!res.empty() && res.back() > s[idx] && remainCnt[res.back()] > 0) {
                    visited.erase(res.back());
                    res.pop_back();
                }
                res.push_back(s[idx]);
                visited.insert(s[idx]);
            }
        }
        string resStr;
        for (auto c: res) {
            resStr += c;
        }
        return resStr;
    }
};

int main() {
    Solution s;
    cout << s.removeDuplicateLetters("bcabc") << endl;
    cout << s.removeDuplicateLetters("cbacdcbc") << endl;
}