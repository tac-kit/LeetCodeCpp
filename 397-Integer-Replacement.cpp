/*
Solution 1: 可能的元素数太多，所以不适合使用自底向上的动态规划，可以自顶向下，使用缓存实现。
*/

#include<iostream>
#include<unordered_map>
#include<cassert>

using namespace std;

class Solution {
public:
    int integerReplacement(int n) {
        // 这道题的难点是支持x^31-1。
        // 为了支持n == x^31 - 1，需要转换为long long int
        // Q: 为什么写在integerReplacement里面会导致stack overflow？
        // 因为虽然在内部转换成了long long int，但递归调用的integerReplacement的形参依然是int
        // 导致实际传入的变成负数，造成无限递归，栈溢出。
        // 解决方案是写一个单独的、形参为long long int的helper函数
        // long long int longN = (long long int)n;
        // auto findIter = cache.find(longN);
        // if (findIter == cache.end()) {
        //     int res;
        //     if (longN % 2 == 1) res = min(integerReplacement(longN-1), integerReplacement(longN+1)) + 1;
        //     else res = integerReplacement(longN / 2) + 1;
        //     cache.emplace(longN, res);
        //     return res;
        // }else{
        //     return findIter->second;
        // }

        return helper((long long int)n);
    }

private:
    int helper(long long int n) {
        long long int longN = n;
        auto findIter = cache.find(longN);
        if (findIter == cache.end()) {
            int res;
            if (longN % 2 == 1) res = min(helper(longN-1), helper(longN+1)) + 1;
            else res = helper(longN / 2) + 1;
            cache.emplace(longN, res);
            return res;
        }else{
            return findIter->second;
        }
    }

    unordered_map<long long int, int> cache{{(long long int)1,0}};  // base case
};

int main() {
    Solution s;
    assert(s.integerReplacement(8) == 3);
    assert(s.integerReplacement(7) == 4);
    assert(s.integerReplacement(15) == 5);
    assert(s.integerReplacement(2147483646) == 32);
    assert(s.integerReplacement(2147483647) == 32);
}