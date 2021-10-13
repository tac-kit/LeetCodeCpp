#include<iostream>
#include<vector>

using namespace std;

class Solution {
public:
    int search(const vector<int>& nums, int target) {
        int left=0, right=nums.size()-1;  // 闭区间。查找指定元素，right=nums.size()-1；查找插入下标，right=nums.size()
        while (left < right) {  // if-else写法，循环条件为left<right
            int mid = (left+right) / 2;
            if (nums[mid] < target) {
                left = mid+1;
            }else{
                right = mid;
            }
        }
        return nums[left] == target ? left : -1;
    }
};

int main() {
    Solution s;
    cout << s.search(vector<int>{1,3,5}, 0) << endl;
    cout << s.search(vector<int>{1,3,5}, 1) << endl;
    cout << s.search(vector<int>{1,3,5}, 4) << endl;
    cout << s.search(vector<int>{1,3,5}, 5) << endl;
    cout << s.search(vector<int>{1,3,5}, 6) << endl;
}