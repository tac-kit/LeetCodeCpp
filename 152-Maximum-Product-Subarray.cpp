/*
Solution 1: DP，计算nums[:i]与nums[j:]的积，相乘得到(nums的积/nums[i:j]的积)，取积的最大值。时间复杂度O(n^2).
Solution 2: 含有0的数组的最大积的最小值为0；不含有0的数组全部积的绝对值最大，去掉第1个或最后一个
负数后变为正数。时间复杂度O(n)。
Solution 2.1: (TODO)利用性质“非零数组的最大积数组必为前/后缀”，可简化nonZeroProduct方法。
https://leetcode.com/problems/maximum-product-subarray/discuss/183483/JavaC%2B%2BPython-it-can-be-more-simple
Solution 3: https://leetcode.com/problems/maximum-product-subarray/discuss/48230/Possibly-simplest-solution-with-O(n)-time-complexity
*/

#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

// Solution 2
/*
class Solution {
public:
    int maxProduct(const vector<int>& nums) {
        int totalSum = product(nums, 0, nums.size()-1);
        // 全部积的绝对值总是最大，如果为正直接返回
        if (totalSum > 0)
            return totalSum;
        auto nonZeroEnd = find(nums.begin(), nums.end(), 0);
        auto nonZeroBegin = nums.begin();
        int ret = totalSum == 0 ? 0 : INT_MIN;
        while (nonZeroEnd != nums.end()) {
            if (nonZeroBegin != nonZeroEnd) {
                ret = max(ret, nonZeroProduct(nums, distance(nums.begin(), nonZeroBegin), distance(nums.begin(), nonZeroEnd-1)));
            }
            nonZeroBegin = nonZeroEnd+1;
            nonZeroEnd = find(nonZeroEnd+1, nums.end(), 0);
        }
        return max(ret, nonZeroProduct(nums, distance(nums.begin(), nonZeroBegin), distance(nums.begin(), nonZeroEnd-1)));
    }

private:
    int product(const vector<int>& nums, int left, int right) {
        if (left > right)
            return INT_MIN;
        int ret = 1;
        for (int idx=left; idx<=right; ++idx) {
            ret *= nums[idx];
        }
        return ret;
    }

    // 非零区间最大积
    int nonZeroProduct(const vector<int>& nums, int left, int right) {
        if (left == right)
            return nums[left];
        int totalSum = product(nums, left, right);
        // 全部积的绝对值总是最大，如果为正直接返回
        if (totalSum > 0)
            return totalSum;
        // NOTE: 使用reverse iterator实现从后往前查找
        // 这里因为要指定区间，所以用iterator不方便？
        auto firstNegIter = find_if(nums.begin()+left, nums.begin()+right+1, [](int num){return num<0;});
        int firstNegIdx = distance(nums.begin(), firstNegIter);
        int lastNegIdx = 0;
        for (int idx=right; idx>=left; --idx) {
            if (nums[idx] < 0) {
                lastNegIdx = idx;
                break;
            }
        }
        return max(product(nums, firstNegIdx+1, right), product(nums, left, lastNegIdx-1));
    }
};
*/

// Solution 3
class Solution {
public:
    int maxProduct(const vector<int>& nums) {
        int ret=nums[0], imin=nums[0], imax=nums[0];
        for (auto iter=nums.begin()+1; iter!=nums.end(); ++iter) {
            auto num = *iter;
            if (num < 0)
                swap(imin, imax);
            imin = min(num, imin*num);
            imax = max(num, imax*num);
            ret = max(ret, imax);
        }
        return ret;
    }
};

int main() {
    Solution s;
    cout << s.maxProduct(vector<int>{2,3,-2,4}) << endl;
    cout << s.maxProduct(vector<int>{-2,0,-1}) << endl;
    cout << s.maxProduct(vector<int>{-1}) << endl;
    cout << s.maxProduct(vector<int>{-2,-1}) << endl;
    cout << s.maxProduct(vector<int>{-2,-1,-2}) << endl;
    cout << s.maxProduct(vector<int>{1,0,-1}) << endl;
    cout << s.maxProduct(vector<int>{0}) << endl;
    cout << s.maxProduct(vector<int>{0,0}) << endl;
    cout << s.maxProduct(vector<int>{0,-1}) << endl;
}