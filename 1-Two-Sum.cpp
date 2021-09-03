/*
Solution 1: 拷贝数组，新数组排序，双指针找到两个数，然后在原数组中查找这两个数的下标。
时间复杂度：排序O(nlogn)，查找O(2n)，合并O(nlogn)。空间复杂度：O(n)。
Solution 2: 使用字典存储经过的数与下标，计算target-nums[idx]是否在字典中。
时间复杂度：O(n)，空间复杂度O(n)。
*/

#include<iostream>
#include<vector>
#include<cassert>
#include<algorithm>
#include<unordered_map>

using namespace std;

class Solution {
public:
    // Solution 1
    // Q: 官方模板nums参数不是常量
    // vector<int> twoSum(const vector<int>& nums, int target) {
    //     vector<int> nums_sorted(nums);
    //     sort(nums_sorted.begin(), nums_sorted.end());
    //     int left=0, right=nums_sorted.size()-1;
    //     // assume that each input would have exactly one solution
    //     while (left<right && nums_sorted[left]+nums_sorted[right] != target){
    //         if (nums_sorted[left]+nums_sorted[right]>target){
    //             right--;
    //         }else{
    //             left++;
    //         }
    //     }
    //     vector<int> res;
    //     auto find_iter = find(nums.cbegin(), nums.cend(), nums_sorted[left]);
    //     res.push_back(find_iter-nums.begin());
    //     if (nums_sorted[left] == nums_sorted[right])
    //         find_iter = find(find_iter+1, nums.cend(), nums_sorted[right]);
    //     else
    //         find_iter = find(nums.cbegin(), nums.cend(), nums_sorted[right]);
    //     res.push_back(find_iter-nums.begin());
    //     return res;
    // }

    vector<int> twoSum(const vector<int>& nums, int target){
        // assume that each input would have exactly one solution
        unordered_map<int, int> num_idx_dict;  // value -> index
        vector<int> res;
        for (int idx=0; idx<nums.size(); ++idx){
            auto find_iter = num_idx_dict.find(target-nums[idx]);
            if (find_iter == num_idx_dict.end()){
                // NOTE: emplace的接口类似pair
                // num_idx_dict.emplace(nums[idx], idx);
                // NOTE: 也可以直接用下标增加元素
                num_idx_dict[nums[idx]] = idx;
            }else{
                // NOTE: 如果访问map的迭代器，接口类似pair
                // res.push_back((*find_iter).second);
                // NOTE: 如果是通过下标访问，返回值
                res.push_back(num_idx_dict[target-nums[idx]]);
                res.push_back(idx);
                break;
            }
        }
        return res;
    }
};

int main(){
    Solution s;
    vector<int> res = s.twoSum(vector<int>{2,7,11,15}, 9);
    vector<int> ans{0,1};
    assert(res == ans);
}

