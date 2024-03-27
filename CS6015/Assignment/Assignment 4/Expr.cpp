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

//bool VarExpr::has_variable(){
//    return true;
//}

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

//bool NumExpr::has_variable(){
//    return false;
//}

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
AddExpr::AddExpr(Expr *left, Expr *right) {
    lhs = left;
    rhs = right;
}

AddExpr::AddExpr(int left, int right) {
    lhs = new NumExpr(left);
    rhs = new NumExpr(right);
}

AddExpr::AddExpr(std::string left, int right) {
    lhs = new VarExpr(left);
    rhs = new NumExpr(right);
}

AddExpr::AddExpr(int left, std::string right) {
    lhs = new NumExpr(left);
    rhs = new VarExpr(right);
}
AddExpr::AddExpr(std::string left, std::string right) {
    lhs = new VarExpr(left);
    rhs = new VarExpr(right);
}

AddExpr::AddExpr(int left, Expr* right) {
    lhs = new NumExpr(left);
    rhs = right;
}
AddExpr::AddExpr(Expr* left, int right) {
    lhs = left;
    rhs = new NumExpr(right);
}

AddExpr::AddExpr(std::string left, Expr* right) {
    lhs = new VarExpr(left);
    rhs = right;
}

AddExpr::AddExpr(Expr* left, std::string right) {
    lhs = left;
    rhs = new VarExpr(right);
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

//bool AddExpr::has_variable(){
//    return lhs->has_variable() || rhs->has_variable();
//}
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

MultExpr::MultExpr(int left, int right) {
    lhs = new NumExpr(left);
    rhs = new NumExpr(right);
}
MultExpr::MultExpr(std::string left, int right) {
    lhs = new VarExpr(left);
    rhs = new NumExpr(right);
}
MultExpr::MultExpr(int left, std::string right) {
    lhs = new NumExpr(left);
    rhs = new VarExpr(right);
}
MultExpr::MultExpr(std::string left, std::string right) {
    lhs = new VarExpr(left);
    rhs = new VarExpr(right);
}
MultExpr::MultExpr(int left, Expr* right) {
    lhs = new NumExpr(left);
    rhs = right;
}
MultExpr::MultExpr(Expr* left, int right) {
    lhs = left;
    rhs = new NumExpr(right);
}
MultExpr::MultExpr(std::string left, Expr* right) {
    lhs = new VarExpr(left);
    rhs = right;
}
MultExpr::MultExpr(Expr* left, std::string right) {
    lhs = left;
    rhs = new VarExpr(right);
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

//bool MultExpr::has_variable() {
//    return lhs->has_variable() || rhs->has_variable();
//}

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

//bool letExpr::has_variable() {
//    // Check if the body expression contains a variable
//    return bodyExpr->has_variable();
//}

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


//bool BoolExpr::has_variable() {
//    return false;
//}

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

IfExpr::IfExpr(bool test, Expr* then, Expr* else_) {
    test_part = new BoolExpr(test);
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

//bool IfExpr::has_variable() {
//    return test_part->has_variable() || then_part->has_variable() || else_part->has_variable();
//}

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

EqExpr::EqExpr(std::string left, int right) {
    lhs = new VarExpr(left);
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

//bool EqExpr::has_variable() {
//    return lhs->has_variable() || rhs->has_variable();
//}

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
 * This is the FunExpr function
 *
 */

FunExpr::FunExpr(std::string arg, Expr* expr) {
    formal_arg = arg;
    body = expr;
}

bool FunExpr::equals(Expr *rhs) {
    FunExpr* other = dynamic_cast<FunExpr*>(rhs);
    if (other == nullptr) {
        return false;
    }
    return formal_arg == other->formal_arg && body->equals(other->body);
}

Val* FunExpr::interp() {
    return new FunVal(formal_arg, body);
}

Expr* FunExpr::subst(std::string s, Expr* expr) {
    if (formal_arg == s) {
        return this;
    }
    return new FunExpr(formal_arg, body->subst(s, expr));
}

void FunExpr::print(std::ostream& out) {
    out << "(_fun (" << formal_arg << ") ";
    body->print(out);
    out << ")";
}

void FunExpr::pretty_print(std::ostream& out, precedence_t precedence, std::streampos& newLinePrevPos, bool addParen) {
    if (addParen) {
        out << "(";
    }
    int indent = out.tellp() - newLinePrevPos;
    out << "_fun (" << formal_arg << ") \n";
    newLinePrevPos = out.tellp();

    out << std::string(indent + 2, ' ');
    body->pretty_print(out, prec_none, newLinePrevPos, false);
    if (addParen) {
        out << ")";
    }
}





/**
 * This is the CallExpr function
 *
 */
CallExpr::CallExpr(Expr* func, Expr* arg) {
    to_be_called = func;
    actual_arg = arg;
}

CallExpr::CallExpr(Expr* func, int n) {
    to_be_called = func;
    actual_arg = new NumExpr(n);
}

CallExpr::CallExpr(std::string funcName, int n) {
    to_be_called = new VarExpr(funcName);
    actual_arg = new NumExpr(n);
}

CallExpr::CallExpr(std::string funcName, Expr* arg) {
    to_be_called = new VarExpr(funcName);
    actual_arg = arg;
}

CallExpr::CallExpr(std::string funcName1, std::string funcName2) {
    to_be_called = new VarExpr(funcName1);
    actual_arg = new VarExpr(funcName2);
}

bool CallExpr::equals(Expr* rhs) {
    CallExpr* other = dynamic_cast<CallExpr*>(rhs);
    if (other == nullptr) {
        return false;
    }
    return to_be_called->equals(other->to_be_called) && actual_arg->equals(other->actual_arg);
}

Val* CallExpr::interp() {
    return to_be_called->interp()->call(actual_arg->interp());
}

Expr* CallExpr::subst(std::string s, Expr* expr) {
    return new CallExpr(to_be_called->subst(s, expr), actual_arg->subst(s, expr)); // TODO
}

void CallExpr::print(std::ostream& out) {
    to_be_called->print(out);
    out << "(";
    actual_arg->print(out);
    out << ")";
}

void CallExpr::pretty_print(std::ostream& out, precedence_t precedence, std::streampos& newLinePrevPos, bool addParen) {
    VarExpr* tmp1 = dynamic_cast<VarExpr*>(to_be_called);
    CallExpr* tmp2 = dynamic_cast<CallExpr*>(to_be_called);
    /**
     * var or call expressions don't need parentheses
     * e.g., f(2), f(2)(3),
     * other expression need parentheses
     * e.g. (_fun (x) x + 1)(2)
     */
    bool printParen = tmp1 == nullptr && tmp2 == nullptr;
    if (printParen) out << "(";
    to_be_called->pretty_print(out, prec_none, newLinePrevPos, false); // TODO
    if (printParen) out << ")";
    out << "(";
    actual_arg->pretty_print(out, prec_none, newLinePrevPos, false);
    out << ")";
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

        CHECK((new letExpr("x", new NumExpr(5),new AddExpr(new letExpr("y", new NumExpr(3), new AddExpr(new VarExpr("y"), new NumExpr(2))), new VarExpr("x"))))->equals(new letExpr("x", new NumExpr(5),new AddExpr(new letExpr("y", new NumExpr(3), new AddExpr(new VarExpr("y"), new NumExpr(2))), new VarExpr("x")))) == true);
        CHECK((new letExpr("x", new NumExpr(5),new AddExpr(new letExpr("y", new NumExpr(3), new AddExpr(new VarExpr("y"), new NumExpr(2))), new VarExpr("x"))))->equals(new NumExpr(7)) == false);
//        CHECK((new letExpr("x", new NumExpr(5), new AddExpr(new letExpr("y", new NumExpr(3), new AddExpr(new VarExpr("y"), new NumExpr(2))),new VarExpr("x"))))->has_variable() == true);
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

TEST_CASE("FunExpr") {
    FunExpr func1("x", new AddExpr("x", 1));
    FunExpr func2("x", new FunExpr("y", new AddExpr(new MultExpr("x", "x"), new MultExpr("y", "y"))));

    SECTION("equals") {
        CHECK(!func1.equals(new NumExpr(1)));
        CHECK(!func1.equals(new FunExpr("x", new AddExpr("x", 2))));
        CHECK(!func1.equals(new FunExpr("y", new AddExpr("x", 1))));
        CHECK(func1.equals(new FunExpr("x", new AddExpr("x", 1))));
    }

    SECTION("print") {
        CHECK(func1.to_string() == "(_fun (x) (x+1))");
        CHECK(func2.to_string() == "(_fun (x) (_fun (y) ((x*x)+(y*y))))");
    }

    SECTION("pretty_print") {
        CHECK(func1.to_pretty_string() == "_fun (x) \n"
                                          "  x + 1");

        CHECK(func2.to_pretty_string() == "_fun (x) \n"
                                          "  _fun (y) \n"
                                          "    x * x + y * y");
    }
}

TEST_CASE("CallExpr") {
    FunExpr func1("x", new AddExpr("x", 1));
    FunExpr func2("y", new AddExpr("y", 2));
    CallExpr call1(&func1, 2);

    SECTION("equals") {
        CHECK(call1.equals(new CallExpr(new FunExpr("x", new AddExpr("x", 1)), 2)));
        CHECK(!call1.equals(new NumExpr(2)));
        CHECK(!call1.equals(new CallExpr(&func1, 3)));
        CHECK(!call1.equals(new CallExpr(new FunExpr("x", new MultExpr("x", 2)), 2)));
    }

    SECTION("interp + print + pretty-print") {
        CHECK(call1.interp()->equals(new NumVal(3)));
        CHECK(call1.to_string() == "(_fun (x) (x+1))(2)");
        CHECK(call1.to_pretty_string() == "(_fun (x) \n"
                                          "   x + 1)(2)");
        // let + fun + call
        letExpr call2("f", &func1, new CallExpr(new VarExpr("f"), 2));
        CHECK(call2.interp()->equals(new NumVal(3)));
        CHECK(call2.to_string() == "(_let f=(_fun (x) (x+1)) _in f(2))");
        CHECK(call2.to_pretty_string() == "_let f = _fun (x) \n"
                                          "           x + 1\n"
                                          "_in  f(2)");
        // let + fun + (if + call)
        letExpr call3("f", &func1, new IfExpr(false, new CallExpr("f", 5), new CallExpr("f", 6)));
        CHECK(call3.interp()->equals(new NumVal(7)));
        CHECK(call3.to_pretty_string() == "_let f = _fun (x) \n"
                                          "           x + 1\n"
                                          "_in  _if _false\n"
                                          "     _then f(5)\n"
                                          "     _else f(6)");

        // 2 func2
        letExpr call4("f", &func1,
                      new letExpr("g", &func2, new IfExpr(true, new CallExpr("f", 5), new CallExpr("g", 6))));
        CHECK(call4.interp()->equals(new NumVal(6)));
        CHECK(call4.to_pretty_string() == "_let f = _fun (x) \n"
                                          "           x + 1\n"
                                          "_in  _let g = _fun (y) \n"
                                          "                y + 2\n"
                                          "     _in  _if _true\n"
                                          "          _then f(5)\n"
                                          "          _else g(6)");
        letExpr call5("f", &func1,
                      new letExpr("g", new FunExpr("y", new CallExpr("f", new AddExpr("y", 2))), new CallExpr("g", 5)));
        CHECK(call5.interp()->equals(new NumVal(8)));
        CHECK(call5.to_pretty_string() == "_let f = _fun (x) \n"
                                          "           x + 1\n"
                                          "_in  _let g = _fun (y) \n"
                                          "                f(y + 2)\n"
                                          "     _in  g(5)");
        letExpr call6("f", &func1,
                      new letExpr("g", new FunExpr("x", new AddExpr(new CallExpr("f", 2), "x")), new CallExpr("g", 5)));
        CHECK(call6.interp()->equals(new NumVal(8)));
        CHECK(call6.to_pretty_string() == "_let f = _fun (x) \n"
                                          "           x + 1\n"
                                          "_in  _let g = _fun (x) \n"
                                          "                f(2) + x\n"
                                          "     _in  g(5)");
        letExpr call7("f", new IfExpr(false, &func1, &func2), new CallExpr("f", 5));
        CHECK(call7.interp()->equals(new NumVal(7)));
        CHECK(call7.to_pretty_string() == "_let f = _if _false\n"
                                          "         _then _fun (x) \n"
                                          "                 x + 1\n"
                                          "         _else _fun (y) \n"
                                          "                 y + 2\n"
                                          "_in  f(5)");
        CallExpr call8(new IfExpr(false, &func1, &func2), new NumExpr(5));
        CHECK(call8.interp()->equals(new NumVal(7)));
        CHECK(call8.to_pretty_string() == "(_if _false\n"
                                          " _then _fun (x) \n"
                                          "         x + 1\n"
                                          " _else _fun (y) \n"
                                          "         y + 2)(5)");
        letExpr call9("f", new FunExpr("g", new CallExpr("g", 5)), new letExpr("g", &func2, new CallExpr("f", "g")));
        CHECK(call9.interp()->equals(new NumVal(7)));
        CHECK(call9.to_pretty_string() == "_let f = _fun (g) \n"
                                          "           g(5)\n"
                                          "_in  _let g = _fun (y) \n"
                                          "                y + 2\n"
                                          "     _in  f(g)");
        letExpr call10("f", new FunExpr("g", new CallExpr("g", 5)), new CallExpr("f", &func2));
        CHECK(call10.interp()->equals(new NumVal(7)));
        CHECK(call10.to_pretty_string() == "_let f = _fun (g) \n"
                                           "           g(5)\n"
                                           "_in  f(_fun (y) \n"
                                           "         y + 2)");
        letExpr call11("f", new FunExpr("x", new FunExpr("y", new AddExpr("x", "y"))),
                       new CallExpr(new CallExpr("f", 5), 1));
        CHECK(call11.interp()->equals(new NumVal(6))); // TODO how does this work?
        letExpr call12("y", new NumExpr(8),
                       new letExpr("f", new FunExpr("x", new MultExpr("x", "y")), new CallExpr("f", 2)));
        CHECK(call12.interp()->equals(new NumVal(16)));
        CHECK(call12.to_pretty_string() == "_let y = 8\n"
                                           "_in  _let f = _fun (x) \n"
                                           "                x * y\n"
                                           "     _in  f(2)");
        letExpr call13("x", new NumExpr(8),
                       new letExpr("f", new FunExpr("x", new MultExpr("x", "x")), new CallExpr("f", 2)));
        CHECK(call13.interp()->equals(new NumVal(4)));
        CHECK(call13.to_pretty_string() == "_let x = 8\n"
                                           "_in  _let f = _fun (x) \n"
                                           "                x * x\n"
                                           "     _in  f(2)");
        letExpr call14("f", new FunExpr("x", new AddExpr("x", "y")),
                       new letExpr("y", new NumExpr(10), new CallExpr("f", 1)));
        CHECK(call14.interp()->equals(new NumVal(11))); // TODO substitution bug
        CHECK(call14.to_pretty_string() == "_let f = _fun (x) \n"
                                           "           x + y\n"
                                           "_in  _let y = 10\n"
                                           "     _in  f(1)");
        letExpr call15("f",
                       new FunExpr("x", new FunExpr("y", new AddExpr(new MultExpr("x", "x"), new MultExpr("y", "y")))),
                       new CallExpr(new CallExpr("f", 2), 3));
        CHECK(call15.interp()->equals(new NumVal(13)));
        CHECK(call15.to_pretty_string() == "_let f = _fun (x) \n"
                                           "           _fun (y) \n"
                                           "             x * x + y * y\n"
                                           "_in  f(2)(3)");
        letExpr call16("factrl", new FunExpr("factrl", new FunExpr("x", new IfExpr(new EqExpr("x", 1), new NumExpr(1),
                                                                                   new MultExpr("x", new CallExpr(
                                                                                           new CallExpr("factrl",
                                                                                                        "factrl"),
                                                                                           new AddExpr("x", -1)))))),
                       new CallExpr(new CallExpr("factrl", "factrl"), 10));
        CHECK(call16.interp()->equals(new NumVal(3628800)));
        CHECK(call16.to_pretty_string() == "_let factrl = _fun (factrl) \n"
                                           "                _fun (x) \n"
                                           "                  _if x == 1\n"
                                           "                  _then 1\n"
                                           "                  _else x * factrl(factrl)(x + -1)\n"
                                           "_in  factrl(factrl)(10)"); // TODO
    }
}


