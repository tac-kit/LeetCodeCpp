/*
Solution 1: 二分查找
*/

#include<iostream>
#include<vector>

using namespace std;

class Solution {
public:
    int searchInsert(const vector<int>& nums, int target) {
        int left=0, right=nums.size();
        while (left < right) {
            int mid = (left + right) / 2;
            if (nums[mid] < target)
                left = mid+1;
            else
                right = mid;
        }
        return left;
    }
};

int main() {
    Solution s;
    cout << s.searchInsert(vector<int>{1,3,5,6}, 5) << endl;
}