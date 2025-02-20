#include <iostream>
#include <stdexcept>

// 定义队列节点结构
struct QueueNode {
    int data;
    QueueNode* next;
    QueueNode(int val) : data(val), next(nullptr) {}
};

class LinkedQueue {
private:
    QueueNode* front;  // 队头指针
    QueueNode* rear;   // 队尾指针
    int size;          // 队列长度

public:
    // 构造函数初始化空队列
    LinkedQueue() : front(nullptr), rear(nullptr), size(0) {}

    // 析构函数释放所有节点
    ~LinkedQueue() {
        while (!isEmpty()) {
            dequeue();
        }
    }

    // 判断队列是否为空
    bool isEmpty() const {
        return front == nullptr;  // [[3]], [[5]]
    }

    // 获取队列长度
    int getSize() const {
        return size;
    }

    // 入队操作
    void enqueue(int value) {
        QueueNode* newNode = new QueueNode(value);
        if (isEmpty()) {
            front = rear = newNode;  // 空队列时首尾指针都指向新节点 [[7]]
        }
        else {
            rear->next = newNode;    // 非空时追加到尾节点后 [[5]]
            rear = newNode;
        }
        size++;
    }

    // 出队操作
    void dequeue() {
        if (isEmpty()) {
            throw std::runtime_error("队列为空，无法出队");  // [[4]]
        }
        QueueNode* temp = front;
        front = front->next;         // 移动头指针 [[3]]
        if (front == nullptr) {      // 队列变空时重置尾指针 [[9]]
            rear = nullptr;
        }
        delete temp;                 // 释放原头节点内存 [[5]]
        size--;
    }

    // 获取队头元素
    int getFront() const {
        if (isEmpty()) {
            throw std::runtime_error("队列为空");  // [[4]]
        }
        return front->data;          // [[15]]
    }

    // 打印队列内容
    void printQueue() const {
        QueueNode* current = front;
        while (current != nullptr) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }
};

// 测试代码
int main() {
    LinkedQueue queue;
    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);

    std::cout << "队列内容: ";
    queue.printQueue();  // 输出: 10 20 30 [[3]]

    std::cout << "队头元素: " << queue.getFront() << std::endl;  // 10 [[5]]

    queue.dequeue();
    std::cout << "出队后内容: ";
    queue.printQueue();  // 输出: 20 30 [[4]]

    return 0;
}
