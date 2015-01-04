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

void MACRO_2special(void);
void MACRO_isnotprime(void);
void MACRO_isprime(void);
void MACRO_nop(void);
void MACRO_dup(void);
void MACRO_3special(void);
void MACRO_sub1(void);
void MACRO_edgeclean(void);
void MACRO_primeinit2(void);
void MACRO_primeinit(void);
void MACRO_primecheck2(void);
void MACRO_primecheck1(void);
void MACRO_0check(void);
void MACRO_evencheck(void);
void MACRO_evencheck1(void);
void MACRO_2check(void);
void MACRO_startcheck1(void);
void MACRO_1check(void);
void MACRO_startcheck(void);
void MACRO_primecheck(void);
void MACRO_prime1(void);
void MACRO_edgecheck(void);
void MACRO_loop(void);
void MACRO_primesearch1(void);
void MACRO_cleanstack(void);
void MACRO_primesearch(void);
int main(void);
void MACRO_2special(void) {
//line 25 "slowprime.clac"
*++sp = 2; STACK_RESIZE();
//line 25 "slowprime.clac"
CHECK_SIZE(1); sp--; STACK_RESIZE();
//line 25 "slowprime.clac"
CHECK_SIZE(1); printf("%d\n", *sp--); STACK_RESIZE();
//line 25 "slowprime.clac"
sp--; *sp = *sp * *(sp+1); STACK_RESIZE();
return;
}
void MACRO_isnotprime(void) {
//line 19 "slowprime.clac"
*++sp = 0; STACK_RESIZE();
//line 19 "slowprime.clac"
*++sp = 0; STACK_RESIZE();
return;
}
void MACRO_isprime(void) {
//line 20 "slowprime.clac"
*++sp = 0; STACK_RESIZE();
//line 20 "slowprime.clac"
*++sp = 1; STACK_RESIZE();
return;
}
void MACRO_nop(void) {
return;
}
void MACRO_dup(void) {
//line 8 "slowprime.clac"
*++sp = 1; STACK_RESIZE();
//line 8 "slowprime.clac"
CHECK_SIZE(1); CHECK_PICK(); {clac_t *i=sp - *sp; *sp = *i;};
return;
}
void MACRO_3special(void) {
//line 26 "slowprime.clac"
*++sp = 2; STACK_RESIZE();
//line 26 "slowprime.clac"
*++sp = 3; STACK_RESIZE();
//line 26 "slowprime.clac"
CHECK_SIZE(1); printf("%d\n", *sp--); STACK_RESIZE();
//line 26 "slowprime.clac"
CHECK_SIZE(1); printf("%d\n", *sp--); STACK_RESIZE();
//line 26 "slowprime.clac"
CHECK_SIZE(1); sp--; STACK_RESIZE();
//line 26 "slowprime.clac"
sp--; *sp = *sp * *(sp+1); STACK_RESIZE();
return;
}
void MACRO_sub1(void) {
//line 33 "slowprime.clac"
*++sp = 1; STACK_RESIZE();
//line 33 "slowprime.clac"
CHECK_SIZE(2); sp--; *sp = *sp - *(sp+1); STACK_RESIZE();
return;
}
void MACRO_edgeclean(void) {
//line 31 "slowprime.clac"
CHECK_SIZE(1); sp--; STACK_RESIZE();
//line 31 "slowprime.clac"
sp--; *sp = *sp * *(sp+1); STACK_RESIZE();
return;
}
void MACRO_primeinit2(void) {
//line 10 "slowprime.clac"
MACRO_dup();
//line 10 "slowprime.clac"
CHECK_SIZE(3); {clac_t tmp=*(sp-2); *(sp-2)=*(sp-1); *(sp-1)=*sp; *sp=tmp;}; STACK_RESIZE();
//line 10 "slowprime.clac"
MACRO_dup();
//line 10 "slowprime.clac"
CHECK_SIZE(3); {clac_t tmp=*(sp-2); *(sp-2)=*(sp-1); *(sp-1)=*sp; *sp=tmp;}; STACK_RESIZE();
//line 10 "slowprime.clac"
*++sp = 2; STACK_RESIZE();
//line 10 "slowprime.clac"
CHECK_SIZE(2); CHECK_DIV(); sp--; *sp = *sp / *(sp+1); STACK_RESIZE();
//line 10 "slowprime.clac"
CHECK_SIZE(2); sp--; *sp = *sp < *(sp+1); STACK_RESIZE();
//line 10 "slowprime.clac"
if (!*sp--){STACK_RESIZE();goto LABEL17;}
//line 10 "slowprime.clac"
MACRO_primeinit();
//line 10 "slowprime.clac"
STACK_RESIZE();goto LABEL18;

LABEL17:
//line 10 "slowprime.clac"
CHECK_SIZE(2); {clac_t temp = *sp; *sp = *(sp-1); *(sp-1) = temp;}; STACK_RESIZE();

LABEL18:
return;
}
void MACRO_primeinit(void) {
//line 9 "slowprime.clac"
MACRO_dup();
//line 9 "slowprime.clac"
*++sp = 2; STACK_RESIZE();
//line 9 "slowprime.clac"
CHECK_SIZE(2); sp--; *sp = *sp + *(sp+1); STACK_RESIZE();
//line 9 "slowprime.clac"
CHECK_SIZE(3); {clac_t tmp=*(sp-2); *(sp-2)=*(sp-1); *(sp-1)=*sp; *sp=tmp;}; STACK_RESIZE();
//line 9 "slowprime.clac"
MACRO_primeinit2();
return;
}
void MACRO_primecheck2(void) {
//line 15 "slowprime.clac"
CHECK_SIZE(2); CHECK_DIV(); sp--; *sp = *sp % *(sp+1); STACK_RESIZE();
//line 15 "slowprime.clac"
if (!*sp--){STACK_RESIZE();goto LABEL21;}
//line 15 "slowprime.clac"
MACRO_primecheck1();
//line 15 "slowprime.clac"
STACK_RESIZE();goto LABEL22;

LABEL21:
//line 15 "slowprime.clac"
*++sp = 0; STACK_RESIZE();

LABEL22:
return;
}
void MACRO_primecheck1(void) {
//line 14 "slowprime.clac"
MACRO_dup();
//line 14 "slowprime.clac"
CHECK_SIZE(3); {clac_t tmp=*(sp-2); *(sp-2)=*(sp-1); *(sp-1)=*sp; *sp=tmp;}; STACK_RESIZE();
//line 14 "slowprime.clac"
MACRO_dup();
//line 14 "slowprime.clac"
*++sp = 1; STACK_RESIZE();
//line 14 "slowprime.clac"
CHECK_SIZE(2); sp--; *sp = *sp - *(sp+1); STACK_RESIZE();
//line 14 "slowprime.clac"
if (!*sp--){STACK_RESIZE();goto LABEL9;}
//line 14 "slowprime.clac"
MACRO_primecheck2();
//line 14 "slowprime.clac"
STACK_RESIZE();goto LABEL10;

LABEL9:
//line 14 "slowprime.clac"
*++sp = 1; STACK_RESIZE();

LABEL10:
return;
}
void MACRO_0check(void) {
//line 18 "slowprime.clac"
MACRO_dup();
//line 18 "slowprime.clac"
if (!*sp--){STACK_RESIZE();goto LABEL5;}
//line 18 "slowprime.clac"
MACRO_isprime();
//line 18 "slowprime.clac"
STACK_RESIZE();goto LABEL6;

LABEL5:
//line 18 "slowprime.clac"
MACRO_isnotprime();

LABEL6:
return;
}
void MACRO_evencheck(void) {
//line 16 "slowprime.clac"
MACRO_dup();
//line 16 "slowprime.clac"
*++sp = 2; STACK_RESIZE();
//line 16 "slowprime.clac"
CHECK_SIZE(2); CHECK_DIV(); sp--; *sp = *sp % *(sp+1); STACK_RESIZE();
return;
}
void MACRO_evencheck1(void) {
//line 23 "slowprime.clac"
MACRO_dup();
//line 23 "slowprime.clac"
*++sp = 2; STACK_RESIZE();
//line 23 "slowprime.clac"
CHECK_SIZE(2); CHECK_DIV(); sp--; *sp = *sp % *(sp+1); STACK_RESIZE();
//line 23 "slowprime.clac"
if (!*sp--){STACK_RESIZE();goto LABEL23;}
//line 23 "slowprime.clac"
MACRO_nop();
//line 23 "slowprime.clac"
STACK_RESIZE();goto LABEL24;

LABEL23:
//line 23 "slowprime.clac"
MACRO_sub1();

LABEL24:
return;
}
void MACRO_2check(void) {
//line 27 "slowprime.clac"
MACRO_dup();
//line 27 "slowprime.clac"
*++sp = 2; STACK_RESIZE();
//line 27 "slowprime.clac"
CHECK_SIZE(2); sp--; *sp = *sp - *(sp+1); STACK_RESIZE();
//line 27 "slowprime.clac"
if (!*sp--){STACK_RESIZE();goto LABEL15;}
//line 27 "slowprime.clac"
MACRO_edgeclean();
//line 27 "slowprime.clac"
STACK_RESIZE();goto LABEL16;

LABEL15:
//line 27 "slowprime.clac"
MACRO_2special();

LABEL16:
return;
}
void MACRO_startcheck1(void) {
//line 13 "slowprime.clac"
*++sp = 1; STACK_RESIZE();
//line 13 "slowprime.clac"
MACRO_primeinit();
//line 13 "slowprime.clac"
MACRO_primecheck1();
return;
}
void MACRO_1check(void) {
//line 17 "slowprime.clac"
MACRO_dup();
//line 17 "slowprime.clac"
*++sp = 1; STACK_RESIZE();
//line 17 "slowprime.clac"
CHECK_SIZE(2); sp--; *sp = *sp - *(sp+1); STACK_RESIZE();
//line 17 "slowprime.clac"
if (!*sp--){STACK_RESIZE();goto LABEL19;}
//line 17 "slowprime.clac"
MACRO_0check();
//line 17 "slowprime.clac"
STACK_RESIZE();goto LABEL20;

LABEL19:
//line 17 "slowprime.clac"
MACRO_isnotprime();

LABEL20:
return;
}
void MACRO_startcheck(void) {
//line 12 "slowprime.clac"
MACRO_evencheck();
//line 12 "slowprime.clac"
if (!*sp--){STACK_RESIZE();goto LABEL13;}
//line 12 "slowprime.clac"
MACRO_startcheck1();
//line 12 "slowprime.clac"
STACK_RESIZE();goto LABEL14;

LABEL13:
//line 12 "slowprime.clac"
*++sp = 0; STACK_RESIZE();

LABEL14:
return;
}
void MACRO_primecheck(void) {
//line 11 "slowprime.clac"
MACRO_dup();
//line 11 "slowprime.clac"
*++sp = 4; STACK_RESIZE();
//line 11 "slowprime.clac"
CHECK_SIZE(2); sp--; *sp = *sp < *(sp+1); STACK_RESIZE();
//line 11 "slowprime.clac"
if (!*sp--){STACK_RESIZE();goto LABEL3;}
//line 11 "slowprime.clac"
MACRO_1check();
//line 11 "slowprime.clac"
STACK_RESIZE();goto LABEL4;

LABEL3:
//line 11 "slowprime.clac"
MACRO_startcheck();

LABEL4:
return;
}
void MACRO_prime1(void) {
//line 29 "slowprime.clac"
CHECK_SIZE(1); sp--; STACK_RESIZE();
//line 29 "slowprime.clac"
CHECK_SIZE(1); printf("%d\n", *sp--); STACK_RESIZE();
//line 29 "slowprime.clac"
MACRO_loop();
return;
}
void MACRO_edgecheck(void) {
//line 24 "slowprime.clac"
MACRO_dup();
//line 24 "slowprime.clac"
*++sp = 3; STACK_RESIZE();
//line 24 "slowprime.clac"
CHECK_SIZE(2); sp--; *sp = *sp - *(sp+1); STACK_RESIZE();
//line 24 "slowprime.clac"
*++sp = 2; STACK_RESIZE();
//line 24 "slowprime.clac"
CHECK_SIZE(2); sp--; *sp = *sp < *(sp+1); STACK_RESIZE();
//line 24 "slowprime.clac"
if (!*sp--){STACK_RESIZE();goto LABEL7;}
//line 24 "slowprime.clac"
MACRO_3special();
//line 24 "slowprime.clac"
STACK_RESIZE();goto LABEL8;

LABEL7:
//line 24 "slowprime.clac"
MACRO_primesearch1();

LABEL8:
return;
}
void MACRO_loop(void) {
//line 32 "slowprime.clac"
*++sp = 2; STACK_RESIZE();
//line 32 "slowprime.clac"
CHECK_SIZE(2); sp--; *sp = *sp - *(sp+1); STACK_RESIZE();
//line 32 "slowprime.clac"
MACRO_primesearch();
return;
}
void MACRO_primesearch1(void) {
//line 28 "slowprime.clac"
MACRO_evencheck1();
//line 28 "slowprime.clac"
MACRO_primecheck();
//line 28 "slowprime.clac"
if (!*sp--){STACK_RESIZE();goto LABEL1;}
//line 28 "slowprime.clac"
MACRO_prime1();
//line 28 "slowprime.clac"
STACK_RESIZE();goto LABEL2;

LABEL1:
//line 28 "slowprime.clac"
MACRO_cleanstack();

LABEL2:
return;
}
void MACRO_cleanstack(void) {
//line 30 "slowprime.clac"
CHECK_SIZE(2); {clac_t temp = *sp; *sp = *(sp-1); *(sp-1) = temp;}; STACK_RESIZE();
//line 30 "slowprime.clac"
*++sp = 1; STACK_RESIZE();
//line 30 "slowprime.clac"
CHECK_SIZE(2); sp--; *sp = *sp - *(sp+1); STACK_RESIZE();
//line 30 "slowprime.clac"
if (!*sp--){STACK_RESIZE();goto LABEL25;}
//line 30 "slowprime.clac"
MACRO_cleanstack();
//line 30 "slowprime.clac"
STACK_RESIZE();goto LABEL26;

LABEL25:
//line 30 "slowprime.clac"
MACRO_loop();

LABEL26:
return;
}
void MACRO_primesearch(void) {
//line 22 "slowprime.clac"
MACRO_dup();
//line 22 "slowprime.clac"
*++sp = 3; STACK_RESIZE();
//line 22 "slowprime.clac"
CHECK_SIZE(2); sp--; *sp = *sp < *(sp+1); STACK_RESIZE();
//line 22 "slowprime.clac"
if (!*sp--){STACK_RESIZE();goto LABEL11;}
//line 22 "slowprime.clac"
MACRO_2check();
//line 22 "slowprime.clac"
STACK_RESIZE();goto LABEL12;

LABEL11:
//line 22 "slowprime.clac"
MACRO_edgecheck();

LABEL12:
return;
}
int main(void){
allocated = SMALL_STACK_SIZE;
stack = malloc(allocated*sizeof(clac_t));
sp=stack-1;

//line 34 "slowprime.clac"
scanf("%d", ++sp); STACK_RESIZE();
//line 34 "slowprime.clac"
MACRO_primesearch();

return 0;
}
