#include <iostream>
using namespace std;

// 定义结点类
class Node {
public:
	int data;// 数据域
	Node* next;// 指针域,指向下一个结点
	//构造函数
	Node(int value) {
		data = value;
		next = nullptr;
	}
};
// 定义循环单链表类
class CircularLinkedList {
private:
	Node* head;//指向头结点的指针

public:
	//构造函数
	CircularLinkedList() {
		head = nullptr;
	}
	//在头部插入节点
	void insertAtHead(int value) {
		Node* newNode = new Node(value);
		if (head == nullptr) {
			head = newNode;
			head->next = head;//自己指向自己，形成循环
		}
		else {
			Node* temp = head;
			while (temp->next != head) {
				temp = temp->next;
			}
			newNode->next = head;//生成新节点指向头结点
			head = newNode;//现在的头结点是新节点
			temp->next = head;//原来的尾结点指向新的头结点
		}
	}
	//在尾部插入节点
	void insertAtTail(int value) {
		Node* newNode = new Node(value);
		if (head == nullptr) {
			head = newNode;
			head->next = head;//自己指向自己，形成循环
		}
		else {
			Node* temp = head;
			while (temp->next != head) {
				temp = temp->next;
			}
			temp->next = newNode;//原来的尾结点指向新节点
			newNode->next = head;//新节点指向头结点
		}
	}
	//删除指定值的节点
	void deleteValue(int value) {
		if (head == nullptr) {
			cout << "链表为空" << endl;
			return;
		}
		if (head->data == value) {
			if (head->next == head) {
				//只有一个节点
				delete head;
				head = nullptr;
				return;
			}
			else {
				Node* temp = head;
				while (temp->next != head) {
					temp = temp->next;
				}//到末尾节点节点
				Node* toDelete = head;//要删除的节点
				head = head->next;//将现在头结点变更为原来节点的下一个节点
				temp->next = head;//末尾节点指向新的头结点
				delete toDelete;//删除掉这个节点
			}
			return;

		}
		Node* current = head;
		while (current->next != head && current->next->data != value) {
			//当前结点的下一个结点不是要删除的结点且下一个结点不是头结点
			//继续往下找，直到找到要删除的结点或者到达末尾
			current = current->next;
		}
		if (current->next->data == value) {//找到要删除的结点
			Node* toDelete = current->next;//新建结点为要删除的结点
			current->next = current->next->next;//当前结点的指针域指向要删除结点的下一个结点位置
			delete toDelete;
		}
		else {//到末尾未找到要删除的结点
			cout << "未找到要删除的值" << endl;
		}
	}
	//修改指定位置的结点值
	void updateValue(int index, int value) {
		if (head == nullptr) {
			cout << "链表为空" << endl;
			return;
		}
		Node* current = head;
		int i = 0;
		while (current->next != head && i != index) {
			//从头结点往下走，直到找到指定位置的结点或者到达末尾
			current = current->next;
			i++;
		}
		if (i == index) {//找到结点位置
			current->data = value;
		}
		else {//未找到结点位置
			cout << "未找到指定位置" << endl;
		}
	}
	//查找指定值的结点
	bool searchValue(int value) {
		if (head == nullptr) {
			cout << "链表为空" << endl;
			return false;
		}
		Node* current = head;
		do {
			if (current->data == value) {
				return true;
			}
			current = current->next;
		} while (current != head);
		return false;
	}
	//打印链表
	void printList() {
		if (head == nullptr) {
			cout << "链表为空" << endl;
			return;
		}
		Node* current = head;
		do {
			cout << current->data << " ";
			current = current->next;
		} while (current != head);
		cout << endl;
	}
	//链表逆置
	void reverseList() {
		if (head == nullptr||head->next==head) {
			//链表为空或者只有一个结点
			cout << "链表为空" << endl;
			return;
		}
		Node* pre = nullptr;
		Node* current = head;
		Node* next = nullptr;
		Node* tail = head;
		do {//从头结点下一个结点开始
			next = current->next;//next保存下一个结点的位置要改变的位置
			current->next = pre;//当前结点指向前一个结点，第一次指向nullptr
			pre = current;//pre指向当前结点
			current = next;//current指向下一个结点
		} while (current != head);

		//循环结束后，pre现在在原来的尾结点，current指向原来的头结点
		head->next = pre;//将现在头结点的指针域指向尾结点
		head = pre;//尾结点所在的位置变为头结点	
	}
	//析构函数，释放链表内存
	~CircularLinkedList() {
		if (head == nullptr) {
			return;
		}
		Node* current = head;
		while(current->next!=head){
			Node* toDelete = current;
			current = current->next;
			delete toDelete;
		}
		delete current;
		head = nullptr;
	}
};

// 主函数
int main()
{
	CircularLinkedList list;

	int choice, value, position;

	while (true)
	{
		cout << "1. 在头部插入节点" << endl;
		cout << "2. 在尾部插入节点" << endl;
		cout << "3. 删除节点" << endl;
		cout << "4. 修改节点" << endl;
		cout << "5. 查找节点" << endl;
		cout << "6. 打印链表" << endl;
		cout << "7. 逆置链表" << endl;
		cout << "8. 退出" << endl;
		cout << "请输入你的选择: ";
		cin >> choice;

		switch (choice) {
		case 1:
			cout << "请输入要插入的值: ";
			cin >> value;
			list.insertAtHead(value);
			system("pause");
			system("cls");
			break;
		case 2:
			cout << "请输入要插入的值: ";
			cin >> value;
			list.insertAtTail(value);
			system("pause");
			system("cls");
			break;
		case 3:
			cout << "请输入要删除的值: ";
			cin >> value;
			list.deleteValue(value);
			system("pause");
			system("cls");
			break;
		case 4:
			cout << "请输入要修改的位置和新值: ";
			cin >> position >> value;
			list.updateValue(position, value);
			system("pause");
			system("cls");
			break;
		case 5:
			cout << "请输入要查找的值: ";
			cin >> value;
			if (list.searchValue(value)) {
				cout << "找到节点: " << value << endl;
			}
			else {
				cout << "未找到节点: " << value << endl;
			}
			system("pause");
			system("cls");
			break;
		case 6:
			list.printList();
			system("pause");
			system("cls");
			break;
		case 7:
			list.reverseList();
			cout << "链表已逆置。" << endl;
			system("pause");
			system("cls");
			break;
		case 8:
			return 0;
		default:
			cout << "无效选择，请重试。" << endl;
		}
	}

	system("pause");
	return 0;
}
