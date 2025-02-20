#include <iostream>
#include <stack>
#include <string>
using namespace std;

// 判断运算符优先级
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0; // 括号和其他字符优先级最低[[3,19]]
}

string infixToPostfix(string infix) {
    stack<char> st;
    string postfix;
    
    for (int i = 0; i < infix.length(); i++) {
        cout << "中缀表达式: " << infix[i] << endl;
    }
        

    for (int i = 0; i < infix.length(); i++) {
        char c = infix[i];

        // 处理多位数
        if (isdigit(c)) {
            while (i < infix.length() && isdigit(infix[i])) {
                postfix += infix[i++];
            }
            postfix += ' '; // 数字后加空格分隔[[7,18]]
            i--; // 补偿循环自增
        }
        // 左括号直接入栈
        else if (c == '(') {
            st.push(c);
        }
        // 右括号处理
        else if (c == ')') {
            while (!st.empty() && st.top() != '(') {
                postfix += st.top();
                postfix += ' ';
                st.pop();
            }
            st.pop(); // 弹出左括号[[6,19]]
        }
        // 运算符处理
        else if (c == '+' || c == '-' || c == '*' || c == '/') {
            while (!st.empty() && precedence(c) <= precedence(st.top())) {
                postfix += st.top();
                postfix += ' ';
                st.pop();
            }
            st.push(c);// [[16, 19]]
        }
    }

    // 弹出剩余运算符
    while (!st.empty()) {
        postfix += st.top();
        postfix += ' ';
        st.pop();
    }

    return postfix;
}

int main() {
    string expr = "9+(3-1111)*3+8/2";
    cout << "中缀表达式: " << expr << endl;
    cout << "后缀表达式: " << infixToPostfix(expr) << endl;
    // 输出：9 3 11 - 3 * + 8 2 / + [[7]]
    return 0;
}
