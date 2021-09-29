/*
Q: 
1. 这道题如何想到使用并查集来做？并查集适用于哪一类问题？（此题可以将连续序列看成连通分量）
2. -1e9 <= nums[i] <= 1e9，如果用并查集，空间复杂度会不会过大？（0 <= nums.length <= 1e5，可以使用一个哈希表做映射）
3. 并查集的时间复杂度怎么算？（在采用了按秩合并和路径压缩后，时间复杂度是O(m*alpha(n))，m为操作次数，n为元素数）

NOTE:
1. 考虑重复数字；
2. 考虑负数；
3. 考虑nums为空；

Solution 1: 排序后查找，时间复杂度O(nlogn)
Solution 2: 并查集。
Solution 3: 这道题用并查集做存在冗余，例如这道题不需要判断(idx != idxLeft)，因为数字是一维的。
以100, 4, 200, 1, 3, 2为例，排序后是1,2,3,4,100,200，可以从前面没有数字的1,100,200开始自增遍历，
得到2,101,201，如果set中存在对应的数，则说明是连续序列，序列长度加1.
*/

#include<iostream>
#include<vector>
#include<unordered_map>

using namespace std;

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        // 由于-1e9 <= nums[i] <= 1e9值域过大，所以使用0-N的数字对num重新编号，顺便去重。
        unordered_map<int, int> numIdxMap;
        int cnt = 0;
        for (auto num: nums) {
            if (numIdxMap.find(num) == numIdxMap.end()) numIdxMap[num] = cnt++;
        }

        unionFind = vector<int>(cnt, -1);
        for (auto numIdx: numIdxMap) {
            // 与左边的数合并
            int idx = getRoot(numIdx.second);
            if (numIdxMap.find(numIdx.first-1) != numIdxMap.end()) {
                int idxLeft = getRoot(numIdxMap[numIdx.first-1]);
                if (idx != idxLeft) {
                    combine(idx, idxLeft);
                }
            }
            // 与右边的数合并
            idx = getRoot(numIdx.second);
            if (numIdxMap.find(numIdx.first+1) != numIdxMap.end()) {
                int idxRight = getRoot(numIdxMap[numIdx.first+1]);
                if (idx != idxRight) {
                    combine(idx, idxRight);
                }
            }
        }

        int maxVal=0;
        for (auto num: unionFind) {
            if (num < maxVal) maxVal = num;
        }
        return abs(maxVal);
    }

private:
    vector<int> unionFind;

    int getRoot(int idx) {
        // NOTE: 因为unionFind从0开始，所以这里的循环条件应该是>=0
        while (unionFind[idx] >= 0) idx = unionFind[idx];
        return idx;
    }

    void combine(int idx1, int idx2) {
        if (unionFind[idx1] < unionFind[idx2]) {
            unionFind[idx1] += unionFind[idx2];
            unionFind[idx2] = idx1;
        }else{
            unionFind[idx2] += unionFind[idx1];
            unionFind[idx1] = idx2;
        }
    }
};

int main() {
    Solution s;
    vector<int> myVec1{100, 4, 200, 1, 3, 2};
    cout << s.longestConsecutive(myVec1) << endl;

    vector<int> myVec2{0,3,7,2,5,8,4,6,0,1};
    cout << s.longestConsecutive(myVec2) << endl;
}