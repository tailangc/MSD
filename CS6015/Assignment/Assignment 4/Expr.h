#ifndef EXPR_EXPR_H
#define EXPR_EXPR_H

#include <string>
#include <sstream>
#include "catch.hpp"
#include "iostream"


typedef enum {
    prec_none,  // = 0
    prec_add,   // = 1
    prec_mult,   // = 2
} precedence_t;


class Expr {
public:
    virtual bool equals(Expr *e) = 0;
    virtual int interp() = 0;
    virtual bool has_variable() = 0;
    virtual Expr *subst(std::string,Expr *s) = 0;
    virtual void print(std::ostream &ot) = 0;
    virtual void pretty_print(std::ostream &ot, precedence_t prec, int, bool let_Para) = 0;
    std::string to_string(){
        std::stringstream st("");
        this ->print(st);
        return st.str();
    }
//    virtual void pretty_print_dr(std::ostream &ot) = 0;
    void pretty_print_dr(std::ostream &ot){
        pretty_print(ot,prec_none,0, false);
    }
    std::string to_pretty_string(){
        std::stringstream st("");
        this ->pretty_print_dr(st);
        return st.str();
    }

};

class Var:public Expr{
public:
    std::string val;
    Var(std::string val);
    bool equals(Expr *e) ;
    int interp () ;
    bool has_variable();
    Expr *subst(std::string,Expr *s)  ;
    void print(std::ostream &ot) ;
    void pretty_print_dr(std::ostream &ot);
    void pretty_print(std::ostream &ot, precedence_t prec, int, bool let_Para);
};

class Num:public Expr{
public:
    int val;
    Num(int val);
    bool equals(Expr *e);
    int interp ();
    bool has_variable();
    Expr *subst(std::string,Expr *s);
    void print(std::ostream &ot) ;
    void pretty_print_dr(std::ostream &ot);
    void pretty_print(std::ostream &ot, precedence_t prec, int, bool let_Para);
};

class  Add:public Expr{
public:
    Expr *lhs;
    Expr *rhs;
    Add(Expr *lhs,Expr *rhs);
    bool equals(Expr *e);
    int interp () ;
    bool has_variable() ;
    Expr *subst(std::string,Expr *s);
    void print(std::ostream &ot);
    void pretty_print_dr(std::ostream &ot);
    void pretty_print(std::ostream &ot, precedence_t pre, int, bool let_Para);
};

class Mult:public Expr{
public:
    Expr *lhs;
    Expr *rhs;
    Mult(Expr *lhs, Expr *rhs);
    bool equals(Expr *e) ;
    int interp () ;
    bool has_variable() ;
    Expr *subst(std::string,Expr *s) ;
    void print(std::ostream &ot) ;
    void pretty_print_dr(std::ostream &ot);
    void pretty_print(std::ostream &ot, precedence_t prec, int, bool let_Para);
};

class letExpr:public Expr{
public:
    std::string variable;
    Expr *valueExpr;
    Expr *bodyExpr;
    letExpr(std::string variable, Expr *valueExpr, Expr *bodyExpr);
    bool equals(Expr *e) ;
    int interp () ;
    bool has_variable();
    Expr *subst(std::string,Expr *s)  ;
    void print(std::ostream &ot) ;
    void pretty_print_dr(std::ostream &ot);
    void pretty_print(std::ostream &ot, precedence_t prec, int, bool let_Para);
};


#endif //EXPR_EXPR_H