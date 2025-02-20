#include <stack>
#include <iostream>
using namespace std;

class MyQueue {
private:
    stack<int> stackIn;  // ����ջ���������
    stack<int> stackOut; // ���ջ��������ӺͲ鿴��ͷ

public:
    // ��Ӳ�����ֱ��ѹ������ջ
    void push(int x) {
        stackIn.push(x);
    }

    // ���Ӳ����������ջΪ�գ�ת��Ԫ�غ󵯳�
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

    // �鿴��ͷԪ�أ��߼�ͬ���ӣ���������
    int peek() {
        if (stackOut.empty()) {
            while (!stackIn.empty()) {
                stackOut.push(stackIn.top());
                stackIn.pop();
            }
        }
        return stackOut.top();
    }

    // �ж϶����Ƿ�Ϊ�գ�����ջ��Ϊ��ʱ����Ϊ��
    bool empty() {
        return stackIn.empty() && stackOut.empty();
    }
};
int main() {
    MyQueue q;
    q.push(1);
    q.push(2);
    q.push(3);
    cout << q.peek() << endl; // ��� 1 [[1]]
    q.pop();
    cout << q.peek() << endl; // ��� 2 [[1]]
    return 0;
}
