#include <stdio.h>

/* Issues the next mess token number, starting from 1001 */
int next_token(void) {
    /* TODO 1: Use a static local variable so that the counter keeps its value between calls */
    static int token = 1000;
    return ++token;
}

/* The same logic with an automatic variable, for comparison */
int auto_token(void) {
    int token = 1000;
    return ++token;
}

/* Multi-counter extension (veg and non-veg) */
int next_veg_token(void) {
    static int veg_token = 1000;
    return ++veg_token;
}

int next_nonveg_token(void) {
    static int nonveg_token = 2000;
    return ++nonveg_token;
}

int main(void) {
    int s1 = next_token(), s2 = next_token(), s3 = next_token();
    int a1 = auto_token(), a2 = auto_token(), a3 = auto_token();

    printf("static: %d %d %d\n", s1, s2, s3);
    printf("auto : %d %d %d\n", a1, a2, a3);

    printf("\n--- Dual Counter Requirement (Veg vs Non-Veg) ---\n");
    printf("Veg Tokens    : %d, %d\n", next_veg_token(), next_veg_token());
    printf("Non-Veg Tokens: %d, %d\n", next_nonveg_token(), next_nonveg_token());

    /* Fast register loop demonstration */
    printf("\n--- Register Storage Class Demonstration ---\n");
    register int i;
    for (i = 0; i < 3; i++) {
        printf("Printing batch token receipt #%d\n", i + 1);
    }

    return 0;
}