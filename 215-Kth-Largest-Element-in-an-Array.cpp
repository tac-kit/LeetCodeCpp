/*
Solution 1: 使用最小堆实现
Solution 2: (TODO)快排实现
*/

#include<iostream>
#include<vector>
#include<queue>
#include<cassert>

using namespace std;

class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        // NOTE: 最小堆定义：int, vector<int> greater<int>
        priority_queue<int, vector<int>, greater<int>> min_heap;
        // 初始化，否则top报错
        // min_heap.push(-100000);
        // for (auto num: nums){
        //     if (num > min_heap.top()){
        //         if (min_heap.size() < k){
        //             min_heap.push(num);
        //         }else{
        //             min_heap.pop();
        //             min_heap.push(num);
        //         }
        //     }
        // }
        // 下面这种方法更好，将外面的if整合进heap
        for (auto num: nums){
            min_heap.push(num);
            if (min_heap.size()>k)
                min_heap.pop();
        }
        return min_heap.top();
    }
};

int main(){
    vector<int> data{3,2,1,5,6,4};
    Solution s;
    int res = s.findKthLargest(data, 2);
    int ans = 5;
    assert(res == ans);
}