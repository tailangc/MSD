#include "Expr.h"
#include "iostream"

//using namespace std;
//
/**
 * this is the value function
 * @param val
 */
Var::Var(std::string val){ //constructor for var
    this->val = val;
}

bool Var::equals(Expr *e) { //Check if the given expression is equal to this Var instance.
    Var *v = dynamic_cast<Var*>(e);
    if(v == nullptr){
        return false;
    } else{
        return (this->val == v->val);
    }
}

int Var::interp(){
    throw std::runtime_error("variable doesnt have a value");
}

bool Var::has_variable(){
    return true;
}

Expr *Var::subst(std::string replace,Expr *s){ //Substitute a variable in the expression with another expression.
    if(this->val == replace){
        return s;
    }else{
        return this;
    }
}

void Var::print(std::ostream &ot) {
    ot << val;
}

void Var::pretty_print_dr(std::ostream &ot){}


void Var::pretty_print(std::ostream &ot,precedence_t p){
    ot << val;
}


/**
 * this is the Num function
 * @param val
 */
Num::Num(int val){ //constructor for num
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

int Num::interp(){
    return this->val;
}

bool Num::has_variable(){
    return false;
}

Expr *Num::subst(std::string replace,Expr *s) { //No substitution needed for Num instances,
    return this;
}

void Num::print(std::ostream &ot)  {
    ot << val;
}

void Num::pretty_print_dr(std::ostream &ot){}


void Num::pretty_print(std::ostream &ot, precedence_t prec) {
    ot << val;
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
        return (this->lhs->equals(a->lhs) && this->rhs->equals(a->rhs));
    }
}

int Add::interp(){
    return this->lhs->interp() + this->rhs->interp() ;
}

bool Add::has_variable(){
    return lhs->has_variable() || rhs->has_variable();
}
Expr *Add::subst(std::string replace,Expr *s) {
    return new Add(lhs->subst(replace,s),rhs->subst(replace,s));
}

void Add::print(std::ostream &ot) {
    ot<<"(";
    lhs->print(ot);
    ot <<"+";
    rhs->print(ot);
    ot<<")";
}

void Add::pretty_print_dr(std::ostream &ot){}

void Add::pretty_print(std::ostream &ot, precedence_t prec)  {
    if(prec > prec_add){
        ot<<"(";
        lhs->pretty_print(ot,prec_add);
        ot <<" + ";
        rhs->pretty_print(ot,prec_add);
        ot<<")";
    }
    else {
        lhs->pretty_print(ot,prec_add);
        ot << " + ";
        rhs->pretty_print(ot,prec_add);
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

bool Mult::equals(Expr *e){
    Mult *m = dynamic_cast<Mult *>(e);
    if (m == nullptr) {
        return false;
    } else {
        return (this->lhs->equals(m->lhs) && this->rhs->equals(m->rhs));
    }
}

int Mult::interp(){
    return this->lhs->interp() * this->rhs->interp() ;
}

bool Mult::has_variable() {
    return lhs->has_variable() || rhs->has_variable();
}

Expr *Mult::subst(std::string replace,Expr *s) {
    return new Mult(lhs->subst(replace,s),rhs->subst(replace,s));
}

void Mult::print(std::ostream &ot)  {
    ot<<"(";
    lhs->print(ot);
    ot <<"*";
    rhs->print(ot);
    ot<<")";
}
void Mult::pretty_print_dr(std::ostream &ot) {
    pretty_print(ot, prec_mult);
}

void Mult::pretty_print(std::ostream &ot, precedence_t prec)  {
    if ( prec > prec_mult ){
        ot << "(";
    }
    lhs->pretty_print(ot, static_cast<precedence_t>(prec_mult + 1));
    ot << " * ";
    rhs->pretty_print(ot, prec_mult);
    if ( prec > prec_mult ){
        ot << ")";
    }
}




/**
 * this is the Test case
 */
TEST_CASE( "Tests") {
SECTION("HW3"){
CHECK( (new Var("x"))->equals(new Var("x")) == true );
CHECK( (new Var("x"))->equals(new Var("y")) == false );
CHECK( (new Num(1))->equals(new Var("x")) == false );
CHECK( (new Num(1))->equals(new Num(1)) == true );
CHECK( (new Add(new Num(2),new Num(3)))->equals(new Add(new Num(2),new Num(3)))==true );
CHECK( (new Add(new Num(2),new Num(3)))->equals(new Add(new Num(3),new Num(2)))==false );
CHECK( (new Add(new Num(-2),new Num(-3)))->equals(new Add(new Num(-2),new Num(-3)))==true );
CHECK( (new Add(new Num(-2),new Num(0)))->equals(new Add(new Num(-2),new Num(0)))==true );
CHECK( (new Mult(new Num(2),new Num(3)))->equals(new Mult(new Num(3),new Num(2)))==false );
CHECK( (new Mult(new Num(2),new Num(3)))->equals(new Mult(new Num(2),new Num(3)))==true );
CHECK( (new Mult(new Num(-2),new Num(-3)))->equals(new Mult(new Num(-2),new Num(-3)))==true );
CHECK( (new Mult(new Num(-2),new Num(0)))->equals(new Mult(new Num(-2),new Num(0)))==true );
//CHECK_THROWS_WITH( (new Var("x"))->interp(), "no value for variable" );
CHECK( (new Mult(new Num(3), new Num(2)))->interp()==6 );
CHECK( (new Mult(new Num(0), new Num(3)))->interp()==0 );
CHECK( (new Add(new Add(new Num(10), new Num(15)),new Add(new Num(20),new Num(20))))->interp()==65);
CHECK((new Add(new Num (8) , new Num(2)))->interp() == 10);
CHECK((new Add(new Num(8),new Add(new Num(10),new Num(12))))->interp() == 30);
CHECK( (new Add(new Var("x"), new Num(7)))->subst("x", new Var("y"))
->equals(new Add(new Var("y"), new Num(7))) );
CHECK( (new Var("x"))
->subst("x", new Add(new Var("y"),new Num(7)))
->equals(new Add(new Var("y"),new Num(7))) );
CHECK( (new Var("x"))
->subst("x", new Num(3))
->equals(new Num(3)) );

CHECK( (new Add(new Var("x"), new Num(5)))
->subst("x", new Num(2))
->equals(new Add(new Num(2), new Num(5))) );

CHECK( (new Mult(new Var("x"), new Num(4)))
->subst("x", new Num(6))
->equals(new Mult(new Num(6), new Num(4))) );

CHECK( (new Add(new Var("x"), new Var("x")))
->subst("x", new Num(10))
->equals(new Add(new Num(10), new Num(10))) );

CHECK( (new Mult(new Add(new Var("x"), new Num(2)), new Var("x")))
->subst("x", new Num(8))
->equals(new Mult(new Add(new Num(8), new Num(2)), new Num(8))) );

}

    SECTION("HW4"){
        CHECK ( (new Mult(new Num(1), new Add(new Num(2), new Num(3))))->to_pretty_string() ==  "1 * (2 + 3)" );
        CHECK ( (new Mult(new Mult(new Num(8), new Num(1)), new Var("y")))->to_pretty_string() ==  "(8 * 1) * y" );
        CHECK ( (new Mult(new Add(new Num(3), new Num(5)), new Mult(new Num(6), new Num(1))))->to_pretty_string() ==  "(3 + 5) * 6 * 1" );
        CHECK ( (new Mult(new Mult(new Num(7), new Num(7)), new Add(new Num(9), new Num(2))) )->to_pretty_string() ==  "(7 * 7) * (9 + 2)" );

}