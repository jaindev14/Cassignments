/* Q8: Library Issue System - issued flag + member_id */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Book {
    int book_id;
    char title[60];
    char author[50];
    int issued;        /* 0 = available, 1 = issued */
    int member_id;     /* who has it (0 if nobody) */
};

struct Book *b = NULL;
int n = 0;

void addBook(void) {
    struct Book *tmp = realloc(b, (n + 1) * sizeof(struct Book));
    if (!tmp) { printf("Memory error!\n"); return; }
    b = tmp;
    printf("Book ID: ");  scanf("%d", &b[n].book_id);
    printf("Title: ");    scanf(" %59[^\n]", b[n].title);
    printf("Author: ");   scanf(" %49[^\n]", b[n].author);
    b[n].issued = 0;
    b[n].member_id = 0;
    n++;
    printf("Book added.\n");
}

void issueBook(void) {
    int id, mid, i;
    printf("Book ID to issue: "); scanf("%d", &id);
    for (i = 0; i < n; i++) {
        if (b[i].book_id == id) {
            if (b[i].issued) {
                printf("Already issued to member %d.\n", b[i].member_id);
                return;
            }
            printf("Member ID: "); scanf("%d", &mid);
            b[i].issued = 1;
            b[i].member_id = mid;
            printf("Book issued to member %d.\n", mid);
            return;
        }
    }
    printf("Book not found.\n");
}

void returnBook(void) {
    int id, i;
    printf("Book ID to return: "); scanf("%d", &id);
    for (i = 0; i < n; i++) {
        if (b[i].book_id == id) {
            if (!b[i].issued) { printf("This book was not issued.\n"); return; }
            b[i].issued = 0;
            b[i].member_id = 0;
            printf("Book returned.\n");
            return;
        }
    }
    printf("Book not found.\n");
}

void listIssued(void) {
    int i, found = 0;
    for (i = 0; i < n; i++) {
        if (b[i].issued) {
            if (!found) printf("%-5s %-25s %-15s %s\n", "ID", "Title", "Author", "Member");
            printf("%-5d %-25s %-15s %d\n", b[i].book_id, b[i].title, b[i].author, b[i].member_id);
            found = 1;
        }
    }
    if (!found) printf("No books are issued.\n");
}

int main(void) {
    int ch;
    do {
        printf("\n--- LIBRARY ISSUE SYSTEM ---\n");
        printf("1.Add book 2.Issue 3.Return 4.List issued 0.Exit\n");
        printf("Choice: "); scanf("%d", &ch);
        switch (ch) {
            case 1: addBook(); break;
            case 2: issueBook(); break;
            case 3: returnBook(); break;
            case 4: listIssued(); break;
            case 0: break;
            default: printf("Invalid choice!\n");
        }
    } while (ch != 0);
    free(b);
    return 0;
}
