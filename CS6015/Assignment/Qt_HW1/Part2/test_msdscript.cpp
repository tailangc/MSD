#include <iostream>
#include <cstdlib>
#include "exec.h"


static std::string random_expr_string();


int main(int argc, char **argv) {
    const char *modes[] = {"--interp", "--print", "--pretty-print"};
    if(argc == 2){
        const char * const interp1_argv[] = { argv[1], "--interp" };
        const char * const print1_argv[] = { argv[1], "--print" };
        const char * const pprint1_argv[] = { argv[1], "--pretty-print" };

        for (int i = 0; i < 100; i++) {
            std::string in = random_expr_string();
            std::cout << "Trying " << in << "\n";
            ExecResult interp1_result = exec_program(2, interp1_argv, in);
            ExecResult print1_result = exec_program(2, print1_argv, in);
            ExecResult pprint1_result = exec_program(2, pprint1_argv, in);

            ExecResult interp_again = exec_program(2, interp1_argv, print1_result.out);
//            std::cout << "Entering if";
            if(interp_again.out != interp1_result.out){
                std::cout << "Different results for printed" << "\n";
            }
        }
        return 0;

    }else if (argc >= 3) {
        for (int j = 0; j < 3; j++) {
            const char *const argv_1[] = {argv[1], modes[j]};
            const char *const argv_2[] = {argv[2], modes[j]};

            for (int i = 0; i < 100; i++) {
                std::string in = random_expr_string();
//                std::cout << "Testing with input: " << in << std::endl;

                try {
                    ExecResult result_1 = exec_program(2, argv_1, in);
                    ExecResult result_2 = exec_program(2, argv_2, in);

                    if (result_1.out != result_2.out) {
                        std::cerr << "Mismatch found in mode '" << modes[j] << "' with input: " << in << "\n";
                        std::cerr << argv_1[0] << " output: " << result_1.out << "\n";
                        std::cerr << argv_2[0] << " output: " << result_2.out << "\n";
                        throw std::runtime_error("Outputs do not match!\n");
                    } else if (result_1.out == result_2.out){
                        std::cout << "Result Match" << "\n";
                    }
                } catch (const std::exception& e) {
                    std::cerr << "Exception caught: " << e.what() << std::endl;
                }
            }
        }
    } else {
        std::cerr << "Usage: " << argv[0] << " <program1> <program2>\n";
        return 1;
    }
    return 0;
}

std::string random_variable(){
    std::string s = "";
    for(int i=0; i < rand()%6;i++){
        s+=(rand()%26) + 'a';
    }
    return s;
}

std::string random_expr_string() {
    if ((rand() % 10) == 6 || (rand() % 10) == 5 || (rand() % 10) == 4) {
        return std::to_string(rand() % 1000);
    }else if((rand() % 10) == 3){
        return "(" + random_expr_string() + ")";
    }else if ((rand() % 10) < 3){
        return "-" + std::to_string(rand()%1000);
    }else if ((rand() % 10) == 7 ){
        return "_let " + random_variable() + " = " + random_expr_string() + " _in " + random_expr_string();
    } else if ((rand() % 10) == 8 ) {
        return random_expr_string() + "*" + random_expr_string();
    } else if ((rand() % 10) == 9 ){
        return random_variable();
    } else {
        return random_expr_string() + "+" + random_expr_string();
    }
}

