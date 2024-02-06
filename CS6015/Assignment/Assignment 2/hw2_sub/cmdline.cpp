#include <iostream>
#include <cstdlib>

void use_arguments(int argc, char* argv[]) {
    bool testSeen = false;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];

        if (arg == "--help") {
            std::cout << "Please refer to the manual" << std::endl;
            exit(0);
        } else if (arg == "--test") {
            if (testSeen) {
                std::cerr << "Error: '--test' has been used before." << std::endl;
                exit(1);
            }
            std::cout << "Tests passed" << std::endl;
            testSeen = true;
        } else {
            std::cerr << "Error: Unrecognized argument '" << arg << "'." << std::endl;
            exit(1);
        }
    }
}

