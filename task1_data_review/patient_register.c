#include <stdio.h>
#include <string.h>

#define MAX_PATIENTS 100

/* Nested structure for structured calendar date */
typedef struct {
    int day;
    int month;
    int year;
} Date;

/* Nested structure separating systolic and diastolic blood pressure */
typedef struct {
    int systolic;
    int diastolic;
} BloodPressure;

/* Clean, cohesive patient record */
typedef struct {
    char name[50];
    int age;
    char phone[15]; /* 15 chars safely holds 10-digit number + country code + '\0' */
    BloodPressure bp;
    Date visitDate;
} Patient;

typedef struct {
    Patient records[MAX_PATIENTS];
    int count;
} PatientRegister;

/* Re-engineered addPatient accepting a pointer to prevent global variable pollution */
int addPatient(PatientRegister *reg, const Patient *p) {
    if (reg->count >= MAX_PATIENTS) {
        printf("[ERROR] Patient register is full!\n");
        return 0;
    }
    reg->records[reg->count] = *p;
    reg->count++;
    return 1;
}

int main(void) {
    PatientRegister reg = { .count = 0 };

    Patient p1 = {
        .name = "Kavitha Raman",
        .age = 42,
        .phone = "9876543210",
        .bp = { .systolic = 120, .diastolic = 80 },
        .visitDate = { .day = 12, .month = 10, .year = 2026 }
    };

    addPatient(&reg, &p1);

    printf("=== Primary Health Centre Patient Register ===\n");
    for (int i = 0; i < reg.count; i++) {
        Patient *curr = &reg.records[i];
        printf("Patient #%d: %s | Age: %d | Phone: %s | BP: %d/%d mmHg | Date: %02d/%02d/%04d\n",
               i + 1, curr->name, curr->age, curr->phone,
               curr->bp.systolic, curr->bp.diastolic,
               curr->visitDate.day, curr->visitDate.month, curr->visitDate.year);
    }
    return 0;
}