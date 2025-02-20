#include<iostream>
#include<stdexcept>
template <typename T>
class CircularQueue{
private:
	T* data;//存储队列元素的数组
	int front;//队首指针
	int rear;//队尾指针
	int capacity;//队列最大容量
	int size;//队列当前元素个数
public:
	//构造函数,初始化队列容量
	explicit CircularQueue(int cap) :capacity(cap), size(0), front(0), rear(0) {
		data = new T[capacity];//动态分配数组空间
		if (!data) throw std::runtime_error("Memory allocation failed");
	}
	//析构函数,释放数组空间
	~CircularQueue() {
		delete[] data;
	}
    // 判断队列是否为空
    bool isEmpty() const {
        return size == 0; // 通过size判断更直观 [[17]]
    }

    // 判断队列是否已满
    bool isFull() const {
        return size == capacity; // 通过size判断容量 [[17]]
    }

    // 入队操作
    bool enqueue(const T& item) {
        if (isFull()) {
            std::cout << "队列已满，无法入队" << std::endl;
            return false;
        }
        data[rear] = item;//要入队的数
        rear = (rear + 1) % capacity; // 环形移动尾指针 [[2]]
        size++;
        return true;
    }

    // 出队操作
    bool dequeue(T& item) {
        if (isEmpty()) {
            std::cout << "队列为空，无法出队" << std::endl;
            return false;
        }
        item = data[front];//要出队的数
        front = (front + 1) % capacity; // 环形移动头指针 [[2]]
        size--;
        return true;
    }

    // 获取队头元素
    T getFront() const {
        if (isEmpty()) throw std::runtime_error("队列为空");
        return data[front];
    }

    // 获取队尾元素
    T getRear() const {
        if (isEmpty()) throw std::runtime_error("队列为空");
        int lastPos = (rear - 1 + capacity) % capacity; // 计算实际队尾位置 [[7]]
        return data[lastPos];
    }

    // 打印队列内容
    void printQueue() const {
        if (isEmpty()) {
            std::cout << "队列为空" << std::endl;
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

// 示例用法
int main() {
    CircularQueue<int> q(5);

    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    q.enqueue(40);
    q.enqueue(50);  // 队列满

    std::cout << "队头元素: " << q.getFront() << std::endl;  // 10
    std::cout << "队尾元素: " << q.getRear() << std::endl;   // 50

    int val;
    q.dequeue(val);  // 出队10
    q.enqueue(60);   // 入队60

    q.printQueue();  // 输出: 20 30 40 50 60

    return 0;
}