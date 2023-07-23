#include <cstdlib>
#include <cstdio>

inline void flush_exit_failure() {
    fflush(stdout) ;
    exit(EXIT_FAILURE);
}

