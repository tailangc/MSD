#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include <iostream>
#include "Expr.h"
#include "cmdline.h"


int main(int argc, char **argv) {

    use_arguments(argc, argv);
    if (Catch::Session().run() != 0) {
        exit(1);
    };
    return 0;
}
