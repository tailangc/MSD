#include "Expr.h"
#include "iostream"
#include "Val.h"
//using namespace std;
//
/**
 * this is the value function
 * @param val
 */
VarExpr::VarExpr(std::string val){ //constructor for var
    this->val = val;
}

bool VarExpr::equals(Expr *e) { //Check if the given expression is equal to this Var instance.
    VarExpr *v = dynamic_cast<VarExpr*>(e);
    if(v == nullptr){
        return false;
    } else{
        return (this->val == v->val);
    }
}

Val *VarExpr::interp(){
    throw std::runtime_error("unbound variable: x");
}

bool VarExpr::has_variable(){
    return true;
}

Expr *VarExpr::subst(std::string replace,Expr *s){ //Substitute a variable in the expression with another expression.
    if(this->val == replace){
        return s;
    }else{
        return this;
    }
}

void VarExpr::print(std::ostream &ot) {
    ot << val;
}

void VarExpr::pretty_print_dr(std::ostream &ot){}


void VarExpr::pretty_print(std::ostream& out, precedence_t precedence, std::streampos& newLinePrevPos, bool addParenthesesToLet){
    out << val;
}


/**
 * this is the Num function
 * @param val
 */
NumExpr::NumExpr(int val){ //constructor for num
    this->val = val;
}

bool NumExpr::equals(Expr *e) {
    NumExpr *n = dynamic_cast<NumExpr*>(e);
    if(n== nullptr){
        return false;
    } else{
        return (this->val == n->val);
    }
}

Val *NumExpr::interp(){
    return new NumVal(this->val);
}

bool NumExpr::has_variable(){
    return false;
}

Expr *NumExpr::subst(std::string replace,Expr *s) { //No substitution needed for Num instances,
    return this;
}

void NumExpr::print(std::ostream &ot)  {
    ot << val;
}

void NumExpr::pretty_print_dr(std::ostream &ot){}


void NumExpr::pretty_print(std::ostream& out, precedence_t prec, std::streampos& newLinePrevPos, bool addParenthesesToLet) {
    out << val;
}



/**
 * this is the Add function
 * @param lhs
 * @param rhs
 */
AddExpr::AddExpr(Expr *lhs,Expr *rhs){
    this->lhs=lhs;
    this->rhs=rhs;
}
bool AddExpr::equals(Expr *e) {
    AddExpr *a = dynamic_cast<AddExpr *>(e);
    if (a == nullptr) {
        return false;
    } else {
        return (this->lhs->equals(a->lhs) && this->rhs->equals(a->rhs));
    }
}

Val *AddExpr::interp(){
    return this->lhs->interp() ->add_to(this->rhs->interp())  ;
}

bool AddExpr::has_variable(){
    return lhs->has_variable() || rhs->has_variable();
}
Expr *AddExpr::subst(std::string replace,Expr *s) {
    return new AddExpr(lhs->subst(replace,s),rhs->subst(replace,s));
}

void AddExpr::print(std::ostream &ot) {
    ot<<"(";
    lhs->print(ot);
    ot <<"+";
    rhs->print(ot);
    ot<<")";
}

//void Add::pretty_print_dr(std::ostream &ot){}

void AddExpr::pretty_print(std::ostream& out, precedence_t prec, std::streampos& newLinePrevPos, bool addParenthesesToLet)  {
    bool addPar = prec_add <= prec;
    if(addPar) {
        out << "(";
    }

    lhs->pretty_print(out,prec_add, newLinePrevPos, true);
    out <<" + ";
    rhs->pretty_print(out,prec_add, newLinePrevPos, false);


    if(addPar) {
        out << ")";
    }
}






/**
 * this is the Mult function
 * @param lhs
 * @param rhs
 */
MultExpr::MultExpr(Expr *lhs, Expr *rhs){
    this->lhs = lhs;
    this->rhs = rhs;
}

bool MultExpr::equals(Expr *e){
    MultExpr *m = dynamic_cast<MultExpr *>(e);
    if (m == nullptr) {
        return false;
    } else {
        return (this->lhs->equals(m->lhs) && this->rhs->equals(m->rhs));
    }
}

Val *MultExpr::interp(){
    return this->lhs->interp() ->mult_to(this->rhs->interp())  ;
}

bool MultExpr::has_variable() {
    return lhs->has_variable() || rhs->has_variable();
}

