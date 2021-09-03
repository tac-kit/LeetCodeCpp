/*
NOTE:
1. 本题不存在全部方法均为O(1)的解法。
Solution 1: 使用一个队列模拟栈，若队列长度为n，则在pop时循环n-1次，
将pop再push，将最后一个元素移至最前，然后return top。
pop与top的时间复杂度O(n)，push的时间复杂度O(1).
Solution 1.1: 可以在push时翻转，使push时间复杂度为O(n)，而pop与top时间复杂度O(1)
*/

#include<iostream>
#include<queue>
#include<cassert>

using namespace std;

class MyStack {
public:
    /** Initialize your data structure here. */
    MyStack() {

    }
    
    /** Push element x onto stack. */
    void push(int x) {
        q.push(x);
    }
    
    /** Removes the element on top of the stack and returns that element. */
    int pop() {
        round();
        int ret = q.front();
        q.pop();
        return ret;
    }
    
    /** Get the top element. */
    int top() {
        round();
        int ret = q.front();
        q.push(q.front());
        q.pop();
        return ret;
    }
    
    /** Returns whether the stack is empty. */
    bool empty() {
        return q.empty();
    }

private:
    queue<int> q;

    void round(){
        for (int i=1; i<q.size(); ++i){
            q.push(q.front());
            q.pop();
        }
    }
};

int main(){
    MyStack s;
    s.push(1);
    s.push(2);
    assert(s.top() == 2);
    assert(s.pop() == 2);
    assert(s.empty() == false);
}
