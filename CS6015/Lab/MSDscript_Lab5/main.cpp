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

int main(int argc, char **argv) {
    use_arguments(argc, argv);
    if (Catch::Session().run() != 0) {
        exit(1);
    };
    return 0;
}
