/* Q10: Hotel Room Booking - booked flag in the structure */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Room {
    int number;
    char type[20];    /* e.g. Single, Double, Suite */
    float price;
    int booked;       /* 0 = free, 1 = booked */
};

struct Room *r = NULL;
int n = 0;

void addRoom(void) {
    struct Room *tmp = realloc(r, (n + 1) * sizeof(struct Room));
    if (!tmp) { printf("Memory error!\n"); return; }
    r = tmp;
    printf("Room number: "); scanf("%d", &r[n].number);
    printf("Type (Single/Double/Suite): "); scanf(" %19s", r[n].type);
    printf("Price per night: "); scanf("%f", &r[n].price);
    r[n].booked = 0;
    n++;
    printf("Room added.\n");
}

void bookRoom(void) {
    int no, i;
    printf("Room number to book: "); scanf("%d", &no);
    for (i = 0; i < n; i++) {
        if (r[i].number == no) {
            if (r[i].booked) { printf("Room already booked.\n"); return; }
            r[i].booked = 1;
            printf("Room %d booked.\n", no);
            return;
        }
    }
    printf("Room not found.\n");
}

void freeRoom(void) {
    int no, i;
    printf("Room number to free: "); scanf("%d", &no);
    for (i = 0; i < n; i++) {
        if (r[i].number == no) {
            if (!r[i].booked) { printf("Room is already free.\n"); return; }
            r[i].booked = 0;
            printf("Room %d is now free.\n", no);
            return;
        }
    }
    printf("Room not found.\n");
}

void listAvailableByType(void) {
    char t[20]; int i, found = 0;
    printf("Room type: "); scanf(" %19s", t);
    for (i = 0; i < n; i++) {
        if (!r[i].booked && strcmp(r[i].type, t) == 0) {
            printf("Room %d  %-8s  Rs.%.2f\n", r[i].number, r[i].type, r[i].price);
            found = 1;
        }
    }
    if (!found) printf("No available %s rooms.\n", t);
}

int main(void) {
    int ch;
    do {
        printf("\n--- HOTEL ROOM BOOKING ---\n");
        printf("1.Add room 2.Book 3.Free 4.Available by type 0.Exit\n");
        printf("Choice: "); scanf("%d", &ch);
        switch (ch) {
            case 1: addRoom(); break;
            case 2: bookRoom(); break;
            case 3: freeRoom(); break;
            case 4: listAvailableByType(); break;
            case 0: break;
            default: printf("Invalid choice!\n");
        }
    } while (ch != 0);
    free(r);
    return 0;
}
