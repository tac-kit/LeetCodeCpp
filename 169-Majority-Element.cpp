/*
Solution 1: 使用有限大小的小顶堆记录元素频率，因为小顶堆大小有限，所以时间复杂度可视为常数。
但这种方法有一个问题，就是如何更新不在堆顶的元素的频率？如果使用指针，如何在更新频率之后
更新堆的排序？
Solution 2: Boyer-Moore算法。
*/

#include<iostream>
#include<vector>
#include<queue>

using namespace std;

class Solution {
public:
    // Solution 2
    int majorityElement(vector<int>& nums) {
        int res;
        int cnt = 0;
        for (int num: nums) {
            if (cnt == 0)
                res = num;
            cnt += res == num ? 1 : -1;
        }
        return res;
    }
};

int main() {
    Solution s;
    vector<int> myVec{3,2,3};
    cout << s.majorityElement(myVec) << endl;
}