#include<iostream>
#include<vector>
#include<cassert>
#include<algorithm>

using namespace std;

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        // NOTE: 使用INT_MIN和INT_MAX定义最大最小值
        int res=INT_MIN, curr=0;
        for (auto num: nums) {
            curr += num;  // 考虑全负数的情况，这一句放前面
            res = max(curr, res);
            curr = max(curr, 0);
        }
        return res;
    }
};

int main() {
    Solution s;
    vector<int> myVec{-2,1,-3,4,-1,2,1,-5,4};
    int res = s.maxSubArray(myVec);
    assert(res == 6);
}