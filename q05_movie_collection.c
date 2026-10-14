/* Q5: Movie Collection - max search + average */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Movie {
    int id;
    char title[60];
    char director[50];
    float rating;
    int year;
};

struct Movie *m = NULL;
int n = 0;

void addMovie(void) {
    struct Movie *tmp = realloc(m, (n + 1) * sizeof(struct Movie));
    if (!tmp) { printf("Memory error!\n"); return; }
    m = tmp;
    printf("ID: ");       scanf("%d", &m[n].id);
    printf("Title: ");    scanf(" %59[^\n]", m[n].title);
    printf("Director: "); scanf(" %49[^\n]", m[n].director);
    printf("Rating: ");   scanf("%f", &m[n].rating);
    printf("Year: ");     scanf("%d", &m[n].year);
    n++;
    printf("Movie added.\n");
}

void printOne(struct Movie x) {
    printf("%-4d %-25s %-20s %5.1f %5d\n", x.id, x.title, x.director, x.rating, x.year);
}

void printByDirector(void) {
    char d[50]; int i, found = 0;
    printf("Director: "); scanf(" %49[^\n]", d);
    for (i = 0; i < n; i++)
        if (strcmp(m[i].director, d) == 0) { printOne(m[i]); found = 1; }
    if (!found) printf("No movies by %s.\n", d);
}

void printByYear(void) {
    int y, i, found = 0;
    printf("Year: "); scanf("%d", &y);
    for (i = 0; i < n; i++)
        if (m[i].year == y) { printOne(m[i]); found = 1; }
    if (!found) printf("No movies of %d.\n", y);
}

void bestRated(void) {
    int i, best = 0;
    if (n == 0) { printf("No movies.\n"); return; }
    for (i = 1; i < n; i++)
        if (m[i].rating > m[best].rating) best = i;
    printf("Best rated movie:\n");
    printOne(m[best]);
}

void averageRating(void) {
    double sum = 0; int i;
    if (n == 0) { printf("No movies.\n"); return; }
    for (i = 0; i < n; i++) sum += m[i].rating;
    printf("Average rating = %.2f\n", sum / n);
}

void saveToFile(void) {
    FILE *fp = fopen("movies.db", "wb");
    if (!fp) { printf("File error!\n"); return; }
    fwrite(m, sizeof(struct Movie), n, fp);
    fclose(fp);
    printf("%d record(s) saved to movies.db\n", n);
}

int main(void) {
    int ch;
    do {
        printf("\n--- MOVIE COLLECTION ---\n");
        printf("1.Add 2.By director 3.By year 4.Best rated 5.Average rating 0.Exit\n");
        printf("Choice: "); scanf("%d", &ch);
        switch (ch) {
            case 1: addMovie(); break;
            case 2: printByDirector(); break;
            case 3: printByYear(); break;
            case 4: bestRated(); break;
            case 5: averageRating(); break;
            case 0: saveToFile(); break;
            default: printf("Invalid choice!\n");
        }
    } while (ch != 0);
    free(m);
    return 0;
}
