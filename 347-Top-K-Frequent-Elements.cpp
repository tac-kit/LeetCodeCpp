/*
Solution 1: 哈希表计数，按频数排序。时间复杂度O(nlogn)
Solution 2: 哈希表计数，小顶堆求频数TopK。
这道题的难点是，需要将哈希表按值排序后，输出最大的值对应的键。
使用C++实现的方法是，堆中存键，排序时用键查值，按值排序。
这种做法会用到匿名函数的捕获列表。
*/

#include<iostream>
#include<vector>
#include<queue>
#include<unordered_map>
#include<algorithm>

using namespace std;

class Solution {
public:
    // vector<int> topK(vector<int> nums, int k) {
    //     // 计数
    //     unordered_map<int, int> counter;
    //     for (int num: nums) {
    //         counter[num]++;
    //     }

    //     // 转换为列表后排序
    //     vector<pair<int, int>> cntNumList;
    //     for (auto p: counter) {
    //         cntNumList.emplace_back(p.second, p.first);
    //     }
    //     sort(cntNumList.begin(), cntNumList.end(), [](pair<int, int> p1, pair<int,int> p2){return p1.first>p2.first;});

    //     vector<int> res;
    //     for (int i=0; i<k; ++i) {
    //         res.push_back(cntNumList[i].second);
    //     }
    //     return res;
    // }

    vector<int> topKFrequent(vector<int>& nums, int k) {
        // 计数
        unordered_map<int, int> counter;
        for (int num: nums)
            counter[num]++;
        
        // 转换为小顶堆
        // NOTE: 优先队列使用匿名函数时，需要加上decltype，且没有默认构造函数
        // NOTE: 如果使用函数对象，则不需要。因为模板参数应该填类型，函数对象有类型，匿名函数没类型。
        // https://stackoverflow.com/questions/16111337/declaring-a-priority-queue-in-c-with-a-custom-comparator
        auto comp = [&counter](int i, int j){return counter[i] > counter[j];};
        priority_queue<int, vector<int>, decltype(comp)> minHeap(comp);

        for (auto p: counter) {
            minHeap.push(p.first);
            if (minHeap.size() > k)
                minHeap.pop();
        }

        vector<int> res;
        for (int idx=0; idx<k; ++idx) {
            res.push_back(minHeap.top());
            minHeap.pop();
        }
        return res;
    }
};

void printVec(vector<int> vec) {
    for_each(vec.begin(), vec.end(), [](int i){cout << i << endl;});
}

int main() {
    Solution s;
    vector<int> myVec{1,1,1,2,2,3};
    vector<int> res = s.topKFrequent(myVec, 2);
    printVec(res);

    vector<int> myVec1{1,1,1,1,1,1,1,2,3,3,3,3,3,3,4,4,5,5,5,5,5,6,6,6,7,7,7,7};
    vector<int> res1 = s.topKFrequent(myVec1, 4);
    printVec(res1);
}