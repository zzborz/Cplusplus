#pragma once
#include <iostream>
#include "stack.h"
#include<assert.h>

//����Ϊ������Ϊջ�Ĵ洢�ռ�
using namespace std;
const int stackIncreament = 20;//ջ���ʱ��ջ�Ĵ洢�ռ������

template<class T>
class SeqStack :public Stack<T>
	//˳��ջ,����ע�� Stack�����<T>��ʾStackΪ��ģ�壬
	// ��������ͨ����.public�̳�
{
public:
	SeqStack(int sz = 50);//���캯��,����һ����ջ
	~
};