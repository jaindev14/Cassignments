/* Q3: Product Inventory - value = sum of quantity * price */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Product {
    int id;
    char name[50];
    int quantity;
    float price;
};

struct Product *p = NULL;
int n = 0;

void addProduct(void) {
    struct Product *tmp = realloc(p, (n + 1) * sizeof(struct Product));
    if (!tmp) { printf("Memory error!\n"); return; }
    p = tmp;
    printf("ID: ");       scanf("%d", &p[n].id);
    printf("Name: ");     scanf(" %49[^\n]", p[n].name);
    printf("Quantity: "); scanf("%d", &p[n].quantity);
    printf("Price: ");    scanf("%f", &p[n].price);
    n++;
    printf("Product added.\n");
}

void deleteProduct(void) {
    int id, i, pos = -1;
    printf("ID to delete: "); scanf("%d", &id);
    for (i = 0; i < n; i++) if (p[i].id == id) { pos = i; break; }
    if (pos == -1) { printf("Not found.\n"); return; }
    for (i = pos; i < n - 1; i++) p[i] = p[i + 1];
    n--;
    printf("Deleted.\n");
}

void printOne(struct Product x) {
    printf("%-5d %-20s %6d %10.2f\n", x.id, x.name, x.quantity, x.price);
}

void printAll(void) {
    int i;
    if (n == 0) { printf("No products.\n"); return; }
    printf("%-5s %-20s %6s %10s\n", "ID", "Name", "Qty", "Price");
    for (i = 0; i < n; i++) printOne(p[i]);
}

void printLowStock(void) {
    int limit, i, found = 0;
    printf("Enter stock limit: "); scanf("%d", &limit);
    for (i = 0; i < n; i++)
        if (p[i].quantity < limit) { printOne(p[i]); found = 1; }
    if (!found) printf("No low-stock products.\n");
}

void totalValue(void) {
    double total = 0;
    int i;
    for (i = 0; i < n; i++) total += p[i].quantity * (double)p[i].price;
    printf("Total inventory value = %.2f\n", total);
}

void updateQuantity(void) {
    int id, i, q;
    printf("Product ID: "); scanf("%d", &id);
    for (i = 0; i < n; i++) {
        if (p[i].id == id) {
            printf("Current quantity = %d. New quantity: ", p[i].quantity);
            scanf("%d", &q);
            p[i].quantity = q;
            printf("Updated.\n");
            return;
        }
    }
    printf("Product not found.\n");
}

void saveToFile(void) {
    FILE *fp = fopen("products.db", "wb");
    if (!fp) { printf("File error!\n"); return; }
    fwrite(p, sizeof(struct Product), n, fp);
    fclose(fp);
    printf("%d record(s) saved to products.db\n", n);
}

int main(void) {
    int ch;
    do {
        printf("\n--- PRODUCT INVENTORY ---\n");
        printf("1.Add 2.Delete 3.Print all 4.Low stock 5.Total value 6.Update qty 0.Exit\n");
        printf("Choice: "); scanf("%d", &ch);
        switch (ch) {
            case 1: addProduct(); break;
            case 2: deleteProduct(); break;
            case 3: printAll(); break;
            case 4: printLowStock(); break;
            case 5: totalValue(); break;
            case 6: updateQuantity(); break;
            case 0: saveToFile(); break;
            default: printf("Invalid choice!\n");
        }
    } while (ch != 0);
    free(p);
    return 0;
}
