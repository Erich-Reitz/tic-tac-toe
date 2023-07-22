#include <stdlib.h>
#include <stdio.h>

inline void flush_exit_failure() {
    fflush(stdout) ;
    exit(EXIT_FAILURE);
}

