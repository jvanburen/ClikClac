#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define SMALL_STACK_SIZE 1024 

typedef int32_t clac_t;

clac_t *sp;
clac_t *stack;
size_t allocated;

#ifdef DEBUG
static inline void CHECK_DIV(void) {
    if (!*sp) {
        fputs("Error: division by 0\n", stderr);
        abort();
    } else if (*(sp-1) == INT32_MIN && *sp == -1) {
        fputs("Error: division overflow\n", stderr);
        abort();
    }
}
static inline void CHECK_SIZE(clac_t n) {
    if (sp + 1 < stack + n) {
        fputs("Error: not enough elements on stack\n", stderr);
        abort();
    }
}
static inline void CHECK_PICK(void) {
    if (*sp < 0) {
        fputs("Error: pick must be positive\n", stderr);
        abort();
    }
    CHECK_SIZE(*sp);
}

#else
static inline void CHECK_DIV(void) {
    (void)0;
}
static inline void CHECK_SIZE(clac_t n) {
    (void)n;
}
static inline void CHECK_PICK(void) {
    (void)0;
}
#endif

void STACK_RESIZE(void) {
    if (sp >= stack + allocated) {
        allocated *= 2;
        stack = realloc(stack, allocated*sizeof(clac_t));
    } else if (allocated > SMALL_STACK_SIZE && sp <= stack + allocated / 4 ) {
        allocated /= 2;
        stack = realloc(stack, allocated*sizeof(clac_t));
    }
}
