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
//销毁单链表
int DestoryList(LinkList& L) {
	LinkList p;//创建一个指针
	while (L != NULL) {
		p = L;
		L = L->next;
		delete p;//L移动到下一个指针，删除p指向的节点。
	}
	return OK;
}
//清空链表
int ClearList(LinkList& L) {
	LinkList p;
	LinkList q;//创建两个指针，用于依次释放节点
	p = L->next;//将指针p指向首元节点处
	while (L != NULL) {
		q = p->next;//将p指向的那个节点的指针域赋给q,实际上就是让q指向p的下一个节点。
		delete p;//释放p指向的节点
		p = q;//将q赋给p，实际上就是让p指向q指向的节点	
	}
	L->next = NULL;//���头节点的指针域置空
	return OK;
}
//获取单链表的表长只要统计表长，不改变链表元素，因此不用&
int GetLength(LinkList L) //这里
{
	LinkList p;
	p = L->next;//将头节点的next阈值赋给p
	int i = 0;
	while (p!= NULL) {
		i++;
		p = p->next;

	}
	return i;
}
//获取链表中第i个元素的值
int GetElem(LinkList L, int i, int& e)
{
	LinkList p;
	p = L->next;//p指向首元节点
	int j = 1;//因为p已经在首元节点了，所以这里赋值直接使j=1
	while (p != NULL && j < i)//依次向后扫描，直到p指向第i个元素或者p指向空
	{
		p = p->next;
		j++;
	}
	if (!p || j > i)
	{
		cout << "out of range" << endl;
		return ERROR;
	}
	e = p->data;
	return OK;
}
//查找---按值查找，返回地址 --地址要用 指针形式返
Lnode* LocateElem(LinkList L, int e)
{
	LinkList p;
	p = L->next;//p指向首元节点
	while (p != NULL && p->data)
	{
		p = p->next;
	}
	return p;//不管找没找到都返回地址，只是没找到时p指向空处
}
//查找-按值查找，返回位置序号
int LocateElem_L(LinkList L, int e)
{
	LinkList p;
	p = L->next;//p指向首元结点
	int j = 1;
	while (p != NULL && p->data != e)
	{
		p = p->next;
		j++;
	}
	if (p != NULL)//如果p不为空，说明找到了，返回j的位置
	{
		return j;
	}
	else//否则返回0
	{
		return 0;
	}
}
//在链表第i个位置插入新结点e
bool InsertList(LinkList& L, int i, int e) {
	LinkList p;
	p = L;//p指向头节点
	int j = 0;//j从0开始
	while (p != NULL && j < i - 1) {//寻找第i-1个节点，让指针p指向第i-1个节点位置
		p = p->next;
		++j;
	}
	if(!p||j>i-1){//i大于表长+1或者小于1，插入位置违法
		return ERROR;
	}
	Lnode* s = new Lnode;//创建一个新节点	
	s->data = e;//将新节点的数据域赋值为e
	s->next = p->next;//将新节点的指针域指向p的下一个节点
	p->next = s;//将p的指针域指向新节点
	return true;
}
//删除链表第i个位置的元素
int DeletLnode(LinkList& L, int i, int& e) {
	LinkList p;//创建一个指针,指向第i-1个节点的位置，不能直接指向第i个节点，因为删除时需要找到第i-1个节点
	p = L;
	int j = 0;
	while (p->next != NULL && j < i - 1) {//寻找第i-1个节点,并令p指向第i-1个节点
		p = p->next;
		++j;
	}
	if (!p->next || j > i - 1) {//i大于表长+1或者小于1，删除位置违法
		return ERROR;
	}
	LinkList q = p->next;//创建一个指针q，指向第i个节点
	p->next = q->next;//将第i-1个节点的指针域指向第i+1个节点
	e = q->data;//将第i个节点的数据域赋值给e
	//释放删除节点的空间，另外说明：这里不特定删除指针去，因为指针q不是在堆区开辟的，即不是new出来的，所以局部
	//变量执行完毕后，还给栈区了。
	delete q;
	return OK;
}
//输出链表 打印链表所有数据域的数据
void PrintList(LinkList L) {
	LinkList p;
	p = L->next;//p指向首元节点
	while (p != NULL) {
		cout << p->data << " ";
		p = p->next;
	}
	cout << endl;
}
//单链表的建立——头插法
void CreateListHead(LinkList& L, int n) {
	L = new Lnode;//创建一个头节点;在堆区开辟；注意这里new过之后才是结点，否则就是一个指针
	L->next = nullptr;//头节点的指针域置空 c++11写法
	for(int i=n;i>0;--i){
		Lnode* p = new Lnode;//创建新节点
		cin >> p->data;//输入新节点的数据
		//解释：第一次把p的结点的next域指针置为NULL，意思是最后一个结点的next域指针指向NULL,而后来的
		//结点的next域指针指向前一个结点，这样就形成了一个链表
		p->next = L->next;//将新节点的指针域指向头节点的指针域
		L->next = p;//将头节点的指针域指向新节点
	}
}
//单链表的建立——尾插法
void CreateListTail(LinkList& L,int n){//通过&返回链表
	L = new Lnode;//创建一个头节点;在堆区开辟；���意这里new过之后才是结点，否则就是一个指针
	L->next = nullptr;//头节点的指针域置空 c++11写法
	LinkList r = L;//创建一个尾指针，尾指针指向头节点
	for (int i = n; i > 0; --i) {
		Lnode* p = new Lnode;//创建新节点
		cin >> p->data;//输入新节点的数据
		r->next = p;//将尾指针的指针域指向新节点,插入到尾部
		r = p;//将尾指针指向新节点，每连接上一个新结点，就把尾指针后移到新结点上，所以称之为尾指针
	}
}
/*int main() {
	LinkList L;
	InitList(L);
	CreateListTail(L, 5);
	PrintList(L);
	int e;
	GetElem(L, 3, e);
	cout << e << endl;
	InsertList(L, 3, 100);
	PrintList(L);
	int a;
	DeletLnode(L, 3, a);
	PrintList(L);
	DestoryList(L);
	return 0;
}*/