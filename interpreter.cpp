//
// Created by yael6 on 13/11/2019.
//
#include "interpreter.h"
#include <string>
#include <cstring>
#include "ex1.h"
#include "Expression.h"
#include <queue>
#include <stack>

Interpreter::Interpreter() {
}

Interpreter::~Interpreter() {}

void Interpreter::setVariables(string str) {
    map<string, string>::iterator it;
    unsigned p = 0;
    while (p < str.size()) {
        string subString = str.substr(p);
        //separating variables
        size_t endOfNum = subString.find_first_of(" ;");
        if (endOfNum == string::npos) {
            endOfNum = (str.size() - p);
        }
        string variable = str.substr(p,endOfNum);
        //separating between name and value
        size_t endOfNum1 = variable.find_first_of('=');
        if (endOfNum1 == string::npos) {
            throw "Exception, wrong string in set variables";
        }
        //name of variable
        string name = variable.substr(0,endOfNum1);
        //check if it's an illegal name
//        if (!Variable::checkName(name)) {
//            throw "Exception, wrong variable name";
//        } else {
            //value of variable
            string value = variable.substr(endOfNum1 + 1, (variable.size() - endOfNum1 - 1));
            for (unsigned j = 0; j < value.size(); j++) {
                //check if it's an illegal value
                if (!isdigit(value[j])) {
                    if (value[j] == '-') {
                        if ((isdigit(value[j+1])) && (j != (value.size() -1))) {
                            continue;
                        }
                    }
                    if (value[j] == '.') {
                        if ((isdigit(value[j-1])) && (isdigit(value[j+1])) && (j != 0) && (j != (value.size() -1))) {
                            continue;
                        }
                    }
                    throw "Exception, not a number assigned to variable";
                }
            }
            if (!variables.empty()) {
                for (it = variables.begin(); it != variables.end(); ++it) {
                    //updating variable value
                    if (variables.find(name) != variables.end()) {
                        (*it).second = value;
                        break;
                    } else {
                        //creating variables
                        variables.insert(pair<string, string>(name, value));
                        break;
                    }
                }
            }
            else {
                //first variable
                variables.insert(pair<string, string>(name, value));
            }
        //}
        p = p + (endOfNum + 1);
    }
}

