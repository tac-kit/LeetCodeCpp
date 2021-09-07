#include<iostream>
#include<string>
#include<algorithm>

using namespace std;

class Solution {
public:
    string addStrings(string num1, string num2) {
        // NOTE: 字符串可以通过reverse反转
        reverse(num1.begin(), num1.end());
        reverse(num2.begin(), num2.end());
        string resString;
        int carry=0;
        int maxLen = max(num1.size(), num2.size());
        for (int i=0; i<maxLen; ++i) {
            int digit1 = i < num1.size() ? num1[i] - '0' : 0;
            int digit2 = i < num2.size() ? num2[i] - '0' : 0;
            int res = digit1+digit2+carry;
            carry = res / 10;
            res %= 10;
            // NOTE: 数字转字符串有两种方法，一是加上'0'，二是使用to_string
            // 此处只处理单个字符，所以法一速度更快
            resString += res + '0';
        }
        // 最后可能进位
        if (carry == 1) {
            resString += '1';
        }
        reverse(resString.begin(), resString.end());
        return resString;
    }
};

int main() {
    Solution s;
    cout << s.addStrings("11", "123") << endl;
    cout << s.addStrings("0", "0") << endl;
    cout << s.addStrings("0", "123") << endl;
    cout << s.addStrings("10", "20") << endl;
    cout << s.addStrings("1", "999") << endl;
}