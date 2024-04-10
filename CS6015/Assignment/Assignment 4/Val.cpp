
#include "Val.h"
#include "Expr.h"

#include <stdio.h>
#include <iostream>
#include "pointer.h"
#include "env.h"


NumVal::NumVal(int val){
    this->val = val;
}

bool NumVal::equals(PTR(Val) other){
    PTR(NumVal) other_num = CAST(NumVal)(other);
    if (other_num == NULL){
        return false;
    } else {
        return this->val == other_num->val;
    }
}

PTR(Expr) NumVal::to_expr(){
    return NEW (NumExpr)(this->val);
}

PTR(Val) NumVal::add_to(PTR(Val) other){
    PTR(NumVal) other_num = CAST(NumVal)(other);
    if (other_num == NULL) throw std::runtime_error("add of non-number");
    return NEW (NumVal)((unsigned) val + (unsigned) other_num->val);
}

PTR(Val) NumVal::mult_to(PTR(Val) other){
    PTR(NumVal) other_num = CAST(NumVal)(other);
    if (other_num == NULL) throw std::runtime_error("multiplication of non-number");
    return NEW ( NumVal)((unsigned) val * (unsigned) other_num->val);
}

std::string NumVal::to_string() {
    return std::to_string(val);
}

bool NumVal::is_true(){
    throw std::runtime_error("Test expression is not a boolean");
}

PTR(Val) NumVal::call(PTR(Val) actual_arg) {
    throw std::runtime_error("no function to call!"); // TODO
}

BoolVal::BoolVal(bool val){
    this->val = val;
}

PTR(Expr) BoolVal::to_expr(){
    return NEW (BoolExpr)(this->val);
}

bool BoolVal::equals(PTR(Val) other){
    PTR(BoolVal) other_val = CAST (BoolVal)(other);
    if (other == NULL){
        return false;
    } else {
        return (this->val == other_val->val);
    }
}

PTR(Val) BoolVal::add_to(PTR(Val) rhs){
    throw std::runtime_error("addition of non-number");
}

PTR(Val) BoolVal::mult_to(PTR(Val) rhs){
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

PTR(Val) BoolVal::call(PTR(Val) actual_arg) {
    throw std::runtime_error("no function to call!"); // TODO
}

/**
* This is the FUnVal function
 *
*/
FunVal::FunVal(std::string arg, PTR(Expr) expr, PTR(Env) env_) {
    formal_arg = arg;
    body = expr;
    env = env_;
}

PTR(Expr) FunVal::to_expr() {
    return NEW (FunExpr)(formal_arg, body);
}

bool FunVal::equals(PTR(Val) rhs) {
    PTR(FunVal) other = CAST(FunVal)(rhs);
    if (other == nullptr) {
        return false;
    }
    return formal_arg == other->formal_arg && body->equals(other->body);
}

PTR(Val) FunVal::add_to(PTR(Val) rhs) {
    throw std::runtime_error("add of non-number");
}

PTR(Val) FunVal::mult_to(PTR(Val) rhs) {
    throw std::runtime_error("multiply with non-number");
}

std::string FunVal::to_string() {
    return to_expr()->to_pretty_string();
}

bool FunVal::is_true() { // TODO should I interp the function before I check if it's true?
    throw std::runtime_error("a function value can not be evaluated to a boolean");
}

PTR(Val) FunVal::call(PTR(Val) actual_arg) {
    return body->interp(NEW(ExtendedEnv) (formal_arg, actual_arg, env));
}

