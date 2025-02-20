#include <queue>
#include <iostream>
using namespace std;

class MyStack {
private:
    queue<int> q1, q2;
public:
    MyStack() {}

    void push(int x) {
        q1.push(x); // ֱ�����������
    }

    int pop() {
        // ��q1��ǰn-1��Ԫ��ת�Ƶ�q2
        while (q1.size() > 1) {
            q2.push(q1.front());
            q1.pop();
        }
        int res = q1.front(); // ջ��Ԫ��
        q1.pop();
        swap(q1, q2); // �������н�ɫ
        return res;
    }

    int top() {
        return q1.back(); // ֱ�ӷ���������β��Ԫ��
    }

    bool empty() {
        return q1.empty() && q2.empty();
    }
};

int main() {
    MyStack s;
    s.push(1);
    s.push(2);
    cout << s.top() << endl;  // ���2
    cout << s.pop() << endl;  // ���2
    cout << s.empty() << endl;// ���0��false��
    return 0;
}