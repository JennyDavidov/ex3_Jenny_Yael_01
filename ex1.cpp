//
// Created by yael6 on 10/11/2019.
//

#include <utility>
#include <string>
#include "ex1.h"
#include "Expression.h"

BinaryOperator::BinaryOperator(Expression* _left, Expression* _right) {
    this->left = _left;
    this->right = _right;
}
BinaryOperator::~BinaryOperator() {
    if (right != nullptr) {
        delete right;
    }
    if (left != nullptr) {
        delete left;
    }
}
Expression *BinaryOperator::getRight() const {
    return right;
}
Expression *BinaryOperator::getLeft() const {
    return left;
}
void BinaryOperator::setLeft(Expression *leftExp) {
    BinaryOperator::left = leftExp;
}
void BinaryOperator::setRight(Expression *rightExp) {
    BinaryOperator::right = rightExp;
}

Plus::Plus(Expression *_left, Expression *_right) : BinaryOperator(_left, _right) {
    this->setLeft(_left);
    this->setRight(_right);
}
Plus::~Plus() {}
double Plus::calculate() {
    return (this->getLeft()->calculate() + this->getRight()->calculate());
}

Minus::Minus(Expression *_left, Expression *_right) : BinaryOperator(_left, _right) {
    this->setRight(_right);
    this->setLeft(_left);
}
Minus::~Minus() {
}
double Minus::calculate() {
    return (this->getLeft()->calculate() - this->getRight()->calculate());
}

Mul::Mul(Expression *_left, Expression *_right) : BinaryOperator(_left, _right) {
    this->setLeft(_left);
    this->setRight(_right);
}
Mul::~Mul() {
}
double Mul::calculate() {
    return (this->getLeft()->calculate() * this->getRight()->calculate());
}

Div::Div(Expression *_left, Expression *_right) : BinaryOperator(_left, _right) {
    this->setRight(_right);
    this->setLeft(_left);
}
Div::~Div() {
}
double Div::calculate() {
    if (this->getRight()->calculate() == 0) {
        throw "Exception, division by zero";
    } else {
        return (this->getLeft()->calculate() / this->getRight()->calculate());
    }
}

UnaryOperator::UnaryOperator(Expression* expression) {
    this->exp = expression;
}
UnaryOperator::~UnaryOperator() {
    if (exp != nullptr) {
        delete exp;
    }
}
Expression *UnaryOperator::getExp() const {
    return exp;
}
void UnaryOperator::setExp(Expression *expression) {
    UnaryOperator::exp = expression;
}

UPlus::UPlus(Expression *expression) : UnaryOperator(expression) {
    this->setExp(expression);
}
UPlus::~UPlus() {
}
double UPlus::calculate() {
    return this->getExp()->calculate();
}
UMinus::UMinus(Expression *expression) : UnaryOperator(expression) {
    this->setExp(expression);
}
UMinus::~UMinus() {
}
double UMinus::calculate() {
    return (-1 * this->getExp()->calculate());
}

Variable::Variable(string _name, double _value) {
        this->sim = std::move(_name);
        this->value = _value;
        this->direction = -1;
}
Variable::~Variable() {
}
Variable& Variable::operator++(int) {
    this->value++;
    return *this;
}
Variable& Variable::operator++() {
    this->value++;
    return *this;
}
Variable& Variable::operator--(int) {
    this->value--;
    return *this;
}
Variable& Variable::operator--() {
    this->value--;
    return *this;
}
Variable& Variable::operator+=(double val) {
    this->value = (this->value + val);
    return *this;
}
Variable& Variable::operator-=(double val) {
    this->value = (this->value - val);
    return *this;
}
string Variable::getName() const {
    return sim;
}
double Variable::getValue() const {
    return value;
}
void Variable::setName(string _name) {
    Variable::sim = std::move(_name);
}
void Variable::setValue(double _value) {
    Variable::value = _value;
}
double Variable::calculate() {
    return this->getValue();
}

//bool Variable::checkName(string sim) {
//    if (isalpha(sim[0]) || sim[0] == '_') {
//        for (unsigned i=1; i < sim.size(); i++) {
//            if ((!isalpha(sim[i])) && (!isdigit(sim[i])) && (sim[i] != '_')) {
//                return false;
//            }
//        }
//    }
//    else {
//        return false;
//    }
//    return true;
//}

Value::Value(double val) {
    this->value = val;
}
Value::~Value() {
}
double Value::getValue() const {
    return value;
}
double Value::calculate() {
    return this->getValue();
}

void Variable::setDirection(int direction1) {
    this->direction = direction1;
}

int Variable::getDirection() const {
    return this->direction;
}
