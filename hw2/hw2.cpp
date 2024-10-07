#include <iostream>
#include <stack>
#include <queue>
#include <string>
#include <cctype>  // 提供 isdigit 函數來檢查是否為數字
#include <cmath>   // 提供數學運算的函數

using namespace std;

// 檢查運算式的括號是否對稱
// 使用stack來追蹤左右括號的數量是否相等
bool areParenthesesBalanced(const string& expression) {
    stack<char> parentheses;  // 用來存放左括號 '('

    // 遍歷每一個字元
    for (char ch : expression) {
        // 如果是左括號，將它壓入stack中
        if (ch == '(') {
            parentheses.push(ch);
        }
        // 如果是右括號
        else if (ch == ')') {
            // 如果stack為空，意味著右括號比左括號多，返回false
            if (parentheses.empty()) {
                return false;
            }
            // 否則彈出一個左括號，表示匹配了一對括號
            parentheses.pop();
        }
    }
    // 最後如果stack為空，表示括號完全匹配，返回true
    return parentheses.empty();
}

// 檢查運算符的優先級
// '+' 和 '-' 的優先級為1， '*' 和 '/' 的優先級為2
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;  // 非運算符號返回0
}

// 執行基本的數學運算
// 依據運算符來進行對應的數學操作
int applyOperation(int a, int b, char op) {
    switch (op) {
    case '+': return a + b;   // 加法
    case '-': return a - b;   // 減法
    case '*': return a * b;   // 乘法
    case '/': return a / b;   // 除法 (假設輸入不會導致除以0)
    default: return 0;        // 默認返回0，應該不會進入這個情況
    }
}

// 將中序運算式轉換為後序表達式 (逆波蘭表示法)
// 使用stack來處理運算符，將輸出後序表達式的字元串
string infixToPostfix(const string& expression) {
    stack<char> operators;  // 用來存放操作符的棧
    queue<char> output;     // 用來存放最終輸出的後序表達式的隊列

    // 遍歷整個輸入的運算式
    for (char ch : expression) {
        // 如果是數字，直接加入到輸出的隊列中
        if (isdigit(ch)) {
            output.push(ch);
        }
        // 如果是左括號，壓入stack中
        else if (ch == '(') {
            operators.push(ch);
        }
        // 如果是右括號，將stack中的運算符彈出，直到遇到左括號
        else if (ch == ')') {
            while (!operators.empty() && operators.top() != '(') {
                output.push(operators.top());
                operators.pop();
            }
            operators.pop();  // 最後彈出左括號 '('
        }
        // 如果是運算符，根據其優先級處理
        else {
            // 如果當前運算符的優先級小於等於stack頂部的運算符，則彈出stack頂部的運算符
            while (!operators.empty() && precedence(operators.top()) >= precedence(ch)) {
                output.push(operators.top());
                operators.pop();
            }
            // 將當前運算符壓入stack中
            operators.push(ch);
        }
    }

    // 最後將stack中剩餘的運算符加入到輸出隊列中
    while (!operators.empty()) {
        output.push(operators.top());
        operators.pop();
    }

    // 將隊列中的後序表達式轉換為字串
    string postfix = "";
    while (!output.empty()) {
        postfix += output.front();
        output.pop();
    }
    return postfix;  // 返回後序表達式
}

// 計算後序表達式的結果
// 使用stack來處理數字與運算符，逐步計算結果
int evaluatePostfix(const string& postfix) {
    stack<int> values;  // 用來存放數字的棧

    // 遍歷整個後序表達式
    for (char ch : postfix) {
        // 如果是數字，將其壓入stack中
        if (isdigit(ch)) {
            values.push(ch - '0');  // 將字符轉為對應的數字 (例如 '3' 轉為 3)
        }
        // 如果是運算符，取出棧頂的兩個數字，進行對應的運算
        else {
            int val2 = values.top(); values.pop();  // 第二個數
            int val1 = values.top(); values.pop();  // 第一個數
            // 計算結果並將結果壓入stack中
            values.push(applyOperation(val1, val2, ch));
        }
    }
    // 最後棧頂的值就是最終的計算結果
    return values.top();
}

int main() {
    string expression;  // 用來存放使用者輸入的運算式
    char continueTest;  // 用來判斷是否繼續測試

    // 循環讓使用者重複測試，直到使用者選擇退出
    do {
        // 讀取使用者輸入的運算式
        cout << "請輸入運算式: ";
        cin >> expression;

        // 檢查括號是否對稱
        if (!areParenthesesBalanced(expression)) {
            // 如果括號不對稱，輸出錯誤訊息
            cout << "此運算式的括號不對稱，無法繼續運算。" << endl;
        }
        else {
            // 如果括號對稱，開始處理運算式
            cout << "A. " << expression << " 運算式的左右括號對稱" << endl;

            // 將中序表達式轉換為後序表達式
            string postfix = infixToPostfix(expression);
            cout << "B. " << expression << " 運算式的後序表式法為：" << postfix << endl;

            // 計算後序表達式的結果
            int result = evaluatePostfix(postfix);
            cout << "C. " << expression << " 運算式的運算結果為：" << result << endl;
        }

        // 詢問使用者是否繼續測試
        cout << "是否繼續測試？ (Y/N): ";
        cin >> continueTest;

    } while (continueTest == 'Y' || continueTest == 'y');  // 當使用者輸入 'Y' 或 'y' 時繼續執行

    return 0;
}
