/*
Solution 1: 根据左右值大小判断区间特征（单调/间断）
Solution 2: 二分查找，将间断点的另一边视为正/负无穷
https://leetcode.com/problems/search-in-rotated-sorted-array/discuss/14435/Clever-idea-making-it-simple
*/

#include<iostream>
#include<vector>
#include<cassert>

using namespace std;

class Solution {
public:
    // Solution 1
    // int search(vector<int>& nums, int target) {
    //     int left=0, right=nums.size()-1;
    //     while (left <= right) {
    //         int mid = (left + right) / 2;
    //         if (nums[mid] == target) {
    //             return mid;
    //         }else if (nums[mid] > nums[left]) {
    //             if (target >= nums[left] && target < nums[mid]) {
    //                 right = mid-1;
    //             }else{
    //                 left = mid+1;
    //             }
    //         }else if (nums[mid] == nums[left]) {
    //             left = mid + 1;
    //         }else{
    //             if (target > nums[mid] && target <= nums[right]) {
    //                 left = mid + 1;
    //             }else{
    //                 right = mid-1;
    //             }
    //         }
    //     }
    //     return -1;
    // }

    int search(vector<int>& nums, int target) {
        int left=0, right=nums.size()-1;
        while (left <= right) {
            // 常规二分查找
            int mid = (left+right)/2;

            // 核心代码
            // 使用nums[0]（而非间断点）将数组区分为两边，并根据target、nums[mid]、nums[0]相对大小
            // 判断target与nums[mid]是否在同一边，如果在同一边直接二分，否则基于无穷值实现二分区间的延长
            int midNum = (nums[mid] < nums[0]) == (target < nums[0]) ? nums[mid] : (target < nums[0] ? INT_MIN : INT_MAX);

            // 常规二分查找
            if (midNum == target) {
                return mid;
            }else if (midNum < target) {
                left = mid+1;
            }else{
                right = mid-1;
            }
        }
        return -1;
    }
};

int main() {
    Solution s;
    vector<int> myVec{4,5,6,7,0,1,2};
    assert(s.search(myVec, 0) == 4);
    assert(s.search(myVec, 4) == 0);
    assert(s.search(myVec, 5) == 1);
    assert(s.search(myVec, 6) == 2);
    assert(s.search(myVec, 7) == 3);
    assert(s.search(myVec, 1) == 5);
    assert(s.search(myVec, 2) == 6);
    assert(s.search(myVec, 3) == -1);
}