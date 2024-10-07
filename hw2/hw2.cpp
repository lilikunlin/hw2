// hw2.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
    #include <iostream>
    #include <stack>
    #include <string>
    #include <cctype>
    #include <sstream>
    #include <vector>
    #include <algorithm>

    using namespace std;

    // 檢查括號是否對稱
    bool areParenthesesBalanced(const string &expr) {
        stack<char> s;
        for (char ch : expr) {
            if (ch == '(') {
                s.push(ch);
            } else if (ch == ')') {
                if (s.empty()) {
                    return false;
                }
                s.pop();
            }
        }
        return s.empty();
    }

    // 判斷運算子優先順序
    int precedence(char op) {
        if (op == '+' || op == '-') return 1;
        if (op == '*' || op == '/') return 2;
        return 0;
    }

    // 中序轉後序
    string infixToPostfix(const string &expr) {
        stack<char> s;
        string postfix;
        for (char ch : expr) {
            if (isdigit(ch)) {
                postfix += ch;
            } else if (ch == '(') {
                s.push(ch);
            } else if (ch == ')') {
                while (!s.empty() && s.top() != '(') {
                    postfix += s.top();
                    s.pop();
                }
                s.pop();
            } else {
                while (!s.empty() && precedence(s.top()) >= precedence(ch)) {
                    postfix += s.top();
                    s.pop();
                }
                s.push(ch);
            }
        }
        while (!s.empty()) {
            postfix += s.top();
            s.pop();
        }
        return postfix;
    }

    // 計算後序表式法的結果
    int evaluatePostfix(const string &postfix) {
        stack<int> s;
        for (char ch : postfix) {
            if (isdigit(ch)) {
                s.push(ch - '0');
            } else {
                int val2 = s.top(); s.pop();
                int val1 = s.top(); s.pop();
                switch (ch) {
                    case '+': s.push(val1 + val2); break;
                    case '-': s.push(val1 - val2); break;
                    case '*': s.push(val1 * val2); break;
                    case '/': s.push(val1 / val2); break;
                }
            }
        }
        return s.top();
    }

    int main() {
        string expr;
        char cont = 'Y';
        while (toupper(cont) == 'Y') {
            cout << "請輸入運算式: ";
            cin >> expr;

            if (!areParenthesesBalanced(expr)) {
                cout << expr << " 運算式的括號不對稱，無法繼續運算" << endl;
            } else {
                cout << expr << " 運算式的左右括號對稱" << endl;
                string postfix = infixToPostfix(expr);
                cout << expr << " 運算式的後序表式法為: " << postfix << endl;
                int result = evaluatePostfix(postfix);
                cout << expr << " 運算式的運算結果為: " << result << endl;
            }

            cout << "是否繼續測試 (Y/N)? ";
            cin >> cont;
        }
        return 0;
    }


