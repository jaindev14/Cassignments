/* Q9: Student Attendance - percentage + floating compare */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int roll;
    char name[50];
    int present;
    int total;
};

struct Student *s = NULL;
int n = 0;

void addStudent(void) {
    struct Student *tmp = realloc(s, (n + 1) * sizeof(struct Student));
    if (!tmp) { printf("Memory error!\n"); return; }
    s = tmp;
    printf("Roll: ");               scanf("%d", &s[n].roll);
    printf("Name: ");               scanf(" %49[^\n]", s[n].name);
    printf("Total days: ");         scanf("%d", &s[n].total);
    printf("Days present: ");       scanf("%d", &s[n].present);
    if (s[n].total <= 0 || s[n].present < 0 || s[n].present > s[n].total) {
        printf("Invalid attendance data. Not added.\n");
        return;
    }
    n++;
    printf("Student added.\n");
}

float percent(struct Student x) {
    return ((float)x.present / x.total) * 100.0f;   /* cast to float! */
}

void printAll(void) {
    int i;
    if (n == 0) { printf("No students.\n"); return; }
    printf("%-6s %-20s %8s %6s %8s\n", "Roll", "Name", "Present", "Total", "Percent");
    for (i = 0; i < n; i++)
        printf("%-6d %-20s %8d %6d %7.2f%%\n", s[i].roll, s[i].name, s[i].present, s[i].total, percent(s[i]));
}

void printBelow75(void) {
    int i, found = 0;
    for (i = 0; i < n; i++) {
        if (percent(s[i]) < 75.0f) {   /* floating compare */
            if (!found) printf("Students below 75%% attendance:\n");
            printf("%-6d %-20s %7.2f%%\n", s[i].roll, s[i].name, percent(s[i]));
            found = 1;
        }
    }
    if (!found) printf("No student is below 75%%.\n");
}

int main(void) {
    int ch;
    do {
        printf("\n--- STUDENT ATTENDANCE ---\n");
        printf("1.Add 2.Print all 3.Below 75%% 0.Exit\n");
        printf("Choice: "); scanf("%d", &ch);
        switch (ch) {
            case 1: addStudent(); break;
            case 2: printAll(); break;
            case 3: printBelow75(); break;
            case 0: break;
            default: printf("Invalid choice!\n");
        }
    } while (ch != 0);
    free(s);
    return 0;
}
