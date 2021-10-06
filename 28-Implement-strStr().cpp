/*
Solution 1: KMP, https://www.youtube.com/watch?v=GTJr8OvyEVQ
Solution 1.1: Solution 1存在bug，当needle为"abaababaab"时建的table不对
（不影响strStr结果正确性，因为table只起到加速作用，但会影响速度，并且在LC459中影响结果正确性）。
这个实现参考了https://www.geeksforgeeks.org/kmp-algorithm-for-pattern-searching/
以及https://leetcode.com/problems/implement-strstr/discuss/12956/C%2B%2B-Brute-Force-and-KMP，
但比它们都简单。TODO: 逐行解释为什么能work。
*/

#include<iostream>
#include<vector>
#include<string>

using namespace std;

class Solution {
public:
    int strStr(string haystack, string needle) {
        if (needle.empty()) return 0;
        vector<int> table(needle.size(), 0);
        int j=0;
        for (int i=1; i<table.size(); ++i) {
            if (needle[i] == needle[j]) {
                table[i] = table[i-1] + 1;  // 注意这里是自增，与else部分不同
                j++;
            }else{
                // 这一步可以理解为：在needle前半部分内匹配后半部分字符，也就是在needle内部的strstr
                while (j > 0 && needle[i] != needle[j]) {
                    j = table[j-1];
                }
                if (needle[i] == needle[j]) {
                    table[i] = table[j] + 1;  // 这里是table[j]+1，不是自增
                    j++;
                }
            }
        }
        
        j=0;
        int i=0;
        for (; i<haystack.size() && j < needle.size(); ++i) {
            // 注意到实际的搜索过程与之前构造table的过程非常相似
            if (haystack[i] == needle[j]) {
                j++;
            }else{
                while (j > 0 && haystack[i] != needle[j]) {
                    j = table[j-1];
                }
                if (haystack[i] == needle[j]) {
                    j++;
                }
            }
        }
        if (j == needle.size()) {
            return i-j;
        }else{
            return -1;
        }
    }
};

class Solution11 {
public:
    int strStr(string haystack, string needle) {
        if (needle.size()==0) return 0;
        int m=haystack.size(), n=needle.size();
        vector<int> table(n, 0);
        int i=1, j=0;
        while (i < n) {
            if (needle[i] == needle[j]) table[i++] = ++j;
            else j == 0 ? i++ : j = table[j-1];
        }
        i=0; j=0;
        while (i < m) {
            if (haystack[i] == needle[j]) {
                i++; j++;
                if (j == n) return i-j;
            }else{
                j == 0 ? i++ : j = table[j-1];
            }
        }
        return -1;
    }
};

int main() {
    Solution s;
    cout << s.strStr("hello", "ll") << endl;
    cout << s.strStr("aaaaa", "bba") << endl;
    cout << s.strStr("", "") << endl;
    cout << s.strStr("abaababaab", "abaababaab") << endl;

    Solution11 s11;
    cout << s11.strStr("abaababaab", "abaababaab") << endl;
}