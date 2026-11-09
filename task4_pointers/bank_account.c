#include <stdio.h>

struct account {
    int number;
    float balance;
};

/* Repaired: Passed by pointer so changes mutate the actual caller's memory */
void addinterest(struct account *a, float rate) {
    printf("[Inside addinterest] Address of struct: %p\n", (void*)a);
    a->balance = a->balance + a->balance * rate / 100.0f;
}

int main(void) {
    struct account list[3] = {
        {101, 5000.0f},
        {102, 12000.0f},
        {103, 800.0f}
    };
    struct account *p = list;

    printf("=== Repaired Bank Account Interest Calculator ===\n");
    for (int i = 0; i < 3; i++) {
        printf("[Inside main] Address of list[%d]: %p\n", i, (void*)&list[i]);
        addinterest(&list[i], 4.0f);
    }

    printf("\n--- Updated Balances ---\n");
    for (int i = 0; i < 3; i++) {
        /* Correct syntax using structure pointer and arrow operator */
        printf("Account %d: Rs %.2f\n", (p + i)->number, (p + i)->balance);
    }

    return 0;
}