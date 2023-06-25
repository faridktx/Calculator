#include <iostream>
#include <stack>
#include <sstream>
#include <iomanip>
#include <cmath>

using namespace std;

// Function to check if a character is an operator
bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

// Function to get the precedence of an operator
int getPrecedence(char op) {
    if (op == '^')
        return 3;
    else if (op == '*' || op == '/')
        return 2;
    else if (op == '+' || op == '-')
        return 1;
    else
        return 0;
}

// Function to perform arithmetic operations
double performOperation(double a, double b, char op) {
    switch (op) {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            return a / b;
        case '^':
            return pow(a, b);
        default:
            return 0;
    }
}

// Function to evaluate the mathematical expression
double evaluateExpression(string expression) {
    stack<double> values;
    stack<char> operators;

    for (int i = 0; i < expression.length(); i++) {
        if (expression[i] == ' ')
            continue;

        // If the character is a digit, extract the number
        if (isdigit(expression[i])) {
            string num;
            while (i < expression.length() && (isdigit(expression[i]) || expression[i] == '.'))
                num += expression[i++];
            i--;
            values.push(stod(num));
        }
            // If the character is an opening parenthesis, push it to the operator stack
        else if (expression[i] == '(') {
            operators.push(expression[i]);
        }
            // If the character is a closing parenthesis, evaluate the expression inside it
        else if (expression[i] == ')') {
            while (!operators.empty() && operators.top() != '(') {
                double val2 = values.top();
                values.pop();

                double val1 = values.top();
                values.pop();

                char op = operators.top();
                operators.pop();

                values.push(performOperation(val1, val2, op));
            }

            if (!operators.empty())
                operators.pop();
        }
            // If the character is an operator, perform the operations based on precedence
        else if (isOperator(expression[i])) {
            while (!operators.empty() && getPrecedence(operators.top()) >= getPrecedence(expression[i])) {
                double val2 = values.top();
                values.pop();

                double val1 = values.top();
                values.pop();

                char op = operators.top();
                operators.pop();

                values.push(performOperation(val1, val2, op));
            }

            operators.push(expression[i]);
        }
    }

    // Perform remaining operations
    while (!operators.empty()) {
        double val2 = values.top();
        values.pop();

        double val1 = values.top();
        values.pop();

        char op = operators.top();
        operators.pop();

        values.push(performOperation(val1, val2, op));
    }

    return values.top();
}

void printBorder(int width) {
    cout << "+";
    for (int i = 0; i < width - 2; i++)
        cout << "-";
    cout << "+" << endl;
}

void printLine(string line, int width) {
    cout << "| ";
    int padding = (width - 4 - line.length()) / 2;
    int extraPadding = (width - 4 - line.length()) % 2;
    for (int i = 0; i < padding; i++)
        cout << " ";
    cout << line;
    for (int i = 0; i < padding + extraPadding; i++)
        cout << " ";
    cout << " |" << endl;
}

int main() {
    string expression;
    char choice;

    cout << fixed;

    do {
        cout << "Enter a mathematical expression: ";
        getline(cin, expression);

        double result = evaluateExpression(expression);

        int width = max(static_cast<int>(expression.length()) + 6, 20);

        printBorder(width);
        printLine(expression, width);
        printBorder(width);
        cout << setprecision(6); // Set decimal precision to 6
        printLine("Result: " + to_string(result), width);
        printBorder(width);

        cout << "Do you want to continue (y/n)? ";
        cin >> choice;
        cin.ignore(); // Ignore the remaining newline character

        cout << endl;
    } while (choice == 'y' || choice == 'Y');

    return 0;
}