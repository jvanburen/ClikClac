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


void MACRO_cleanstack(void);
void MACRO_primesearch(void);
void MACRO_prime1(void);
void MACRO_loop(void);
void MACRO_primesearch1(void);
void MACRO_edgecheck(void);
int main(void);
void MACRO_cleanstack(void) {
  //line 39 "tests/clacprime.clac"
  CHECK_SIZE(2); {clac_t temp = *sp; *sp = *(sp-1); *(sp-1) = temp;}; STACK_RESIZE();
  //line 39 "tests/clacprime.clac"
  *++sp = 1; STACK_RESIZE();
  //line 39 "tests/clacprime.clac"
  CHECK_SIZE(2); sp--; *sp = *sp - *(sp+1); STACK_RESIZE();
  //line 39 "tests/clacprime.clac"
  if (!*sp--){STACK_RESIZE();goto LABEL21;}
  //line 39 "tests/clacprime.clac"
  MACRO_cleanstack();
  //line 39 "tests/clacprime.clac"
  STACK_RESIZE();goto LABEL22;
  LABEL21:
  //line 39 "tests/clacprime.clac"
  MACRO_loop();
  LABEL22:
return;
}
void MACRO_primesearch(void) {
  //line 17 "tests/clacprime.clac"
  *++sp = 1; STACK_RESIZE();
  //line 17 "tests/clacprime.clac"
  CHECK_SIZE(1); CHECK_PICK(); {clac_t *i=sp - *sp; *sp = *i;};
  //line 31 "tests/clacprime.clac"
  *++sp = 3; STACK_RESIZE();
  //line 31 "tests/clacprime.clac"
  CHECK_SIZE(2); sp--; *sp = *sp < *(sp+1); STACK_RESIZE();
  //line 31 "tests/clacprime.clac"
  if (!*sp--){STACK_RESIZE();goto LABEL9;}
  //line 17 "tests/clacprime.clac"
  *++sp = 1; STACK_RESIZE();
  //line 17 "tests/clacprime.clac"
  CHECK_SIZE(1); CHECK_PICK(); {clac_t *i=sp - *sp; *sp = *i;};
  //line 36 "tests/clacprime.clac"
  *++sp = 2; STACK_RESIZE();
  //line 36 "tests/clacprime.clac"
  CHECK_SIZE(2); sp--; *sp = *sp - *(sp+1); STACK_RESIZE();
  //line 36 "tests/clacprime.clac"
  if (!*sp--){STACK_RESIZE();goto LABEL41;}
  //line 40 "tests/clacprime.clac"
  CHECK_SIZE(1); sp--; STACK_RESIZE();
  //line 40 "tests/clacprime.clac"
  abort(); STACK_RESIZE();
  //line 36 "tests/clacprime.clac"
  STACK_RESIZE();goto LABEL42;
  LABEL41:
  //line 34 "tests/clacprime.clac"
  *++sp = 2; STACK_RESIZE();
  //line 34 "tests/clacprime.clac"
  CHECK_SIZE(1); sp--; STACK_RESIZE();
  //line 34 "tests/clacprime.clac"
  CHECK_SIZE(1); clac_print(*sp--); STACK_RESIZE();
  //line 34 "tests/clacprime.clac"
  abort(); STACK_RESIZE();
  LABEL42:
  //line 31 "tests/clacprime.clac"
  STACK_RESIZE();goto LABEL10;
  LABEL9:
  //line 31 "tests/clacprime.clac"
  MACRO_edgecheck();
  LABEL10:
return;
}
void MACRO_prime1(void) {
  //line 38 "tests/clacprime.clac"
  CHECK_SIZE(1); sp--; STACK_RESIZE();
  //line 38 "tests/clacprime.clac"
  CHECK_SIZE(1); clac_print(*sp--); STACK_RESIZE();
  //line 38 "tests/clacprime.clac"
  MACRO_loop();
return;
}
void MACRO_loop(void) {
  //line 41 "tests/clacprime.clac"
  *++sp = 2; STACK_RESIZE();
  //line 41 "tests/clacprime.clac"
  CHECK_SIZE(2); sp--; *sp = *sp - *(sp+1); STACK_RESIZE();
  //line 41 "tests/clacprime.clac"
  MACRO_primesearch();
return;
}
void MACRO_primesearch1(void) {
  //line 17 "tests/clacprime.clac"
  *++sp = 1; STACK_RESIZE();
  //line 17 "tests/clacprime.clac"
  CHECK_SIZE(1); CHECK_PICK(); {clac_t *i=sp - *sp; *sp = *i;};
  //line 32 "tests/clacprime.clac"
  *++sp = 2; STACK_RESIZE();
  //line 32 "tests/clacprime.clac"
  CHECK_SIZE(2); CHECK_DIV(); sp--; *sp = *sp % *(sp+1); STACK_RESIZE();
  //line 32 "tests/clacprime.clac"
  if (!*sp--){STACK_RESIZE();goto LABEL43;}
  //line 32 "tests/clacprime.clac"
  STACK_RESIZE();goto LABEL44;
  LABEL43:
  //line 42 "tests/clacprime.clac"
  *++sp = 1; STACK_RESIZE();
  //line 42 "tests/clacprime.clac"
  CHECK_SIZE(2); sp--; *sp = *sp - *(sp+1); STACK_RESIZE();
  LABEL44:
  //line 17 "tests/clacprime.clac"
  *++sp = 1; STACK_RESIZE();
  //line 17 "tests/clacprime.clac"
  CHECK_SIZE(1); CHECK_PICK(); {clac_t *i=sp - *sp; *sp = *i;};
  //line 20 "tests/clacprime.clac"
  *++sp = 4; STACK_RESIZE();
  //line 20 "tests/clacprime.clac"
  CHECK_SIZE(2); sp--; *sp = *sp < *(sp+1); STACK_RESIZE();
  //line 20 "tests/clacprime.clac"
  if (!*sp--){STACK_RESIZE();goto LABEL49;}
  //line 17 "tests/clacprime.clac"
  *++sp = 1; STACK_RESIZE();
  //line 17 "tests/clacprime.clac"
  CHECK_SIZE(1); CHECK_PICK(); {clac_t *i=sp - *sp; *sp = *i;};
  //line 26 "tests/clacprime.clac"
  *++sp = 1; STACK_RESIZE();
  //line 26 "tests/clacprime.clac"
  CHECK_SIZE(2); sp--; *sp = *sp - *(sp+1); STACK_RESIZE();
  //line 26 "tests/clacprime.clac"
  if (!*sp--){STACK_RESIZE();goto LABEL47;}
  //line 17 "tests/clacprime.clac"
  *++sp = 1; STACK_RESIZE();
  //line 17 "tests/clacprime.clac"
  CHECK_SIZE(1); CHECK_PICK(); {clac_t *i=sp - *sp; *sp = *i;};
  //line 27 "tests/clacprime.clac"
  if (!*sp--){STACK_RESIZE();goto LABEL45;}
  //line 29 "tests/clacprime.clac"
  *++sp = 0; STACK_RESIZE();
  //line 29 "tests/clacprime.clac"
  *++sp = 1; STACK_RESIZE();
  //line 27 "tests/clacprime.clac"
  STACK_RESIZE();goto LABEL46;
  LABEL45:
  //line 28 "tests/clacprime.clac"
  *++sp = 0; STACK_RESIZE();
  //line 28 "tests/clacprime.clac"
  *++sp = 0; STACK_RESIZE();
  LABEL46:
  //line 26 "tests/clacprime.clac"
  STACK_RESIZE();goto LABEL48;
  LABEL47:
  //line 28 "tests/clacprime.clac"
  *++sp = 0; STACK_RESIZE();
  //line 28 "tests/clacprime.clac"
  *++sp = 0; STACK_RESIZE();
  LABEL48:
  //line 20 "tests/clacprime.clac"
  STACK_RESIZE();goto LABEL54;
  LABEL49:
  //line 17 "tests/clacprime.clac"
  *++sp = 1; STACK_RESIZE();
  //line 17 "tests/clacprime.clac"
  CHECK_SIZE(1); CHECK_PICK(); {clac_t *i=sp - *sp; *sp = *i;};
  //line 25 "tests/clacprime.clac"
  *++sp = 2; STACK_RESIZE();
  //line 25 "tests/clacprime.clac"
  CHECK_SIZE(2); CHECK_DIV(); sp--; *sp = *sp % *(sp+1); STACK_RESIZE();
  //line 21 "tests/clacprime.clac"
  if (!*sp--){STACK_RESIZE();goto LABEL52;}
  //line 22 "tests/clacprime.clac"
  *++sp = 1; STACK_RESIZE();
  //line 17 "tests/clacprime.clac"
  *++sp = 1; STACK_RESIZE();
  //line 17 "tests/clacprime.clac"
  CHECK_SIZE(1); CHECK_PICK(); {clac_t *i=sp - *sp; *sp = *i;};
  //line 18 "tests/clacprime.clac"
  *++sp = 2; STACK_RESIZE();
  //line 18 "tests/clacprime.clac"
  CHECK_SIZE(2); sp--; *sp = *sp + *(sp+1); STACK_RESIZE();
  //line 18 "tests/clacprime.clac"
  CHECK_SIZE(3); {clac_t tmp=*(sp-2); *(sp-2)=*(sp-1); *(sp-1)=*sp; *sp=tmp;}; STACK_RESIZE();
  //line 18 "tests/clacprime.clac"
  MACRO_primeinit2();
  //line 17 "tests/clacprime.clac"
  *++sp = 1; STACK_RESIZE();
  //line 17 "tests/clacprime.clac"
  CHECK_SIZE(1); CHECK_PICK(); {clac_t *i=sp - *sp; *sp = *i;};
  //line 23 "tests/clacprime.clac"
  CHECK_SIZE(3); {clac_t tmp=*(sp-2); *(sp-2)=*(sp-1); *(sp-1)=*sp; *sp=tmp;}; STACK_RESIZE();
  //line 17 "tests/clacprime.clac"
  *++sp = 1; STACK_RESIZE();
  //line 17 "tests/clacprime.clac"
  CHECK_SIZE(1); CHECK_PICK(); {clac_t *i=sp - *sp; *sp = *i;};
  //line 23 "tests/clacprime.clac"
  *++sp = 1; STACK_RESIZE();
  //line 23 "tests/clacprime.clac"
  CHECK_SIZE(2); sp--; *sp = *sp - *(sp+1); STACK_RESIZE();
  //line 23 "tests/clacprime.clac"
  if (!*sp--){STACK_RESIZE();goto LABEL50;}
  //line 23 "tests/clacprime.clac"
  MACRO_primecheck2();
  //line 23 "tests/clacprime.clac"
  STACK_RESIZE();goto LABEL51;
  LABEL50:
  //line 23 "tests/clacprime.clac"
  *++sp = 1; STACK_RESIZE();
  LABEL51:
  //line 21 "tests/clacprime.clac"
  STACK_RESIZE();goto LABEL53;
  LABEL52:
  //line 21 "tests/clacprime.clac"
  *++sp = 0; STACK_RESIZE();
  LABEL53:
  LABEL54:
  //line 37 "tests/clacprime.clac"
  if (!*sp--){STACK_RESIZE();goto LABEL25;}
  //line 37 "tests/clacprime.clac"
  MACRO_prime1();
  //line 37 "tests/clacprime.clac"
  STACK_RESIZE();goto LABEL26;
  LABEL25:
  //line 37 "tests/clacprime.clac"
  MACRO_cleanstack();
  LABEL26:
return;
}
void MACRO_edgecheck(void) {
  //line 17 "tests/clacprime.clac"
  *++sp = 1; STACK_RESIZE();
  //line 17 "tests/clacprime.clac"
  CHECK_SIZE(1); CHECK_PICK(); {clac_t *i=sp - *sp; *sp = *i;};
  //line 33 "tests/clacprime.clac"
  *++sp = 3; STACK_RESIZE();
  //line 33 "tests/clacprime.clac"
  CHECK_SIZE(2); sp--; *sp = *sp - *(sp+1); STACK_RESIZE();
  //line 33 "tests/clacprime.clac"
  *++sp = 2; STACK_RESIZE();
  //line 33 "tests/clacprime.clac"
  CHECK_SIZE(2); sp--; *sp = *sp < *(sp+1); STACK_RESIZE();
  //line 33 "tests/clacprime.clac"
  if (!*sp--){STACK_RESIZE();goto LABEL5;}
  //line 35 "tests/clacprime.clac"
  *++sp = 2; STACK_RESIZE();
  //line 35 "tests/clacprime.clac"
  *++sp = 3; STACK_RESIZE();
  //line 35 "tests/clacprime.clac"
  CHECK_SIZE(1); clac_print(*sp--); STACK_RESIZE();
  //line 35 "tests/clacprime.clac"
  CHECK_SIZE(1); clac_print(*sp--); STACK_RESIZE();
  //line 35 "tests/clacprime.clac"
  CHECK_SIZE(1); sp--; STACK_RESIZE();
  //line 35 "tests/clacprime.clac"
  abort(); STACK_RESIZE();
  //line 33 "tests/clacprime.clac"
  STACK_RESIZE();goto LABEL6;
  LABEL5:
  //line 33 "tests/clacprime.clac"
  MACRO_primesearch1();
  LABEL6:
return;
}
int main(void){
  allocated = SMALL_STACK_SIZE;
stack = malloc(allocated*sizeof(clac_t));
sp=stack-1;

  //line 43 "tests/clacprime.clac"
  scanf("%d", ++sp); STACK_RESIZE();
  //line 43 "tests/clacprime.clac"
  MACRO_primesearch();
  free(stack);
return 0;
}
