#include<iostream>
using namespace std;
using std::cout;
using std::endl;
//结点类  
class Node {
public:
    int data;
    Node* pPre, * pNext;
};
//双向循环链表类  
class DoubleCircularLinkList {
public:
    DoubleCircularLinkList() {
        head = new Node;
        head->data = 0;
        head->pNext = head;
        head->pPre = head;
    }
    ~DoubleCircularLinkList() { delete head; }
    void CreateLinkList(int n);
    void InsertNode(int position, int d);
    void TraverseLinkList();
    bool IsEmpty();
    int GetLength();
    void DeleteNode(int posiiton);
    void DeleteLinkList();
private:
    Node* head;
};

void DoubleCircularLinkList::CreateLinkList(int n) {
    if (n < 0) {
        cout << "输入结点个数错误！" << endl;
        exit(EXIT_FAILURE);
    }
    else {
        int i = 0;
        Node* pnew, * ptemp;
        ptemp = head;
        i = n;

        while (n-- > 0) {
            pnew = new Node;
            cout << "输入第" << i - n << "个结点：";
            cin >> pnew->data;
            pnew->pNext = head;
            pnew->pPre = ptemp;
            ptemp->pNext = pnew;
            ptemp = pnew;
        }
    }
}

void DoubleCircularLinkList::InsertNode(int position, int d) {
    if (position < 0 || position > GetLength() + 1) {
        cout << "输入位置错误！" << endl;
        exit(EXIT_FAILURE);
    }
    else {
        Node* pnew, * ptemp;
        pnew = new Node;
        pnew->data = d;
        ptemp = head;
        while (position-- > 1)
            ptemp = ptemp->pNext;
        pnew->pNext = ptemp->pNext;
        pnew->pPre = ptemp;
        ptemp->pNext = pnew;
        ptemp = pnew;
    }
}

void DoubleCircularLinkList::TraverseLinkList() {
    Node* ptemp = head->pNext;
    while (ptemp != head) {
        cout << ptemp->data << " ";
        ptemp = ptemp->pNext;
    }
    cout << endl;
}

bool DoubleCircularLinkList::IsEmpty() {
    if (head == head->pNext)
        return true;
    else
        return false;
}

int DoubleCircularLinkList::GetLength() {
    int n = 0;
    Node* ptemp = head->pNext;
    while (ptemp != head) {
        n++;
        ptemp = ptemp->pNext;
    }
    return n;
}

void DoubleCircularLinkList::DeleteNode(int position) {
    if (position < 0 || position > GetLength()) {
        cout << "输入位置错误！" << endl;
        exit(EXIT_FAILURE);
    }
    else {
        Node* pdelete, * ptemp;
        ptemp = head;
        while (position-- > 1)
            ptemp = ptemp->pNext;
        pdelete = ptemp->pNext;
        ptemp->pNext = pdelete->pNext;
        pdelete->pNext->pPre = ptemp;
        delete pdelete;
        pdelete = NULL;
    }
}

void DoubleCircularLinkList::DeleteLinkList() {
    Node* pdelete, * ptemp;
    pdelete = head->pNext;
    while (pdelete != head) {
        ptemp = pdelete->pNext;
        head->pNext = ptemp;
        ptemp->pPre = head;
        delete pdelete;
        pdelete = ptemp;
    }
}

//测试函数  
int main() {
    DoubleCircularLinkList dcl;
    int position = 0, value = 0, n = 0;
    bool flag = false;

    cout << "请输入需要创建双向循环链表的结点个数：";
    cin >> n;
    dcl.CreateLinkList(n);

    cout << "打印链表值如下：";
    dcl.TraverseLinkList();

    cout << "请输入插入结点的位置和值：";
    cin >> position >> value;
    dcl.InsertNode(position, value);

    cout << "打印链表值如下：";
    dcl.TraverseLinkList();

    cout << "请输入要删除结点的位置：";
    cin >> position;
    dcl.DeleteNode(position);

    cout << "打印链表值如下：";
    dcl.TraverseLinkList();

    dcl.DeleteLinkList();
    flag = dcl.IsEmpty();
    if (flag)
        cout << "删除链表成功！" << endl;
    else
        cout << "删除链表失败！" << endl;

    return 0;
}