

#include "Expr.h"
#include "iostream"
#include "catch.hpp"


using namespace std;
/**
 * this is the value function
 * @param val
 */
Var::Var(std::string val){
    this->val = val;
}

bool Var::equals(Expr *e) {
    Var *v = dynamic_cast<Var*>(e);
    if(v == nullptr){
        return false;
    } else{
        return (this->val == v->val);
    }
}

/**
 * this is the Num function
 * @param val
 */
Num::Num(int val){
    this->val = val;
}

bool Num::equals(Expr *e) {
    Num *n = dynamic_cast<Num*>(e);
    if(n== nullptr){
        return false;
    } else{
        return (this->val == n->val);
    }
}



/**
 * this is the Add function
 * @param lhs
 * @param rhs
 */
Add::Add(Expr *lhs,Expr *rhs){
    this->lhs=lhs;
    this->rhs=rhs;
}
bool Add::equals(Expr *e) {
    Add *a = dynamic_cast<Add *>(e);
    if (a == nullptr) {
        return false;
    } else {
        return (this->lhs->equals(a->lhs)
                && this->rhs->equals(a->rhs));
    }
}

/**
 * this is the Mult function
 * @param lhs
 * @param rhs
 */
Mult::Mult(Expr *lhs, Expr *rhs){
    this->lhs = lhs;
    this->rhs = rhs;
}

bool Mult::equals(Expr *e) {
    Mult *m = dynamic_cast<Mult *>(e);
    if (m == nullptr) {
        return false;
    } else {
        return (this->lhs->equals(m->lhs) && this->rhs->equals(m->rhs));
    }
}


/**
 * this is the Test case
 */

TEST_CASE( "Tests") {
    SECTION("HW2") {
        CHECK((new Var("x"))->equals(new Var("x")) == true);
        CHECK((new Var("x"))->equals(new Var("y")) == false);
        CHECK((new Num(1))->equals(new Var("x")) == false);
        CHECK((new Num(1))->equals(new Num(1)) == true);
        CHECK((new Add(new Num(2), new Num(3)))->equals(new Add(new Num(2), new Num(3))) == true);
        CHECK((new Add(new Num(2), new Num(3)))->equals(new Add(new Num(3), new Num(2))) == false);
        CHECK((new Add(new Num(-2), new Num(-3)))->equals(new Add(new Num(-2), new Num(-3))) == true);
        CHECK((new Add(new Num(-2), new Num(0)))->equals(new Add(new Num(-2), new Num(0))) == true);
        CHECK((new Mult(new Num(2), new Num(3)))->equals(new Mult(new Num(3), new Num(2))) == false);
        CHECK((new Mult(new Num(2), new Num(3)))->equals(new Mult(new Num(2), new Num(3))) == true);
        CHECK((new Mult(new Num(-2), new Num(-3)))->equals(new Mult(new Num(-2), new Num(-3))) == true);
        CHECK((new Mult(new Num(-2), new Num(0)))->equals(new Mult(new Num(-2), new Num(0))) == true);
    }
}
