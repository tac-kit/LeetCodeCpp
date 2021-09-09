/*
思考方向：
logn+有序->二分查找
中位数->对当前数左边的数计数
Solution 1: 对于a[i]，在b中找小于a[i]的最后一个数或大于a[i]的第一个数。
答案：
不是确定a[i]然后在b中找相等的数，而是确定i后如果i是中位数那么j也确定，再看a[i]与b[j]是否满足要求
要求：leftMax <= rightMin 相当于 a[i-1] <= b[j] and b[j-1] <= a[i]
*/

#include<iostream>
#include<vector>
#include<cassert>

using namespace std;

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        // a较短
        vector<int> numsa = nums1.size() < nums2.size() ? nums1 : nums2;
        vector<int> numsb = nums1.size() < nums2.size() ? nums2 : nums1;
        int lena = numsa.size();
        int lenb = numsb.size();
        int halfLen = (lena + lenb + 1) / 2;
        int left=0, right=lena;
        while (left <= right) {
            int mida = (left + right) / 2;
            int midb = halfLen - mida;

            if (mida < lena && numsa[mida] < numsb[midb-1]) {
                // 右区间
                left = mida+1;
            }else if (mida > 0 && numsa[mida-1] > numsb[midb]) {
                // 左区间
                right = mida-1;
            }else {
                // 满足要求
                int leftMax;
                if (mida == 0) leftMax = numsb[midb-1];
                else if (midb == 0) leftMax = numsa[mida-1];
                else leftMax = max(numsa[mida-1], numsb[midb-1]);

                // 如果为奇数，直接返回左边最大值
                if ((lena + lenb) % 2 == 1) {
                    return leftMax;
                }

                int rightMin;
                if (mida == lena) rightMin = numsb[midb];
                else if (midb == lenb) rightMin = numsa[mida];
                else rightMin = min(numsa[mida], numsb[midb]);

                return (leftMax + rightMin) / 2.0;
            }
        }
        return -1.0;
    }
};

int main() {
    Solution s;
    vector<int> myVec1{1,3};
    vector<int> myVec2{2};
    assert(s.findMedianSortedArrays(myVec1, myVec2) == 2.0);
}