Expression *Interpreter::interpret(string string1) {
    map<::string, ::string> ::iterator it1;
    queue<::string> output;
    stack<::string> operators;
    stack<double> numbers;
    Expression *exp = nullptr;
    Expression *ex1 = nullptr;
    //infix to postfix
    unsigned i = 0;
    while (i < string1.size()) {
        //if it's a number or variable
        if (isdigit(string1[i]) || isalpha(string1[i])) {
            string sub = string1.substr(i);
            size_t endOfNum = sub.find_first_of("+-*/()");
            if (endOfNum == string::npos) {
                endOfNum = (string1.size() - i);
            }
            string number = string1.substr(i,endOfNum);
            if (isdigit(string1[i])) {
                output.push(number);
            }
            //find the value of the variable
            else {
                it1 = variables.find(number);
                if (it1 != variables.end()) {
                    if ((*it1).second[0] == '-') {
                        output.push((*it1).second.substr(1));
                        output.push("'-'");
                    } else {
                        output.push((*it1).second);
                    }
                }
                else {
                    throw "Exception, variable doesn't exist in this interpreter";
                }
            }
            i += endOfNum;
        }
        //if it's operator
        else if ((string1[i] == '+') ||(string1[i] == '-') || (string1[i] == '*') || (string1[i] == '/')) {
            //checking illegal math expression
            if ((i != 0) && ((string1[i - 1] == '+') ||(string1[i - 1] == '-') || (string1[i - 1] == '*') || (string1[i - 1] == '/'))) {
                throw "Exception, wrong infix expression, operator next to another";
            }
            //if it's an operator with priority
            while(((isEqualOp(operators, string1[i])) || (isHighOp(operators, string1[i]))) && ((operators.top() != "("))) {
                string c = operators.top();
                operators.pop();
                output.push(c);
            }
            //if there is a negative number in the expression
            if ((string1[i] == '-') && (isdigit(string1[i+1]) && ((i+1) < string1.size()))
            && (i != 0) && (!isdigit(string1[i-1])) && (!isalpha(string1[i-1]))) {
                if ((!operators.empty()) && (operators.top() == ":")) {
                    operators.pop();
                    operators.push("'-'");
                    operators.push(":");
                }
                else {
                    operators.push("'-'");
                }
            }
            else {
                string op;
                //char to string
                op.assign(1, string1[i]);
                if ((!operators.empty()) && (operators.top() == ":")) {
                    operators.pop();
                    operators.push(op);
                    operators.push(":");
                }
                else {
                    operators.push(op);
                }
            }
            i++;
        }
        //if it's left paren
        else if (string1[i] == '(') {
            if ((i != 0) && ((string1[i - 1] == '+') || (string1[i - 1] == '-') || (string1[i - 1] == '*') || (string1[i - 1] == '/'))) {
                if ((i >= 2) && (string1[i-2] == ')')) {
                    //there are two expressions in one - ":" is the symbol for an inner expression
                    operators.push(":");
                }
                if ((i != 0) && ((string1[i - 1] == '+') || (string1[i - 1] == '-'))) {
                    //when it's a unary expression
                    if ((i == 1) || ((string1[i - 2] == '(') && (i >= 2))) {
                        operators.pop();
                        if ((!operators.empty()) && (operators.top() == ":")) {
                            operators.pop();
                            operators.push("(");
                            //UPlus
                            if (string1[i - 1] == '+') {
                                operators.push("'+'");
                            } //UMinus
                            else {
                                operators.push("'-'");
                            }
                            operators.push(":");
                        }
                        else {
                            operators.push("(");
                            if (string1[i - 1] == '+') {
                                operators.push("'+'");
                            } else {
                                operators.push("'-'");
                            }
                        }
                    }
                    else {
                        if ((!operators.empty()) && (operators.top() == ":")) {
                            operators.pop();
                            operators.push("(");
                            operators.push(":");
                        }
                        else {
                            operators.push("(");
                        }
                    }
                }
                else {
                    if ((!operators.empty()) && (operators.top() == ":")) {
                        operators.pop();
                        operators.push("(");
                        operators.push(":");
                    }
                    else {
                        operators.push("(");
                    }
                }
            }
            else {
                if ((!operators.empty()) && (operators.top() == ":")) {
                    operators.pop();
                    operators.push("(");
                    operators.push(":");
                } else {
                    operators.push("(");
                }
            }
            i++;
        }
        //if it's a right paren
        else if (string1[i] == ')') {
            if (operators.empty()) {
                throw "Exception, wrong infix expression, num of paren isn't equal";
            }
            while (operators.top() != "(") {
                output.push(operators.top());
                operators.pop();
            }
            if (operators.top() == "(") {
                operators.pop();
            }
            i++;
        }
    }
    //when we finish to read the string and there are still operators in stack
    while (!operators.empty()) {
        if (operators.top() == "(") {
            throw "Exception, wrong infix expression, num of paren isn't equal";
        }
        output.push(operators.top());
        operators.pop();
    }
    //postfix to expression
    while (!output.empty()) {
        //if it's a number, push it to the numbers stack
        if (isdigit(output.front()[0])) {
            numbers.push(stod(output.front()));
            output.pop();
        }
        //if it's an operator, make the relevant expression
        else {
            //UPlus expression
            if (output.front() == "'+'") {
                if (exp == nullptr) {
                    exp = new UPlus(new Value(numbers.top()));
                    numbers.pop();
                } else {
                    if (ex1 != nullptr) {
                        exp = new UPlus(ex1);
                        ex1 = nullptr;
                    }
                    else {
                        exp = new UPlus(exp);
                    }
                }
                output.pop();
            } //UMinus expression
            else if (output.front() == "'-'") {
                if (exp == nullptr) {
                    exp = new UMinus(new Value(numbers.top()));
                    numbers.pop();
                } else {
                    if (ex1 != nullptr) {
                        exp = new UMinus(ex1);
                        ex1 = nullptr;
                    }
                    else {
                        exp = new UMinus(exp);
                    }
                }
                output.pop();
            } //Plus binary expression
            else if (output.front() == "+") {
                if (exp == nullptr) {
                    double num1 = numbers.top();
                    numbers.pop();
                    double num2 = numbers.top();
                    numbers.pop();
                    exp = new Plus(new Value(num2), new Value(num1));
                }
                else {
                    if (ex1 != nullptr) {
                        exp = new Plus(exp, ex1);
                        ex1 = nullptr;
                    }
                    else {
                        double num = numbers.top();
                        numbers.pop();
                        exp = new Plus(new Value(num), exp);
                    }
                }
                output.pop();
            } //Minus binary expression
            else if (output.front() == "-") {
                if (exp == nullptr) {
                    double num1 = numbers.top();
                    numbers.pop();
                    double num2 = numbers.top();
                    numbers.pop();
                    exp = new Minus(new Value(num2), new Value(num1));
                }
                else {
                    if (ex1 != nullptr) {
                        exp = new Minus(exp, ex1);
                        ex1 = nullptr;
                    }
                    else {
                        double num = numbers.top();
                        numbers.pop();
                        exp = new Minus(new Value(num), exp);
                    }
                }
                output.pop();
            } //Mult binary expression
            else if (output.front() == "*") {
                if (exp == nullptr) {
                    double num1 = numbers.top();
                    numbers.pop();
                    double num2 = numbers.top();
                    numbers.pop();
                    exp = new Mul(new Value(num2), new Value(num1));
                }
                else {
                    if (ex1 != nullptr) {
                        exp = new Mul(exp, ex1);
                        ex1 = nullptr;
                    }
                    else {
                        double num = numbers.top();
                        numbers.pop();
                        exp = new Mul(new Value(num), exp);
                    }
                }
                output.pop();
            } //Div binary expression
            else if (output.front() == "/") {
                if (exp == nullptr) {
                    double num1 = numbers.top();
                    numbers.pop();
                    double num2 = numbers.top();
                    numbers.pop();
                    exp = new Div(new Value(num2), new Value(num1));
                }
                else {
                    if (ex1 != nullptr) {
                        exp = new Div(exp, ex1);
                        ex1 = nullptr;
                    }
                    else {
                        double num = numbers.top();
                        numbers.pop();
                        exp = new Div(new Value(num), exp);
                    }
                }
                output.pop();
            } //inner expression
            else if (output.front() == ":") {
                output.pop();
                ex1 = anotherExp(output, numbers, ex1);
            }
        }
    }
return exp;
}
bool Interpreter::isEqualOp(stack<string> s, char op) {
    if (!s.empty()) {
        if (((s.top() == "+") || (s.top() == "-")) && ((op == '+') || (op == '-'))) {
            return true;
        }
        else if (((s.top() == "*") || (s.top() == "/")) && ((op == '*') || (op == '/'))) {
            return true;
        }
    }
    return false;
}
bool Interpreter::isHighOp(stack<string> s, char op) {
    if (!s.empty()) {
        if (((s.top() == "*") || (s.top() == "/")) && ((op == '+') || (op == '-'))) {
            return true;
        }
        //the infix begin with a negative number
        else if ((s.top() == "'-'") && (s.size() == 1)) {
            return true;
        }
    }
    return false;
}

