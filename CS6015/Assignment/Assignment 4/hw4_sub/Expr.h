#ifndef EXPR_EXPR_H
#define EXPR_EXPR_H

#include <string>
#include <sstream>
#include "catch.hpp"
#include "iostream"


typedef enum {
    prec_none,  // = 0
    prec_add,   // = 1
    prec_mult   // = 2
} precedence_t;


class Expr {
public:
    virtual bool equals(Expr *e) = 0;
    virtual int interp() = 0;
    virtual bool has_variable() = 0;
    virtual Expr *subst(std::string,Expr *s) = 0;
    virtual void print(std::ostream &ot) = 0;
    virtual void pretty_print(std::ostream &ot, precedence_t prec) = 0;
    std::string to_string(){
        std::stringstream st("");
        this ->print(st);
        return st.str();
    }
    std::string to_pretty_string(){
        std::stringstream st("");
        this ->pretty_print(st, prec_none);
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
    void pretty_print(std::ostream &ot, precedence_t prec);
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
    void pretty_print(std::ostream &ot, precedence_t prec);
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
    void pretty_print(std::ostream &ot, precedence_t prec);
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
    void pretty_print(std::ostream &ot, precedence_t prec);
};


#endif //EXPR_EXPR_H