/*
Solution 1: 使用一个vector记住当前的最长递增子串，使用二分查找确定新元素的位置。
*/

#include<iostream>
#include<vector>

using namespace std;

class Solution {
public:
    int lengthOfLIS(const vector<int>& nums) {
        vector<int> incVec;
        for (int num: nums) {
            int idx = binarySearch(incVec, num);
            if (idx == incVec.size())
                incVec.push_back(num);
            else
                incVec[idx] = num;
        }
        return incVec.size();
    }

private:
    int binarySearch(const vector<int>& nums, int target) {
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
    cout << s.lengthOfLIS(vector<int>{10,9,2,5,3,7,101,18}) << endl;
    cout << s.lengthOfLIS(vector<int>{0,1,0,3,2,3}) << endl;
    cout << s.lengthOfLIS(vector<int>{7,7,7,7,7,7}) << endl;
}