/*
Solution 1: 动态规划+转换。转换为“给定鸡蛋数k和尝试次数t，可以检测的最大楼层数n”
动态规划有两个分支：蛋没碎，鸡蛋数不变；蛋碎了，鸡蛋数减1。
superEggDrop(k, m) + superEggDrop(k-1, n-m)
n=1时有两种情况：蛋碎，f=0；蛋没碎，f=1。所以最好将楼层数加1，输出结果时再减1。
Q: 这道题之所以要转换，是因为时间复杂度高还是算不出来？时间复杂度高。
转换前时间复杂度是O(k*n)，其中n<=1e4；转换后时间复杂度是O(k*t)，当k=100 n=1e4时t=14.
*/

#include<iostream>
#include<vector>

using namespace std;

class Solution {
public:
    int superEggDrop(int k, int n) {
        // 代码中楼层数全部加1
        // 初始化为1，表示即使不尝试也可以确定n=0的情况
        vector<int> eggVec(k+1, 1);
        int cnt = 0;
        // 与实际楼层数比较需要减1，eggVec.back()-1 < n，转化为<=。
        while (eggVec.back() <= n) {
            vector<int> newEggVec(k+1, 1);
            for (int i=1; i<eggVec.size(); ++i) {
                newEggVec[i] = eggVec[i-1] + eggVec[i];
            }
            eggVec = newEggVec;
            cnt++;
        }
        return cnt;
    }
};

int main() {
    Solution s;
    cout << s.superEggDrop(1,2) << endl;
    cout << s.superEggDrop(2,6) << endl;
    cout << s.superEggDrop(3,14) << endl;
}