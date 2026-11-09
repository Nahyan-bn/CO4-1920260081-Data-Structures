#include <stdio.h>

enum kind { TEMPERATURE, HUMIDITY, STATUS };

struct reading {
    enum kind type; /* tag: tells which union member is valid */
    union {
        float celsius;
        int percent;
        char status[8];
    } value;
};

void show(const struct reading *r) {
    /* TODO 1: Use a switch on r->type to print only the valid union member:
       "Temp 31.5 C", "Humidity 68 %" or "Status OK" */
    switch (r->type) {
        case TEMPERATURE:
            printf("Temp %.1f C\n", r->value.celsius);
            break;
        case HUMIDITY:
            printf("Humidity %d %%\n", r->value.percent);
            break;
        case STATUS:
            printf("Status %s\n", r->value.status);
            break;
    }
}

int main(void) {
    struct reading log[3] = {
        { TEMPERATURE, .value.celsius = 31.5f },
        { HUMIDITY,    .value.percent = 68 },
        { STATUS,      .value.status = "OK" }
    };

    printf("sizeof union = %zu, sizeof struct reading = %zu\n",
           sizeof(log[0].value), sizeof(log[0]));

    for (int i = 0; i < 3; i++) {
        show(&log[i]);
    }

    /* Task 3.4 Misuse experiment: store float, read int */
    printf("\n--- Misuse Experiment (Task 3.4) ---\n");
    struct reading test;
    test.type = TEMPERATURE;
    test.value.celsius = 31.5f;
    printf("Stored celsius: %.1f\n", test.value.celsius);
    printf("Interpreted as int percent: %d (Raw IEEE-754 bit reinterpretation)\n", test.value.percent);

    return 0;
}