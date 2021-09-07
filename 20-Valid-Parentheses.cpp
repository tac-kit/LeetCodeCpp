/*
Solution 1: 计数，左括号加1右括号减1. Wrong Answer: ([)]
Solution 2: 栈
*/

#include<iostream>
#include<string>
#include<cassert>
#include<stack>
#include<map>

using namespace std;

class Solution {
public:
    // Solution 1
    // bool isValid(string s) {
    //     int cnt1=0, cnt2=0, cnt3=0;
    //     for (char c: s) {
    //         switch(c) {
    //             case '(':cnt1++;break;
    //             case ')':cnt1--;break;
    //             case '[':cnt2++;break;
    //             case ']':cnt2--;break;
    //             case '{':cnt3++;break;
    //             case '}':cnt3--;break;
    //         }
    //         if (cnt1<0 || cnt2<0 || cnt3<0) {
    //             return false;
    //         }
    //     }
    //     return bool(cnt1==0 && cnt2==0 && cnt3==0);
    // }

    // Solution 2
    bool isValid(string s) {
        stack<char> charStack;
        map<char, char> pairMap{{')', '('}, {']', '['}, {'}', '{'}};
        for (char c: s) {
            switch(c) {
                case '(':
                case '[':
                case '{':charStack.push(c);break;
                default :{
                    if (!charStack.empty() && pairMap[c] == charStack.top())
                        charStack.pop();
                    else
                        return false;
                }
            }
        }
        return charStack.empty();
    }
};

int main() {
    Solution s;
    bool res = s.isValid("()");
    cout << res << endl;
}