#ifndef EXPR_EXPR_H
#define EXPR_EXPR_H

#include <string>
#include <sstream>
#include "catch.hpp"
#include "iostream"
#include "pointer.h"


typedef enum {
    prec_none,
    prec_equal,
    prec_add,
    prec_mult
} precedence_t;


class Val;


CLASS (Expr) {
public:
    virtual bool equals(PTR(Expr) e) = 0;
    virtual PTR(Val) interp() = 0;
//    virtual bool has_variable() = 0;
    virtual PTR(Expr) subst(std::string name,PTR(Expr) replacement) = 0;
    virtual void print(std::ostream &ot) = 0;
    virtual void pretty_print(std::ostream& out, precedence_t prec, std::streampos& newLinePrevPos, bool addParenthesesToLet) = 0;
    void pretty_print_dr(std::ostream &ot){
        std::streampos pos = ot.tellp();
        pretty_print(ot, prec_none, pos, false);
    };
    std::string to_string(){
        std::stringstream st("");
        this ->print(st);
        return st.str();
    }
//    virtual void pretty_print_dr(std::ostream &ot) = 0;
    std::string to_pretty_string(){
        std::stringstream st("");
        this ->pretty_print_dr(st);
        return st.str();
    }

};



class VarExpr:public Expr{
public:
    std::string val;
    VarExpr(std::string val);
    bool equals(PTR(Expr) e) override;
    PTR(Val)  interp () override;
//    bool has_variable();
    PTR(Expr) subst(std::string string,PTR(Expr) s)  override;
    void print(std::ostream &ot) override;
    void pretty_print_dr(std::ostream &ot);
    void pretty_print(std::ostream& out, precedence_t prec, std::streampos& newLinePrevPos, bool addParenthesesToLet) override;
};



class NumExpr:public Expr{
public:
    int val;
    NumExpr(int val);
    bool equals(PTR(Expr) e);
    PTR(Val) interp ();
//    bool has_variable();
    PTR(Expr) subst(std::string name,PTR(Expr) replacement) override;
    void print(std::ostream &ot) ;
    void pretty_print_dr(std::ostream &ot);
    void pretty_print(std::ostream& out, precedence_t prec, std::streampos& newLinePrevPos, bool addParenthesesToLet);
};

class  AddExpr:public Expr{
public:
    PTR(Expr) lhs;
    PTR(Expr) rhs;
    AddExpr(PTR(Expr) left,PTR(Expr) right);
    AddExpr(int left, int right);
    AddExpr(std::string left, int right);
    AddExpr(int left, std::string right);
    AddExpr(std::string left, std::string right);
    AddExpr(int left, PTR(Expr) right);
    AddExpr(PTR(Expr) left, int right);
    AddExpr(std::string left, PTR(Expr) right);
    AddExpr(PTR(Expr) left, std::string right);
    bool equals(PTR(Expr) expr) override;
    PTR(Val) interp() override;
    PTR(Expr) subst(std::string s, PTR(Expr) expr) override;
    void print(std::ostream &ot) override;
    void pretty_print_dr(std::ostream &ot);
    void pretty_print(std::ostream& out, precedence_t prec, std::streampos& newLinePrevPos, bool addParenthesesToLet) override;
};

class MultExpr:public Expr{
public:
    PTR(Expr) lhs;
    PTR(Expr) rhs;
    MultExpr(PTR(Expr) left, PTR(Expr) right);
    MultExpr(int left, int right);
    MultExpr(std::string left, int right);
    MultExpr(int left, std::string right);
    MultExpr(std::string left, std::string right);
    MultExpr(int left, PTR(Expr) right);
    MultExpr(PTR(Expr) left, int right);
    MultExpr(std::string left, PTR(Expr) right);
    MultExpr(PTR(Expr) left, std::string right);
    bool equals(PTR(Expr) e) override;
    PTR(Val) interp () override;
//    bool has_variable() ;
    PTR(Expr) subst(std::string name,PTR(Expr) replacement) override;
    void print(std::ostream &ot) override;
    void pretty_print_dr(std::ostream &ot);
    void pretty_print(std::ostream& out, precedence_t prec, std::streampos& newLinePrevPos, bool addParenthesesToLet)override;
};