Expr *MultExpr::subst(std::string replace,Expr *s) {
    return new MultExpr(lhs->subst(replace,s),rhs->subst(replace,s));
}

void MultExpr::print(std::ostream &ot)  {
    ot<<"(";
    lhs->print(ot);
    ot <<"*";
    rhs->print(ot);
    ot<<")";
}

void MultExpr::pretty_print(std::ostream& out, precedence_t prec, std::streampos& newLinePrevPos, bool addParenthesesToLet)  {
    bool addPar = prec_mult <= prec;
    if (addPar) {
        out << "(";
    }
    lhs->pretty_print(out, prec_mult, newLinePrevPos, true);
    out << " * ";
    // add parentheses for rhs when : 1. rhs is let 2. the outermost mult expression is followed with an add expression
    rhs->pretty_print(out, prec_add, newLinePrevPos, addParenthesesToLet && !addPar);
    if (addPar) {
        out << ")";
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

Val *letExpr::interp() {
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
    if(var == variable){
        return new letExpr(variable, valueExpr->subst(var,s), bodyExpr);
    }
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

//void letExpr::pretty_print_dr(std::ostream &ot) {
//    int pos = ot.tellp();
//    pretty_print(ot, prec_none, pos, false);
//}

void letExpr::pretty_print(std::ostream& out, precedence_t prec, std::streampos& newLinePrevPos, bool addParenthesesToLet) {
    // Pretty print the let expression with appropriate parentheses
    if (addParenthesesToLet) {
        out << "(";
    }
    int indentation = out.tellp() - newLinePrevPos;
    out << "_let " << variable << " = ";
    valueExpr->pretty_print(out, prec_none,newLinePrevPos, false);
    out << "\n";
    newLinePrevPos = out.tellp();

    out << std::string(indentation, ' ');
    out << "_in  ";
    bodyExpr->pretty_print(out, prec_none, newLinePrevPos, false);

    if (addParenthesesToLet) {
        out << ")";
    }
}



/**
 * This is the BoolExpr function
 *
 */

BoolExpr::BoolExpr(bool v) {
    val = v;
}

bool BoolExpr::equals(Expr* rhs) {
    BoolExpr* other = dynamic_cast<BoolExpr*>(rhs);
    if (other == nullptr) {
        return false;
    }
    return val == other->val;
}

Val* BoolExpr::interp() {
    return new BoolVal(val);
}


bool BoolExpr::has_variable() {
    return false;
}

Expr* BoolExpr::subst(std::string s, Expr* expr) {
    return this;
}

void BoolExpr::print(std::ostream& out) {
    val ? out << "_true" : out << "_false";
}

void BoolExpr::pretty_print(std::ostream& out, precedence_t precedence, std::streampos& newLinePrevPos, bool addParenthesesToLet) {
    val ? out << "_true" : out << "_false";
}


/**
 * This is the IfExpr function
 *
 */
IfExpr::IfExpr(Expr* test, Expr* then, Expr* else_) {
    test_part = test;
    then_part = then;
    else_part = else_;
}

bool IfExpr::equals(Expr* rhs) {
    IfExpr* other = dynamic_cast<IfExpr*>(rhs);
    if (other == nullptr) {
        return false;
    }
    return test_part->equals(other->test_part) && then_part->equals(other->then_part) && else_part->equals(other->else_part);
}

Val* IfExpr::interp() {
    if (test_part->interp()->is_true()) {
        return then_part->interp();
    }
    return else_part->interp();
}

bool IfExpr::has_variable() {
    return test_part->has_variable() || then_part->has_variable() || else_part->has_variable();
}

Expr* IfExpr::subst(std::string s, Expr* expr) {
    return new IfExpr(test_part->subst(s, expr), then_part->subst(s, expr), else_part->subst(s, expr));
}

void IfExpr::print(std::ostream& out) {
    out << "(_if ";
    test_part->print(out);
    out << " _then ";
    then_part->print(out);
    out << " _else ";
    else_part->print(out);
    out << ")";
}

void IfExpr::pretty_print(std::ostream& out, precedence_t precedence, std::streampos& newLinePrevPos, bool addParenthesesToLet) {
    if (addParenthesesToLet) {
        out << "(";
    }
    int indentation = out.tellp() - newLinePrevPos;
    out << "_if ";
    test_part->pretty_print(out, prec_none, newLinePrevPos, false);
    out << "\n";
    newLinePrevPos = out.tellp();

    out << std::string(indentation, ' ') << "_then ";
    then_part->pretty_print(out, prec_none, newLinePrevPos, false);
    out << "\n";
    newLinePrevPos = out.tellp();

    out << std::string(indentation, ' ') << "_else ";
    else_part->pretty_print(out, prec_none, newLinePrevPos, false);

    if (addParenthesesToLet) {
        out << ")";
    }
}


/**
 * This is the EqExpr function
 *
 */

EqExpr::EqExpr(Expr* left, Expr* right) {
    lhs = left;
    rhs = right;
}

EqExpr::EqExpr(int left, int right) {
    lhs = new NumExpr(left);
    rhs = new NumExpr(right);
}

bool EqExpr::equals(Expr* rhs_) {
    EqExpr* other = dynamic_cast<EqExpr*>(rhs_);
    if (other == nullptr) {
        return false;
    }
    return lhs->equals(other->lhs) && rhs->equals(other->rhs);
}

Val* EqExpr::interp() {
    return new BoolVal(lhs->interp()->equals(rhs->interp()));
}

bool EqExpr::has_variable() {
    return lhs->has_variable() || rhs->has_variable();
}

Expr *EqExpr::subst(std::string s, Expr* expr) {
    return new EqExpr(lhs->subst(s, expr), rhs->subst(s, expr));
}

void EqExpr::print(std::ostream& out) {
    out << "(";
    lhs->print(out);
    out << "==";
    rhs->print(out);
    out << ")";
}

void EqExpr::pretty_print(std::ostream& out, precedence_t precedence, std::streampos& newLinePrevPos,
                             bool addParenthesesToLet) {
    bool addParentheses = prec_equal <= precedence;
    if (addParentheses) {
        out << "(";
    }
    lhs->pretty_print(out, prec_equal, newLinePrevPos, true);
    out << " == ";
    rhs->pretty_print(out, prec_none, newLinePrevPos, !addParentheses && addParenthesesToLet);
    if (addParentheses) {
        out << ")";
    }

}



/**
 * this is the Test case
 */
TEST_CASE( "Tests") {
    SECTION("HW3") {
        CHECK((new VarExpr("x"))->equals(new VarExpr("x")) == true);
        CHECK((new VarExpr("x"))->equals(new VarExpr("y")) == false);
        CHECK((new NumExpr(1))->equals(new VarExpr("x")) == false);
        CHECK((new NumExpr(1))->equals(new NumExpr(1)) == true);
        CHECK((new AddExpr(new NumExpr(2), new NumExpr(3)))->equals(new AddExpr(new NumExpr(2), new NumExpr(3))) == true);
        CHECK((new AddExpr(new NumExpr(2), new NumExpr(3)))->equals(new AddExpr(new NumExpr(3), new NumExpr(2))) == false);
        CHECK((new AddExpr(new NumExpr(-2), new NumExpr(-3)))->equals(new AddExpr(new NumExpr(-2), new NumExpr(-3))) == true);
        CHECK((new AddExpr(new NumExpr(-2), new NumExpr(0)))->equals(new AddExpr(new NumExpr(-2), new NumExpr(0))) == true);
        CHECK((new MultExpr(new NumExpr(2), new NumExpr(3)))->equals(new MultExpr(new NumExpr(3), new NumExpr(2))) == false);
        CHECK((new MultExpr(new NumExpr(2), new NumExpr(3)))->equals(new MultExpr(new NumExpr(2), new NumExpr(3))) == true);
        CHECK((new MultExpr(new NumExpr(-2), new NumExpr(-3)))->equals(new MultExpr(new NumExpr(-2), new NumExpr(-3))) == true);
        CHECK((new MultExpr(new NumExpr(-2), new NumExpr(0)))->equals(new MultExpr(new NumExpr(-2), new NumExpr(0))) == true);
//CHECK_THROWS_WITH( (new Var("x"))->interp(), "no value for variable" );
        CHECK((new MultExpr(new NumExpr(3), new NumExpr(2)))->interp() ->equals(new NumVal(6)));
        CHECK((new MultExpr(new NumExpr(0), new NumExpr(3)))->interp() ->equals(new NumVal(0)));
        CHECK((new AddExpr(new AddExpr(new NumExpr(10), new NumExpr(15)), new AddExpr(new NumExpr(20), new NumExpr(20))))->interp() ->equals(new NumVal(65)));
        CHECK((new AddExpr(new NumExpr(8), new NumExpr(2)))->interp() ->equals(new NumVal(10)));
        CHECK((new AddExpr(new NumExpr(8), new AddExpr(new NumExpr(10), new NumExpr(12))))->interp() ->equals(new NumVal(30)));
        CHECK((new AddExpr(new VarExpr("x"), new NumExpr(7)))->subst("x", new VarExpr("y"))
                      ->equals(new AddExpr(new VarExpr("y"), new NumExpr(7))));
        CHECK((new VarExpr("x"))
                      ->subst("x", new AddExpr(new VarExpr("y"), new NumExpr(7)))
                      ->equals(new AddExpr(new VarExpr("y"), new NumExpr(7))));
        CHECK((new VarExpr("x"))
                      ->subst("x", new NumExpr(3))
                      ->equals(new NumExpr(3)));

        CHECK((new AddExpr(new VarExpr("x"), new NumExpr(5)))
                      ->subst("x", new NumExpr(2))
                      ->equals(new AddExpr(new NumExpr(2), new NumExpr(5))));

        CHECK((new MultExpr(new VarExpr("x"), new NumExpr(4)))
                      ->subst("x", new NumExpr(6))
                      ->equals(new MultExpr(new NumExpr(6), new NumExpr(4))));

        CHECK((new AddExpr(new VarExpr("x"), new VarExpr("x")))
                      ->subst("x", new NumExpr(10))
                      ->equals(new AddExpr(new NumExpr(10), new NumExpr(10))));

        CHECK((new MultExpr(new AddExpr(new VarExpr("x"), new NumExpr(2)), new VarExpr("x")))
                      ->subst("x", new NumExpr(8))
                      ->equals(new MultExpr(new AddExpr(new NumExpr(8), new NumExpr(2)), new NumExpr(8))));

    }

    SECTION("HW4") {
        CHECK ((new MultExpr(new NumExpr(1), new AddExpr(new NumExpr(2), new NumExpr(3))))->to_pretty_string() == "1 * (2 + 3)");
        CHECK ((new MultExpr(new MultExpr(new NumExpr(8), new NumExpr(1)), new VarExpr("y")))->to_pretty_string() == "(8 * 1) * y");
        CHECK ((new MultExpr(new AddExpr(new NumExpr(3), new NumExpr(5)), new MultExpr(new NumExpr(6), new NumExpr(1))))->to_pretty_string() ==
               "(3 + 5) * 6 * 1");
        CHECK ((new MultExpr(new MultExpr(new NumExpr(7), new NumExpr(7)), new AddExpr(new NumExpr(9), new NumExpr(2))))->to_pretty_string() ==
               "(7 * 7) * (9 + 2)");
    }

    SECTION("HW5") {
//        CHECK( (new letExpr("x", new NumExpr(5), new AddExpr(new VarExpr("x"), new NumExpr(3))))->to_pretty_string() == "_let x = 5\n_in x + 3" );
        CHECK((new letExpr("x", new NumExpr(5),new AddExpr(new letExpr("y", new NumExpr(3), new AddExpr(new VarExpr("y"), new NumExpr(2))), new VarExpr("x"))))->equals(new letExpr("x", new NumExpr(5),new AddExpr(new letExpr("y", new NumExpr(3), new AddExpr(new VarExpr("y"), new NumExpr(2))), new VarExpr("x")))) == true);
        CHECK((new letExpr("x", new NumExpr(5),new AddExpr(new letExpr("y", new NumExpr(3), new AddExpr(new VarExpr("y"), new NumExpr(2))), new VarExpr("x"))))->equals(new NumExpr(7)) == false);
        CHECK((new letExpr("x", new NumExpr(5), new AddExpr(new letExpr("y", new NumExpr(3), new AddExpr(new VarExpr("y"), new NumExpr(2))),new VarExpr("x"))))->has_variable() == true);
        // print
        CHECK((new letExpr("x", new NumExpr(5), new AddExpr(new letExpr("y", new NumExpr(3), new AddExpr(new VarExpr("y"), new NumExpr(2))),new VarExpr("x"))))->to_string() ==
              "(_let x=5 _in ((_let y=3 _in (y+2))+x))");
        CHECK((new letExpr("x", new NumExpr(5), new letExpr("x", new NumExpr(6), new AddExpr(new VarExpr("x"), new NumExpr(1)))))->to_string() ==
              "(_let x=5 _in (_let x=6 _in (x+1)))");
        // interp()
        CHECK((new letExpr("x", new NumExpr(5),new AddExpr(new letExpr("y", new NumExpr(3), new AddExpr(new VarExpr("y"), new NumExpr(2))), new VarExpr("x"))))->interp() ->equals(new NumVal(10)));


        // subst
        CHECK((new letExpr("x", new NumExpr(5), new letExpr("y", new NumExpr(6), new AddExpr(new VarExpr("x"), new NumExpr(1)))))->interp() ->equals(new NumVal(6)));
        CHECK((new letExpr("x", new AddExpr(new NumExpr(5), new NumExpr(2)), new AddExpr(new VarExpr("x"), new NumExpr(1))))->interp() ->equals(new NumVal(8)));
        CHECK((new letExpr("x", new NumExpr(5), new AddExpr(new VarExpr("x"), new NumExpr(3))))->to_pretty_string() ==
              "_let x = 5\n_in  x + 3");
        //        /Let nested as right argument of parenthesized multiplication expression

        //Let nested as right argument of parenthesized multiplication expression
        CHECK ((new MultExpr(new MultExpr(new NumExpr(2), new letExpr("x", new NumExpr(5), new AddExpr(new VarExpr("x"), new NumExpr(1)))),new NumExpr(3)))->to_pretty_string() == "(2 * _let x = 5\n"
                                                             "     _in  x + 1) * 3");
        //Let nested to the left in add expression which is nested to the right within a multiplication expression
        CHECK((new MultExpr(new NumExpr(5), new AddExpr(new letExpr("x", new NumExpr(5), new VarExpr("x")), new NumExpr(1))))->to_pretty_string() ==
              "5 * ((_let x = 5\n"
              "      _in  x) + 1)");

        //Let in lhs of add
        CHECK ( (new AddExpr(new letExpr("x", new NumExpr(2), new AddExpr(new VarExpr("x"), new NumExpr(9))), new NumExpr(4)))->to_pretty_string() == "(_let x = 2\n"" _in  x + 9) + 4");
        //Let in lhs of multiplication expression
        CHECK((new MultExpr(new letExpr("x", new NumExpr(5), new AddExpr(new VarExpr("x"), new NumExpr(8))), new NumExpr(3)))->to_pretty_string() == "(_let x = 5\n"" _in  x + 8) * 3");
        //Let nest as right argument of un-parenthesized multiplication expression
        CHECK((new AddExpr (new MultExpr(new NumExpr(4), new letExpr("x", new NumExpr(5), new AddExpr(new VarExpr("x"), new NumExpr(1)))), new NumExpr(9)))->to_pretty_string() == "4 * (_let x = 5\n"
                                                                                                                                               "     _in  x + 1) + 9");
        //Let nested in lhs of Add expression nested within body of let expression
        CHECK((new letExpr("x", new NumExpr(5), new AddExpr(new letExpr("y" , new NumExpr(3), new AddExpr(new VarExpr("y"), new NumExpr(2))), new VarExpr("x"))))
                      ->to_pretty_string() == "_let x = 5\n"
                                              "_in  (_let y = 3\n"
                                              "      _in  y + 2) + x");


        CHECK ((new AddExpr(new letExpr("x", new NumExpr(3), new letExpr("y", new NumExpr(3), new AddExpr(new VarExpr("y"), new NumExpr(2))) ), new VarExpr("x")))->to_pretty_string() == "(_let x = 3\n"
                                                                                                                                                              " _in  _let y = 3\n""      _in  y + 2) + x");
        CHECK_THROWS_WITH( (new VarExpr("x"))->interp(), "unbound variable: x" );
        CHECK( (new letExpr("x", new NumExpr(1), new letExpr("x", new NumExpr(2), new VarExpr("x")))) ->interp() ->equals(new NumVal(2)) );
    }

}
TEST_CASE ( "let equals" ){
    std::string name = "x";
    letExpr *let1 = new letExpr(name, new NumExpr(5), (new AddExpr (new VarExpr("x"), new NumExpr (4))));
    letExpr *sameLet1 = new letExpr(name, new NumExpr(5), (new AddExpr (new VarExpr("x"), new NumExpr (4))));
    letExpr *let2 = new letExpr(name, new NumExpr(5), (new AddExpr (new VarExpr("y"), new NumExpr (4))));
    CHECK((let1->equals(sameLet1))==true);
    CHECK((let1->equals(let2))==false);
}

TEST_CASE ("bool equals"){
    BoolExpr *true_bool = new BoolExpr(true);
    BoolExpr *true_bool_2 = new BoolExpr(true);
    BoolExpr *false_bool = new BoolExpr(false);
    BoolExpr *false_bool_2 = new BoolExpr(false);
    CHECK(true_bool->equals(true_bool_2));
    CHECK(false_bool->equals(false_bool_2));
}

TEST_CASE("if equals"){
    IfExpr *test = new IfExpr(new BoolExpr(true), new NumExpr(5), new NumExpr(2));
    IfExpr *same_test = new IfExpr(new BoolExpr(true), new NumExpr(5), new NumExpr(2));
    IfExpr *diff_test = new IfExpr(new BoolExpr(true), new NumExpr(5), new NumExpr(7));
    CHECK(test->equals(same_test));
    CHECK(test->equals(diff_test) == false);
}

TEST_CASE("equivalence equals"){
    CHECK((new EqExpr(new NumExpr(2), new NumExpr(0)))->equals(new EqExpr(new NumExpr(2), new NumExpr(0))) == true);
    CHECK((new EqExpr(new NumExpr(0), new NumExpr(1)))->equals(new EqExpr(new NumExpr(0), new NumExpr(0))) == false);
}

TEST_CASE ( "Object Comparisions" ){
    CHECK((new MultExpr(new NumExpr(0),new NumExpr(1)))->equals(new AddExpr(new NumExpr(1),new NumExpr(0))) == false);
    CHECK((new VarExpr("*"))->equals(new NumExpr(5)) == false);
    CHECK((new AddExpr(new NumExpr(0),new NumExpr(1)))->equals(new VarExpr("%")) == false);
    CHECK((new MultExpr(new NumExpr(0),new NumExpr(1)))->equals(new NumExpr(7)) == false);
    CHECK((new VarExpr("*"))->equals(new MultExpr(new NumExpr(0),new NumExpr(1))) == false);
    CHECK(((new letExpr("x", new NumExpr(5), (new AddExpr (new VarExpr("x"), new NumExpr (4)))))->equals(new MultExpr(new NumExpr(0),new NumExpr(1))))==false);
    CHECK((new BoolExpr(true))->equals(new AddExpr(new NumExpr(0), new NumExpr(2))) == false);
    CHECK((new IfExpr(new BoolExpr(true), new NumExpr(5), new NumExpr(2)))->equals(new AddExpr(new NumExpr(0), new NumExpr(2))) == false);
    CHECK((new EqExpr(new NumExpr(0), new NumExpr(3)))->equals(new NumExpr(5)) == false);
}

TEST_CASE ("EqExpr Pretty Print"){
    CHECK((new EqExpr(new NumExpr(-9), new NumExpr(-7)))->to_pretty_string() == "-9 == -7");
    CHECK((new AddExpr (new EqExpr(new NumExpr(7), new NumExpr(4)), new NumExpr(6)))->to_pretty_string() == "(7 == 4) + 6");
    CHECK((new AddExpr (new NumExpr(6), new EqExpr(new NumExpr(0), new NumExpr(3))))->to_pretty_string() == "6 + (0 == 3)");
    CHECK((new MultExpr (new EqExpr(new NumExpr(7), new NumExpr(4)), new NumExpr(6)))->to_pretty_string() == "(7 == 4) * 6");
    CHECK((new MultExpr (new NumExpr(6), new EqExpr(new NumExpr(0), new NumExpr(3))))->to_pretty_string() == "6 * (0 == 3)");
    CHECK((new EqExpr(new EqExpr(new NumExpr(1), new NumExpr(2)), new EqExpr(new NumExpr(3), new NumExpr(4))))->to_pretty_string() == "(1 == 2) == 3 == 4");
}


