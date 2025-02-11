#include<iostream>
using std::cout;
using std::endl;

struct Node {
	Node(int data = 0, Node* pre = nullptr, Node* next = nullptr)
		: _data(data)
		, _pre(pre)
		, _next(next) {
		cout << "Node(int=0,Node*=nullptr,node*=nullptr)" << endl;
	}
	~Node() {
		cout << "~Node()" << endl;
	}
	int _data;
	Node* _pre;
	Node* _next;
	};
class List {
	private:
		Node* _head;
		Node* _tail;
		int _size;
	public:
		List()
			: _head(new Node())
			, _tail(new Node())
			, _size(0) {
			cout << "List()" << endl;
			_head->_next = _tail;//ͷ���ĺ��ָ��β���
			_tail->_pre = _head;//β����ǰ��ָ��ͷ���
		}
		//��ͷ�����в���
		void push_front(int data) {
			Node* newNode = new Node(data);//������һ���½ڵ�
			newNode->_pre = _head;//�½���ǰ��ָ��ͷ���
			newNode->_next = _head->_next;//�½��ĺ��ָ��ͷ������һ���ڵ�
			//���ڽ��������ǰ���������ָ��������
			_head->_next->_pre = newNode;//ͷ������һ���ڵ��ǰ��ָ���½ڵ�
			_head->_next = newNode;//ͷ���ĺ��ָ���½ڵ�

			++_size;
		}
		//��β�����в��룬β���һֱ��β��
		void push_back(int data) {
			Node* newNode = new Node(data);
			newNode->_pre = _tail->_pre;//�½���ǰ��ָ��β����ǰ��
			newNode->_next = _tail;//�½��ĺ��ָ��β���
			//���ڽ��������ǰ���������ָ��������
			_tail->_pre->_next = newNode;//β����ǰ���ĺ��ָ���½��
			_tail->_pre = newNode;//β����ǰ��ָ���½��

			++_size;

		}
		//��ͷ������ɾ��
		void pop_front() {
			if (size() > 0) {
				Node* pNode = _head->_next;//���ҵ�ͷ������һ���ڵ�
				pNode->_next->_pre = _head;//ͷ������һ���ڵ��ǰ��ָ��ͷ���
				_head->_next = pNode->_next;//ͷ���ĺ��ָ��ͷ������һ���ڵ�
				//���ɾ�����ͷ�����ڵ�
				delete pNode;
				pNode = nullptr;
				--_size;
			}
			else {
				cout << "������Ϊ�գ��޷�ɾ��" << endl;
				return;
			}
		}
		//��β������ɾ��
		void pop_back() {
			if (size() > 0) {
				Node* pNode = _tail->_pre;//���ҵ�β����ǰһ���ڵ�
				pNode->_pre->_next = _tail;//β����ǰһ���ڵ�ĺ��ָ��β���
				_tail->_pre = pNode->_pre;//β����ǰ��ָ��β����ǰһ���ڵ�

				delete pNode;
				pNode = nullptr;
				--_size;
			}
			else {
				cout << "������Ϊ�գ��޷�ɾ��" << endl;
				return;
			}
		}

		//���м���в���
		void insert(int pos, int data) {
			if (pos < 0 || pos > size()) {
				cout << "��λ���쳣���޷�����" << endl;
				return;
			}

			Node* pNode = _head;
			while (pos-- > 0) {//��ͷ����ҵ�Ҫ�����λ�ã�
				pNode = pNode->_next;
			}
			
			Node* newNode = new Node(data);//�½�һ���ڵ㣬������Ϊdata��ǰ���������Ϊ��
			//���ڽ��½����뵽pNode����
			newNode->_pre = pNode;//�½ڵ��ǰ��pNode
			newNode->_next = pNode->_next;//�½ڵ�ĺ��pNode�ĺ�һ���ڵ�
			//���Ͽ�֮�������newNode
			pNode->_next->_pre = newNode;
			pNode->_next = newNode;

			++_size;
		}

		//���м����ɾ��
		void erase(int data) {
			//������û�����Ԫ�أ���ִ�У�û�в�ִ��
			bool flag = find(data);
			if (flag) {
				Node* pNode = _head->_next;//��ͷ����һ����㿪ʼ��
				while (pNode && pNode != _tail) {//pNode��Ϊ���Ҳ���β���
					if (pNode->_data == data) {//�ҵ����Ԫ��
						Node* ptmp = pNode->_pre;//����ǰһ���ڵ�
						pNode->_next->_pre = ptmp;//��һ���ڵ��ǰ��ָ��ǰһ���ڵ�
						ptmp->_next = pNode->_next;//ǰһ���ڵ�ĺ��ָ���һ���ڵ�

						delete pNode;
						pNode = nullptr;
						--_size;

						pNode = ptmp;
					}
					pNode = pNode->_next;
				}
			}
			else {
				cout << "��Ԫ�ز�������֮�У��޷�ɾ��" << endl;
				return;
			}
		}
		//�����Ƿ������Ԫ��
		bool find(int data) {
			if (size() > 0) {
				Node* pNode = _head->_next;
				while (pNode && pNode != _tail) {//pNode��Ϊ���Ҳ���β���
					if (data == pNode->_data) {
						return true;
					}
					pNode = pNode->_next;
				}

				return false;
			}
			else {
				cout << "������Ϊ�գ��޷�����" << endl;
				return false;
			}
		}

		void display() const {
			if (size() > 0) {
				Node* pNode = _head->_next;
				while (pNode && pNode != _tail) {
					cout << pNode->_data << "  ";
					pNode = pNode->_next;
				}
				cout << endl;
			}
			else {
				cout << "������Ϊ�գ��޷���ӡ" << endl;
				return;
			}
		}
		//��������
		~List() {
			cout << "~List()" << endl;
			Node* deleteNode = _head->_next;
			while (deleteNode) {
				Node* ptmp = deleteNode->_next;
				delete deleteNode;
				deleteNode = nullptr;
				deleteNode = ptmp;
			}
			delete _head;
			_head = nullptr;
		}

		int size() const {
			return _size;
		}

};
/*int main(int argc, char** argv) {
	List lst;
	lst.display();

	cout << endl << "������ͷ�����в��� :" << endl;
	lst.push_front(1);
	lst.push_front(3);
	lst.push_front(5);
	lst.display();

	cout << endl << "������β�����в��� :" << endl;
	lst.push_back(11);
	lst.push_back(33);
	lst.push_back(55);
	lst.display();

	cout << endl << "������ͷ������ɾ�� :" << endl;
	lst.pop_front();
	lst.display();

	cout << endl << "������β������ɾ�� :" << endl;
	lst.pop_back();
	lst.display();

	cout << endl << "����Ԫ�� :" << endl;*/

	/*// bool flag = lst.find(100); 
	bool flag = lst.find(11);
	cout << "flag = " << flag << endl;

	cout << endl << "���м���в���" << endl;
	//lst.insert(10, 100); 
	lst.insert(2, 100);
	lst.display();

	cout << endl << "���м����ɾ��" << endl;
	lst.erase(11);
	lst.display();
	return 0;
}
*/