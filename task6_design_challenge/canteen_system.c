#include <stdio.h>
#include <string.h>

typedef enum { PACKAGED, COOKED, COMBO } ItemType;

typedef struct {
    int day, month, year;
} ExpiryDate;

typedef struct {
    int hour, minute;
} PrepTime;

typedef struct {
    int id;
    char name[30];
    float price;
    int stock;
    ItemType type;
    union {
        ExpiryDate expiry;
        PrepTime prepared;
        int combo_item_ids[3];
    } detail;
    float revenue_generated;
} CanteenItem;

/* Check if packaged item expires within 2 days of current date (Assumed today: 12/10/2026) */
void check_expiry(const CanteenItem *item, int cur_d, int cur_m, int cur_y) {
    if (item->type == PACKAGED) {
        if (item->detail.expiry.year == cur_y && item->detail.expiry.month == cur_m) {
            int diff = item->detail.expiry.day - cur_d;
            if (diff >= 0 && diff <= 2) {
                printf("[ALERT] Item \"%s\" expires in %d day(s) on %02d/%02d/%04d!\n",
                       item->name, diff,
                       item->detail.expiry.day, item->detail.expiry.month, item->detail.expiry.year);
            }
        }
    }
}

/* Record a sale safely with stock verification */
int record_sale(CanteenItem *item, int qty) {
    if (item->stock < qty) {
        printf("[TRANSACTION FAILED] Insufficient stock for %s! Requested: %d, Available: %d\n",
               item->name, qty, item->stock);
        return 0;
    }
    item->stock -= qty;
    item->revenue_generated += (item->price * qty);
    printf("[SALE SUCCESS] %d x %s sold for Rs %.2f. Remaining stock: %d\n",
           qty, item->name, item->price * qty, item->stock);
    return 1;
}

int main(void) {
    CanteenItem inventory[4] = {
        { 1, "Milk Tetrapack", 30.0f, 15, PACKAGED, .detail.expiry = {13, 10, 2026}, 0.0f },
        { 2, "Veg Biryani",    90.0f, 20, COOKED,   .detail.prepared = {11, 30}, 0.0f },
        { 3, "Mini Combo Meal", 120.0f, 10, COMBO,   .detail.combo_item_ids = {1, 2, 0}, 0.0f },
        { 4, "Fruit Juice",    25.0f, 5,  PACKAGED, .detail.expiry = {25, 10, 2026}, 0.0f }
    };
    int n = 4;

    printf("=== Canteen Inventory Initial Warnings ===\n");
    for (int i = 0; i < n; i++) {
        check_expiry(&inventory[i], 12, 10, 2026);
    }

    printf("\n=== Processing Counter Transactions ===\n");
    record_sale(&inventory[0], 5);   /* Normal sale */
    record_sale(&inventory[1], 2);   /* Normal sale */
    record_sale(&inventory[3], 10);  /* Exceeds stock failure */

    /* Sort items by revenue generated descending */
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (inventory[j].revenue_generated < inventory[j + 1].revenue_generated) {
                CanteenItem temp = inventory[j];
                inventory[j] = inventory[j + 1];
                inventory[j + 1] = temp;
            }
        }
    }

    printf("\n=== Day-End Summary Sorted by Revenue ===\n");
    printf("%-20s | %-10s | %-12s | %-10s\n", "Item Name", "Price", "Units Left", "Revenue");
    printf("------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%-20s | Rs %7.2f | %10d | Rs %8.2f\n",
               inventory[i].name, inventory[i].price, inventory[i].stock, inventory[i].revenue_generated);
    }

    return 0;
}