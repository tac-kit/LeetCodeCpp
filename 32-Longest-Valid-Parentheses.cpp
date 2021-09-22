/*
Solution 1: 栈，答案Approach 3
Solution 2: DP，答案Approach 2
Solution 3: (TODO)空间复杂度O(1)，答案Approach 4
*/

#include<iostream>
#include<vector>
#include<stack>

using namespace std;

// Solution 1
/*
class Solution {
public:
    int longestValidParentheses(string s) {
        // 使用栈存储独立的配对括号长度，例如"()(()"就是存储2、2
        stack<int> leftStack;
        // 预置的0用于区分完整的配对括号"()"与多余的右括号"())"
        // 例如"()()"，第2对括号合龙后要合并第1对括号；
        // 而"())()"，第2对括号合龙后不能合并第1对括号。
        // 预置0之后，"()"在栈中存放一个数值2；而"())"中的第2个右括号会将2弹出，重新插入0
        leftStack.push(0);
        int resLen=0, currLen=0;
        for (char c: s) {
            if (c == '(')
                leftStack.push(0);
            else {
                currLen = leftStack.top();
                leftStack.pop();
                if (leftStack.empty()) {
                    // 栈为空，说明当前的右括号多余，将现有栈中元素弹出，重新插入0
                    leftStack.push(0);
                }else{
                    // 加2表示当前左括号配对；
                    // 将结果加在leftStack.top()上保存，表示合并两组配对括号，
                    // 例如"(())()"需要将4与2合并
                    currLen += 2 + leftStack.top();
                    if (currLen > resLen)
                        resLen = currLen;
                    leftStack.pop();
                    leftStack.push(currLen);
                }
            }
        }
        return resLen;
    }
};
*/

// Solution 2
class Solution {
public:
    int longestValidParentheses(string s) {
        vector<int> dp(s.size(), 0);
        int resLen=0;
        for (int idx=1; idx<s.size(); ++idx) {
            if (s[idx] == ')') {
                // 根据s[idx-1]讨论
                if (s[idx-1] == '(') {
                    // 如果是"()"，直接加上dp[idx-2]
                    dp[idx] = (idx>1 ? dp[idx-2] : 0) + 2;
                }else{
                    // 如果是"))"，需要检查对称位置是否为"("
                    if (idx-1-dp[idx-1] >= 0 && s[idx-1-dp[idx-1]] == '(') {
                        dp[idx] = (idx-2-dp[idx-1] >= 0 ? dp[idx-2-dp[idx-1]] : 0) + dp[idx-1] + 2;
                    }
                }
                if (dp[idx] > resLen)
                    resLen = dp[idx];
            }
        }
        return resLen;
    }
};

int main() {
    Solution s;
    cout << s.longestValidParentheses("(()") << endl;
    cout << s.longestValidParentheses(")()())") << endl;
    cout << s.longestValidParentheses("") << endl;
}