#include<iostream>
#include<vector>

using namespace std;

class Solution {
public:
    int trailingZeroes(int n) {
        vector<pair<int, int>> table{{3125,781},{625,156},{125,31},{25,6},{5,1}};
        int res = 0;
        for (auto p: table) {
            while (p.first <= n) {
                res += p.second;
                n -= p.first;
            }
        }
        return res;
    }
};

int main() {
    Solution s;
    cout << s.trailingZeroes(0) << " " << 0 << endl;
    cout << s.trailingZeroes(5) << " " << 1 << endl;
}