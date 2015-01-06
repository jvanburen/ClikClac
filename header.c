#include <signal.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
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
        raise(SIGFPE);
    } else if (*(sp-1) == INT32_MIN && *sp == -1) {
        fputs("Error: division overflow\n", stderr);
        raise(SIGFPE);
    }
}
static inline void CHECK_SIZE(clac_t n) {
    if (stack + n > sp + 1) {
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

static inline void STACK_REALLOC(void) {
  static ptrdiff_t offset;
  offset = sp - stack;
  stack = realloc(stack, allocated*sizeof(clac_t));
  if (stack == NULL) {
    fputs("REALLOC FAILED\n", stderr);
    raise(SIGTRAP); //for debugging
    abort();
  } 
  sp = stack + offset;
}

static inline void STACK_RESIZE(void) {
    if (sp + 1 >= stack + allocated) {
        allocated *= 2;
        STACK_REALLOC();
    } else if (allocated > SMALL_STACK_SIZE && sp <= stack + allocated / 4 ) {
        allocated /= 2;
        STACK_REALLOC();
    }
}


static void iprint(uintmax_t x){
	if (x >= 10) iprint(x/10);
	putc('0'+x%10, stdout);
}

static inline void clac_print(clac_t x){
  static uintmax_t abs;
  if (x < 0) {
    putc('-', stdout);
    x = ~x;
    abs = x;
    abs++;
    iprint(abs);
  } else if (x == 0){
    putc('0', stdout);
  } else {
    abs = x;
    iprint(abs);
  }
  putc('\n', stdout);
}

