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

void MACRO_sub1(void);
void MACRO_edgeclean(void);
void MACRO_isprime(void);
void MACRO_nop(void);
void MACRO_2special(void);
void MACRO_dup(void);
void MACRO_isnotprime(void);
void MACRO_3special(void);
void MACRO_primeinit2(void);
void MACRO_primeinit(void);
void MACRO_2check(void);
void MACRO_evencheck1(void);
void MACRO_evencheck(void);
void MACRO_primecheck2(void);
void MACRO_primecheck1(void);
void MACRO_0check(void);
void MACRO_startcheck1(void);
void MACRO_1check(void);
void MACRO_startcheck(void);
void MACRO_primecheck(void);
void MACRO_cleanstack(void);
void MACRO_primesearch(void);
void MACRO_prime1(void);
void MACRO_loop(void);
void MACRO_primesearch1(void);
void MACRO_edgecheck(void);
int main(void);
void MACRO_sub1(void) {

*++sp = 1; STACK_RESIZE();

CHECK_SIZE(2); sp--; *sp = *sp - *(sp+1); STACK_RESIZE();
return;
}
void MACRO_edgeclean(void) {

CHECK_SIZE(1); sp--; STACK_RESIZE();

sp--; *sp = *sp * *(sp+1); STACK_RESIZE();
return;
}
void MACRO_isprime(void) {

*++sp = 0; STACK_RESIZE();

*++sp = 1; STACK_RESIZE();
return;
}
void MACRO_nop(void) {
return;
}
void MACRO_2special(void) {

*++sp = 2; STACK_RESIZE();

CHECK_SIZE(1); sp--; STACK_RESIZE();

CHECK_SIZE(1); printf("%d\n", *sp--); STACK_RESIZE();

sp--; *sp = *sp * *(sp+1); STACK_RESIZE();
return;
}
void MACRO_dup(void) {

*++sp = 1; STACK_RESIZE();

CHECK_SIZE(1); CHECK_PICK(); {clac_t *i=sp - *sp; *sp = *i;};
return;
}
void MACRO_isnotprime(void) {

*++sp = 0; STACK_RESIZE();

*++sp = 0; STACK_RESIZE();
return;
}
void MACRO_3special(void) {

*++sp = 2; STACK_RESIZE();

*++sp = 3; STACK_RESIZE();

CHECK_SIZE(1); printf("%d\n", *sp--); STACK_RESIZE();

CHECK_SIZE(1); printf("%d\n", *sp--); STACK_RESIZE();

CHECK_SIZE(1); sp--; STACK_RESIZE();

sp--; *sp = *sp * *(sp+1); STACK_RESIZE();
return;
}
void MACRO_primeinit2(void) {

MACRO_dup();

CHECK_SIZE(3); {clac_t tmp=*(sp-2); *(sp-2)=*(sp-1); *(sp-1)=*sp; *sp=tmp;}; STACK_RESIZE();

MACRO_dup();

CHECK_SIZE(3); {clac_t tmp=*(sp-2); *(sp-2)=*(sp-1); *(sp-1)=*sp; *sp=tmp;}; STACK_RESIZE();

*++sp = 2; STACK_RESIZE();

CHECK_SIZE(2); CHECK_DIV(); sp--; *sp = *sp / *(sp+1); STACK_RESIZE();

CHECK_SIZE(2); sp--; *sp = *sp < *(sp+1); STACK_RESIZE();

if (!*sp--){STACK_RESIZE();goto LABEL21;}

MACRO_primeinit();

STACK_RESIZE();goto LABEL22;

LABEL21:

CHECK_SIZE(2); {clac_t temp = *sp; *sp = *(sp-1); *(sp-1) = temp;}; STACK_RESIZE();

LABEL22:
return;
}
void MACRO_primeinit(void) {

MACRO_dup();

*++sp = 2; STACK_RESIZE();

CHECK_SIZE(2); sp--; *sp = *sp + *(sp+1); STACK_RESIZE();

CHECK_SIZE(3); {clac_t tmp=*(sp-2); *(sp-2)=*(sp-1); *(sp-1)=*sp; *sp=tmp;}; STACK_RESIZE();

MACRO_primeinit2();
return;
}
void MACRO_2check(void) {

MACRO_dup();

*++sp = 2; STACK_RESIZE();

CHECK_SIZE(2); sp--; *sp = *sp - *(sp+1); STACK_RESIZE();

if (!*sp--){STACK_RESIZE();goto LABEL25;}

MACRO_edgeclean();

STACK_RESIZE();goto LABEL26;

LABEL25:

MACRO_2special();

LABEL26:
return;
}
void MACRO_evencheck1(void) {

MACRO_dup();

*++sp = 2; STACK_RESIZE();

CHECK_SIZE(2); CHECK_DIV(); sp--; *sp = *sp % *(sp+1); STACK_RESIZE();

if (!*sp--){STACK_RESIZE();goto LABEL3;}

MACRO_nop();

STACK_RESIZE();goto LABEL4;

LABEL3:

MACRO_sub1();

LABEL4:
return;
}
void MACRO_evencheck(void) {

MACRO_dup();

*++sp = 2; STACK_RESIZE();

CHECK_SIZE(2); CHECK_DIV(); sp--; *sp = *sp % *(sp+1); STACK_RESIZE();
return;
}
void MACRO_primecheck2(void) {

CHECK_SIZE(2); CHECK_DIV(); sp--; *sp = *sp % *(sp+1); STACK_RESIZE();

if (!*sp--){STACK_RESIZE();goto LABEL17;}

MACRO_primecheck1();

STACK_RESIZE();goto LABEL18;

LABEL17:

*++sp = 0; STACK_RESIZE();

LABEL18:
return;
}
void MACRO_primecheck1(void) {

MACRO_dup();

CHECK_SIZE(3); {clac_t tmp=*(sp-2); *(sp-2)=*(sp-1); *(sp-1)=*sp; *sp=tmp;}; STACK_RESIZE();

MACRO_dup();

*++sp = 1; STACK_RESIZE();

CHECK_SIZE(2); sp--; *sp = *sp - *(sp+1); STACK_RESIZE();

if (!*sp--){STACK_RESIZE();goto LABEL5;}

MACRO_primecheck2();

STACK_RESIZE();goto LABEL6;

LABEL5:

*++sp = 1; STACK_RESIZE();

LABEL6:
return;
}
void MACRO_0check(void) {

MACRO_dup();

if (!*sp--){STACK_RESIZE();goto LABEL1;}

MACRO_isprime();

STACK_RESIZE();goto LABEL2;

LABEL1:

MACRO_isnotprime();

LABEL2:
return;
}
void MACRO_startcheck1(void) {

*++sp = 1; STACK_RESIZE();

MACRO_primeinit();

MACRO_primecheck1();
return;
}
void MACRO_1check(void) {

MACRO_dup();

*++sp = 1; STACK_RESIZE();

CHECK_SIZE(2); sp--; *sp = *sp - *(sp+1); STACK_RESIZE();

if (!*sp--){STACK_RESIZE();goto LABEL13;}

MACRO_0check();

STACK_RESIZE();goto LABEL14;

LABEL13:

MACRO_isnotprime();

LABEL14:
return;
}
void MACRO_startcheck(void) {

MACRO_evencheck();

if (!*sp--){STACK_RESIZE();goto LABEL9;}

MACRO_startcheck1();

STACK_RESIZE();goto LABEL10;

LABEL9:

*++sp = 0; STACK_RESIZE();

LABEL10:
return;
}
void MACRO_primecheck(void) {

MACRO_dup();

*++sp = 4; STACK_RESIZE();

CHECK_SIZE(2); sp--; *sp = *sp < *(sp+1); STACK_RESIZE();

if (!*sp--){STACK_RESIZE();goto LABEL23;}

MACRO_1check();

STACK_RESIZE();goto LABEL24;

LABEL23:

MACRO_startcheck();

LABEL24:
return;
}
void MACRO_cleanstack(void) {

CHECK_SIZE(2); {clac_t temp = *sp; *sp = *(sp-1); *(sp-1) = temp;}; STACK_RESIZE();

*++sp = 1; STACK_RESIZE();

CHECK_SIZE(2); sp--; *sp = *sp - *(sp+1); STACK_RESIZE();

if (!*sp--){STACK_RESIZE();goto LABEL7;}

MACRO_cleanstack();

STACK_RESIZE();goto LABEL8;

LABEL7:

MACRO_loop();

LABEL8:
return;
}
void MACRO_primesearch(void) {

MACRO_dup();

*++sp = 3; STACK_RESIZE();

CHECK_SIZE(2); sp--; *sp = *sp < *(sp+1); STACK_RESIZE();

if (!*sp--){STACK_RESIZE();goto LABEL19;}

MACRO_2check();

STACK_RESIZE();goto LABEL20;

LABEL19:

MACRO_edgecheck();

LABEL20:
return;
}
void MACRO_prime1(void) {

CHECK_SIZE(1); sp--; STACK_RESIZE();

CHECK_SIZE(1); printf("%d\n", *sp--); STACK_RESIZE();

MACRO_loop();
return;
}
void MACRO_loop(void) {

*++sp = 2; STACK_RESIZE();

CHECK_SIZE(2); sp--; *sp = *sp - *(sp+1); STACK_RESIZE();

MACRO_primesearch();
return;
}
void MACRO_primesearch1(void) {

MACRO_evencheck1();

MACRO_primecheck();

if (!*sp--){STACK_RESIZE();goto LABEL11;}

MACRO_prime1();

STACK_RESIZE();goto LABEL12;

LABEL11:

MACRO_cleanstack();

LABEL12:
return;
}
void MACRO_edgecheck(void) {

MACRO_dup();

*++sp = 3; STACK_RESIZE();

CHECK_SIZE(2); sp--; *sp = *sp - *(sp+1); STACK_RESIZE();

*++sp = 2; STACK_RESIZE();

CHECK_SIZE(2); sp--; *sp = *sp < *(sp+1); STACK_RESIZE();

if (!*sp--){STACK_RESIZE();goto LABEL15;}

MACRO_3special();

STACK_RESIZE();goto LABEL16;

LABEL15:

MACRO_primesearch1();

LABEL16:
return;
}
int main(void){
allocated = SMALL_STACK_SIZE;
stack = malloc(allocated*sizeof(clac_t));
sp=stack-1;


scanf("%d", ++sp); STACK_RESIZE();

MACRO_primesearch();

return 0;
}
