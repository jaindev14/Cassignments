/* Q2: Employee Payroll - enum for department, double for sum */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum Dept { HR = 1, IT, FINANCE, SALES };

const char *deptName(enum Dept d) {
    switch (d) {
        case HR:      return "HR";
        case IT:      return "IT";
        case FINANCE: return "Finance";
        case SALES:   return "Sales";
    }
    return "Unknown";
}

struct Employee {
    int id;
    char name[50];
    enum Dept dept;
    double salary;
};

struct Employee *emp = NULL;
int n = 0;

void addEmployee(void) {
    struct Employee *tmp = realloc(emp, (n + 1) * sizeof(struct Employee));
    if (!tmp) { printf("Memory error!\n"); return; }
    emp = tmp;
    int d;
    printf("ID: ");     scanf("%d", &emp[n].id);
    printf("Name: ");   scanf(" %49[^\n]", emp[n].name);
    printf("Department (1=HR 2=IT 3=Finance 4=Sales): ");
    scanf("%d", &d);
    if (d < 1 || d > 4) { printf("Invalid department.\n"); return; }
    emp[n].dept = (enum Dept)d;
    printf("Salary: "); scanf("%lf", &emp[n].salary);
    n++;
    printf("Employee added.\n");
}

void deleteById(void) {
    int id, i, pos = -1;
    printf("ID to delete: "); scanf("%d", &id);
    for (i = 0; i < n; i++) if (emp[i].id == id) { pos = i; break; }
    if (pos == -1) { printf("Not found.\n"); return; }
    for (i = pos; i < n - 1; i++) emp[i] = emp[i + 1];
    n--;
    printf("Deleted.\n");
}

void printOne(struct Employee e) {
    printf("%-5d %-20s %-10s %12.2f\n", e.id, e.name, deptName(e.dept), e.salary);
}

void printAll(void) {
    int i;
    if (n == 0) { printf("No employees.\n"); return; }
    printf("%-5s %-20s %-10s %12s\n", "ID", "Name", "Dept", "Salary");
    for (i = 0; i < n; i++) printOne(emp[i]);
}

void printByDept(void) {
    int d, i, found = 0;
    printf("Department (1=HR 2=IT 3=Finance 4=Sales): ");
    scanf("%d", &d);
    for (i = 0; i < n; i++)
        if (emp[i].dept == (enum Dept)d) { printOne(emp[i]); found = 1; }
    if (!found) printf("No employee in that department.\n");
}

void totalSalary(void) {
    double total = 0;   /* sum in a double */
    int i;
    for (i = 0; i < n; i++) total += emp[i].salary;
    printf("Total salary = %.2f\n", total);
}

void saveToFile(void) {
    FILE *fp = fopen("employees.db", "wb");
    if (!fp) { printf("File error!\n"); return; }
    fwrite(emp, sizeof(struct Employee), n, fp);
    fclose(fp);
    printf("%d record(s) saved to employees.db\n", n);
}

int main(void) {
    int ch;
    do {
        printf("\n--- EMPLOYEE PAYROLL ---\n");
        printf("1.Add 2.Delete by id 3.Print all 4.By department 5.Total salary 6.Save 0.Exit\n");
        printf("Choice: "); scanf("%d", &ch);
        switch (ch) {
            case 1: addEmployee(); break;
            case 2: deleteById(); break;
            case 3: printAll(); break;
            case 4: printByDept(); break;
            case 5: totalSalary(); break;
            case 6: saveToFile(); break;
            case 0: saveToFile(); break;
            default: printf("Invalid choice!\n");
        }
    } while (ch != 0);
    free(emp);
    return 0;
}
