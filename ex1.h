//
// Created by yael6 on 10/11/2019.
//

#ifndef EX1_EX1_H
#define EX1_EX1_H

#include "Expression.h"
#include "interpreter.h"
#include <string>

using namespace std;

class BinaryOperator : public Expression{
protected:
    Expression* left = nullptr;
    Expression* right = nullptr;
public:
    BinaryOperator(Expression* _left, Expression* _right);
    virtual ~BinaryOperator();

    Expression *getRight() const;
    Expression *getLeft() const;
    void setLeft(Expression *leftExp);
    void setRight(Expression *rightExp);
};
class Plus : public BinaryOperator{
public:
    Plus(Expression* _left, Expression* _right);
    double calculate();
    virtual ~Plus();
};
class Minus : public BinaryOperator{
public:
    Minus(Expression *_left, Expression *_right);
    double calculate();
    virtual ~Minus();
};
class Mul : public BinaryOperator{
public:
    Mul(Expression *_left, Expression *_right);
    double calculate();
    virtual ~Mul();
};
class Div : public BinaryOperator {
public:
    Div(Expression *_left, Expression *_right);
    double calculate();
    virtual ~Div();
};
class UnaryOperator : public Expression{
protected:
    Expression* exp = nullptr;
public:
    UnaryOperator(Expression* expression);
    virtual ~UnaryOperator();
    Expression *getExp() const;
    void setExp(Expression *expression);
};
class UPlus : public UnaryOperator{
public:
    UPlus(Expression *expression);
    virtual ~UPlus();
    double calculate();
};
class UMinus : public UnaryOperator{
public:
    UMinus(Expression *expression);
    double calculate();
    virtual ~UMinus();
};
class Variable : public Expression{
    string sim;
    double value;
    int direction;
public:
    int getDirection() const;

public:
    void setDirection(int direction);

public:
    Variable(string _name, double _value);
    virtual ~Variable();
    string getName() const;
    double getValue() const;
    void setName(string _name);
    void setValue(double _value);
    double calculate();
    Variable& operator++(int);
    Variable& operator++();
    Variable& operator--(int);
    Variable& operator--();
    Variable& operator+=(double val);
    Variable& operator-=(double val);
    //static bool checkName (string name);
};
class Value : public Expression{
    double value;
public:
    Value(double val);
    virtual ~Value();
    double getValue() const;
    double calculate();
};
#endif //EX1_EX1_H
