

#ifndef ASSIGNMENT_4_VAL_H
#define ASSIGNMENT_4_VAL_H

#include <stdio.h>
#include <iostream>

class Expr;

class Val{
public:
    virtual Expr* to_expr() = 0;
    virtual bool equals(Val* v) = 0;
    virtual Val* add_to(Val* rhs) = 0;
    virtual Val* mult_to(Val* rhs) = 0;
    virtual std::string to_string() = 0;
    virtual bool is_true() = 0;
    virtual Val* call(Val *actual_arg) = 0;
};

class NumVal: public Val {
public:
    int val;

    NumVal(int val);
    Expr* to_expr() override;
    bool equals(Val* v) override;
    Val* add_to(Val* rhs) override;
    Val* mult_to(Val* rhs) override;
    std::string to_string() override;
    bool is_true() override;
    virtual Val* call(Val *actual_arg) override;
};

class BoolVal: public Val {
public:
    bool val;

    BoolVal(bool val);
    Expr* to_expr() override;
    bool equals(Val* v) override;
    Val* add_to(Val* rhs) override;
    Val* mult_to(Val* rhs) override;
    std::string to_string() override;
    bool is_true() override;
    virtual Val* call(Val *actual_arg) override;
};

class FunVal : public Val {
private:
    std::string formal_arg;
    Expr* body;
public:
    FunVal(std::string arg, Expr* expr);
    Expr* to_expr() override;
    bool equals(Val* rhs) override;
    Val* add_to(Val* rhs) override;
    Val* mult_to(Val* rhs) override;
    std::string to_string() override;
    bool is_true() override;
    virtual Val* call(Val *actual_arg) override;
};

#endif /* val_hpp */