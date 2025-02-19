#include <iostream>
#include <stdexcept> // �����쳣����
using namespace std;

template <typename T>
class LinkedStack {
private:
    // ��������ڵ�ṹ
    struct Node {
        T data;
        Node* next;
        Node(const T& val) : data(val), next(nullptr) {}
    };

    Node* topPtr; // ջ��ָ��

public:
    // ���캯������ʼ����ջ
    LinkedStack() : topPtr(nullptr) {}

    // �����������ͷ����нڵ��ڴ�
    ~LinkedStack() {
        while (!isEmpty()) {
            pop();
        }
    }

    // �пղ���
    bool isEmpty() const {
        return topPtr == nullptr;
    }

    // ��ջ����
    void push(const T& value) {
        Node* newNode = new Node(value); // �����½ڵ�
        newNode->next = topPtr;          // �½ڵ�ָ��ԭջ��
        topPtr = newNode;                // ����ջ��ָ��
    }

    // ��ջ����
    void pop() {
        if (isEmpty()) {
            throw runtime_error("Pop from empty stack");
        }
        Node* temp = topPtr;      // ���浱ǰջ��
        topPtr = topPtr->next;    // ջ��ָ����һ�ڵ�
        delete temp;              // �ͷ�ԭջ���ڴ�
    }

    // ��ȡջ��Ԫ��
    T top() const {
        if (isEmpty()) {
            throw runtime_error("Top from empty stack");
        }
        return topPtr->data;
    }
};

// ��������
int main() {
    LinkedStack<int> stack;

    stack.push(10);
    stack.push(20);
    stack.push(30);

    cout << "Top element: " << stack.top() << endl; // ���30

    stack.pop();
    cout << "After pop, top element: " << stack.top() << endl; // ���20

    return 0;
}
