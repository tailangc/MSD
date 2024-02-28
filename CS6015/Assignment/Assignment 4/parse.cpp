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


Expr *parse_expr(std::istream &in) {
    Expr *e = parse_addend(in);
    skip_whitespace(in);
    int c = in.peek();
    if (c == '+') {
        consume(in, '+');
        Expr *rhs = parse_expr(in);
        return new Add(e, rhs);
    }
    else {
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
    return new Num(n);
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
    return new Var(std::string(s.begin(), s.end()));
}





Expr* parse_addend(std::istream &in){
    skip_whitespace(in);
    Expr* e = parse_multicand(in);
    skip_whitespace(in);

    int c = in.peek();
    if(c == '*'){
        consume(in, '*');
        Expr* rhs = parse_addend(in);
        return new Mult(e,rhs);
    }
    else
        return e;
}





Expr* parse_multicand(std::istream& in){
    skip_whitespace(in);
    int c = in.peek();
    if ((c == '-') || isdigit(c)){
        return parse_num(in);
    }
    else if (isalpha(c)){
        return parse_var(in);
    }
    else if (c == '_'){
        return parse_let(in);
    }
    else if (c == '(') {
        consume(in, '(');
        Expr *e = parse_expr(in);
        skip_whitespace(in);
        c = in.get();
        if (c != ')') {
            throw std::runtime_error("missing close parenthesis");
        }
        return e;
    }
    else {
        consume(in, c);
        throw std::runtime_error("invalid input");
    }
}



Expr* parse_let(std::istream& in) {
    consume(in, '_');
    consume(in, 'l');
    consume(in, 'e');
    consume(in, 't');
    Expr* temp = parse_var(in);
    Var* var = dynamic_cast<Var*>(temp);
    if (var == NULL) {
        throw std::runtime_error("wrong format for let expression");
    }
    skip_whitespace(in);

    consume(in, '=');

    Expr* rhs = parse_expr(in);
    skip_whitespace(in);

    consume(in, '_');
    consume(in, 'i');
    consume(in, 'n');
    Expr* body = parse_expr(in);
    return new letExpr(var->val, rhs, body);
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
    CHECK_THROWS_WITH( parse_str("()"), "invalid input" );

    CHECK( parse_str("(1)")->equals(new Num(1)) );
    CHECK( parse_str("(((1)))")->equals(new Num(1)) );

    CHECK_THROWS_WITH( parse_str("(1"), "missing close parenthesis" );

    CHECK( parse_str("1")->equals(new Num(1)) );
    CHECK( parse_str("10")->equals(new Num(10)) );
    CHECK( parse_str("-3")->equals(new Num(-3)) );
    CHECK( parse_str("  \n 5  ")->equals(new Num(5)) );
    CHECK_THROWS_WITH( parse_str("-"), "invalid input" );


    // This was some temporary debugging code:
    //  std::istringstream in("-");
    //  parse_num(in)->print(std::cout); std::cout << "\n";

    //  CHECK_THROWS_WITH( parse_str(" -   5  "), "invalid input" );
    CHECK( parse_str("     -      5  ")->equals(new Num(-5)) );
    CHECK( parse_str("x")->equals(new Var("x")) );
    CHECK( parse_str("xyz")->equals(new Var("xyz")) );
    CHECK( parse_str("xYz")->equals(new Var("xYz")) );
    CHECK_THROWS_WITH( parse_str("x_z"), "invalid input" );

    CHECK( parse_str("x + y")->equals(new Add(new Var("x"), new Var("y"))) );

    CHECK( parse_str("x")->equals(new Var("x"))) ;

    CHECK( parse_str("x * y")->equals(new Mult(new Var("x"), new Var("y"))) );

    CHECK( parse_str("z * x + y")
                   ->equals(new Add(new Mult(new Var("z"), new Var("x")),
                                    new Var("y"))) );

    CHECK( parse_str("z * (x + y)")
                   ->equals(new Mult(new Var("z"),
                                     new Add(new Var("x"), new Var("y"))) ));

};