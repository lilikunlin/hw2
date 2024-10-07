// 引入必要的標頭檔
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
    stack<char> s; // 使用堆疊來追蹤括號
    for (char ch : expr) {
        if (ch == '(') {
            s.push(ch); // 遇到左括號，推入堆疊
        } else if (ch == ')') {
            if (s.empty()) {
                return false; // 遇到右括號但堆疊為空，表示不對稱
            }
            s.pop(); // 遇到右括號，彈出堆疊頂端的左括號
        }
    }
    return s.empty(); // 最後檢查堆疊是否為空，為空表示對稱
}

// 判斷運算子優先順序
int precedence(char op) {
    if (op == '+' || op == '-') return 1; // 加減運算優先順序為1
    if (op == '*' || op == '/') return 2; // 乘除運算優先順序為2
    return 0; // 其他運算符號優先順序為0
}

// 中序轉後序
string infixToPostfix(const string &expr) {
    stack<char> s; // 使用堆疊來儲存運算子
    string postfix; // 儲存後序表式法
    for (char ch : expr) {
        if (isdigit(ch)) {
            postfix += ch; // 遇到數字，直接加入後序表式法
        } else if (ch == '(') {
            s.push(ch); // 遇到左括號，推入堆疊
        } else if (ch == ')') {
            while (!s.empty() && s.top() != '(') {
                postfix += s.top(); // 遇到右括號，彈出堆疊中的運算子直到遇到左括號
                s.pop();
            }
            s.pop(); // 彈出左括號
        } else {
            while (!s.empty() && precedence(s.top()) >= precedence(ch)) {
                postfix += s.top(); // 遇到運算子，彈出堆疊中優先順序較高或相同的運算子
                s.pop();
            }
            s.push(ch); // 推入當前運算子
        }
    }
    while (!s.empty()) {
        postfix += s.top(); // 將剩餘的運算子加入後序表式法
        s.pop();
    }
    return postfix; // 返回後序表式法
}

// 計算後序表式法的結果
int evaluatePostfix(const string &postfix) {
    stack<int> s; // 使用堆疊來儲存操作數
    for (char ch : postfix) {
        if (isdigit(ch)) {
            s.push(ch - '0'); // 遇到數字，轉換為整數後推入堆疊
        } else {
            int val2 = s.top(); s.pop(); // 彈出堆疊頂端的兩個操作數
            int val1 = s.top(); s.pop();
            switch (ch) {
                case '+': s.push(val1 + val2); break; // 加法運算
                case '-': s.push(val1 - val2); break; // 減法運算
                case '*': s.push(val1 * val2); break; // 乘法運算
                case '/': s.push(val1 / val2); break; // 除法運算
            }
        }
    }
    return s.top(); // 返回最終結果
}

int main() {
    string expr; // 儲存使用者輸入的運算式
    char cont = 'Y'; // 控制是否繼續測試
    while (toupper(cont) == 'Y') {
        cout << "請輸入運算式: ";
        cin >> expr; // 讀取使用者輸入的運算式

        if (!areParenthesesBalanced(expr)) {
            cout << expr << " 運算式的括號不對稱，無法繼續運算" << endl;
        } else {
            cout << expr << " 運算式的左右括號對稱" << endl;
            string postfix = infixToPostfix(expr); // 將中序表式法轉換為後序表式法
            cout << expr << " 運算式的後序表式法為: " << postfix << endl;
            int result = evaluatePostfix(postfix); // 計算後序表式法的結果
            cout << expr << " 運算式的運算結果為: " << result << endl;
        }

        cout << "是否繼續測試 (Y/N)? ";
        cin >> cont; // 讀取使用者是否繼續測試的選擇
    }
    return 0; // 結束程式
}
