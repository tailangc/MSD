//
// Created by Tailang  Cao on 1/10/24.
//

#include "cmdline.h"
#include <iostream>

void use_arguments(int argc, char **argv) {
    bool testSeen = false;

    for (int i = 1; i < argc; i++) {
        std::string input = argv[i];
        if (input == "--help") {
            std::cout << "Please refer to the help manual book";
            exit(0);
        }
        if (input == "--test") {
            if (testSeen) {
                std::cerr << "test has been seen before";
                exit(1);
            }
            testSeen = true;
        }
    }
    if (testSeen) {
        std::cout << "Tests passed";
        exit(1);
    }
    std::cerr << "test has been seen before";
    exit(1);
}
