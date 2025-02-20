#include <stack>
#include <iostream>
using namespace std;

class MyQueue {
private:
    stack<int> stackIn;  // 输入栈，处理入队
    stack<int> stackOut; // 输出栈，处理出队和查看队头

public:
    // 入队操作：直接压入输入栈
    void push(int x) {
        stackIn.push(x);
    }

    // 出队操作：若输出栈为空，转移元素后弹出
    int pop() {
        if (stackOut.empty()) {
            while (!stackIn.empty()) {
                stackOut.push(stackIn.top());
                stackIn.pop();
            }
        }
        int result = stackOut.top();
        stackOut.pop();
        return result;
    }

    // 查看队头元素：逻辑同出队，但不弹出
    int peek() {
        if (stackOut.empty()) {
            while (!stackIn.empty()) {
                stackOut.push(stackIn.top());
                stackIn.pop();
            }
        }
        return stackOut.top();
    }

    // 判断队列是否为空：两个栈均为空时队列为空
    bool empty() {
        return stackIn.empty() && stackOut.empty();
    }
};
int main() {
    MyQueue q;
    q.push(1);
    q.push(2);
    q.push(3);
    cout << q.peek() << endl; // 输出 1 [[1]]
    q.pop();
    cout << q.peek() << endl; // 输出 2 [[1]]
    return 0;
}
