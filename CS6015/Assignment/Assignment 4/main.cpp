/**
* \mainpage MSDScript
* \author Tailang Cao
* \author Second Author (if applicable)
* \date 06-02-2024
*/


#include "cmdline.h"
#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include <cstring>
#include "Expr.h"
#include "parse.h"
#include <iostream>
#include "pointer.h"
#include <sstream>

int main(int argc, char **argv) {
    try{
    run_mode_t mode = use_arguments(argc, argv);

    switch (mode) {
        case do_test:
            if (Catch::Session().run() != 0) {
                exit(1);
            };
            break;
        case do_interp:
        {
            std::string input;
            std::getline(std::cin, input);
            try {
                Expr* expr = parse_str(input);
                std::cout << expr->interp() << std::endl;
                delete expr;
            } catch (const std::exception& e) {
                std::cerr << "Error: " << e.what() << std::endl;
                exit(1);
            }
        }
            break;
        case do_print:
        {
            std::string input;
            std::getline(std::cin, input);
            Expr* expr = parse_str(input);
            expr->print(std::cout);
            std::cout << std::endl;
            delete expr;
        }
            break;
        case do_pretty_print:
        {
            std::string input;
            std::getline(std::cin, input);
            Expr* expr = parse_str(input);
            expr->pretty_print_dr(std::cout);
            std::cout << std::endl;
            delete expr;
        }
            break;
        default:
            break;
    }
    return 0;
}

    catch (std::runtime_error exn) {
        std::cerr << exn.what() << "\n";
        return 1;
    }
}