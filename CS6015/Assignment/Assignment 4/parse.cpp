#include <iostream>
#include "parse.h"
#include "Expr.h"

static void consume(std::istream &in, int expect);
void skip_whitespace(std::istream &in);
Expr *parse_num(std::istream &in);
Expr* parse_addend(std::istream &in);
Expr* parse_multicand(std::istream& in);
Expr* parse_var(std::istream& in);
Expr* parse_let(std::istream& in);
Expr* parse_str(std::string s);




Expr* parse_comparg(std::istream &in){
    Expr *e;
    e = parse_addend(in);
    skip_whitespace(in);
    int c = in.peek();
    if (c=='+'){
        consume(in, '+');
        Expr *rhs = parse_comparg(in);
        return new AddExpr(e,rhs);
    }else{
        return e;
    }
}


Expr *parse_expr(std::istream &in) {
    Expr *e;
    e = parse_comparg(in);
    skip_whitespace(in);
    int c = in.peek();
    if (c=='='){
        consume(in, '=');
        c=in.peek();
        if (c=='='){
            consume(in, '=');
            Expr *rhs = parse_expr(in);
            return new EqExpr(e,rhs);
        } else{
            throw std::runtime_error("2nd equal sign expected");
        }
    } else {
        return e;
    }
}


Expr *parse_num(std::istream &in) {
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
    return new NumExpr(n);
}




Expr* parse_var(std::istream& in) {
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
    return new VarExpr(std::string(s.begin(), s.end()));
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


Expr* parse_addend(std::istream &in){
    skip_whitespace(in);
    Expr* e = parse_multicand(in);
    skip_whitespace(in);

    int c = in.peek();
    if(c == '*'){
        consume(in, '*');
        Expr* rhs = parse_addend(in);
        return new MultExpr(e,rhs);
    }
    else
        return e;
}


Expr* parse_if(std::istream &in){
    skip_whitespace(in);
    Expr* test_part = parse_expr(in);
    skip_whitespace(in);
    int c = in.peek();
    if(parse_keyword(in) != "_then"){
        throw std::runtime_error("then expected");
    }
    skip_whitespace(in);
    Expr* then_part = parse_expr(in);
    skip_whitespace(in);
    c = in.peek();
    if(parse_keyword(in) != "_else"){
        throw std::runtime_error("else expected");
    }
    Expr* else_part = parse_expr(in);
    return new IfExpr(test_part, then_part, else_part);
}


Expr* parse_multicand(std::istream& in){
    skip_whitespace(in);
    int c = in.peek();
    if((c=='-') || isdigit(c)){
        return parse_num(in);
    } else if (c == '('){
        consume(in, '(');
        Expr *e = parse_expr(in); //recursive function
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
            return new BoolExpr(false);
        } else if (kw == "_true"){
            return new BoolExpr(true);
        } else if (kw == "_if"){
            return parse_if(in);
        } else {
            throw std::runtime_error("Unable to process keyword");
        }
    } else {
    }
}




Expr* parse_let(std::istream& in) {
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
    Expr* rhs = parse_expr(in);
    skip_whitespace(in);
    if(parse_keyword(in) != "_in"){
        throw std::runtime_error("in expected");
    }
    skip_whitespace(in);
    Expr* body = parse_expr(in);
    return new letExpr(lhs, rhs, body);
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

Expr* parse_str(std::string s) {
    std::istringstream in(s);
    return parse_expr(in);
}


TEST_CASE("parse") {

    CHECK( parse_str("(1)")->equals(new NumExpr(1)) );
    CHECK( parse_str("(((1)))")->equals(new NumExpr(1)) );

    CHECK_THROWS_WITH( parse_str("(1"), "missing close parenthesis" );

    CHECK( parse_str("1")->equals(new NumExpr(1)) );
    CHECK( parse_str("10")->equals(new NumExpr(10)) );
    CHECK( parse_str("-3")->equals(new NumExpr(-3)) );
    CHECK( parse_str("  \n 5  ")->equals(new NumExpr(5)) );
    CHECK_THROWS_WITH( parse_str("-"), "invalid input" );


    // This was some temporary debugging code:
    //  std::istringstream in("-");
    //  parse_num(in)->print(std::cout); std::cout << "\n";

    //  CHECK_THROWS_WITH( parse_str(" -   5  "), "invalid input" );
    CHECK( parse_str("     -      5  ")->equals(new NumExpr(-5)) );
    CHECK( parse_str("x")->equals(new VarExpr("x")) );
    CHECK( parse_str("xyz")->equals(new VarExpr("xyz")) );
    CHECK( parse_str("xYz")->equals(new VarExpr("xYz")) );
    CHECK_THROWS_WITH( parse_str("x_z"), "invalid input" );

    CHECK( parse_str("x + y")->equals(new AddExpr(new VarExpr("x"), new VarExpr("y"))) );

    CHECK( parse_str("x")->equals(new VarExpr("x"))) ;

    CHECK( parse_str("x * y")->equals(new MultExpr(new VarExpr("x"), new VarExpr("y"))) );

    CHECK( parse_str("z * x + y")
                   ->equals(new AddExpr(new MultExpr(new VarExpr("z"), new VarExpr("x")),
                                    new VarExpr("y"))) );

    CHECK( parse_str("z * (x + y)")
                   ->equals(new MultExpr(new VarExpr("z"),
                                     new AddExpr(new VarExpr("x"), new VarExpr("y"))) ));

};