class letExpr:public Expr{
public:
    std::string variable;
    PTR(Expr) valueExpr;
    PTR(Expr) bodyExpr;
    letExpr(std::string variable, PTR(Expr) valueExpr, PTR(Expr) bodyExpr);
    bool equals(PTR(Expr) e) ;
    PTR(Val) interp () ;
//    bool has_variable();
    PTR(Expr) subst(std::string name,PTR(Expr) replacement)  ;
    void print(std::ostream &ot) ;
    void pretty_print_dr(std::ostream &ot);
    void pretty_print(std::ostream& out, precedence_t prec, std::streampos& newLinePrevPos, bool addParenthesesToLet);
};


class BoolExpr: public Expr{
public:
    bool val;

    BoolExpr(bool val);
    bool equals(PTR(Expr) other);
    PTR(Val) interp();
//    bool has_variable();
    PTR(Expr) subst(std::string name, PTR(Expr) replacement);
    void print(std::ostream& output);
    void pretty_print_dr(std::ostream& output);
    void pretty_print(std::ostream& out, precedence_t prec, std::streampos& newLinePrevPos, bool addParenthesesToLet);
};

class IfExpr : public Expr{
public:
    PTR(Expr) test_part;
    PTR(Expr) then_part;
    PTR(Expr) else_part;

    IfExpr(PTR(Expr) test_part, PTR(Expr) then_part, PTR(Expr) else_part);
    IfExpr(bool test, PTR(Expr) then, PTR(Expr) else_);
    bool equals(PTR(Expr) other);
    PTR(Val) interp();
//    bool has_variable();
    PTR(Expr) subst(std::string name, PTR(Expr) replacement);
    void print(std::ostream& output);
    void pretty_print_dr(std::ostream& output);
    void pretty_print(std::ostream& out, precedence_t prec, std::streampos& newLinePrevPos, bool addParenthesesToLet);
};

class EqExpr : public Expr {
public:
    PTR(Expr) lhs;
    PTR(Expr) rhs;

    EqExpr(PTR(Expr) lhs, PTR(Expr) rhs);
    EqExpr(int left, int right);
    EqExpr(std::string left, int right);
    bool equals(PTR(Expr) other);
    PTR(Val) interp();
//    bool has_variable();
    PTR(Expr) subst(std::string name, PTR(Expr) replacement) override;
    void print(std::ostream &output);
    void pretty_print_dr(std::ostream &output) ;
    void pretty_print(std::ostream& out, precedence_t prec, std::streampos& newLinePrevPos, bool addParenthesesToLet);
};

class FunExpr : public Expr {
private:
    std::string formal_arg;
    PTR(Expr) body;
public:
    FunExpr(std::string arg, PTR(Expr) expr);
    bool equals(PTR(Expr) rhs) override;
    PTR(Val) interp() override;
    PTR(Expr) subst(std::string s, PTR(Expr) expr) override;
    void print(std::ostream& out) override;
    void pretty_print_dr(std::ostream& output);
    void pretty_print(std::ostream& out, precedence_t precedence, std::streampos& newLinePrevPos, bool addParen) override;
};

class CallExpr : public Expr {
private:
    PTR(Expr) to_be_called;
    PTR(Expr) actual_arg;
public:
    CallExpr(PTR(Expr) func, PTR(Expr) arg);
    CallExpr(PTR(Expr) func, int n);
    CallExpr(std::string funcName, int n);
    CallExpr(std::string funcName, PTR(Expr) arg);
    CallExpr(std::string funcName1, std::string funcName2);
    bool equals(PTR(Expr) rhs) override;
    PTR(Val) interp() override;
    PTR(Expr) subst(std::string s, PTR(Expr) expr) override;
    void print(std::ostream& out) override;
    void pretty_print_dr(std::ostream& output);
    void pretty_print(std::ostream& out, precedence_t precedence, std::streampos& newLinePrevPos, bool addParen) override;
};

#endif //EXPR_EXPR_H