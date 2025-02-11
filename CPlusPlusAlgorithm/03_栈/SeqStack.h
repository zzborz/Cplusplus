#pragma once
#include <iostream>
#include "stack.h"
#include<assert.h>

//以意为数组作为栈的存储空间
using namespace std;
const int stackIncreament = 20;//栈溢出时候栈的存储空间的增量

template<class T>
class SeqStack :public Stack<T>
	//顺序栈,这里注意 Stack后面加<T>表示Stack为类模板，
	// 区别于普通的类.public继承
{
public:
	SeqStack(int sz = 50);//构造函数,建立一个空栈
	~
};