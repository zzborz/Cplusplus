#pragma once
#include <iostream>
using namespace std;
const int maxSize = 50;//˳��ջ��Ĭ�����Ԫ�ظ�������ʽջ�ò���
template<class T>
class Stack {
public:
	Stack() {};//���캯��
	virtual void Push(const T& x) = 0;//��ջ
	virtual bool Pop(T& x) = 0;//��ջ,��x�����ܳ�ջԪ��
	virtual bool getTop(T& x) const = 0;//��ȡջ��Ԫ�أ���x������ջ��Ԫ�أ������const��������thisָ�룬ʹ���Ӧ�Ķ������޸ĳ�Ա����
	virtual bool IsEmpty() const = 0;//�ж�ջ�Ƿ�Ϊ��
	virtual bool IsFull() const = 0;//�ж�ջ�Ƿ�Ϊ��
	virtual int getSize() const = 0;//����ջ��Ԫ�ظ���
};