#include <iostream>
using namespace std;

// ��������
class Node {
public:
	int data;// ������
	Node* next;// ָ����,ָ����һ�����
	//���캯��
	Node(int value) {
		data = value;
		next = nullptr;
	}
};
// ����ѭ����������
class CircularLinkedList {
private:
	Node* head;//ָ��ͷ����ָ��

public:
	//���캯��
	CircularLinkedList() {
		head = nullptr;
	}
	//��ͷ������ڵ�
	void insertAtHead(int value) {
		Node* newNode = new Node(value);
		if (head == nullptr) {
			head = newNode;
			head->next = head;//�Լ�ָ���Լ����γ�ѭ��
		}
		else {
			Node* temp = head;
			while (temp->next != head) {
				temp = temp->next;
			}
			newNode->next = head;//�����½ڵ�ָ��ͷ���
			head = newNode;//���ڵ�ͷ������½ڵ�
			temp->next = head;//ԭ����β���ָ���µ�ͷ���
		}
	}
	//��β������ڵ�
	void insertAtTail(int value) {
		Node* newNode = new Node(value);
		if (head == nullptr) {
			head = newNode;
			head->next = head;//�Լ�ָ���Լ����γ�ѭ��
		}
		else {
			Node* temp = head;
			while (temp->next != head) {
				temp = temp->next;
			}
			temp->next = newNode;//ԭ����β���ָ���½ڵ�
			newNode->next = head;//�½ڵ�ָ��ͷ���
		}
	}
	//ɾ��ָ��ֵ�Ľڵ�
	void deleteValue(int value) {
		if (head == nullptr) {
			cout << "����Ϊ��" << endl;
			return;
		}
		if (head->data == value) {
			if (head->next == head) {
				//ֻ��һ���ڵ�
				delete head;
				head = nullptr;
				return;
			}
			else {
				Node* temp = head;
				while (temp->next != head) {
					temp = temp->next;
				}//��ĩβ�ڵ�ڵ�
				Node* toDelete = head;//Ҫɾ���Ľڵ�
				head = head->next;//������ͷ�����Ϊԭ���ڵ����һ���ڵ�
				temp->next = head;//ĩβ�ڵ�ָ���µ�ͷ���
				delete toDelete;//ɾ��������ڵ�
			}
			return;

		}
		Node* current = head;
		while (current->next != head && current->next->data != value) {
			//��ǰ������һ����㲻��Ҫɾ���Ľ������һ����㲻��ͷ���
			//���������ң�ֱ���ҵ�Ҫɾ���Ľ����ߵ���ĩβ
			current = current->next;
		}
		if (current->next->data == value) {//�ҵ�Ҫɾ���Ľ��
			Node* toDelete = current->next;//�½����ΪҪɾ���Ľ��
			current->next = current->next->next;//��ǰ����ָ����ָ��Ҫɾ��������һ�����λ��
			delete toDelete;
		}
		else {//��ĩβδ�ҵ�Ҫɾ���Ľ��
			cout << "δ�ҵ�Ҫɾ����ֵ" << endl;
		}
	}
	//�޸�ָ��λ�õĽ��ֵ
	void updateValue(int index, int value) {
		if (head == nullptr) {
			cout << "����Ϊ��" << endl;
			return;
		}
		Node* current = head;
		int i = 0;
		while (current->next != head && i != index) {
			//��ͷ��������ߣ�ֱ���ҵ�ָ��λ�õĽ����ߵ���ĩβ
			current = current->next;
			i++;
		}
		if (i == index) {//�ҵ����λ��
			current->data = value;
		}
		else {//δ�ҵ����λ��
			cout << "δ�ҵ�ָ��λ��" << endl;
		}
	}
	//����ָ��ֵ�Ľ��
	bool searchValue(int value) {
		if (head == nullptr) {
			cout << "����Ϊ��" << endl;
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
	//��ӡ����
	void printList() {
		if (head == nullptr) {
			cout << "����Ϊ��" << endl;
			return;
		}
		Node* current = head;
		do {
			cout << current->data << " ";
			current = current->next;
		} while (current != head);
		cout << endl;
	}
	//��������
	void reverseList() {
		if (head == nullptr||head->next==head) {
			//����Ϊ�ջ���ֻ��һ�����
			cout << "����Ϊ��" << endl;
			return;
		}
		Node* pre = nullptr;
		Node* current = head;
		Node* next = nullptr;
		Node* tail = head;
		do {//��ͷ�����һ����㿪ʼ
			next = current->next;//next������һ������λ��Ҫ�ı��λ��
			current->next = pre;//��ǰ���ָ��ǰһ����㣬��һ��ָ��nullptr
			pre = current;//preָ��ǰ���
			current = next;//currentָ����һ�����
		} while (current != head);

		//ѭ��������pre������ԭ����β��㣬currentָ��ԭ����ͷ���
		head->next = pre;//������ͷ����ָ����ָ��β���
		head = pre;//β������ڵ�λ�ñ�Ϊͷ���	
	}
	//�����������ͷ������ڴ�
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

// ������
int main()
{
	CircularLinkedList list;

	int choice, value, position;

	while (true)
	{
		cout << "1. ��ͷ������ڵ�" << endl;
		cout << "2. ��β������ڵ�" << endl;
		cout << "3. ɾ���ڵ�" << endl;
		cout << "4. �޸Ľڵ�" << endl;
		cout << "5. ���ҽڵ�" << endl;
		cout << "6. ��ӡ����" << endl;
		cout << "7. ��������" << endl;
		cout << "8. �˳�" << endl;
		cout << "���������ѡ��: ";
		cin >> choice;

		switch (choice) {
		case 1:
			cout << "������Ҫ�����ֵ: ";
			cin >> value;
			list.insertAtHead(value);
			system("pause");
			system("cls");
			break;
		case 2:
			cout << "������Ҫ�����ֵ: ";
			cin >> value;
			list.insertAtTail(value);
			system("pause");
			system("cls");
			break;
		case 3:
			cout << "������Ҫɾ����ֵ: ";
			cin >> value;
			list.deleteValue(value);
			system("pause");
			system("cls");
			break;
		case 4:
			cout << "������Ҫ�޸ĵ�λ�ú���ֵ: ";
			cin >> position >> value;
			list.updateValue(position, value);
			system("pause");
			system("cls");
			break;
		case 5:
			cout << "������Ҫ���ҵ�ֵ: ";
			cin >> value;
			if (list.searchValue(value)) {
				cout << "�ҵ��ڵ�: " << value << endl;
			}
			else {
				cout << "δ�ҵ��ڵ�: " << value << endl;
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
			cout << "���������á�" << endl;
			system("pause");
			system("cls");
			break;
		case 8:
			return 0;
		default:
			cout << "��Чѡ�������ԡ�" << endl;
		}
	}

	system("pause");
	return 0;
}
