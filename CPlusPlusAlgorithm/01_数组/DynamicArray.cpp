#include<iostream>//包含标准输入输出流库
using namespace std;//使用标准命名空间，简化代码种的std::前缀
//定义一个DynamicArray类，用于动态数组的管理
class DynamicArray {
private:
	int* data;//指向动态分配数组的指针
	int size;//当前数组中存储的元素个数
	int capacity;//当前数组的容量（即已分配的空间大小）
	//动态扩容数组，当数组容量不足时调用
	void resize() {
		capacity *= 2;//将容量翻倍
		int* newData = new int[capacity];//分配新的内存空间
		for (int i = 0; i < size; i++) {
			newData[i] = data[i];//将旧数据复制到新空间
		}
		delete[] data;//释放旧内存空间
		data = newData;//更新指针，指向新空间

	}
public:
	//构造函数，初始化动态数组
	DynamicArray(int initialCapcity = 2) {
		data = new int[initialCapcity];//分配初始内存空间
		size = 0;//初始化元素个数为0
		capacity = initialCapcity;//初始化容量为传入值或默认值
	}
	//添加元素到动态数组末尾
	void add(int value) {
		if (size >= capacity) {
			resize();//如果当前元素个数达到容量上限，则进行扩容
		}
		data[size++] = value;//在数组末尾添加新元素，并更新元素个数
	}
	//添加元素到指定位置
	void insertElement(int index, int value) {
		if (size >= capacity) {
			resize();//如果当前元素个数达到容量上限，则进行扩容
		}
		
		for (int i = size; i >index; i--)
		{
			data[i ] = data[i-1];
		}
		data[index] = value;
		size++;
	}

	//删除指定位置的元素
	void remove(int index) {
		if (index < 0 || index >= size) {
			cout << "Index out of bounds" << endl;//如果索引超出范围，输出错误信息
			return;
		}
		for (int i = index; i < size-1; i++)
		{
			data[i] = data[i + 1];//将指定位置后元素前移
		}
		size--;//更新元素个数

	}
	//获取指定位置的元素值
	int get(int index) const {
		if (index < 0 || index >= size) {
			cout << "Index out of bounds" << endl;//如果索引超出范围，输出错误信息
			return -1;//返回-1表示错误
		}
		return data[index];//返回指定位置的元素值
	}
	//修改指定位置的元素
	int set(int index,int value) const {
		if (index < 0 || index >= size) {
			cout << "Index out of bounds" << endl;//如果索引超出范围，输出错误信息
			return -1;//返回-1表示错误
		}
		data[index] = value;//修改指定位置的元素值

	}
	//获取当前元素数组的元素个数
	int getSize() const {
		return size;
	}
	//析构函数，释放动态分配的内存空间
	~DynamicArray() {
		delete[] data;//释放数组内存
	}

};



int main() {
	DynamicArray arr;
	arr.add(10);
	arr.add(20);
	arr.add(30);
	arr.add(50);
	arr.insertElement(1, 70);
	cout << "Element at index 0:" << arr.get(0) << endl;
	cout << "Element at index 1:" << arr.get(1) << endl;
	cout << "Element at index 2:" << arr.get(2) << endl; 
	cout << "Element at index 3:" << arr.get(3) << endl;
	
	arr.set(1, 40);
	cout << "Element at index 1 after updata:" << arr.get(1) << endl;
	arr.remove(1);
	cout << "Array size after deletion:" << arr.getSize() << endl;

	return 0;
}