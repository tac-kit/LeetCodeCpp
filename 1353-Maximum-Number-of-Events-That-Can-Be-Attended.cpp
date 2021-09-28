/*
Solution 1: 两个小顶堆，一个即将到来的会议（按起始日期排列），一个存可以参加但尚未参加的会议（按结束日期排列）
*/

#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;

class Solution {
public:
    int maxEvents(vector<vector<int>>& events) {
        if (events.empty()) return 0;
        // 排序这里不用匿名函数也是可以的。参数是否声明为const &对内存消耗量的影响极大。
        // sort(events.begin(), events.end(), [](vector<int> event1, vector<int> event2){return event1[0] < event2[0];});
        sort(events.begin(), events.end(), [](const vector<int>& event1, const vector<int>& event2){return event1[0] < event2[0];});
        // sort(events.begin(), events.end());
        priority_queue<int, vector<int>, greater<int>> nextHeap;
        
        // day是当前天数，idx是events中的下标，cnt是已参加会议次数
        int day=1, idx=0, cnt=0;
        while (idx < events.size() || !nextHeap.empty()) {
            // 首先排除nextHead中所有过期会议
            while (!nextHeap.empty() && nextHeap.top() < day)
                nextHeap.pop();
            // 之后将当天开始的会议加入小顶堆
            while (idx < events.size() && events[idx][0] == day)
                nextHeap.push(events[idx++][1]);
            // 如果当天存在可参加但未参加的会议，参加会议
            if (!nextHeap.empty()) {
                nextHeap.pop();
                cnt++;
            }
            day++;
        }
        return cnt;
    }
};

int main() {
    Solution s;
    vector<vector<int>> myVec1{{1,2}, {2,3}, {3,4}};
    cout << s.maxEvents(myVec1) << endl;
}