/*
Solution 1:
使用一个变量存储不重复区间的左边界，使用字典存储{字母:最近出现下标}。
如果nums[idx]不在字典中，idx-左边界+1得到当前不重复区间长度；
如果nums[idx]在字典中，如果dict[nums[idx]]大于等于左边界，将左边界更新为dict[nums[idx]]+1
时间复杂度O(n)，空间复杂度O(n)。
*/

#include<iostream>
#include<string>
#include<unordered_map>
#include<cassert>

using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int unique_left=0, res=0;
        // NOTE: unordered_map键的类型可以为char（用于单字母场景）
        unordered_map<char, int> c_idx_dict;
        for (int idx=0; idx<s.size(); ++idx){
            if (c_idx_dict.find(s[idx]) == c_idx_dict.end()){
                // 如果字典不存在字符
                res = max(res, idx-unique_left+1);
            }else{
                // 如果字符出现过
                if (c_idx_dict[s[idx]] >= unique_left){
                    // 如果出现位置大于等于不重复区间左边界
                    // NOTE: s[idx]类型为char
                    unique_left = c_idx_dict[s[idx]]+1;
                }else{
                    // 否则res可能增大
                    res = max(res, idx-unique_left+1);
                }
            }
            // NOTE: 增、改、查都可以通过[]运算符
            c_idx_dict[s[idx]] = idx;
        }
        return res;
    }
};

int main(){
    Solution s;
    int res = s.lengthOfLongestSubstring("abcabcbb");
    assert(res == 3);
}
