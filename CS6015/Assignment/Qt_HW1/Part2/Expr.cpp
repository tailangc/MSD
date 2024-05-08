#include "Expr.h"
#include "iostream"
#include "Val.h"
#include "pointer.h"
#include "env.h"
//using namespace std;
//
/**
 * this is the value function
 * @param val
 */
VarExpr::VarExpr(std::string val){ //constructor for var
    this->val = val;
}

bool VarExpr::equals(PTR(Expr) e) { //Check if the given expression is equal to this Var instance.
    PTR(VarExpr) v = CAST (VarExpr)(e);
    if(v == nullptr){
        return false;
    } else{
        return (this->val == v->val);
    }
}

PTR(Val) VarExpr::interp(PTR(Env) env){
    return env->lookup(val);
}

//bool VarExpr::has_variable(){
//    return true;
//}

PTR(Expr) VarExpr::subst(std::string replace,PTR(Expr) s){ //Substitute a variable in the expression with another expression.
    if(this->val == replace){
        return s;
    }else{
        return THIS;
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

bool NumExpr::equals(PTR(Expr) e) {
    PTR(NumExpr) n = CAST(NumExpr) (e);
    if(n== nullptr){
        return false;
    } else{
        return (this->val == n->val);
    }
}

PTR(Val) NumExpr::interp(PTR(Env) env){
    return NEW (NumVal)(this->val);
}

//bool NumExpr::has_variable(){
//    return false;
//}

PTR(Expr) NumExpr::subst(std::string replace,PTR(Expr) s) { //No substitution needed for Num instances,
    return THIS;
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
AddExpr::AddExpr(PTR(Expr) left, PTR(Expr) right) {
    lhs = left;
    rhs = right;
}

AddExpr::AddExpr(int left, int right) {
    lhs = NEW (NumExpr)(left);
    rhs = NEW (NumExpr)(right);
}

AddExpr::AddExpr(std::string left, int right) {
    lhs = NEW (VarExpr)(left);
    rhs = NEW (NumExpr)(right);
}

AddExpr::AddExpr(int left, std::string right) {
    lhs = NEW (NumExpr)(left);
    rhs = NEW (VarExpr)(right);
}
AddExpr::AddExpr(std::string left, std::string right) {
    lhs = NEW (VarExpr)(left);
    rhs = NEW (VarExpr)(right);
}

AddExpr::AddExpr(int left, PTR(Expr) right) {
    lhs = NEW (NumExpr)(left);
    rhs = right;
}
AddExpr::AddExpr(PTR(Expr) left, int right) {
    lhs = left;
    rhs = NEW (NumExpr)(right);
}

AddExpr::AddExpr(std::string left, PTR(Expr) right) {
    lhs = NEW (VarExpr)(left);
    rhs = right;
}

AddExpr::AddExpr(PTR(Expr) left, std::string right) {
    lhs = left;
    rhs = NEW (VarExpr)(right);
}

bool AddExpr::equals(PTR(Expr) e) {
    PTR(AddExpr) a = CAST(AddExpr)(e);
    if (a == nullptr) {
        return false;
    } else {
        return (this->lhs->equals(a->lhs) && this->rhs->equals(a->rhs));
    }
}

PTR(Val) AddExpr::interp(PTR(Env) env){
    return lhs->interp(env) -> add_to(rhs->interp(env))  ;
}

//bool AddExpr::has_variable(){
//    return lhs->has_variable() || rhs->has_variable();
//}
PTR(Expr) AddExpr::subst(std::string replace,PTR(Expr) s) {
    return NEW (AddExpr)(lhs->subst(replace,s),rhs->subst(replace,s));
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
MultExpr::MultExpr(PTR(Expr) lhs, PTR(Expr) rhs){
    this->lhs = lhs;
    this->rhs = rhs;
}

MultExpr::MultExpr(int left, int right) {
    lhs = NEW (NumExpr)(left);
    rhs = NEW (NumExpr)(right);
}
MultExpr::MultExpr(std::string left, int right) {
    lhs = NEW (VarExpr)(left);
    rhs = NEW (NumExpr)(right);
}
MultExpr::MultExpr(int left, std::string right) {
    lhs = NEW (NumExpr)(left);
    rhs = NEW (VarExpr)(right);
}
MultExpr::MultExpr(std::string left, std::string right) {
    lhs = NEW (VarExpr)(left);
    rhs = NEW (VarExpr)(right);
}
MultExpr::MultExpr(int left, PTR(Expr) right) {
    lhs = NEW (NumExpr)(left);
    rhs = right;
}
MultExpr::MultExpr(PTR(Expr) left, int right) {
    lhs = left;
    rhs = NEW (NumExpr)(right);
}
MultExpr::MultExpr(std::string left, PTR(Expr) right) {
    lhs = NEW (VarExpr)(left);
    rhs = right;
}
MultExpr::MultExpr(PTR(Expr) left, std::string right) {
    lhs = left;
    rhs = NEW (VarExpr)(right);
}


bool MultExpr::equals(PTR(Expr) e){
    PTR(MultExpr) m = CAST(MultExpr)(e);
    if (m == nullptr) {
        return false;
    } else {
        return (this->lhs->equals(m->lhs) && this->rhs->equals(m->rhs));
    }
}

PTR(Val) MultExpr::interp(PTR(Env) env){
    return this->lhs->interp(env) ->mult_to(this->rhs->interp(env))  ;
}

//bool MultExpr::has_variable() {
//    return lhs->has_variable() || rhs->has_variable();
//}

PTR(Expr) MultExpr::subst(std::string replace, PTR(Expr) s) {
    return NEW( MultExpr)(lhs->subst(replace,s),rhs->subst(replace,s));
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
letExpr::letExpr(std::string variable, PTR(Expr) valueExpr, PTR(Expr) bodyExpr){
    this -> variable = variable;
    this -> valueExpr = valueExpr;
    this -> bodyExpr = bodyExpr;
}

bool letExpr::equals(PTR(Expr) e){
    // Check if the given expression `e` is a LetExpr with the same variable, value expression, and body expression
    PTR(letExpr) letExpr = CAST(class letExpr)(e);

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

PTR(Val) letExpr::interp(PTR(Env) env) {
    // Interpret the value expression and substitute the variable with the result in the body expression
//    PTR(Expr) substitutedBody = bodyExpr->subst(variable, valueExpr);
    PTR(Val) valueExpr_env = valueExpr ->interp(env);
    PTR(Env) new_env = NEW(ExtendedEnv) (variable, valueExpr_env, env);
    return bodyExpr->interp(new_env);

}

//bool letExpr::has_variable() {
//    // Check if the body expression contains a variable
//    return bodyExpr->has_variable();
//}

PTR(Expr) letExpr::subst(std::string var, PTR(Expr) s){
    // Substitute the variable `var` with the expression `s` in the value expression and body expression
    if(var == variable){
        return NEW (letExpr)(variable, valueExpr->subst(var,s), bodyExpr);
    }
    PTR(Expr) substitutedValue = valueExpr->subst(var, s);
    PTR(Expr) substitutedBody = bodyExpr->subst(var, s);
    return NEW (letExpr)(variable, substitutedValue, substitutedBody);
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

bool BoolExpr::equals(PTR(Expr) rhs) {
    PTR(BoolExpr) other = CAST (BoolExpr) (rhs);
    if (other == nullptr) {
        return false;
    }
    return val == other->val;
}

PTR(Val) BoolExpr::interp(PTR(Env) env) {
    return NEW (BoolVal)(val);
}


//bool BoolExpr::has_variable() {
//    return false;
//}

PTR(Expr) BoolExpr::subst(std::string s, PTR(Expr) expr) {
    return THIS;
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
IfExpr::IfExpr(PTR(Expr) test, PTR(Expr) then, PTR(Expr) else_) {
    test_part = test;
    then_part = then;
    else_part = else_;
}

IfExpr::IfExpr(bool test, PTR(Expr) then, PTR(Expr) else_) {
    test_part = NEW (BoolExpr)(test);
    then_part = then;
    else_part = else_;
}


bool IfExpr::equals(PTR(Expr) rhs) {
    PTR(IfExpr) other = CAST (IfExpr)(rhs);
    if (other == nullptr) {
        return false;
    }
    return test_part->equals(other->test_part) && then_part->equals(other->then_part) && else_part->equals(other->else_part);
}

PTR(Val) IfExpr::interp(PTR(Env) env) {
    if (test_part->interp(env)->is_true()) {
        return then_part->interp(env);
    }
    return else_part->interp(env);
}

//bool IfExpr::has_variable() {
//    return test_part->has_variable() || then_part->has_variable() || else_part->has_variable();
//}

PTR(Expr) IfExpr::subst(std::string s, PTR(Expr) expr) {
    return NEW (IfExpr)(test_part->subst(s, expr), then_part->subst(s, expr), else_part->subst(s, expr));
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

EqExpr::EqExpr(PTR(Expr) left, PTR(Expr) right) {
    lhs = left;
    rhs = right;
}

EqExpr::EqExpr(int left, int right) {
    lhs = NEW (NumExpr)(left);
    rhs = NEW (NumExpr)(right);
}

EqExpr::EqExpr(std::string left, int right) {
    lhs = NEW (VarExpr)(left);
    rhs = NEW (NumExpr)(right);
}

bool EqExpr::equals(PTR(Expr) rhs_) {
    PTR(EqExpr) other = CAST(EqExpr)(rhs_);
    if (other == nullptr) {
        return false;
    }
    return lhs->equals(other->lhs) && rhs->equals(other->rhs);
}

PTR(Val) EqExpr::interp(PTR(Env) env) {
    return NEW (BoolVal)(lhs->interp(env)->equals(rhs->interp(env)));
}

//bool EqExpr::has_variable() {
//    return lhs->has_variable() || rhs->has_variable();
//}

PTR(Expr) EqExpr::subst(std::string s, PTR(Expr) expr) {
    return NEW (EqExpr)(lhs->subst(s, expr), rhs->subst(s, expr));
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

FunExpr::FunExpr(std::string arg, PTR(Expr) expr) {
    formal_arg = arg;
    body = expr;
}

bool FunExpr::equals(PTR(Expr) rhs) {
    PTR(FunExpr) other = CAST (FunExpr)(rhs);
    if (other == nullptr) {
        return false;
    }
    return formal_arg == other->formal_arg && body->equals(other->body);
}

PTR(Val) FunExpr::interp(PTR(Env) env) {
    return NEW (FunVal) (formal_arg, body, env);
}

PTR(Expr) FunExpr::subst(std::string s, PTR(Expr) expr) {
    if (formal_arg == s) {
        return THIS;
    }
    return NEW (FunExpr)(formal_arg, body->subst(s, expr));
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
CallExpr::CallExpr(PTR(Expr) func, PTR(Expr) arg) {
    to_be_called = func;
    actual_arg = arg;
}

CallExpr::CallExpr(PTR(Expr) func, int n) {
    to_be_called = func;
    actual_arg = NEW (NumExpr)(n);
}

CallExpr::CallExpr(std::string funcName, int n) {
    to_be_called = NEW (VarExpr)(funcName);
    actual_arg = NEW (NumExpr)(n);
}

CallExpr::CallExpr(std::string funcName, PTR(Expr) arg) {
    to_be_called = NEW (VarExpr)(funcName);
    actual_arg = arg;
}

CallExpr::CallExpr(std::string funcName1, std::string funcName2) {
    to_be_called = NEW( VarExpr)(funcName1);
    actual_arg = NEW (VarExpr)(funcName2);
}

bool CallExpr::equals(PTR(Expr) rhs) {
    PTR(CallExpr) other = CAST(CallExpr)(rhs);
    if (other == nullptr) {
        return false;
    }
    return to_be_called->equals(other->to_be_called) && actual_arg->equals(other->actual_arg);
}

PTR(Val) CallExpr::interp(PTR(Env) env) {
    return to_be_called->interp(env)->call(actual_arg->interp(env));
}

PTR(Expr) CallExpr::subst(std::string s, PTR(Expr) expr) {
    return NEW (CallExpr)(to_be_called->subst(s, expr), actual_arg->subst(s, expr)); // TODO
}

void CallExpr::print(std::ostream& out) {
    to_be_called->print(out);
    out << "(";
    actual_arg->print(out);
    out << ")";
}

void CallExpr::pretty_print(std::ostream& out, precedence_t precedence, std::streampos& newLinePrevPos, bool addParen) {
    PTR(VarExpr) tmp1 = CAST(VarExpr)(to_be_called);
    PTR(CallExpr) tmp2 = CAST(CallExpr)(to_be_called);
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





// /**
//  * this is the Test case
//  */
// TEST_CASE( "Tests") {
//     SECTION("HW3") {
//         CHECK((NEW (VarExpr)("x"))->equals(NEW (VarExpr)("x")) == true);
//         CHECK((NEW (VarExpr)("x"))->equals(NEW (VarExpr)("y")) == false);
//         CHECK((NEW (NumExpr)(1))->equals(NEW (VarExpr)("x")) == false);
//         CHECK((NEW (NumExpr)(1))->equals(NEW (NumExpr)(1)) == true);
//         CHECK((NEW (AddExpr)(NEW (NumExpr)(2), NEW (NumExpr)(3)))->equals(NEW (AddExpr)(NEW (NumExpr)(2), NEW (NumExpr)(3))) == true);
//         CHECK((NEW (AddExpr)(NEW (NumExpr)(2), NEW (NumExpr)(3)))->equals(NEW (AddExpr)(NEW (NumExpr)(3), NEW (NumExpr)(2))) == false);
//         CHECK((NEW (AddExpr)(NEW (NumExpr)(-2), NEW (NumExpr)(-3)))->equals(NEW (AddExpr)(NEW (NumExpr)(-2), NEW (NumExpr)(-3))) == true);
//         CHECK((NEW (AddExpr)(NEW (NumExpr)(-2), NEW (NumExpr)(0)))->equals(NEW (AddExpr)(NEW (NumExpr)(-2), NEW (NumExpr)(0))) == true);
//         CHECK((NEW (MultExpr)(NEW (NumExpr)(2), NEW (NumExpr)(3)))->equals(NEW (MultExpr)(NEW (NumExpr)(3), NEW (NumExpr)(2))) == false);
//         CHECK((NEW (MultExpr)(NEW (NumExpr)(2), NEW (NumExpr)(3)))->equals(NEW (MultExpr)(NEW (NumExpr)(2), NEW (NumExpr)(3))) == true);
//         CHECK((NEW (MultExpr)(NEW (NumExpr)(-2), NEW (NumExpr)(-3)))->equals(NEW (MultExpr)(NEW (NumExpr)(-2), NEW (NumExpr)(-3))) == true);
//         CHECK((NEW (MultExpr)(NEW (NumExpr)(-2), NEW (NumExpr)(0)))->equals(NEW (MultExpr)(NEW (NumExpr)(-2), NEW (NumExpr)(0))) == true);
// //CHECK_THROWS_WITH( (new Var("x"))->interp(), "no value for variable" );
//         CHECK((NEW (MultExpr)(NEW (NumExpr)(3), NEW (NumExpr)(2)))->interp(Env::empty) ->equals(NEW (NumVal)(6)));
//         CHECK((NEW (MultExpr)(NEW (NumExpr)(0), NEW (NumExpr)(3)))->interp(Env::empty) ->equals(NEW (NumVal)(0)));
//         CHECK((NEW (AddExpr)(NEW (AddExpr)(NEW (NumExpr)(10), NEW (NumExpr)(15)), NEW (AddExpr)(NEW (NumExpr)(20), NEW (NumExpr)(20))))->interp(Env::empty) ->equals(NEW (NumVal)(65)));
//         CHECK((NEW (AddExpr)(NEW (NumExpr)(8), NEW (NumExpr)(2)))->interp(Env::empty) ->equals(NEW (NumVal)(10)));
//         CHECK((NEW (AddExpr)(NEW (NumExpr)(8), NEW (AddExpr)(NEW (NumExpr)(10), NEW (NumExpr)(12))))->interp(Env::empty) ->equals(NEW (NumVal)(30)));
//         CHECK((NEW (AddExpr)(NEW (VarExpr)("x"), NEW (NumExpr)(7)))->subst("x", NEW (VarExpr)("y"))
//                       ->equals(NEW (AddExpr)(NEW (VarExpr)("y"), NEW (NumExpr)(7))));
//         CHECK((NEW (VarExpr)("x"))
//                       ->subst("x", NEW (AddExpr)(NEW (VarExpr)("y"), NEW (NumExpr)(7)))
//                       ->equals(NEW (AddExpr)(NEW (VarExpr)("y"), NEW (NumExpr)(7))));
//         CHECK((NEW (VarExpr)("x"))
//                       ->subst("x", NEW (NumExpr)(3))
//                       ->equals(NEW (NumExpr)(3)));

//         CHECK((NEW (AddExpr)(NEW (VarExpr)("x"), NEW (NumExpr)(5)))
//                       ->subst("x", NEW (NumExpr)(2))
//                       ->equals(NEW (AddExpr)(NEW (NumExpr)(2), NEW (NumExpr)(5))));

//         CHECK((NEW (MultExpr)(NEW (VarExpr)("x"), NEW (NumExpr)(4)))
//                       ->subst("x", NEW (NumExpr)(6))
//                       ->equals(NEW (MultExpr)(NEW (NumExpr)(6), NEW (NumExpr)(4))));

//         CHECK((NEW (AddExpr)(NEW (VarExpr)("x"), NEW (VarExpr)("x")))
//                       ->subst("x", NEW (NumExpr)(10))
//                       ->equals(NEW (AddExpr)(NEW (NumExpr)(10), NEW (NumExpr)(10))));

//         CHECK((NEW (MultExpr)(NEW (AddExpr)(NEW (VarExpr)("x"), NEW (NumExpr)(2)), NEW (VarExpr)("x")))
//                       ->subst("x", NEW (NumExpr)(8))
//                       ->equals(NEW (MultExpr)(NEW (AddExpr)(NEW (NumExpr)(8), NEW (NumExpr)(2)), NEW (NumExpr)(8))));

//     }

//     SECTION("HW4") {
//         CHECK ((NEW (MultExpr)(NEW (NumExpr)(1), NEW (AddExpr)(NEW (NumExpr)(2), NEW (NumExpr)(3))))->to_pretty_string() == "1 * (2 + 3)");
//         CHECK ((NEW (MultExpr)(NEW (MultExpr)(NEW (NumExpr)(8), NEW (NumExpr)(1)), NEW (VarExpr)("y")))->to_pretty_string() == "(8 * 1) * y");
//         CHECK ((NEW (MultExpr)(NEW (AddExpr)(NEW (NumExpr)(3), NEW (NumExpr)(5)), NEW (MultExpr)(NEW (NumExpr)(6), NEW (NumExpr)(1))))->to_pretty_string() ==
//                "(3 + 5) * 6 * 1");
//         CHECK ((NEW (MultExpr)(NEW (MultExpr)(NEW (NumExpr)(7), NEW (NumExpr)(7)), NEW (AddExpr)(NEW (NumExpr)(9), NEW (NumExpr)(2))))->to_pretty_string() ==
//                "(7 * 7) * (9 + 2)");
//     }

//     SECTION("HW5") {

//         CHECK((NEW (letExpr)("x", NEW (NumExpr)(5),NEW (AddExpr)(NEW (letExpr)("y", NEW (NumExpr)(3), NEW (AddExpr)(NEW (VarExpr)("y"), NEW (NumExpr)(2))), NEW (VarExpr)("x"))))->equals(NEW (letExpr)("x", NEW (NumExpr)(5),NEW (AddExpr)(NEW (letExpr)("y", NEW (NumExpr)(3), NEW (AddExpr)(NEW (VarExpr)("y"), NEW (NumExpr)(2))), NEW (VarExpr)("x")))) == true);
//         CHECK((NEW (letExpr)("x", NEW (NumExpr)(5),NEW (AddExpr)(NEW (letExpr)("y", NEW (NumExpr)(3), NEW (AddExpr)(NEW (VarExpr)("y"), NEW (NumExpr)(2))), NEW (VarExpr)("x"))))->equals(NEW (NumExpr)(7)) == false);
// //        CHECK((NEW (letExpr)("x", NEW (NumExpr)(5), NEW (AddExpr)(NEW (letExpr)("y", NEW (NumExpr)(3), NEW (AddExpr)(NEW (VarExpr)("y"), NEW (NumExpr)(2))),NEW (VarExpr)("x"))))->has_variable() == true);
//         // print
//         CHECK((NEW (letExpr)("x", NEW (NumExpr)(5), NEW (AddExpr)(NEW (letExpr)("y", NEW (NumExpr)(3), NEW (AddExpr)(NEW (VarExpr)("y"), NEW (NumExpr)(2))),NEW (VarExpr)("x"))))->to_string() ==
//               "(_let x=5 _in ((_let y=3 _in (y+2))+x))");
//         CHECK((NEW (letExpr)("x", NEW (NumExpr)(5), NEW (letExpr)("x", NEW (NumExpr)(6), NEW (AddExpr)(NEW (VarExpr)("x"), NEW (NumExpr)(1)))))->to_string() ==
//               "(_let x=5 _in (_let x=6 _in (x+1)))");
//         // interp()
//         CHECK((NEW (letExpr)("x", NEW (NumExpr)(5),NEW (AddExpr)(NEW (letExpr)("y", NEW (NumExpr)(3), NEW (AddExpr)(NEW (VarExpr)("y"), NEW (NumExpr)(2))), NEW (VarExpr)("x"))))->interp(Env::empty) ->equals(NEW (NumVal)(10)));


//         // subst
//         CHECK((NEW (letExpr)("x", NEW (NumExpr)(5), NEW (letExpr)("y", NEW (NumExpr)(6), NEW (AddExpr)(NEW (VarExpr)("x"), NEW (NumExpr)(1)))))->interp(Env::empty) ->equals(NEW (NumVal)(6)));
//         CHECK((NEW (letExpr)("x", NEW (AddExpr)(NEW (NumExpr)(5), NEW (NumExpr)(2)), NEW (AddExpr)(NEW (VarExpr)("x"), NEW (NumExpr)(1))))->interp(Env::empty) ->equals(NEW (NumVal)(8)));
//         CHECK((NEW (letExpr)("x", NEW (NumExpr)(5), NEW (AddExpr)(NEW (VarExpr)("x"), NEW (NumExpr)(3))))->to_pretty_string() ==
//               "_let x = 5\n_in  x + 3");
//         //        /Let nested as right argument of parenthesized multiplication expression

//         //Let nested as right argument of parenthesized multiplication expression
//         CHECK ((NEW (MultExpr)(NEW (MultExpr)(NEW (NumExpr)(2), NEW (letExpr)("x", NEW (NumExpr)(5), NEW (AddExpr)(NEW (VarExpr)("x"), NEW (NumExpr)(1)))),NEW (NumExpr)(3)))->to_pretty_string() == "(2 * _let x = 5\n"
//                                                              "     _in  x + 1) * 3");
//         //Let nested to the left in add expression which is nested to the right within a multiplication expression
//         CHECK((NEW (MultExpr)(NEW (NumExpr)(5), NEW (AddExpr)(NEW (letExpr)("x", NEW (NumExpr)(5), NEW (VarExpr)("x")), NEW (NumExpr)(1))))->to_pretty_string() ==
//               "5 * ((_let x = 5\n"
//               "      _in  x) + 1)");

//         //Let in lhs of add
//         CHECK ( (NEW (AddExpr)(NEW (letExpr)("x", NEW (NumExpr)(2), NEW (AddExpr)(NEW (VarExpr)("x"), NEW (NumExpr)(9))), NEW (NumExpr)(4)))->to_pretty_string() == "(_let x = 2\n"" _in  x + 9) + 4");
//         //Let in lhs of multiplication expression
//         CHECK((NEW (MultExpr)(NEW (letExpr)("x", NEW (NumExpr)(5), NEW (AddExpr)(NEW (VarExpr)("x"), NEW (NumExpr)(8))), NEW (NumExpr)(3)))->to_pretty_string() == "(_let x = 5\n"" _in  x + 8) * 3");
//         //Let nest as right argument of un-parenthesized multiplication expression
//         CHECK((NEW (AddExpr) (NEW (MultExpr)(NEW (NumExpr)(4), NEW (letExpr)("x", NEW (NumExpr)(5), NEW (AddExpr)(NEW (VarExpr)("x"), NEW (NumExpr)(1)))), NEW (NumExpr)(9)))->to_pretty_string() == "4 * (_let x = 5\n"
//                                                                                                                                                "     _in  x + 1) + 9");
//         //Let nested in lhs of Add expression nested within body of let expression
//         CHECK((NEW (letExpr)("x", NEW (NumExpr)(5), NEW (AddExpr)(NEW (letExpr)("y" , NEW (NumExpr)(3), NEW (AddExpr)(NEW (VarExpr)("y"), NEW (NumExpr)(2))), NEW (VarExpr)("x"))))
//                       ->to_pretty_string() == "_let x = 5\n"
//                                               "_in  (_let y = 3\n"
//                                               "      _in  y + 2) + x");


//         CHECK ((NEW (AddExpr)(NEW (letExpr)("x", NEW (NumExpr)(3), NEW (letExpr)("y", NEW (NumExpr)(3), NEW (AddExpr)(NEW (VarExpr)("y"), NEW (NumExpr)(2))) ), NEW (VarExpr)("x")))->to_pretty_string() == "(_let x = 3\n"
//                                                                                                                                                               " _in  _let y = 3\n""      _in  y + 2) + x");
// //        CHECK_THROWS_WITH( (NEW (VarExpr)("x"))->interp(Env::empty), "unbound variable: x" );
//         CHECK( (NEW (letExpr)("x", NEW (NumExpr)(1), NEW (letExpr)("x", NEW (NumExpr)(2), NEW (VarExpr)("x")))) ->interp(Env::empty) ->equals(NEW (NumVal)(2)) );
//     }

// }
// TEST_CASE ( "let equals" ){
//     std::string name = "x";
//     PTR(letExpr) let1 = NEW (letExpr)(name, NEW (NumExpr)(5), (NEW (AddExpr) (NEW (VarExpr)("x"), NEW (NumExpr) (4))));
//     PTR(letExpr) sameLet1 = NEW (letExpr)(name, NEW (NumExpr)(5), (NEW (AddExpr) (NEW (VarExpr)("x"), NEW (NumExpr) (4))));
//     PTR(letExpr) let2 = NEW (letExpr)(name, NEW (NumExpr)(5), (NEW (AddExpr) (NEW (VarExpr)("y"), NEW (NumExpr) (4))));
//     CHECK((let1->equals(sameLet1))==true);
//     CHECK((let1->equals(let2))==false);
// }

// TEST_CASE ("bool equals"){
//     PTR(BoolExpr) true_bool = NEW (BoolExpr)(true);
//     PTR(BoolExpr) true_bool_2 = NEW (BoolExpr)(true);
//     PTR(BoolExpr) false_bool = NEW (BoolExpr)(false);
//     PTR(BoolExpr) false_bool_2 = NEW (BoolExpr)(false);
//     CHECK(true_bool->equals(true_bool_2));
//     CHECK(false_bool->equals(false_bool_2));
// }

// TEST_CASE("if equals"){
//     PTR(IfExpr) test = NEW (IfExpr)(NEW (BoolExpr)(true), NEW (NumExpr)(5), NEW (NumExpr)(2));
//     PTR(IfExpr) same_test = NEW (IfExpr)(NEW (BoolExpr)(true), NEW (NumExpr)(5), NEW (NumExpr)(2));
//     PTR(IfExpr) diff_test = NEW (IfExpr)(NEW (BoolExpr)(true), NEW (NumExpr)(5), NEW (NumExpr)(7));
//     CHECK(test->equals(same_test));
//     CHECK(test->equals(diff_test) == false);
// }

// TEST_CASE("equivalence equals"){
//     CHECK((NEW (EqExpr)(NEW (NumExpr)(2), NEW (NumExpr)(0)))->equals(NEW (EqExpr)(NEW (NumExpr)(2), NEW (NumExpr)(0))) == true);
//     CHECK((NEW (EqExpr)(NEW (NumExpr)(0), NEW (NumExpr)(1)))->equals(NEW (EqExpr)(NEW (NumExpr)(0), NEW (NumExpr)(0))) == false);
// }

// TEST_CASE ( "Object Comparisions" ){
//     CHECK((NEW (MultExpr)(NEW (NumExpr)(0),NEW (NumExpr)(1)))->equals(NEW (AddExpr)(NEW (NumExpr)(1),NEW (NumExpr)(0))) == false);
//     CHECK((NEW (VarExpr)("*"))->equals(NEW (NumExpr)(5)) == false);
//     CHECK((NEW (AddExpr)(NEW (NumExpr)(0),NEW (NumExpr)(1)))->equals(NEW (VarExpr)("%")) == false);
//     CHECK((NEW (MultExpr)(NEW (NumExpr)(0),NEW (NumExpr)(1)))->equals(NEW (NumExpr)(7)) == false);
//     CHECK((NEW (VarExpr)("*"))->equals(NEW (MultExpr)(NEW (NumExpr)(0),NEW (NumExpr)(1))) == false);
//     CHECK(((NEW (letExpr)("x", NEW (NumExpr)(5), (NEW (AddExpr) (NEW (VarExpr)("x"), NEW (NumExpr) (4)))))->equals(NEW (MultExpr)(NEW (NumExpr)(0),NEW (NumExpr)(1))))==false);
//     CHECK((NEW (BoolExpr)(true))->equals(NEW (AddExpr)(NEW (NumExpr)(0), NEW (NumExpr)(2))) == false);
//     CHECK((NEW (IfExpr)(NEW (BoolExpr)(true), NEW (NumExpr)(5), NEW (NumExpr)(2)))->equals(NEW (AddExpr)(NEW (NumExpr)(0), NEW (NumExpr)(2))) == false);
//     CHECK((NEW (EqExpr)(NEW (NumExpr)(0), NEW (NumExpr)(3)))->equals(NEW (NumExpr)(5)) == false);
// }

// TEST_CASE ("EqExpr Pretty Print"){
//     CHECK((NEW (EqExpr)(NEW (NumExpr)(-9), NEW (NumExpr)(-7)))->to_pretty_string() == "-9 == -7");
//     CHECK((NEW (AddExpr) (NEW (EqExpr)(NEW (NumExpr)(7), NEW (NumExpr)(4)), NEW (NumExpr)(6)))->to_pretty_string() == "(7 == 4) + 6");
//     CHECK((NEW (AddExpr) (NEW (NumExpr)(6), NEW (EqExpr)(NEW (NumExpr)(0), NEW (NumExpr)(3))))->to_pretty_string() == "6 + (0 == 3)");
//     CHECK((NEW (MultExpr) (NEW (EqExpr)(NEW (NumExpr)(7), NEW (NumExpr)(4)), NEW (NumExpr)(6)))->to_pretty_string() == "(7 == 4) * 6");
//     CHECK((NEW (MultExpr) (NEW (NumExpr)(6), NEW (EqExpr)(NEW (NumExpr)(0), NEW (NumExpr)(3))))->to_pretty_string() == "6 * (0 == 3)");
//     CHECK((NEW (EqExpr)(NEW (EqExpr)(NEW (NumExpr)(1), NEW (NumExpr)(2)), NEW (EqExpr)(NEW (NumExpr)(3), NEW (NumExpr)(4))))->to_pretty_string() == "(1 == 2) == 3 == 4");
// }

// TEST_CASE("FunExpr") {
//     FunExpr func1("x", NEW (AddExpr)("x", 1));
//     FunExpr func2("x", NEW (FunExpr)("y", NEW (AddExpr)(NEW (MultExpr)("x", "x"), NEW (MultExpr)("y", "y"))));

//     SECTION("equals") {
//         CHECK(!func1.equals(NEW (NumExpr)(1)));
//         CHECK(!func1.equals(NEW (FunExpr)("x", NEW (AddExpr)("x", 2))));
//         CHECK(!func1.equals(NEW (FunExpr)("y", NEW (AddExpr)("x", 1))));
//         CHECK(func1.equals(NEW (FunExpr)("x", NEW (AddExpr)("x", 1))));
//     }

//     SECTION("print") {
//         CHECK(func1.to_string() == "(_fun (x) (x+1))");
//         CHECK(func2.to_string() == "(_fun (x) (_fun (y) ((x*x)+(y*y))))");
//     }

//     SECTION("pretty_print") {
//         CHECK(func1.to_pretty_string() == "_fun (x) \n"
//                                           "  x + 1");

//         CHECK(func2.to_pretty_string() == "_fun (x) \n"
//                                           "  _fun (y) \n"
//                                           "    x * x + y * y");
//     }
// }

// TEST_CASE("CallExpr") {
//     PTR(FunExpr) func1 = NEW(FunExpr)("x", NEW(AddExpr)("x", 1));
//     PTR(FunExpr) func2 = NEW(FunExpr)("y", NEW(AddExpr)("y", 2));
//     PTR(CallExpr) call1 = NEW(CallExpr)(func1, 2);

//     SECTION("equals") {
//         CHECK(call1->equals(NEW(CallExpr)(NEW(FunExpr)("x", NEW(AddExpr)("x", 1)), 2)));
//         CHECK(!call1->equals(NEW(NumExpr)(2)));
//         CHECK(!call1->equals(NEW(CallExpr)(func1, 3)));
//         CHECK(!call1->equals(NEW(CallExpr)(NEW(FunExpr)("x", NEW(MultExpr)("x", 2)), 2)));
//     }


//         // let + fun + call
//         PTR(letExpr) call2 = NEW(letExpr)("f", func1, NEW(CallExpr)(NEW(VarExpr)("f"), 2));
//         CHECK(call2->interp(Env::empty)->equals(NEW(NumVal) (3)));
//         std::string s2 = "(_let f=(_fun (x) (x+1)) _in f(2))";
//         std::string ps2 = "_let f = _fun (x) \n"
//                           "           x + 1\n"
//                           "_in  f(2)";
//         CHECK(call2->to_string() == s2);
//         CHECK(call2->to_pretty_string() == ps2);

//         // let + fun + (if + call)
//         PTR(letExpr) call3 = NEW(letExpr)("f", func1, NEW(IfExpr)(false, NEW(CallExpr)("f", 5), NEW(CallExpr)("f", 6)));
//         CHECK(call3->interp(Env::empty)->equals(NEW(NumVal) (7)));
//         CHECK(call3->to_pretty_string() == "_let f = _fun (x) \n"
//                                           "           x + 1\n"
//                                           "_in  _if _false\n"
//                                           "     _then f(5)\n"
//                                           "     _else f(6)");

//         // 2 func2
//         PTR(letExpr) call4 = NEW(letExpr)("f", func1, NEW(letExpr)("g", func2, NEW(IfExpr)(true, NEW(CallExpr)("f", 5), NEW(CallExpr)("g", 6))));
//         CHECK(call4->interp(Env::empty)->equals(NEW(NumVal) (6)));
//         CHECK(call4->to_pretty_string() == "_let f = _fun (x) \n"
//                                           "           x + 1\n"
//                                           "_in  _let g = _fun (y) \n"
//                                           "                y + 2\n"
//                                           "     _in  _if _true\n"
//                                           "          _then f(5)\n"
//                                           "          _else g(6)");
//         PTR(letExpr) call5 = NEW(letExpr)("f", func1, NEW(letExpr)("g", NEW(FunExpr)("y", NEW(CallExpr)("f", NEW(AddExpr)("y", 2))), NEW(CallExpr)("g", 5)));
//         CHECK(call5->interp(Env::empty)->equals(NEW(NumVal) (8)));
//         CHECK(call5->to_pretty_string() == "_let f = _fun (x) \n"
//                                           "           x + 1\n"
//                                           "_in  _let g = _fun (y) \n"
//                                           "                f(y + 2)\n"
//                                           "     _in  g(5)");
//         PTR(letExpr) call6 = NEW(letExpr)("f", func1, NEW(letExpr)("g", NEW(FunExpr)("x", NEW(AddExpr)(NEW(CallExpr)("f", 2), "x")), NEW(CallExpr)("g", 5)));
//         CHECK(call6->interp(Env::empty)->equals(NEW(NumVal) (8)));
//         CHECK(call6->to_pretty_string() == "_let f = _fun (x) \n"
//                                           "           x + 1\n"
//                                           "_in  _let g = _fun (x) \n"
//                                           "                f(2) + x\n"
//                                           "     _in  g(5)");
//         PTR(letExpr) call7 = NEW(letExpr)("f", NEW(IfExpr)(false, func1, func2), NEW(CallExpr)("f", 5));
//         CHECK(call7->interp(Env::empty)->equals(NEW(NumVal) (7)));
//         CHECK(call7->to_pretty_string() == "_let f = _if _false\n"
//                                           "         _then _fun (x) \n"
//                                           "                 x + 1\n"
//                                           "         _else _fun (y) \n"
//                                           "                 y + 2\n"
//                                           "_in  f(5)");
//         PTR(CallExpr) call8 = NEW(CallExpr)(NEW(IfExpr)(false, func1, func2), NEW(NumExpr)(5));
//         CHECK(call8->interp(Env::empty)->equals(NEW(NumVal) (7)));
//         CHECK(call8->to_pretty_string() == "(_if _false\n"
//                                           " _then _fun (x) \n"
//                                           "         x + 1\n"
//                                           " _else _fun (y) \n"
//                                           "         y + 2)(5)");
//         PTR(letExpr) call9 = NEW(letExpr)("f", NEW(FunExpr)("g", NEW(CallExpr)("g", 5)), NEW(letExpr)("g", func2, NEW(CallExpr)("f", "g")));
//         CHECK(call9->interp(Env::empty)->equals(NEW(NumVal) (7)));
//         CHECK(call9->to_pretty_string() == "_let f = _fun (g) \n"
//                                           "           g(5)\n"
//                                           "_in  _let g = _fun (y) \n"
//                                           "                y + 2\n"
//                                           "     _in  f(g)");
//         PTR(letExpr) call10 = NEW(letExpr)("f", NEW(FunExpr)("g", NEW(CallExpr)("g", 5)), NEW(CallExpr)("f", func2));
//         CHECK(call10->interp(Env::empty)->equals(NEW(NumVal) (7)));
//         CHECK(call10->to_pretty_string() == "_let f = _fun (g) \n"
//                                            "           g(5)\n"
//                                            "_in  f(_fun (y) \n"
//                                            "         y + 2)");
//         PTR(letExpr) call11 = NEW(letExpr)("f", NEW(FunExpr)("x", NEW(FunExpr)("y", NEW(AddExpr)("x", "y"))), NEW(CallExpr)(NEW(CallExpr)("f", 5), 1));
//         CHECK(call11->interp(Env::empty)->equals(NEW(NumVal) (6)));

//         PTR(letExpr) call12 = NEW(letExpr)("y", NEW(NumExpr)(8), NEW(letExpr)("f", NEW(FunExpr)("x", NEW(MultExpr)("x", "y")), NEW(CallExpr)("f", 2)));
//         CHECK(call12->interp(Env::empty)->equals(NEW(NumVal) (16)));

//         CHECK(call12->to_pretty_string() == "_let y = 8\n"
//                                            "_in  _let f = _fun (x) \n"
//                                            "                x * y\n"
//                                            "     _in  f(2)");
//         PTR(letExpr) call13 = NEW(letExpr)("x", NEW(NumExpr)(8), NEW(letExpr)("f", NEW(FunExpr)("x", NEW(MultExpr)("x", "x")), NEW(CallExpr)("f", 2)));
//         CHECK(call13->interp(Env::empty)->equals(NEW(NumVal) (4)));
//         CHECK(call13->to_pretty_string() == "_let x = 8\n"
//                                            "_in  _let f = _fun (x) \n"
//                                            "                x * x\n"
//                                            "     _in  f(2)");
//         PTR(letExpr) call14 = NEW(letExpr)("f", NEW(FunExpr)("x", NEW(AddExpr)("x", "y")), NEW(letExpr)("y", NEW(NumExpr)(10), NEW(CallExpr)("f", 1)));
//         CHECK(call14->to_pretty_string() == "_let f = _fun (x) \n"
//                                            "           x + y\n"
//                                            "_in  _let y = 10\n"
//                                            "     _in  f(1)");
//         PTR(letExpr) call15 = NEW(letExpr)("f", NEW(FunExpr)("x", NEW(FunExpr)("y", NEW(AddExpr)(NEW(MultExpr)("x", "x"), NEW(MultExpr)("y", "y")))), NEW(CallExpr)(NEW(CallExpr)("f", 2), 3));
//         CHECK(call15->interp(Env::empty)->equals(NEW(NumVal) (13)));
//         CHECK(call15->to_pretty_string() == "_let f = _fun (x) \n"
//                                            "           _fun (y) \n"
//                                            "             x * x + y * y\n"
//                                            "_in  f(2)(3)");
//         PTR(letExpr) call16 = NEW(letExpr)("factrl", NEW(FunExpr)("factrl", NEW(FunExpr)("x", NEW(IfExpr)(NEW(EqExpr)("x", 1), NEW(NumExpr)(1), NEW(MultExpr)("x", NEW(CallExpr)(NEW(CallExpr)("factrl", "factrl"), NEW(AddExpr)("x", -1)))))), NEW(CallExpr)(NEW(CallExpr)("factrl", "factrl"), 10));
//         CHECK(call16->interp(Env::empty)->equals(NEW(NumVal) (3628800)));
//         CHECK(call16->to_pretty_string() == "_let factrl = _fun (factrl) \n"
//                                            "                _fun (x) \n"
//                                            "                  _if x == 1\n"
//                                            "                  _then 1\n"
//                                            "                  _else x * factrl(factrl)(x + -1)\n"
//                                            "_in  factrl(factrl)(10)"); // TODO
//     }



