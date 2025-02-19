#pragma once
#include <iostream>
#include "stack.h"
#include<assert.h>

//����Ϊ������Ϊջ�Ĵ洢�ռ�
using namespace std;
const int stackIncrement = 20;//ջ���ʱ��ջ�Ĵ洢�ռ������

template<class T>
class SeqStack :public Stack<T>
	//˳��ջ,����ע�� Stack�����<T>��ʾStackΪ��ģ�壬
	// ��������ͨ����.public�̳�
{
public:
	SeqStack(int sz = 50);//���캯��,����һ����ջ
	~SeqStack() { delete[] elements; }//��������
	void Push(const T& x);//��ջ
	bool IsFull() const { return top == maxSize - 1 ; }//�ж�ջ�Ƿ�Ϊ��
	bool IsEmpty() const { return top == -1 ; }//�ж�ջ�Ƿ�Ϊ��
	bool Pop(T& x);//��ջ,��x����
	bool getTop(T& x) const;//��ȡջ��Ԫ�أ���x����
	int getSize() const { return top + 1; }//����ջ��Ԫ�ظ���
	void makeEmpty() { top = -1; }//�ڴ���Ȼû����գ������ٴ���ջ�Ḳ��ԭ�������ݡ�����������������ʱ�����ղ������ڴ�
	template<class R>
	friend std::ostream& operator<<(std::ostream& out, SeqStack<R>& s);//<<���������ʵ��ջ����������ȫ�ֺ�������Ԫ

private:
	T* elements;//���ջ��Ԫ�ص�����
	int top;//ջ��ָ��
	int maxSize;//ջ�����Ԫ�ظ���
	void overflowProcess();//ջ�������
};
template<class T>
SeqStack<T>::SeqStack(int sz) : top(-1),maxSize(sz) //����sz��������Ĭ�ϲ�����Ϊʲô��
{
	elements = new T[maxSize];//����һ�����ߴ�Ϊsz�Ŀ�ջ�����ڴ���䲻�ɹ��������

	assert(elements != nullptr);
	//���Ժ������ж������е������� ���������ִ�к������䣻������ֹ����ִ��
}
//ջ�������������ջ�Ŀռ�
template<class T>
void SeqStack<T>::overflowProcess()
{
	int newMaxSize = maxSize + stackIncrement;
	T* newArray = new T[newMaxSize];
	if (newArray == nullptr)
	{
		cerr << "�洢�ڴ����ʧ�ܣ�" << endl;
		exit(1);
	}
	for (int i = 0; i <= top; i++)  // ��ȷ��������Ԫ��
	{
		newArray[i] = elements[i];
	}
	maxSize = newMaxSize;  // ����maxSize
	delete[] elements;     // ɾ��������
	elements = newArray;   // ָ��������
}
template <class T>
void SeqStack<T>::Push(const T& x)
{
	if (IsFull() == true)
		overflowProcess(); //ջ��������������ڴ����䣩
	elements[++top] = x;  //top�ȼ�һ����������ջ
}

template <class T>
bool SeqStack<T>::Pop(T& x)//ջ��Ԫ�س�ջ����x����
{
	if (IsEmpty() == true)//���ջΪ�գ�����false����ջʧ��
		return false;
	x = elements[top--]; //ֻ��ջ��ָ���һ��ԭ��ջ����Ԫ�ز�δ��ա�������Ϊ��ջʱ����ڴ�����ݻᱻ��д���ǵ������Ҳ���ԡ�
	return true;
}

template <class T>
bool SeqStack<T>::getTop(T& x)const    //��ȡջ��Ԫ�أ���x����
{
	//���ж�ջ�Ƿ�Ϊ��
	if (IsEmpty() == true)
	{
		return false;
	}
	x = elements[top];//�ȷ���ջ��Ԫ�أ�top�ټ�һ
	return true;
}

template <class R>
std::ostream& operator<<(std::ostream& out, SeqStack <R>& s) //ȫ�ֺ��������ܼ�������SeqStack<T>::
{
	out << "ջ��top = " << s.top << endl; //���ջ����λ��
	for (int i = 0; i <= s.top; i++)
	{
		out << i << " : " << s.elements[i] << endl;
	}
	return out;
}
