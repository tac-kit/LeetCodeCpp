/*
NOTE:
1. 测试用例卡快排最坏情况（原数组有序/相等）；针对原数组有序的情况，解决办法是随机选择pivot；针对数组全部相等的情况？
Solution 1: 快速排序，Time Limit Exceeded（C++的时间限制应该是512ms）。
*/

#include<iostream>
#include<vector>
#include<algorithm>
#include<cstdlib>
#include<ctime>

using namespace std;

class Solution {
public:
    vector<int> sortArray(vector<int>& nums) {
        srand(time(nullptr));
        quickSort(nums, 0, nums.size()-1);
        return nums;
    }
private:
    void quickSort(vector<int>& nums, int left, int right) {
        if (left < right) {
            int idx = partition(nums, left, right);
            quickSort(nums, left, idx-1);
            quickSort(nums, idx+1, right);
        }
    }

    int partition(vector<int>& nums, int left, int right) {
        // 随机选择pivot，产生[left, right]区间内的随机数
        // NOTE: cppreference说下面这样得到的随机数是有偏的，参考 https://stackoverflow.com/questions/49878942/why-is-rand6-biased
        int random_idx = left + rand()%(right-left+1);
        // 使用自带函数实现交换，减少代码量
        swap(nums[random_idx], nums[right]);

        int pivot = nums[right];
        int pivot_idx=left-1;
        for (int idx=left; idx<=right; ++idx) {
            if (nums[idx] <= pivot) {
                pivot_idx++;
                swap(nums[idx], nums[pivot_idx]);
            }
        }
        return pivot_idx;
    }
};

int main() {
    auto printNum = [](int num){cout << num << endl;};
    Solution s;
    vector<int> myVec{5,2,3,1};
    s.sortArray(myVec);
    // A: 如何判断两个向量逐项相等？
    for_each(myVec.cbegin(), myVec.cend(), printNum);

    vector<int> myVec1{5,1,1,2,0,0};
    s.sortArray(myVec1);
    // A: 如何判断两个向量逐项相等？
    for_each(myVec1.cbegin(), myVec1.cend(), printNum);

    vector<int> myVec2;
    myVec2.reserve(10000);
    for (int i=0; i<10000; ++i){
        myVec2.push_back(i);
    }
    s.sortArray(myVec2);

    vector<int> myVec3(10000, 1);
    s.sortArray(myVec3);
}