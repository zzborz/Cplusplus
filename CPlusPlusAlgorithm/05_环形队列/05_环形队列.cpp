#include<iostream>
#include<stdexcept>
template <typename T>
class CircularQueue{
private:
	T* data;//�洢����Ԫ�ص�����
	int front;//����ָ��
	int rear;//��βָ��
	int capacity;//�����������
	int size;//���е�ǰԪ�ظ���
public:
	//���캯��,��ʼ����������
	explicit CircularQueue(int cap) :capacity(cap), size(0), front(0), rear(0) {
		data = new T[capacity];//��̬��������ռ�
		if (!data) throw std::runtime_error("Memory allocation failed");
	}
	//��������,�ͷ�����ռ�
	~CircularQueue() {
		delete[] data;
	}
    // �ж϶����Ƿ�Ϊ��
    bool isEmpty() const {
        return size == 0; // ͨ��size�жϸ�ֱ�� [[17]]
    }

    // �ж϶����Ƿ�����
    bool isFull() const {
        return size == capacity; // ͨ��size�ж����� [[17]]
    }

    // ��Ӳ���
    bool enqueue(const T& item) {
        if (isFull()) {
            std::cout << "�����������޷����" << std::endl;
            return false;
        }
        data[rear] = item;//Ҫ��ӵ���
        rear = (rear + 1) % capacity; // �����ƶ�βָ�� [[2]]
        size++;
        return true;
    }

    // ���Ӳ���
    bool dequeue(T& item) {
        if (isEmpty()) {
            std::cout << "����Ϊ�գ��޷�����" << std::endl;
            return false;
        }
        item = data[front];//Ҫ���ӵ���
        front = (front + 1) % capacity; // �����ƶ�ͷָ�� [[2]]
        size--;
        return true;
    }

    // ��ȡ��ͷԪ��
    T getFront() const {
        if (isEmpty()) throw std::runtime_error("����Ϊ��");
        return data[front];
    }

    // ��ȡ��βԪ��
    T getRear() const {
        if (isEmpty()) throw std::runtime_error("����Ϊ��");
        int lastPos = (rear - 1 + capacity) % capacity; // ����ʵ�ʶ�βλ�� [[7]]
        return data[lastPos];
    }

    // ��ӡ��������
    void printQueue() const {
        if (isEmpty()) {
            std::cout << "����Ϊ��" << std::endl;
            return;
        }
        int count = 0;
        int index = front;
        while (count < size) {
            std::cout << data[index] << " ";
            index = (index + 1) % capacity;
            count++;
        }
        std::cout << std::endl;
    }
};

// ʾ���÷�
int main() {
    CircularQueue<int> q(5);

    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    q.enqueue(40);
    q.enqueue(50);  // ������

    std::cout << "��ͷԪ��: " << q.getFront() << std::endl;  // 10
    std::cout << "��βԪ��: " << q.getRear() << std::endl;   // 50

    int val;
    q.dequeue(val);  // ����10
    q.enqueue(60);   // ���60

    q.printQueue();  // ���: 20 30 40 50 60

    return 0;
}