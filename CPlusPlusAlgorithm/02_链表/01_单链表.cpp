#include<iostream>
using namespace std;
#define MAXSIZE 100
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
//������
typedef struct Lnode {
	int data;//�ڵ��������
	struct Lnode* next;//�ڵ��ָ����
}Lnode, *LinkList;
//�����ʼ��
bool InitList(LinkList& L) {
	L = new Lnode;//��������һ���½����Ϊ�����ͷ�ڵ㣨head����ͬʱ��Ϊͷָ��ָ��ͷ�ڵ�
	L->next = NULL;
	return true;
}
//�ж������Ƿ�Ϊ��
int IsEmpty(LinkList& L) {
	if (L->next == NULL) return TRUE;
	return FALSE;
}