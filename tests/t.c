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
        abort();
    } else if (*(sp-1) == INT32_MIN && *sp == -1) {
        fputs("Error: division overflow\n", stderr);
        abort();
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

static inline void STACK_RESIZE(void) {
    static ptrdiff_t offset;
    if (sp >= stack + allocated) {
        offset = sp - stack;
        allocated *= 2;
        stack = realloc(stack, allocated*sizeof(clac_t));
        sp = stack + offset;
    } else if (allocated > SMALL_STACK_SIZE && sp <= stack + allocated / 4 ) {
        offset = sp - stack;
        allocated /= 2;
        stack = realloc(stack, allocated*sizeof(clac_t));
        sp = stack + offset;
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
  } else if (x == 0){
    putc('0', stdout);
  } else {
    abs = x;
    iprint(x);
  }
  putc('\n', stdout);
}


void MACRO_end(void);
void MACRO_dup(void);
void MACRO_next(void);
int main(void);
void MACRO_end(void) {
//line 2 "tests/bigstack.clac"
CHECK_SIZE(1); clac_print(*sp--); STACK_RESIZE();
//line 2 "tests/bigstack.clac"
sp--; *sp = *sp * *(sp+1); STACK_RESIZE();
return;
}
void MACRO_dup(void) {
//line 1 "tests/bigstack.clac"
*++sp = 1; STACK_RESIZE();
//line 1 "tests/bigstack.clac"
CHECK_SIZE(1); CHECK_PICK(); {clac_t *i=sp - *sp; *sp = *i;};
return;
}
void MACRO_next(void) {
//line 3 "tests/bigstack.clac"
MACRO_dup();
//line 3 "tests/bigstack.clac"
MACRO_dup();
//line 3 "tests/bigstack.clac"
*++sp = 1; STACK_RESIZE();
//line 3 "tests/bigstack.clac"
CHECK_SIZE(2); sp--; *sp = *sp - *(sp+1); STACK_RESIZE();
//line 3 "tests/bigstack.clac"
if (!*sp--){STACK_RESIZE();goto LABEL1;}
//line 3 "tests/bigstack.clac"
MACRO_next();
//line 3 "tests/bigstack.clac"
STACK_RESIZE();goto LABEL2;

LABEL1:
//line 3 "tests/bigstack.clac"
MACRO_end();

LABEL2:
return;
}
int main(void){
allocated = SMALL_STACK_SIZE;
stack = malloc(allocated*sizeof(clac_t));
sp=stack-1;

//line 4 "tests/bigstack.clac"
*++sp = 0; STACK_RESIZE();
//line 4 "tests/bigstack.clac"
scanf("%d", ++sp); STACK_RESIZE();
//line 4 "tests/bigstack.clac"
MACRO_next();
free(stack);
return 0;
}
