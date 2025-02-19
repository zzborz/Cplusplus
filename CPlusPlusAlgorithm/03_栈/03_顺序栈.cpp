#include <iostream>
#include "SeqStack.h"
using namespace std;
int main()
{
	SeqStack<int> stack1(60);
	for (int i = 0; i < 60; i++)
		stack1.Push(i);

	cout << stack1;

	return 0;
}