Expression *Interpreter::anotherExp(queue<string> &output, stack<double> &nums, Expression *ex1) {
    while (!output.empty()) {
        //unary expression
        if ((output.front() == "'-'") || (output.front() == "'+'")) {
            if (ex1 == nullptr) {
                if (output.front() == "'-'") {
                    ex1 = new UMinus(new Value(nums.top()));
                }
                else {
                    ex1 = new UPlus(new Value(nums.top()));
                }
                output.pop();
                nums.pop();
            }
            else {
                if (output.front() == "'-'") {
                    ex1 = new UMinus(ex1);
                }
                else {
                    ex1 = new UPlus(ex1);
                }
                output.pop();
            }
        }
        //binary expression
        else {
            if (ex1 != nullptr) {
                if (output.front() == "-") {
                    ex1 = new Minus(new Value(nums.top()), ex1);
                } else if (output.front() == "+") {
                    ex1 = new Plus(new Value(nums.top()), ex1);
                } else if (output.front() == "*") {
                    ex1 = new Mul(new Value(nums.top()), ex1);
                } else if (output.front() == "/") {
                    ex1 = new Div(new Value(nums.top()), ex1);
                }
                output.pop();
                nums.pop();
                return ex1;
            }
            else {
                double n1 = nums.top();
                nums.pop();
                double n2 = nums.top();
                nums.pop();
                if (output.front() == "-") {
                    ex1 = new Minus(new Value(n2), new Value(n1));
                } else if (output.front() == "+") {
                    ex1 = new Plus(new Value(n2), new Value(n1));
                } else if (output.front() == "*") {
                    ex1 = new Mul(new Value(n2), new Value(n1));
                } else if (output.front() == "/") {
                    ex1 = new Div(new Value(n2), new Value(n1));
                }
                output.pop();
                return ex1;
            }
        }
    }
    return ex1;
}

