/*
Solution 1: 二分查找，性能瓶颈是insert，时间复杂度O(n^2)
Solution 2: 两个堆，左半边大顶堆，右半边小顶堆。（利用中位数两边数量相等的特点）
插入时较高效的做法是判断两边堆大小然后选择插入的堆，这里选择了一个比较简单的方法，
就是先直接与堆顶元素比较大小，插入，再平衡堆大小。
Solution 2.1: 考虑两种情况：[n,n]和[n+1,n]，两种状态的下一个状态分别是[n+1,n]和[n+1,n+1].
也就是状态1应该在左半边插入。插入什么？应该插入当前插入元素+右半边所有元素中的最小值。
所以在状态1下，先将当前插入元素插入右半边，然后将右半边堆顶元素插入左半边。
https://leetcode.com/problems/find-median-from-data-stream/discuss/74047/JavaPython-two-heap-solution-O(log-n)-add-O(1)-find
*/

#include<iostream>
#include<vector>
#include<queue>

using namespace std;

// Solution 1
/*
class MedianFinder {
public:
    MedianFinder() {
        
    }
    
    void addNum(int num) {
        int idx = binarySearch(stream, num);
        stream.insert(stream.begin() + idx, num);
    }
    
    double findMedian() {
        if (stream.size() % 2 == 1)
            return stream[stream.size() / 2];
        else
            return (stream[stream.size() / 2 - 1] + stream[stream.size() / 2]) / 2.0;
    }

private:
    // bisect_left
    int binarySearch(const vector<int>& nums, int target) {
        int left=0, right=nums.size();
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] < target) {
                left = mid+1;
            }else {
                right = mid;
            }
        }
        return left;
    }
    vector<int> stream;
};*/

// Solution 2
class MedianFinder {
public:
    MedianFinder() {
        
    }
    
    // void addNum(int num) {
    //     if (rightMinHeap.size() > 0 && num > rightMinHeap.top())
    //         rightMinHeap.push(num);
    //     else
    //         leftMaxHeap.push(num);
    //     // 再平衡，左半边始终大于等于右半边
    //     if (leftMaxHeap.size() - 1 > rightMinHeap.size()) {
    //         rightMinHeap.push(leftMaxHeap.top());
    //         leftMaxHeap.pop();
    //     }
    //     if (rightMinHeap.size() > leftMaxHeap.size()) {
    //         leftMaxHeap.push(rightMinHeap.top());
    //         rightMinHeap.pop();
    //     }
    // }

    // Solution 2.1
    void addNum(int num) {
        if (leftMaxHeap.size() == rightMinHeap.size()) {
            rightMinHeap.push(num);
            leftMaxHeap.push(rightMinHeap.top());
            rightMinHeap.pop();
        } else {
            leftMaxHeap.push(num);
            rightMinHeap.push(leftMaxHeap.top());
            leftMaxHeap.pop();
        }
    }
    
    double findMedian() {
        if (leftMaxHeap.size() == rightMinHeap.size())
            return (leftMaxHeap.top() + rightMinHeap.top()) / 2.0;
        else
            return leftMaxHeap.top();
    }

private:
    priority_queue<int> leftMaxHeap;
    priority_queue<int, vector<int>, greater<int>> rightMinHeap;
};

int main() {
    MedianFinder *obj = new MedianFinder();
    obj->addNum(1);
    cout << obj->findMedian() << endl;
    obj->addNum(2);
    cout << obj->findMedian() << endl;
    obj->addNum(3);
    cout << obj->findMedian() << endl;
}