
#include "Val.h"
#include "Expr.h"

#include <stdio.h>
#include <iostream>


NumVal::NumVal(int val){
    this->val = val;
}

bool NumVal::equals(Val *other){
    NumVal *other_num = dynamic_cast<NumVal*>(other);
    if (other_num == NULL){
        return false;
    } else {
        return this->val == other_num->val;
    }
}

Expr* NumVal::to_expr(){
    return new NumExpr(this->val);
}

Val *NumVal::add_to(Val *other){
    NumVal *other_num = dynamic_cast<NumVal*>(other);
    if (other_num == NULL) throw std::runtime_error("add of non-number");
    return new NumVal((unsigned) val + (unsigned) other_num->val);
}

Val *NumVal::mult_to(Val *other){
    NumVal *other_num = dynamic_cast<NumVal*>(other);
    if (other_num == NULL) throw std::runtime_error("multiplication of non-number");
    return new NumVal((unsigned) val * (unsigned) other_num->val);
}

std::string NumVal::to_string() {
    return std::to_string(val);
}

bool NumVal::is_true(){
    throw std::runtime_error("Test expression is not a boolean");
}

Val* NumVal::call(Val *actual_arg) {
    throw std::runtime_error("no function to call!"); // TODO
}

BoolVal::BoolVal(bool val){
    this->val = val;
}

Expr* BoolVal::to_expr(){
    return new BoolExpr(this->val);
}

bool BoolVal::equals(Val* other){
    BoolVal *other_val = dynamic_cast<BoolVal*>(other);
    if (other == NULL){
        return false;
    } else {
        return (this->val == other_val->val);
    }
}

Val* BoolVal::add_to(Val* rhs){
    throw std::runtime_error("addition of non-number");
}

Val* BoolVal::mult_to(Val* rhs){
    throw std::runtime_error("multiplication of non-number");
}

std::string BoolVal::to_string() {
    if (val) {
        return "_true";
    } else {
        return "_false";
    }
}

bool BoolVal::is_true(){
    return this->val;
}

Val* BoolVal::call(Val *actual_arg) {
    throw std::runtime_error("no function to call!"); // TODO
}

/**
* This is the FUnVal function
 *
*/
FunVal::FunVal(std::string arg, Expr* expr) {
    formal_arg = arg;
    body = expr;
}

Expr* FunVal::to_expr() {
    return new FunExpr(formal_arg, body);
}

bool FunVal::equals(Val* rhs) {
    FunVal* other = dynamic_cast<FunVal*>(rhs);
    if (other == nullptr) {
        return false;
    }
    return formal_arg == other->formal_arg && body->equals(other->body);
}

Val* FunVal::add_to(Val* rhs) {
    throw std::runtime_error("add of non-number");
}

Val* FunVal::mult_to(Val* rhs) {
    throw std::runtime_error("multiply with non-number");
}

std::string FunVal::to_string() {
    return to_expr()->to_pretty_string();
}

bool FunVal::is_true() { // TODO should I interp the function before I check if it's true?
    throw std::runtime_error("a function value can not be evaluated to a boolean");
}

Val* FunVal::call(Val *actual_arg) {
    return body->subst(formal_arg, actual_arg->to_expr())->interp(); // TODO
}

