#include <iostream>
#include "parse.h"
#include "Expr.h"
#include "pointer.h"

static void consume(std::istream &in, int expect);
void skip_whitespace(std::istream &in);
PTR(Expr) parse_num(std::istream &in);
PTR(Expr) parse_addend(std::istream &in);
PTR(Expr) parse_multicand(std::istream& in);
PTR(Expr) parse_var(std::istream& in);
PTR(Expr) parse_let(std::istream& in);
PTR(Expr) parse_str(std::string s);




PTR(Expr) parse_comparg(std::istream &in){
    PTR(Expr) e;
    e = parse_addend(in);
    skip_whitespace(in);
    int c = in.peek();
    if (c=='+'){
        consume(in, '+');
        PTR(Expr) rhs = parse_comparg(in);
        return NEW (AddExpr)(e,rhs);
    }else{
        return e;
    }
}


PTR(Expr) parse_expr(std::istream &in) {
    PTR(Expr) e;
    e = parse_comparg(in);
    skip_whitespace(in);
    int c = in.peek();
    if (c=='='){
        consume(in, '=');
        c=in.peek();
        if (c=='='){
            consume(in, '=');
            PTR(Expr) rhs = parse_expr(in);
            return NEW (EqExpr)(e,rhs);
        } else{
            throw std::runtime_error("2nd equal sign expected");
        }
    } else {
        return e;
    }
}


PTR(Expr) parse_num(std::istream &in) {
    bool tracker = false;
    bool negative = false;
    int n = 0;

    if (in.peek() == '-') {
        negative = true;
        consume (in, '-');
    }

    while (1) {
        skip_whitespace(in);
        int c = in.peek();
        if (isdigit(c)){
            consume(in, c);
            n = n*10 + (c - '0');
            tracker = true;
        }
        else {
            break;
        }
    }
    if(!tracker){
        throw std::runtime_error("invalid input");
    }

    if (negative){
        n = -n;
}
    return NEW (NumExpr)(n);
}




PTR(Expr) parse_var(std::istream& in) {
    skip_whitespace(in);
    std::vector<char> s;
    int c;
    while (isalpha(c = in.peek())) {
        consume(in, c);
        s.push_back(c);
    }
    const std::set<char> operators = {'+', '*', '=', '(', ')'};

    if (c != -1 and !isspace(c) and operators.find(c) == operators.end()) {
        throw std::runtime_error("invalid input");
    }
    return NEW (VarExpr)(std::string(s.begin(), s.end()));
}


std::string parse_keyword(std::istream &in){
    int c = in.peek();
    std::string keyword = "_";
    if(c == '_'){
        consume(in,c);
        c = in.peek();
        while(isalpha(c)){
            keyword+=c;
            consume (in, c);
            c = in.peek();
        }
    }
    skip_whitespace(in);
    return keyword;
}


PTR(Expr) parse_addend(std::istream &in){
    skip_whitespace(in);
    PTR(Expr) e = parse_multicand(in);
    skip_whitespace(in);

    int c = in.peek();
    if(c == '*'){
        consume(in, '*');
        PTR(Expr) rhs = parse_addend(in);
        return NEW (MultExpr)(e,rhs);
    }
    else
        return e;
}


PTR(Expr) parse_if(std::istream &in){
    skip_whitespace(in);
    PTR(Expr) test_part = parse_expr(in);
    skip_whitespace(in);
    int c = in.peek();
    if(parse_keyword(in) != "_then"){
        throw std::runtime_error("then expected");
    }
    skip_whitespace(in);
    PTR(Expr) then_part = parse_expr(in);
    skip_whitespace(in);
    c = in.peek();
    if(parse_keyword(in) != "_else"){
        throw std::runtime_error("else expected");
    }
    PTR(Expr) else_part = parse_expr(in);
    return NEW (IfExpr)(test_part, then_part, else_part);
}


