/* Q1: Student Marks System
   Struct + dynamic array (realloc) + menu + binary file save */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int roll;
    char name[50];
    float marks;      /* marks obtained */
    float total;      /* total marks */
    float percentage; /* calculated automatically */
};

struct Student *list = NULL;   /* dynamic array */
int count = 0;

void addStudent(void) {
    struct Student *tmp = realloc(list, (count + 1) * sizeof(struct Student));
    if (tmp == NULL) { printf("Memory allocation failed!\n"); return; }
    list = tmp;

    struct Student *s = &list[count];
    printf("Roll no: ");            scanf("%d", &s->roll);
    printf("Name: ");               scanf(" %49[^\n]", s->name);
    printf("Marks obtained: ");     scanf("%f", &s->marks);
    printf("Total marks: ");        scanf("%f", &s->total);
    s->percentage = (s->marks / s->total) * 100;
    count++;
    printf("Student added.\n");
}

void deleteByRoll(void) {
    int roll, i, found = -1;
    printf("Enter roll to delete: ");
    scanf("%d", &roll);
    for (i = 0; i < count; i++)
        if (list[i].roll == roll) { found = i; break; }
    if (found == -1) { printf("Roll not found.\n"); return; }
    for (i = found; i < count - 1; i++)   /* shift left */
        list[i] = list[i + 1];
    count--;
    printf("Deleted.\n");
}

void printOne(struct Student s) {
    printf("%-6d %-20s %7.2f %7.2f %8.2f%%\n", s.roll, s.name, s.marks, s.total, s.percentage);
}

void printAll(void) {
    int i;
    if (count == 0) { printf("No records.\n"); return; }
    printf("%-6s %-20s %7s %7s %9s\n", "Roll", "Name", "Marks", "Total", "Percent");
    for (i = 0; i < count; i++) printOne(list[i]);
}

void printAboveX(void) {
    float x; int i, found = 0;
    printf("Enter percentage X: ");
    scanf("%f", &x);
    for (i = 0; i < count; i++)
        if (list[i].percentage > x) { printOne(list[i]); found = 1; }
    if (!found) printf("No student above %.2f%%\n", x);
}

void classAverage(void) {
    int i; double sum = 0;
    if (count == 0) { printf("No records.\n"); return; }
    for (i = 0; i < count; i++) sum += list[i].percentage;
    printf("Class average = %.2f%%\n", sum / count);
}

void saveToFile(void) {
    FILE *fp = fopen("students.db", "wb");
    if (fp == NULL) { printf("Cannot open file!\n"); return; }
    fwrite(list, sizeof(struct Student), count, fp);
    fclose(fp);
    printf("%d record(s) saved to students.db\n", count);
}

int main(void) {
    int ch;
    do {
        printf("\n--- STUDENT MARKS SYSTEM ---\n");
        printf("1.Add 2.Delete by roll 3.Print all 4.Above X%% 5.Class average 6.Save to file 0.Exit\n");
        printf("Choice: ");
        scanf("%d", &ch);
        switch (ch) {
            case 1: addStudent(); break;
            case 2: deleteByRoll(); break;
            case 3: printAll(); break;
            case 4: printAboveX(); break;
            case 5: classAverage(); break;
            case 6: saveToFile(); break;
            case 0: saveToFile(); break;
            default: printf("Invalid choice!\n");
        }
    } while (ch != 0);
    free(list);
    return 0;
}
