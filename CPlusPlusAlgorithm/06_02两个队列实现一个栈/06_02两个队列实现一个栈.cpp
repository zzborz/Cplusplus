#include <queue>
#include <iostream>
using namespace std;

class MyStack {
private:
    queue<int> q1, q2;
public:
    MyStack() {}

    void push(int x) {
        q1.push(x); // 直接入队主队列
    }

    int pop() {
        // 将q1的前n-1个元素转移到q2
        while (q1.size() > 1) {
            q2.push(q1.front());
            q1.pop();
        }
        int res = q1.front(); // 栈顶元素
        q1.pop();
        swap(q1, q2); // 交换队列角色
        return res;
    }

    int top() {
        return q1.back(); // 直接返回主队列尾部元素
    }

    bool empty() {
        return q1.empty() && q2.empty();
    }
};

int main() {
    MyStack s;
    s.push(1);
    s.push(2);
    cout << s.top() << endl;  // 输出2
    cout << s.pop() << endl;  // 输出2
    cout << s.empty() << endl;// 输出0（false）
    return 0;
}