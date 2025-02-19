#include <iostream>
#include <stdexcept> // 用于异常处理
using namespace std;

template <typename T>
class LinkedStack {
private:
    // 定义链表节点结构
    struct Node {
        T data;
        Node* next;
        Node(const T& val) : data(val), next(nullptr) {}
    };

    Node* topPtr; // 栈顶指针

public:
    // 构造函数：初始化空栈
    LinkedStack() : topPtr(nullptr) {}

    // 析构函数：释放所有节点内存
    ~LinkedStack() {
        while (!isEmpty()) {
            pop();
        }
    }

    // 判空操作
    bool isEmpty() const {
        return topPtr == nullptr;
    }

    // 入栈操作
    void push(const T& value) {
        Node* newNode = new Node(value); // 创建新节点
        newNode->next = topPtr;          // 新节点指向原栈顶
        topPtr = newNode;                // 更新栈顶指针
    }

    // 出栈操作
    void pop() {
        if (isEmpty()) {
            throw runtime_error("Pop from empty stack");
        }
        Node* temp = topPtr;      // 保存当前栈顶
        topPtr = topPtr->next;    // 栈顶指向下一节点
        delete temp;              // 释放原栈顶内存
    }

    // 获取栈顶元素
    T top() const {
        if (isEmpty()) {
            throw runtime_error("Top from empty stack");
        }
        return topPtr->data;
    }
};

// 测试用例
int main() {
    LinkedStack<int> stack;

    stack.push(10);
    stack.push(20);
    stack.push(30);

    cout << "Top element: " << stack.top() << endl; // 输出30

    stack.pop();
    cout << "After pop, top element: " << stack.top() << endl; // 输出20

    return 0;
}
