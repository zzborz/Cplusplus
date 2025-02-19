#pragma once
#include <iostream>
using namespace std;
const int maxSize = 50;//顺序栈的默认最大元素个数，链式栈用不到
template<class T>
class Stack {
public:
	Stack() {};//构造函数
	virtual void Push(const T& x) = 0;//进栈
	virtual bool Pop(T& x) = 0;//出栈,由x来接受出栈元素
	virtual bool getTop(T& x) const = 0;//读取栈顶元素，由x来接受栈顶元素，这里的const用于修饰this指针，使其对应的对象不能修改成员变量
	virtual bool IsEmpty() const = 0;//判断栈是否为空
	virtual bool IsFull() const = 0;//判断栈是否为满
	virtual int getSize() const = 0;//返回栈的元素个数
};