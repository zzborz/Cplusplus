#include<iostream>//������׼�����������
using namespace std;//ʹ�ñ�׼�����ռ䣬�򻯴����ֵ�std::ǰ׺
//����һ��DynamicArray�࣬���ڶ�̬����Ĺ���
class DynamicArray {
private:
	int* data;//ָ��̬���������ָ��
	int size;//��ǰ�����д洢��Ԫ�ظ���
	int capacity;//��ǰ��������������ѷ���Ŀռ��С��
	//��̬�������飬��������������ʱ����
	void resize() {
		capacity *= 2;//����������
		int* newData = new int[capacity];//�����µ��ڴ�ռ�
		for (int i = 0; i < size; i++) {
			newData[i] = data[i];//�������ݸ��Ƶ��¿ռ�
		}
		delete[] data;//�ͷž��ڴ�ռ�
		data = newData;//����ָ�룬ָ���¿ռ�

	}
public:
	//���캯������ʼ����̬����
	DynamicArray(int initialCapcity = 2) {
		data = new int[initialCapcity];//�����ʼ�ڴ�ռ�
		size = 0;//��ʼ��Ԫ�ظ���Ϊ0
		capacity = initialCapcity;//��ʼ������Ϊ����ֵ��Ĭ��ֵ
	}
	//���Ԫ�ص���̬����ĩβ
	void add(int value) {
		if (size >= capacity) {
			resize();//�����ǰԪ�ظ����ﵽ�������ޣ����������
		}
		data[size++] = value;//������ĩβ�����Ԫ�أ�������Ԫ�ظ���
	}
	//���Ԫ�ص�ָ��λ��
	void insertElement(int index, int value) {
		if (size >= capacity) {
			resize();//�����ǰԪ�ظ����ﵽ�������ޣ����������
		}
		
		for (int i = size; i >index; i--)
		{
			data[i ] = data[i-1];
		}
		data[index] = value;
		size++;
	}

	//ɾ��ָ��λ�õ�Ԫ��
	void remove(int index) {
		if (index < 0 || index >= size) {
			cout << "Index out of bounds" << endl;//�������������Χ�����������Ϣ
			return;
		}
		for (int i = index; i < size-1; i++)
		{
			data[i] = data[i + 1];//��ָ��λ�ú�Ԫ��ǰ��
		}
		size--;//����Ԫ�ظ���

	}
	//��ȡָ��λ�õ�Ԫ��ֵ
	int get(int index) const {
		if (index < 0 || index >= size) {
			cout << "Index out of bounds" << endl;//�������������Χ�����������Ϣ
			return -1;//����-1��ʾ����
		}
		return data[index];//����ָ��λ�õ�Ԫ��ֵ
	}
	//�޸�ָ��λ�õ�Ԫ��
	int set(int index,int value) const {
		if (index < 0 || index >= size) {
			cout << "Index out of bounds" << endl;//�������������Χ�����������Ϣ
			return -1;//����-1��ʾ����
		}
		data[index] = value;//�޸�ָ��λ�õ�Ԫ��ֵ

	}
	//��ȡ��ǰԪ�������Ԫ�ظ���
	int getSize() const {
		return size;
	}
	//�����������ͷŶ�̬������ڴ�ռ�
	~DynamicArray() {
		delete[] data;//�ͷ������ڴ�
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