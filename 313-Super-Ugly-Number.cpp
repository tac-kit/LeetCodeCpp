/*
Solution 1: n指针跟踪当前指向下标，注意去重。Time Limit Exceeded
Solution 1.1: 减少循环次数，缓存乘法结果。Runtime Error: signed integer overflow
Solution 1.2: 虽然结果不会溢出，但因为在push_back之后、检查res.size() < n之前做了乘法，
所以临时结果可能溢出。解决方法是将乘法放在循环前面，这是否会导致代码语义不清晰？
*/

#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

class Solution {
public:
// Solution 1
/*
    int nthSuperUglyNumber(int n, const vector<int>& primes) {
        vector<int> res{1};  // 1 <= n
        vector<int> idx(primes.size(), 0);
        while (res.size() < n) {
            int minVal=INT_MAX, minIdx=0;
            for (int i=0; i<primes.size(); ++i) {
                int nextVal = primes[i] * res[idx[i]];
                if (nextVal < minVal) {
                    minVal = nextVal;
                    minIdx = i;
                }
            }
            // 这样虽然可以实现去重，但上面的for循环执行次数较多。
            // 不如在for循环中记住所有等于最小值的下标，全部自增。
            // 去重
            if (res.back() != minVal)
                res.push_back(minVal);
            idx[minIdx]++;
        }
        return res.back();
    }
*/
// Solution 1.1
/*
    int nthSuperUglyNumber(int n, const vector<int>& primes) {
        vector<int> res{1};  // 1 <= n
        vector<int> idx(primes.size(), 0);
        vector<int> valVec(primes);
        while (res.size() < n) {
            // 可以不使用临时向量记住最小值下标
            int minVal = *min_element(valVec.cbegin(), valVec.cend());
            res.push_back(minVal);
            // 比较是否与最小值相等，相等则自增下标
            for (int i=0; i<primes.size(); ++i) {
                if (valVec[i] == minVal) {
                    idx[i]++;
                    valVec[i] = res[idx[i]] * primes[i]; 
                }
            }
        }
        return res.back();
    }
    */
// Solution 1.2
    int nthSuperUglyNumber(int n, const vector<int>& primes) {
        vector<int> res{1};  // 1 <= n
        vector<int> idx(primes.size(), 0);
        vector<int> valVec(primes);
        int minVal = INT_MAX;
        while (res.size() < n) {
            // 比较是否与最小值相等，相等则自增下标
            for (int i=0; i<primes.size(); ++i) {
                // 2 <= primes[i] <= 1000
                if (valVec[i] == minVal) {
                    idx[i]++;
                    valVec[i] = res[idx[i]] * primes[i]; 
                }
            }
            // 可以不使用临时向量记住最小值下标
            minVal = *min_element(valVec.cbegin(), valVec.cend());
            res.push_back(minVal);
            // 将push_back放在最后，直接检查res.size() < n
        }
        return res.back();
    }
};


int main() {
    Solution s;
    cout << s.nthSuperUglyNumber(12, vector<int>{2,7,13,19}) << endl;
}