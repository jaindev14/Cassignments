/* Q6: Vehicle Parking - fee = hours * rate */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RATE 20   /* rupees per hour */

struct Vehicle {
    char number[15];
    char owner[50];
    int entryHour;   /* 0 - 23 */
};

struct Vehicle *v = NULL;
int n = 0;

void parkVehicle(void) {
    struct Vehicle *tmp = realloc(v, (n + 1) * sizeof(struct Vehicle));
    if (!tmp) { printf("Memory error!\n"); return; }
    v = tmp;
    printf("Vehicle number: "); scanf(" %14[^\n]", v[n].number);
    printf("Owner name: ");     scanf(" %49[^\n]", v[n].owner);
    printf("Entry hour (0-23): "); scanf("%d", &v[n].entryHour);
    n++;
    printf("Vehicle parked.\n");
}

/* returns index of vehicle or -1 */
int findVehicle(const char *num) {
    int i;
    for (i = 0; i < n; i++)
        if (strcmp(v[i].number, num) == 0) return i;
    return -1;
}

void removeVehicle(void) {
    char num[15]; int pos, i, exitHour, hours;
    printf("Vehicle number: "); scanf(" %14[^\n]", num);
    pos = findVehicle(num);
    if (pos == -1) { printf("Vehicle not found.\n"); return; }

    printf("Exit hour (0-23): "); scanf("%d", &exitHour);
    hours = exitHour - v[pos].entryHour;
    if (hours <= 0) hours = 1;               /* minimum 1 hour */
    printf("Parked for %d hour(s). Fee = %d * %d = Rs.%d\n", hours, hours, RATE, hours * RATE);

    for (i = pos; i < n - 1; i++) v[i] = v[i + 1];
    n--;
    printf("Vehicle removed.\n");
}

void printAll(void) {
    int i;
    if (n == 0) { printf("Parking is empty.\n"); return; }
    printf("%-15s %-20s %s\n", "Number", "Owner", "Entry");
    for (i = 0; i < n; i++)
        printf("%-15s %-20s %d:00\n", v[i].number, v[i].owner, v[i].entryHour);
}

int main(void) {
    int ch;
    do {
        printf("\n--- VEHICLE PARKING ---\n");
        printf("1.Park 2.Remove (and pay fee) 3.Print all 4.Count 0.Exit\n");
        printf("Choice: "); scanf("%d", &ch);
        switch (ch) {
            case 1: parkVehicle(); break;
            case 2: removeVehicle(); break;
            case 3: printAll(); break;
            case 4: printf("Vehicles parked: %d\n", n); break;
            case 0: break;
            default: printf("Invalid choice!\n");
        }
    } while (ch != 0);
    free(v);
    return 0;
}
