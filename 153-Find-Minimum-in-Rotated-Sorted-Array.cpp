/*
Solution 1: 通用二分查找方法，适用于[0,a]不满足要求、[a,nums.size()]满足要求，返回a
*/

#include<iostream>
#include<vector>

using namespace std;

class Solution {
public:
    int findMin(vector<int>& nums) {
        int left=0, right=nums.size();
        while (left<right) {
            int mid = left + (right-left)/2;
            if (nums[nums.size()-1] >= nums[mid])
                right = mid;
            else
                left = mid+1;
        }
        return nums[left];
    }
};

int main() {
    Solution s;
    vector<int> myVec{3,4,5,1,2};
    cout << s.findMin(myVec) << endl;
    vector<int> myVec1{2,3,4,5,1};
    cout << s.findMin(myVec1) << endl;
    vector<int> myVec2{1,2,3,4,5};
    cout << s.findMin(myVec2) << endl;
}