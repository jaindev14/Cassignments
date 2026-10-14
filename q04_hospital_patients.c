/* Q4: Hospital Patients - two filters: age and disease */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Patient {
    int id;
    char name[50];
    int age;
    char disease[50];
};

struct Patient *p = NULL;
int n = 0;

void addPatient(void) {
    struct Patient *tmp = realloc(p, (n + 1) * sizeof(struct Patient));
    if (!tmp) { printf("Memory error!\n"); return; }
    p = tmp;
    printf("ID: ");      scanf("%d", &p[n].id);
    printf("Name: ");    scanf(" %49[^\n]", p[n].name);
    printf("Age: ");     scanf("%d", &p[n].age);
    printf("Disease: "); scanf(" %49[^\n]", p[n].disease);
    n++;
    printf("Patient admitted.\n");
}

void discharge(void) {
    int id, i, pos = -1;
    printf("ID to discharge: "); scanf("%d", &id);
    for (i = 0; i < n; i++) if (p[i].id == id) { pos = i; break; }
    if (pos == -1) { printf("Not found.\n"); return; }
    for (i = pos; i < n - 1; i++) p[i] = p[i + 1];
    n--;
    printf("Patient discharged.\n");
}

void printOne(struct Patient x) {
    printf("%-5d %-20s %4d  %-20s\n", x.id, x.name, x.age, x.disease);
}

void printAll(void) {
    int i;
    if (n == 0) { printf("No patients.\n"); return; }
    printf("%-5s %-20s %4s  %-20s\n", "ID", "Name", "Age", "Disease");
    for (i = 0; i < n; i++) printOne(p[i]);
}

void printAboveAge(void) {
    int age, i, found = 0;
    printf("Enter age: "); scanf("%d", &age);
    for (i = 0; i < n; i++)
        if (p[i].age > age) { printOne(p[i]); found = 1; }
    if (!found) printf("No patient above %d.\n", age);
}

void printByDisease(void) {
    char d[50]; int i, found = 0;
    printf("Enter disease: "); scanf(" %49[^\n]", d);
    for (i = 0; i < n; i++)
        if (strcmp(p[i].disease, d) == 0) { printOne(p[i]); found = 1; }
    if (!found) printf("No patient with %s.\n", d);
}

void saveToFile(void) {
    FILE *fp = fopen("patients.db", "wb");
    if (!fp) { printf("File error!\n"); return; }
    fwrite(p, sizeof(struct Patient), n, fp);
    fclose(fp);
    printf("%d record(s) saved to patients.db\n", n);
}

int main(void) {
    int ch;
    do {
        printf("\n--- HOSPITAL PATIENTS ---\n");
        printf("1.Admit 2.Discharge 3.Print all 4.Above age 5.By disease 0.Exit\n");
        printf("Choice: "); scanf("%d", &ch);
        switch (ch) {
            case 1: addPatient(); break;
            case 2: discharge(); break;
            case 3: printAll(); break;
            case 4: printAboveAge(); break;
            case 5: printByDisease(); break;
            case 0: saveToFile(); break;
            default: printf("Invalid choice!\n");
        }
    } while (ch != 0);
    free(p);
    return 0;
}
