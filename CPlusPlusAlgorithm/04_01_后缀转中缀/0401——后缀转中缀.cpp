#include <iostream>
#include <stack>
#include <string>
using namespace std;

// �ж���������ȼ�
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0; // ���ź������ַ����ȼ����[[3,19]]
}

string infixToPostfix(string infix) {
    stack<char> st;
    string postfix;
    
    for (int i = 0; i < infix.length(); i++) {
        cout << "��׺���ʽ: " << infix[i] << endl;
    }
        

    for (int i = 0; i < infix.length(); i++) {
        char c = infix[i];

        // �����λ��
        if (isdigit(c)) {
            while (i < infix.length() && isdigit(infix[i])) {
                postfix += infix[i++];
            }
            postfix += ' '; // ���ֺ�ӿո�ָ�[[7,18]]
            i--; // ����ѭ������
        }
        // ������ֱ����ջ
        else if (c == '(') {
            st.push(c);
        }
        // �����Ŵ���
        else if (c == ')') {
            while (!st.empty() && st.top() != '(') {
                postfix += st.top();
                postfix += ' ';
                st.pop();
            }
            st.pop(); // ����������[[6,19]]
        }
        // ���������
        else if (c == '+' || c == '-' || c == '*' || c == '/') {
            while (!st.empty() && precedence(c) <= precedence(st.top())) {
                postfix += st.top();
                postfix += ' ';
                st.pop();
            }
            st.push(c);// [[16, 19]]
        }
    }

    // ����ʣ�������
    while (!st.empty()) {
        postfix += st.top();
        postfix += ' ';
        st.pop();
    }

    return postfix;
}

int main() {
    string expr = "9+(3-1111)*3+8/2";
    cout << "��׺���ʽ: " << expr << endl;
    cout << "��׺���ʽ: " << infixToPostfix(expr) << endl;
    // �����9 3 11 - 3 * + 8 2 / + [[7]]
    return 0;
}
