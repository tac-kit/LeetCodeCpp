#include<iostream>
#include<vector>
#include<cassert>

using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int beforeMin = INT_MAX, resMax = 0;
        for (auto p: prices) {
            resMax = max(resMax, p-beforeMin);
            beforeMin = min(beforeMin, p);
        }
        return resMax;
    }
};

int main() {
    Solution s;
    vector<int> myVec{7,1,5,3,6,4};
    assert(s.maxProfit(myVec) == 5);
}