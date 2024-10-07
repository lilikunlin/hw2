#include <iostream>
#include <stack>
#include <queue>
#include <string>
#include <cctype>
#include <cmath>

using namespace std;

// 檢查運算式的括號是否對稱
bool areParenthesesBalanced(const string& expression) {
    stack<char> parentheses;
    for (char ch : expression) {
        if (ch == '(') {
            parentheses.push(ch);
        }
        else if (ch == ')') {
            if (parentheses.empty()) {
                return false; // 多了一個右括號
            }
            parentheses.pop();
        }
    }
    return parentheses.empty(); // 確認所有左括號是否被配對
}

// 檢查運算符的優先級
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// 執行基本的數學運算
int applyOperation(int a, int b, char op) {
    switch (op) {
    case '+': return a + b;
    case '-': return a - b;
    case '*': return a * b;
    case '/': return a / b;
    default: return 0;
    }
}

// 將中序運算式轉換為後序表達式
string infixToPostfix(const string& expression) {
    stack<char> operators;
    queue<char> output;
    for (char ch : expression) {
        if (isdigit(ch)) {
            output.push(ch); // 如果是數字直接加入輸出
        }
        else if (ch == '(') {
            operators.push(ch); // 如果是左括號，壓入棧
        }
        else if (ch == ')') {
            // 如果是右括號，彈出所有操作符直到遇到左括號
            while (!operators.empty() && operators.top() != '(') {
                output.push(operators.top());
                operators.pop();
            }
            operators.pop(); // 彈出左括號
        }
        else {
            // 如果是操作符，根據優先級彈出操作符
            while (!operators.empty() && precedence(operators.top()) >= precedence(ch)) {
                output.push(operators.top());
                operators.pop();
            }
            operators.push(ch);
        }
    }
    // 彈出剩餘的操作符
    while (!operators.empty()) {
        output.push(operators.top());
        operators.pop();
    }

    string postfix = "";
    while (!output.empty()) {
        postfix += output.front();
        output.pop();
    }
    return postfix;
}

// 計算後序表達式
int evaluatePostfix(const string& postfix) {
    stack<int> values;
    for (char ch : postfix) {
        if (isdigit(ch)) {
            values.push(ch - '0'); // 將字符轉為數字
        }
        else {
            int val2 = values.top(); values.pop();
            int val1 = values.top(); values.pop();
            values.push(applyOperation(val1, val2, ch)); // 執行運算
        }
    }
    return values.top();
}

int main() {
    string expression;
    char continueTest;

    do {
        cout << "請輸入運算式: ";
        cin >> expression;

        // 檢查括號是否對稱
        if (!areParenthesesBalanced(expression)) {
            cout << "此運算式的括號不對稱，無法繼續運算。" << endl;
        }
        else {
            // 括號對稱，開始處理
            cout << "A. " << expression << " 運算式的左右括號對稱" << endl;

            // 轉換為後序表達式
            string postfix = infixToPostfix(expression);
            cout << "B. " << expression << " 運算式的後序表式法為：" << postfix << endl;

            // 計算結果
            int result = evaluatePostfix(postfix);
            cout << "C. " << expression << " 運算式的運算結果為：" << result << endl;
        }

        // 詢問是否繼續
        cout << "是否繼續測試？ (Y/N): ";
        cin >> continueTest;

    } while (continueTest == 'Y' || continueTest == 'y');

    return 0;
}
