#include<iostream>
using namespace std;
#define MAXSIZE 100
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
//链表定义
typedef struct Lnode {
	int data;//节点的数据域
	struct Lnode* next;//节点的指针域
}Lnode, *LinkList;
//链表初始化
bool InitList(LinkList& L) {
	L = new Lnode;//堆区开辟一个新结点作为链表的头节点（head），同时作为头指针指向头节点
	L->next = NULL;
	return true;
}
//判断链表是否为空
int IsEmpty(LinkList& L) {
	if (L->next == NULL) return TRUE;
	return FALSE;
}