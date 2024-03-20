#ifndef EXPR_EXPR_H
#define EXPR_EXPR_H

#include <string>
#include <sstream>
#include "catch.hpp"
#include "iostream"


typedef enum {
    prec_none,
    prec_equal,
    prec_add,
    prec_mult
} precedence_t;


class Val;


class Expr {
public:
    virtual bool equals(Expr *e) = 0;
    virtual Val* interp() = 0;
    virtual bool has_variable() = 0;
    virtual Expr *subst(std::string name,Expr *replacement) = 0;
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
    bool equals(Expr *e) ;
    Val * interp () ;
    bool has_variable();
    Expr *subst(std::string string,Expr *s)  ;
    void print(std::ostream &ot) ;
    void pretty_print_dr(std::ostream &ot);
    void pretty_print(std::ostream& out, precedence_t prec, std::streampos& newLinePrevPos, bool addParenthesesToLet);
};



class NumExpr:public Expr{
public:
    int val;
    NumExpr(int val);
    bool equals(Expr *e);
    Val *interp ();
    bool has_variable();
    Expr *subst(std::string name,Expr *replacement);
    void print(std::ostream &ot) ;
    void pretty_print_dr(std::ostream &ot);
    void pretty_print(std::ostream& out, precedence_t prec, std::streampos& newLinePrevPos, bool addParenthesesToLet);
};

class  AddExpr:public Expr{
public:
    Expr *lhs;
    Expr *rhs;
    AddExpr(Expr *lhs,Expr *rhs);
    bool equals(Expr *e);
    Val* interp () ;
    bool has_variable() ;
    Expr *subst(std::string name,Expr *replacement);
    void print(std::ostream &ot);
    void pretty_print_dr(std::ostream &ot);
    void pretty_print(std::ostream& out, precedence_t prec, std::streampos& newLinePrevPos, bool addParenthesesToLet);
};

class MultExpr:public Expr{
public:
    Expr *lhs;
    Expr *rhs;
    MultExpr(Expr *lhs, Expr *rhs);
    bool equals(Expr *e) ;
    Val *interp () ;
    bool has_variable() ;
    Expr *subst(std::string name,Expr *replacement) ;
    void print(std::ostream &ot) ;
    void pretty_print_dr(std::ostream &ot);
    void pretty_print(std::ostream& out, precedence_t prec, std::streampos& newLinePrevPos, bool addParenthesesToLet);
};



class letExpr:public Expr{
public:
    std::string variable;
    Expr *valueExpr;
    Expr *bodyExpr;
    letExpr(std::string variable, Expr *valueExpr, Expr *bodyExpr);
    bool equals(Expr *e) ;
    Val *interp () ;
    bool has_variable();
    Expr *subst(std::string name,Expr *replacement)  ;
    void print(std::ostream &ot) ;
    void pretty_print_dr(std::ostream &ot);
    void pretty_print(std::ostream& out, precedence_t prec, std::streampos& newLinePrevPos, bool addParenthesesToLet);
};


class BoolExpr: public Expr{
public:
    bool val;

    BoolExpr(bool val);
    bool equals(Expr *other);
    Val* interp();
    bool has_variable();
    Expr* subst(std::string name, Expr *replacement);
    void print(std::ostream& output);
    void pretty_print_dr(std::ostream& output);
    void pretty_print(std::ostream& out, precedence_t prec, std::streampos& newLinePrevPos, bool addParenthesesToLet);
};

class IfExpr : public Expr{
public:
    Expr *test_part;
    Expr *then_part;
    Expr *else_part;

    IfExpr(Expr *test_part, Expr *then_part, Expr *else_part);
    bool equals(Expr *other);
    Val* interp();
    bool has_variable();
    Expr* subst(std::string name, Expr *replacement);
    void print(std::ostream& output);
    void pretty_print_dr(std::ostream& output);
    void pretty_print(std::ostream& out, precedence_t prec, std::streampos& newLinePrevPos, bool addParenthesesToLet);
};

class EqExpr : public Expr {
public:
    Expr *lhs;
    Expr *rhs;

    EqExpr(Expr *lhs, Expr *rhs);
    EqExpr(int left, int right);
    bool equals(Expr *other);
    Val *interp();
    bool has_variable();
    Expr *subst(std::string name, Expr *replacement);
    void print(std::ostream &output);
    void pretty_print_dr(std::ostream &output);
    void pretty_print(std::ostream& out, precedence_t prec, std::streampos& newLinePrevPos, bool addParenthesesToLet);
};

#endif //EXPR_EXPR_H