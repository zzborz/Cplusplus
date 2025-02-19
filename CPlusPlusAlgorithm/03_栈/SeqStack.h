#pragma once
#include <iostream>
#include "stack.h"
#include<assert.h>

//以意为数组作为栈的存储空间
using namespace std;
const int stackIncrement = 20;//栈溢出时候栈的存储空间的增量

template<class T>
class SeqStack :public Stack<T>
	//顺序栈,这里注意 Stack后面加<T>表示Stack为类模板，
	// 区别于普通的类.public继承
{
public:
	SeqStack(int sz = 50);//构造函数,建立一个空栈
	~SeqStack() { delete[] elements; }//析构函数
	void Push(const T& x);//进栈
	bool IsFull() const { return top == maxSize - 1 ; }//判断栈是否为满
	bool IsEmpty() const { return top == -1 ; }//判断栈是否为空
	bool Pop(T& x);//出栈,由x接受
	bool getTop(T& x) const;//读取栈顶元素，由x接受
	int getSize() const { return top + 1; }//返回栈的元素个数
	void makeEmpty() { top = -1; }//内存虽然没被清空，但是再次入栈会覆盖原来的数据。程序运行完析构的时候回清空并回收内存
	template<class R>
	friend std::ostream& operator<<(std::ostream& out, SeqStack<R>& s);//<<运算符重载实现栈对象的输出。全局函数做友元

private:
	T* elements;//存放栈中元素的数组
	int top;//栈顶指针
	int maxSize;//栈的最大元素个数
	void overflowProcess();//栈溢出处理
};
template<class T>
SeqStack<T>::SeqStack(int sz) : top(-1),maxSize(sz) //这里sz不能设置默认参数，为什么？
{
	elements = new T[maxSize];//建立一个最大尺寸为sz的空栈，若内存分配不成功则错误处理

	assert(elements != nullptr);
	//断言函数，判断括号中的条件， 如果成立，执行后面的语句；否则终止程序执行
}
//栈溢出操作，扩充栈的空间
template<class T>
void SeqStack<T>::overflowProcess()
{
	int newMaxSize = maxSize + stackIncrement;
	T* newArray = new T[newMaxSize];
	if (newArray == nullptr)
	{
		cerr << "存储内存分配失败！" << endl;
		exit(1);
	}
	for (int i = 0; i <= top; i++)  // 正确复制所有元素
	{
		newArray[i] = elements[i];
	}
	maxSize = newMaxSize;  // 更新maxSize
	delete[] elements;     // 删除旧数组
	elements = newArray;   // 指向新数组
}
template <class T>
void SeqStack<T>::Push(const T& x)
{
	if (IsFull() == true)
		overflowProcess(); //栈满则做溢出处理（内存扩充）
	elements[++top] = x;  //top先加一，数据再入栈
}

template <class T>
bool SeqStack<T>::Pop(T& x)//栈顶元素出栈，由x接收
{
	if (IsEmpty() == true)//如果栈为空，返回false，出栈失败
		return false;
	x = elements[top--]; //只是栈顶指针减一，原来栈顶的元素并未清空。这是因为入栈时这块内存的数据会被重写覆盖掉。清空也可以。
	return true;
}

template <class T>
bool SeqStack<T>::getTop(T& x)const    //获取栈顶元素，由x接收
{
	//先判断栈是否为空
	if (IsEmpty() == true)
	{
		return false;
	}
	x = elements[top];//先返回栈顶元素，top再减一
	return true;
}

template <class R>
std::ostream& operator<<(std::ostream& out, SeqStack <R>& s) //全局函数，不能加作用域SeqStack<T>::
{
	out << "栈顶top = " << s.top << endl; //输出栈顶的位置
	for (int i = 0; i <= s.top; i++)
	{
		out << i << " : " << s.elements[i] << endl;
	}
	return out;
}
