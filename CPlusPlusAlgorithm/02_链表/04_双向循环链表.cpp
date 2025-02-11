#include<iostream>
using namespace std;
using std::cout;
using std::endl;
//�����  
class Node {
public:
    int data;
    Node* pPre, * pNext;
};
//˫��ѭ��������  
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
        cout << "�������������" << endl;
        exit(EXIT_FAILURE);
    }
    else {
        int i = 0;
        Node* pnew, * ptemp;
        ptemp = head;
        i = n;

        while (n-- > 0) {
            pnew = new Node;
            cout << "�����" << i - n << "����㣺";
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
        cout << "����λ�ô���" << endl;
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
        cout << "����λ�ô���" << endl;
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

//���Ժ���  
int main() {
    DoubleCircularLinkList dcl;
    int position = 0, value = 0, n = 0;
    bool flag = false;

    cout << "��������Ҫ����˫��ѭ������Ľ�������";
    cin >> n;
    dcl.CreateLinkList(n);

    cout << "��ӡ����ֵ���£�";
    dcl.TraverseLinkList();

    cout << "������������λ�ú�ֵ��";
    cin >> position >> value;
    dcl.InsertNode(position, value);

    cout << "��ӡ����ֵ���£�";
    dcl.TraverseLinkList();

    cout << "������Ҫɾ������λ�ã�";
    cin >> position;
    dcl.DeleteNode(position);

    cout << "��ӡ����ֵ���£�";
    dcl.TraverseLinkList();

    dcl.DeleteLinkList();
    flag = dcl.IsEmpty();
    if (flag)
        cout << "ɾ������ɹ���" << endl;
    else
        cout << "ɾ������ʧ�ܣ�" << endl;

    return 0;
}