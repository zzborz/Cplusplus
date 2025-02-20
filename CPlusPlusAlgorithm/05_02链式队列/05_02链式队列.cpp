#include <iostream>
#include <stdexcept>

// ������нڵ�ṹ
struct QueueNode {
    int data;
    QueueNode* next;
    QueueNode(int val) : data(val), next(nullptr) {}
};

class LinkedQueue {
private:
    QueueNode* front;  // ��ͷָ��
    QueueNode* rear;   // ��βָ��
    int size;          // ���г���

public:
    // ���캯����ʼ���ն���
    LinkedQueue() : front(nullptr), rear(nullptr), size(0) {}

    // ���������ͷ����нڵ�
    ~LinkedQueue() {
        while (!isEmpty()) {
            dequeue();
        }
    }

    // �ж϶����Ƿ�Ϊ��
    bool isEmpty() const {
        return front == nullptr;  // [[3]], [[5]]
    }

    // ��ȡ���г���
    int getSize() const {
        return size;
    }

    // ��Ӳ���
    void enqueue(int value) {
        QueueNode* newNode = new QueueNode(value);
        if (isEmpty()) {
            front = rear = newNode;  // �ն���ʱ��βָ�붼ָ���½ڵ� [[7]]
        }
        else {
            rear->next = newNode;    // �ǿ�ʱ׷�ӵ�β�ڵ�� [[5]]
            rear = newNode;
        }
        size++;
    }

    // ���Ӳ���
    void dequeue() {
        if (isEmpty()) {
            throw std::runtime_error("����Ϊ�գ��޷�����");  // [[4]]
        }
        QueueNode* temp = front;
        front = front->next;         // �ƶ�ͷָ�� [[3]]
        if (front == nullptr) {      // ���б��ʱ����βָ�� [[9]]
            rear = nullptr;
        }
        delete temp;                 // �ͷ�ԭͷ�ڵ��ڴ� [[5]]
        size--;
    }

    // ��ȡ��ͷԪ��
    int getFront() const {
        if (isEmpty()) {
            throw std::runtime_error("����Ϊ��");  // [[4]]
        }
        return front->data;          // [[15]]
    }

    // ��ӡ��������
    void printQueue() const {
        QueueNode* current = front;
        while (current != nullptr) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }
};

// ���Դ���
int main() {
    LinkedQueue queue;
    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);

    std::cout << "��������: ";
    queue.printQueue();  // ���: 10 20 30 [[3]]

    std::cout << "��ͷԪ��: " << queue.getFront() << std::endl;  // 10 [[5]]

    queue.dequeue();
    std::cout << "���Ӻ�����: ";
    queue.printQueue();  // ���: 20 30 [[4]]

    return 0;
}
