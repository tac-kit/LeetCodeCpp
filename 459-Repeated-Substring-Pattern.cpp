/*
Solution 1: KMP
*/

#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

using namespace std;

class Solution {
public:
    bool repeatedSubstringPattern(string s) {
        vector<int> table(s.size(), 0);
        // 对于测试用例"abaababaab"，下面这个方法构造出来的table是0,0,1,1,2,3,1,2,3,4
        // 正确答案是0,0,1,1,2,3,2,3,4,5
        // int j=0;
        // for (int i=1; i<s.size(); ++i) {
        //     if (s[i] == s[j]) {
        //         table[i] = table[i-1]+1;
        //         j++;
        //     }else{
        //         while (j > 0 && s[i] != s[j]) {
        //             j = table[j-1];
        //         }
        //         if (s[i] == s[j]) {
        //             table[i] = table[j] + 1;
        //             j++;
        //         }
        //     }
        // }

        // https://www.geeksforgeeks.org/kmp-algorithm-for-pattern-searching/
        for (int i=1, j=0; i<s.size();) {
            if (s[i] == s[j]) {
                table[i++] = ++j;
            }else{
                j ? j = table[j-1] : i++;
            }
        }

        for_each(table.begin(), table.end(), [](int num){cout << num << " ";});
        cout << endl;
        int repeat = table.size() - table[table.size()-1];
        // 比如测试用例"ab"，table[table.size()-1]=0, repeat=2，所以检查table[table.size()-1]是否为0
        // return bool(table.size() % repeat == 0 && (repeat <= (table.size() / 2)));
        return bool(table[table.size()-1] != 0 && table.size() % repeat == 0);
    }
};

int main() {
    Solution s;
    cout << s.repeatedSubstringPattern("abab") << endl;
    cout << s.repeatedSubstringPattern("aba") << endl;
    cout << s.repeatedSubstringPattern("abcabcabcabc") << endl;
    cout << s.repeatedSubstringPattern("abcabcacabc") << endl;
    cout << s.repeatedSubstringPattern("abcabcabcab") << endl;
    cout << s.repeatedSubstringPattern("bcabcabcabc") << endl;
    cout << s.repeatedSubstringPattern("abacabacaba") << endl;
    cout << s.repeatedSubstringPattern("a") << endl;
    cout << s.repeatedSubstringPattern("ab") << endl;
    cout << s.repeatedSubstringPattern("abcdeabcde") << endl;
    cout << s.repeatedSubstringPattern("abaababaab") << endl;
}