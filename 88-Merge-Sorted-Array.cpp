#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int destPtr = nums1.size()-1;
        m--;
        n--;
        while (m>=0 && n>=0) {
            nums1[destPtr--] = nums1[m] > nums2[n] ? nums1[m--] : nums2[n--];
        }
        while (n>=0) {
            nums1[destPtr--] = nums2[n--];
        }
    }
};

int main() {
    Solution s;
    vector<int> myVec1{1,2,3,0,0,0};
    vector<int> myVec2{2,5,6};
    s.merge(myVec1, 3, myVec2, 3);
    vector<int> res{1,2,2,3,5,6};
    for_each(myVec1.cbegin(), myVec1.cend(), [](int i){cout << i << endl;});
}