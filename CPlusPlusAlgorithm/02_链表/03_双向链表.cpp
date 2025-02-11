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
			_head->_next = _tail;//头结点的后继指向尾结点
			_tail->_pre = _head;//尾结点的前驱指向头结点
		}
		//在头部进行插入
		void push_front(int data) {
			Node* newNode = new Node(data);//先命名一个新节点
			newNode->_pre = _head;//新结点的前驱指向头结点
			newNode->_next = _head->_next;//新结点的后继指向头结点的下一个节点
			//现在将这个结点的前驱后继两个指向这个结点
			_head->_next->_pre = newNode;//头结点的下一个节点的前驱指向新节点
			_head->_next = newNode;//头结点的后继指向新节点

			++_size;
		}
		//在尾部进行插入，尾结点一直在尾部
		void push_back(int data) {
			Node* newNode = new Node(data);
			newNode->_pre = _tail->_pre;//新结点的前驱指向尾结点的前驱
			newNode->_next = _tail;//新结点的后继指向尾结点
			//现在将这个结点的前驱后继两个指向这个结点
			_tail->_pre->_next = newNode;//尾结点的前驱的后继指向新结点
			_tail->_pre = newNode;//尾结点的前驱指向新结点

			++_size;

		}
		//在头部进行删除
		void pop_front() {
			if (size() > 0) {
				Node* pNode = _head->_next;//先找到头结点的下一个节点
				pNode->_next->_pre = _head;//头结点的下一个节点的前驱指向头结点
				_head->_next = pNode->_next;//头结点的后继指向头结点的下一个节点
				//最后删除并释放这个节点
				delete pNode;
				pNode = nullptr;
				--_size;
			}
			else {
				cout << "该链表为空，无法删除" << endl;
				return;
			}
		}
		//在尾部进行删除
		void pop_back() {
			if (size() > 0) {
				Node* pNode = _tail->_pre;//先找到尾结点的前一个节点
				pNode->_pre->_next = _tail;//尾结点的前一个节点的后继指向尾结点
				_tail->_pre = pNode->_pre;//尾结点的前驱指向尾结点的前一个节点

				delete pNode;
				pNode = nullptr;
				--_size;
			}
			else {
				cout << "该链表为空，无法删除" << endl;
				return;
			}
		}

		//在中间进行插入
		void insert(int pos, int data) {
			if (pos < 0 || pos > size()) {
				cout << "该位置异常，无法插入" << endl;
				return;
			}

			Node* pNode = _head;
			while (pos-- > 0) {//从头结点找到要插入的位置，
				pNode = pNode->_next;
			}
			
			Node* newNode = new Node(data);//新建一个节点，数据域为data，前驱后继现在为空
			//现在将新结点插入到pNode后面
			newNode->_pre = pNode;//新节点的前驱pNode
			newNode->_next = pNode->_next;//新节点的后继pNode的后一个节点
			//将断开之后的连上newNode
			pNode->_next->_pre = newNode;
			pNode->_next = newNode;

			++_size;
		}

		//在中间进行删除
		void erase(int data) {
			//先找有没有这个元素，有执行，没有不执行
			bool flag = find(data);
			if (flag) {
				Node* pNode = _head->_next;//从头结点后一个结点开始找
				while (pNode && pNode != _tail) {//pNode不为空且不是尾结点
					if (pNode->_data == data) {//找到这个元素
						Node* ptmp = pNode->_pre;//保存前一个节点
						pNode->_next->_pre = ptmp;//后一个节点的前驱指向前一个节点
						ptmp->_next = pNode->_next;//前一个节点的后继指向后一个节点

						delete pNode;
						pNode = nullptr;
						--_size;

						pNode = ptmp;
					}
					pNode = pNode->_next;
				}
			}
			else {
				cout << "该元素不在链表之中，无法删除" << endl;
				return;
			}
		}
		//查找是否有这个元素
		bool find(int data) {
			if (size() > 0) {
				Node* pNode = _head->_next;
				while (pNode && pNode != _tail) {//pNode不为空且不是尾结点
					if (data == pNode->_data) {
						return true;
					}
					pNode = pNode->_next;
				}

				return false;
			}
			else {
				cout << "该链表为空，无法查找" << endl;
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
				cout << "该链表为空，无法打印" << endl;
				return;
			}
		}
		//析构函数
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

	cout << endl << "在链表头部进行插入 :" << endl;
	lst.push_front(1);
	lst.push_front(3);
	lst.push_front(5);
	lst.display();

	cout << endl << "在链表尾部进行插入 :" << endl;
	lst.push_back(11);
	lst.push_back(33);
	lst.push_back(55);
	lst.display();

	cout << endl << "在链表头部进行删除 :" << endl;
	lst.pop_front();
	lst.display();

	cout << endl << "在链表尾部进行删除 :" << endl;
	lst.pop_back();
	lst.display();

	cout << endl << "查找元素 :" << endl;*/

	/*// bool flag = lst.find(100); 
	bool flag = lst.find(11);
	cout << "flag = " << flag << endl;

	cout << endl << "在中间进行插入" << endl;
	//lst.insert(10, 100); 
	lst.insert(2, 100);
	lst.display();

	cout << endl << "在中间进行删除" << endl;
	lst.erase(11);
	lst.display();
	return 0;
}
*/