PTR(Expr) parse_multicand(std::istream& in){
    skip_whitespace(in);
    int c = in.peek();
    if((c=='-') || isdigit(c)){
        return parse_num(in);
    } else if (c == '('){
        consume(in, '(');
        PTR(Expr) e = parse_expr(in); //recursive function
        skip_whitespace(in);
        c = in.get();
        if (c!= ')'){
            throw std::runtime_error("missing close parenthesis");
        }
        return e;
    } else if (isalpha(c)){
        return parse_var(in);
    } else if ( c == '_'){
        std::string kw = parse_keyword(in);
        if(kw == "_let"){
            return parse_let(in);
        } else if (kw == "_false"){
            return NEW  (BoolExpr)(false);
        } else if (kw == "_true"){
            return NEW (BoolExpr)(true);
        } else if (kw == "_if"){
            return parse_if(in);
        } else {
            throw std::runtime_error("Unable to process keyword");
        }
    } else {
    }
}




PTR(Expr) parse_let(std::istream& in) {
    skip_whitespace(in);
    std::string lhs = parse_var(in)->to_pretty_string();
    skip_whitespace(in);
    int c = in.peek();
    if (c=='='){
        consume(in, '=');
    } else {
        throw std::runtime_error("equal expected");
    }
    skip_whitespace(in);
    PTR(Expr) rhs = parse_expr(in);
    skip_whitespace(in);
    if(parse_keyword(in) != "_in"){
        throw std::runtime_error("in expected");
    }
    skip_whitespace(in);
    PTR(Expr) body = parse_expr(in);
    return NEW (letExpr)(lhs, rhs, body);
}




static void consume(std::istream &in, int expect) {
    int c = in.get();
    if (c!=expect) {
        std::cout <<"Fail: Expect: "<<expect<<std::endl;
        throw std::runtime_error("consume mismatch");
    }
}

void skip_whitespace(std::istream &in) {
    while (1) {
        int c = in.peek();
        if (!isspace(c))
            break;
        consume(in, c);
    }
}

PTR(Expr) parse_str(std::string s) {
    std::istringstream in(s);
    return parse_expr(in);
}


// TEST_CASE("parse") {

//     CHECK( parse_str("(1)")->equals(NEW (NumExpr)(1)) );
//     CHECK( parse_str("(((1)))")->equals(NEW (NumExpr)(1)) );

//     CHECK_THROWS_WITH( parse_str("(1"), "missing close parenthesis" );

//     CHECK( parse_str("1")->equals(NEW (NumExpr)(1)) );
//     CHECK( parse_str("10")->equals(NEW (NumExpr)(10)) );
//     CHECK( parse_str("-3")->equals(NEW (NumExpr)(-3)) );
//     CHECK( parse_str("  \n 5  ")->equals(NEW (NumExpr)(5)) );
//     CHECK_THROWS_WITH( parse_str("-"), "invalid input" );


//     // This was some temporary debugging code:
//     //  std::istringstream in("-");
//     //  parse_num(in)->print(std::cout); std::cout << "\n";

//     //  CHECK_THROWS_WITH( parse_str(" -   5  "), "invalid input" );
//     CHECK( parse_str("     -      5  ")->equals(NEW (NumExpr)(-5)) );
//     CHECK( parse_str("x")->equals(NEW (VarExpr)("x")) );
//     CHECK( parse_str("xyz")->equals(NEW (VarExpr)("xyz")) );
//     CHECK( parse_str("xYz")->equals(NEW (VarExpr)("xYz")) );
//     CHECK_THROWS_WITH( parse_str("x_z"), "invalid input" );

//     CHECK( parse_str("x + y")->equals(NEW (AddExpr)(NEW (VarExpr)("x"), NEW (VarExpr)("y"))) );

//     CHECK( parse_str("x")->equals(NEW (VarExpr)("x"))) ;

//     CHECK( parse_str("x * y")->equals(NEW (MultExpr)(NEW (VarExpr)("x"), NEW (VarExpr)("y"))) );

//     CHECK( parse_str("z * x + y")
//                    ->equals(NEW (AddExpr)(NEW (MultExpr)(NEW (VarExpr)("z"), NEW (VarExpr)("x")),
//                                     NEW (VarExpr)("y"))) );

//     CHECK( parse_str("z * (x + y)")
//                    ->equals(NEW (MultExpr)(NEW (VarExpr)("z"),
//                                      NEW (AddExpr)(NEW (VarExpr)("x"), NEW (VarExpr)("y"))) ));

// };
