/*
Solution 1: 贪心，排序
Solution 1.1: 由于在比较和输出时都需要将数字转换为字符串，因此直接在开头将数字转换为字符串，之后全部基于字符串实现
*/

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<sstream>

using namespace std;

// Solution 1
/*
bool comp(const int& a, const int& b) {
    // NOTE: 数字转字符串，to_string
    string sa = to_string(a);
    string sb = to_string(b);
    string sab = sa+sb;
    string sba = sb+sa;
    // NOTE: 字符串转数字，string to long long
    long long int ab = stoll(sab);
    long long int ba = stoll(sba);
    return ab > ba;
}

class Solution {
public:
    string largestNumber(const vector<int>& nums) {
        vector<int> numsCopy = nums;
        // 排序
        sort(numsCopy.begin(), numsCopy.end(), comp);
        // NOTE: 使用stringstream实现整型数组转换字符串
        stringstream resStream;
        for (int num: numsCopy) {
            resStream << num;
        }
        string res = resStream.str();
        // 去掉开头的零
        // 这一步可以优化为：排序是从大到小排序，如果最大的数为0，则返回"0".
        auto iter = find_if(res.begin(), res.end(), [](char c){return c > '0';});
        if (iter == res.end()) {
            // nums.length >= 1，所以结果不为空
            return "0";
        }else{
            return string(iter, res.end());
        }
    }
};
*/

// Solution 1.1
class Solution {
public:
    string largestNumber(const vector<int>& nums) {
        vector<string> numsStr;
        for (int num: nums) numsStr.push_back(to_string(num));
        // 对于纯数字字符串，直接比较字符串的结果与转换为数字再比较是一样的，所以可以直接比较字符串。
        // 上述结论在长度不等时不成立，例如"100"<"50"。因为s1+s2与s2+s1长度始终相等，所以可以这样写。
        sort(numsStr.begin(), numsStr.end(), [](const string& s1, const string& s2){return s1+s2 > s2+s1;});
        // numsStr已经从大到小排序，如果最大的数为0，则返回"0"
        if (numsStr[0] == "0") return "0";
        string res;
        // NOTE: 使用+=拼接字符串
        for (string s: numsStr) res += s;
        return res;
    }
};

int main() {
    Solution s;
    cout << s.largestNumber(vector<int>{10, 2}) << endl;
    cout << s.largestNumber(vector<int>{0, 0}) << endl;
}