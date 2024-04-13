

#ifndef ASSIGNMENT_4_VAL_H
#define ASSIGNMENT_4_VAL_H

#include <stdio.h>
#include <iostream>
#include "pointer.h"

class Expr;
class Env;

CLASS (Val){
public:
    virtual PTR(Expr) to_expr() = 0;
    virtual bool equals(PTR(Val) v) = 0;
    virtual PTR(Val) add_to(PTR(Val) rhs) = 0;
    virtual PTR(Val) mult_to(PTR(Val) rhs) = 0;
    virtual std::string to_string() = 0;
    virtual bool is_true() = 0;
    virtual PTR(Val) call(PTR(Val) actual_arg) = 0;
};

class NumVal: public Val {
public:
    int val;

    NumVal(int val);
    PTR(Expr) to_expr() override;
    bool equals(PTR(Val) v) override;
    PTR(Val) add_to(PTR(Val) rhs) override;
    PTR(Val) mult_to(PTR(Val) rhs) override;
    std::string to_string() override;
    bool is_true() override;
    PTR(Val) call(PTR(Val) actual_arg) override;
};

class BoolVal: public Val {
public:
    bool val;

    BoolVal(bool val);
    PTR(Expr) to_expr() override;
    bool equals(PTR(Val) v) override;
    PTR(Val) add_to(PTR(Val) rhs) override;
    PTR(Val) mult_to(PTR(Val) rhs) override;
    std::string to_string() override;
    bool is_true() override;
    PTR(Val) call(PTR(Val) actual_arg) override;
};

class FunVal : public Val {
private:
    std::string formal_arg;
    PTR(Expr) body;
    PTR(Env) env;
public:
    FunVal(std::string arg, PTR(Expr) expr, PTR(Env) env_);
    PTR(Expr) to_expr() override;
    bool equals(PTR(Val) rhs) override;
    PTR(Val) add_to(PTR(Val) rhs) override;
    PTR(Val) mult_to(PTR(Val) rhs) override;
    std::string to_string() override;
    bool is_true() override;
    PTR(Val) call(PTR(Val) actual_arg) override;
};

#endif /* val_hpp */