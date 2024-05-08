#ifndef parse_hpp

#define parse_hpp

#include "Expr.h"
#include <stdio.h>
 #include <set>
#include "pointer.h"



PTR(Expr) parse_expr(std::istream &in);
PTR(Expr) parse_num(std::istream &in);
PTR(Expr) parse_addend(std::istream &in);
PTR(Expr) parse_multicand(std::istream& in);
PTR(Expr) parse_var(std::istream& in);
// test
PTR(Expr) parse_str(std::string s);
PTR(Expr) parse_comparg(std::istream &in);
PTR(Expr) parse_if(std::istream &in);

#endif
