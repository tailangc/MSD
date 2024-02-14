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


void Var::pretty_print(std::ostream &ot,precedence_t p, int pos_ini, bool let_Para){
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


void Num::pretty_print(std::ostream &ot, precedence_t prec, int pos_ini, bool let_Para) {
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

//void Add::pretty_print_dr(std::ostream &ot){}

void Add::pretty_print(std::ostream &ot, precedence_t prec, int pos_ini, bool let_Para)  {
    if(prec > prec_add) {
        ot << "(";
    }

    lhs->pretty_print(ot,prec_add, pos_ini, true);
    ot <<" + ";
    rhs->pretty_print(ot,prec_add, pos_ini, let_Para);


    if(prec > prec_add) {
        ot << ")";
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

void Mult::pretty_print(std::ostream &ot, precedence_t prec, int pos_ini, bool let_Para)  {
    bool let_print = let_Para;
    if ( prec > prec_mult ){
        ot << "(";
        let_print = false;
    }

    lhs->pretty_print(ot, static_cast<precedence_t>(prec_mult + 1), pos_ini, true);
    ot << " * ";
    rhs->pretty_print(ot, prec_mult,  pos_ini, let_print);

    if ( prec > prec_mult ){
        ot << ")";
    }
}


/**
 * this is the letExpr function
 * @param variable
 * @param valueExpr
 * @param bodyExpr
 */
letExpr::letExpr(std::string variable, Expr *valueExpr, Expr *bodyExpr){
    this -> variable = variable;
    this -> valueExpr = valueExpr;
    this -> bodyExpr = bodyExpr;
}

bool letExpr::equals(Expr *e){
    // Check if the given expression `e` is a LetExpr with the same variable, value expression, and body expression
    letExpr* letExpr = dynamic_cast<class letExpr*>(e);

    if (letExpr != nullptr) { // If `e` is indeed a `letExpr`
        // Compare the variable, value expression, and body expression of the current `letExpr` with `otherLetExpr`
        bool variableEqual = variable == letExpr->variable;
        bool valueExprEqual = valueExpr->equals(letExpr->valueExpr);
        bool bodyExprEqual = bodyExpr->equals(letExpr->bodyExpr);

        // Return true only if all comparisons are true
        return variableEqual && valueExprEqual && bodyExprEqual;
    }
    return false;
}

int letExpr::interp() {
    // Interpret the value expression and substitute the variable with the result in the body expression
    Expr *substitutedBody = bodyExpr->subst(variable, valueExpr);
    return substitutedBody->interp();
}

bool letExpr::has_variable() {
    // Check if the body expression contains a variable
    return bodyExpr->has_variable();
}

Expr *letExpr::subst(std::string var, Expr *s){
    // Substitute the variable `var` with the expression `s` in the value expression and body expression
    Expr *substitutedValue = valueExpr->subst(var, s);
    Expr *substitutedBody = bodyExpr->subst(var, s);
    return new letExpr(variable, substitutedValue, substitutedBody);
}

void letExpr::print(std::ostream &ot) {
    // Print the let expression with the variable, value expression, and body expression
    ot << "(";
    ot << "_let " << variable << "=";
    valueExpr->print(ot);
    ot << " _in ";
    bodyExpr->print(ot);
    ot << ")";
}

void letExpr::pretty_print_dr(std::ostream &ot) {
    int pos = ot.tellp();
    pretty_print(ot, prec_none, pos, false);
}

void letExpr::pretty_print(std::ostream &ot, precedence_t prec, int pos_ini, bool let_Para) {
    // Pretty print the let expression with appropriate parentheses
    if (prec > prec_none && let_Para){
        ot << "(";
    }

    int curr = ot.tellp();
    curr = curr - pos_ini;

    ot << "_let " << variable << " = ";
    valueExpr ->pretty_print(ot, prec_none,pos_ini, let_Para);
    ot << "\n";
    int before_in = ot.tellp();
//    ot<< std::string(space,  " ");
    while (curr > 0){
        ot << " ";
        curr -= 1;
    }

    ot << "_in  ";
//    int pos_updated = ot.tellp();
    bodyExpr ->pretty_print(ot, prec_none, before_in, let_Para);
    if (prec > prec_none && let_Para){
        ot << ")";
    }

}





/**
 * this is the Test case
 */
TEST_CASE( "Tests") {
    SECTION("HW3") {
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
//CHECK_THROWS_WITH( (new Var("x"))->interp(), "no value for variable" );
        CHECK((new Mult(new Num(3), new Num(2)))->interp() == 6);
        CHECK((new Mult(new Num(0), new Num(3)))->interp() == 0);
        CHECK((new Add(new Add(new Num(10), new Num(15)), new Add(new Num(20), new Num(20))))->interp() == 65);
        CHECK((new Add(new Num(8), new Num(2)))->interp() == 10);
        CHECK((new Add(new Num(8), new Add(new Num(10), new Num(12))))->interp() == 30);
        CHECK((new Add(new Var("x"), new Num(7)))->subst("x", new Var("y"))
                      ->equals(new Add(new Var("y"), new Num(7))));
        CHECK((new Var("x"))
                      ->subst("x", new Add(new Var("y"), new Num(7)))
                      ->equals(new Add(new Var("y"), new Num(7))));
        CHECK((new Var("x"))
                      ->subst("x", new Num(3))
                      ->equals(new Num(3)));

        CHECK((new Add(new Var("x"), new Num(5)))
                      ->subst("x", new Num(2))
                      ->equals(new Add(new Num(2), new Num(5))));

        CHECK((new Mult(new Var("x"), new Num(4)))
                      ->subst("x", new Num(6))
                      ->equals(new Mult(new Num(6), new Num(4))));

        CHECK((new Add(new Var("x"), new Var("x")))
                      ->subst("x", new Num(10))
                      ->equals(new Add(new Num(10), new Num(10))));

        CHECK((new Mult(new Add(new Var("x"), new Num(2)), new Var("x")))
                      ->subst("x", new Num(8))
                      ->equals(new Mult(new Add(new Num(8), new Num(2)), new Num(8))));

    }

    SECTION("HW4") {
        CHECK ((new Mult(new Num(1), new Add(new Num(2), new Num(3))))->to_pretty_string() == "1 * (2 + 3)");
        CHECK ((new Mult(new Mult(new Num(8), new Num(1)), new Var("y")))->to_pretty_string() == "(8 * 1) * y");
        CHECK ((new Mult(new Add(new Num(3), new Num(5)), new Mult(new Num(6), new Num(1))))->to_pretty_string() ==
               "(3 + 5) * 6 * 1");
        CHECK ((new Mult(new Mult(new Num(7), new Num(7)), new Add(new Num(9), new Num(2))))->to_pretty_string() ==
               "(7 * 7) * (9 + 2)");
    }

    SECTION("HW5") {
        CHECK((new letExpr("x", new Num(5),new Add(new letExpr("y", new Num(3), new Add(new Var("y"), new Num(2))), new Var("x"))))->equals(new letExpr("x", new Num(5),new Add(new letExpr("y", new Num(3), new Add(new Var("y"), new Num(2))), new Var("x")))) == true);
        CHECK((new letExpr("x", new Num(5),new Add(new letExpr("y", new Num(3), new Add(new Var("y"), new Num(2))), new Var("x"))))->equals(new Num(7)) == false);
        CHECK((new letExpr("x", new Num(5), new Add(new letExpr("y", new Num(3), new Add(new Var("y"), new Num(2))),new Var("x"))))->has_variable() == true);
        // print
        CHECK((new letExpr("x", new Num(5), new Add(new letExpr("y", new Num(3), new Add(new Var("y"), new Num(2))),new Var("x"))))->to_string() ==
              "(_let x=5 _in ((_let y=3 _in (y+2))+x))");
        CHECK((new letExpr("x", new Num(5), new letExpr("x", new Num(6), new Add(new Var("x"), new Num(1)))))->to_string() ==
              "(_let x=5 _in (_let x=6 _in (x+1)))");
        // interp()
        CHECK((new letExpr("x", new Num(5),new Add(new letExpr("y", new Num(3), new Add(new Var("y"), new Num(2))), new Var("x"))))->interp() ==10);


        // subst
        CHECK((new letExpr("x", new Num(5), new letExpr("y", new Num(6), new Add(new Var("x"), new Num(1)))))->interp() == 6);
        CHECK((new letExpr("x", new Add(new Num(5), new Num(2)), new Add(new Var("x"), new Num(1))))->interp() == 8);
        CHECK((new letExpr("x", new Num(5), new Add(new Var("x"), new Num(3))))->to_pretty_string() ==
              "_let x = 5\n_in  x + 3");
        //        /Let nested as right argument of parenthesized multiplication expression

        //Let nested as right argument of parenthesized multiplication expression
        CHECK ((new Mult(new Mult(new Num(2), new letExpr("x", new Num(5), new Add(new Var("x"), new Num(1)))),new Num(3)))->to_pretty_string() == "(2 * _let x = 5\n"
                                                             "     _in  x + 1) * 3");
        //Let nested to the left in add expression which is nested to the right within a multiplication expression
        CHECK((new Mult(new Num(5), new Add(new letExpr("x", new Num(5), new Var("x")), new Num(1))))->to_pretty_string() ==
              "5 * ((_let x = 5\n"
              "      _in  x) + 1)");

        //Let in lhs of add
        CHECK ( (new Add(new letExpr("x", new Num(2), new Add(new Var("x"), new Num(9))), new Num(4)))->to_pretty_string() == "(_let x = 2\n"" _in  x + 9) + 4");
        //Let in lhs of multiplication expression
        CHECK((new Mult(new letExpr("x", new Num(5), new Add(new Var("x"), new Num(8))), new Num(3)))->to_pretty_string() == "(_let x = 5\n"" _in  x + 8) * 3");
        //Let nest as right argument of un-parenthesized multiplication expression
        CHECK((new Add (new Mult(new Num(4), new letExpr("x", new Num(5), new Add(new Var("x"), new Num(1)))), new Num(9)))->to_pretty_string() == "4 * (_let x = 5\n"
                                                                                                                                               "     _in  x + 1) + 9");
        //Let nested in lhs of Add expression nested within body of let expression
        CHECK((new letExpr("x", new Num(5), new Add(new letExpr("y" , new Num(3), new Add(new Var("y"), new Num(2))), new Var("x"))))
                      ->to_pretty_string() == "_let x = 5\n"
                                              "_in  (_let y = 3\n"
                                              "      _in  y + 2) + x");


        CHECK ((new Add(new letExpr("x", new Num(3), new letExpr("y", new Num(3), new Add(new Var("y"), new Num(2))) ), new Var("x")))->to_pretty_string() == "(_let x = 3\n"
                                                                                                                                                      " _in  _let y = 3\n""      _in  y + 2) + x");
    }
}