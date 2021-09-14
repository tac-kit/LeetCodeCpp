/*
Solution 1: 类似std::vector的扩容机制。注意int可能溢出。
Solution 2: (TODO)二分查找。
*/

#include<iostream>

using namespace std;

class Solution {
public:
    int mySqrt(int x) {
        long long int longX = x;
        long long int ret = 0;
        while (ret * ret <= longX) {
            long long int addRet = 1;
            while ((ret + addRet) * (ret + addRet) <= longX)
                addRet *= 2;
            ret = ret + addRet / 2 + 1;
        }
        return ret - 1;
    }
};

int main() {
    Solution s;
    cout << s.mySqrt(0) << endl;
    cout << s.mySqrt(2147483647) << endl;
}