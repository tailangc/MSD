#ifndef EXPR_EXPR_H
#define EXPR_EXPR_H

#include <string>
#include "catch.hpp"

class Expr {
public:
    virtual bool equals(Expr *e)= 0;
    virtual int interp()= 0;
    virtual bool has_variable()=0;
    virtual Expr *subst(std::string,Expr *s)=0;
};
class Var:public Expr{
public:
    std::string val;
    Var(std::string val);
    bool equals(Expr *e);
    int interp ();
    bool has_variable();
    Expr *subst(std::string,Expr *s);

};

class Num:public Expr{
public:
    int val;
    Num(int val);
    bool equals(Expr *e);
    int interp ();
    bool has_variable();
    Expr *subst(std::string,Expr *s);

};

class  Add:public Expr{
public:
    Expr *lhs;
    Expr *rhs;
    Add(Expr *lhs,Expr *rhs);
    bool equals(Expr *e);
    int interp ();
    bool has_variable();
    Expr *subst(std::string,Expr *s);

};

class Mult:public Expr{
public:
    Expr *lhs;
    Expr *rhs;
    Mult(Expr *lhs, Expr *rhs);
    bool equals(Expr *e);
    int interp ();
    bool has_variable();
    Expr *subst(std::string,Expr *s);
};


#endif //EXPR_EXPR_H