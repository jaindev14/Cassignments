/* Q7: Contact Book - strstr, strcmp, qsort */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Contact {
    char name[50];
    char phone[15];
    char email[50];
};

struct Contact *c = NULL;
int n = 0;

void addContact(void) {
    struct Contact *tmp = realloc(c, (n + 1) * sizeof(struct Contact));
    if (!tmp) { printf("Memory error!\n"); return; }
    c = tmp;
    printf("Name: ");  scanf(" %49[^\n]", c[n].name);
    printf("Phone: "); scanf(" %14[^\n]", c[n].phone);
    printf("Email: "); scanf(" %49[^\n]", c[n].email);
    n++;
    printf("Contact added.\n");
}

void deleteByName(void) {
    char name[50]; int i, pos = -1;
    printf("Name to delete: "); scanf(" %49[^\n]", name);
    for (i = 0; i < n; i++)
        if (strcmp(c[i].name, name) == 0) { pos = i; break; }   /* exact match */
    if (pos == -1) { printf("Not found.\n"); return; }
    for (i = pos; i < n - 1; i++) c[i] = c[i + 1];
    n--;
    printf("Deleted.\n");
}

void printOne(struct Contact x) {
    printf("%-20s %-15s %-30s\n", x.name, x.phone, x.email);
}

void searchByName(void) {
    char key[50]; int i, found = 0;
    printf("Search text: "); scanf(" %49[^\n]", key);
    for (i = 0; i < n; i++)
        if (strstr(c[i].name, key) != NULL) { printOne(c[i]); found = 1; }  /* substring */
    if (!found) printf("No match.\n");
}

/* comparison function for qsort */
int compareByName(const void *a, const void *b) {
    const struct Contact *x = (const struct Contact *)a;
    const struct Contact *y = (const struct Contact *)b;
    return strcmp(x->name, y->name);
}

void printSorted(void) {
    int i;
    if (n == 0) { printf("No contacts.\n"); return; }
    qsort(c, n, sizeof(struct Contact), compareByName);
    printf("%-20s %-15s %-30s\n", "Name", "Phone", "Email");
    for (i = 0; i < n; i++) printOne(c[i]);
}

int main(void) {
    int ch;
    do {
        printf("\n--- CONTACT BOOK ---\n");
        printf("1.Add 2.Delete by name 3.Search (substring) 4.Print sorted 0.Exit\n");
        printf("Choice: "); scanf("%d", &ch);
        switch (ch) {
            case 1: addContact(); break;
            case 2: deleteByName(); break;
            case 3: searchByName(); break;
            case 4: printSorted(); break;
            case 0: break;
            default: printf("Invalid choice!\n");
        }
    } while (ch != 0);
    free(c);
    return 0;
}
