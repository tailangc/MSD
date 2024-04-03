#ifndef CMDLINE_H
#define CMDLINE_H
#include "pointer.h"

typedef enum {
    do_nothing,
    do_test,
    do_interp,
    do_print,
    do_pretty_print
} run_mode_t;

// Declare the use_arguments function.
run_mode_t use_arguments(int argc, char* argv[]);

#endif
