#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int window_year(int yy, int pivot) {
    return (yy >= pivot ? 1900 : 2000) + yy;
}

int read_number(const char *prompt, int min, int max) {
    char line[128];
    char *end;
    long value;

    while (1) {
        printf("%s", prompt);
        fflush(stdout);
        if (!fgets(line, sizeof line, stdin)) {
            printf("\nInput ended.\n");
            exit(0);
        }
        if (!strchr(line, '\n')) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {}
            printf("Invalid input. Enter %d..%d.\n", min, max);
            continue;
        }
        value = strtol(line, &end, 10);
        if (end == line) {
            printf("Invalid input. Enter %d..%d.\n", min, max);
            continue;
        }
        while (*end == ' ' || *end == '\t') end++;
        if (*end != '\n' && *end != '\0') {
            printf("Invalid input. Enter %d..%d.\n", min, max);
            continue;
        }
        if (value < min || value > max) {
            printf("Out of range. Enter %d..%d.\n", min, max);
            continue;
        }
        return (int)value;
    }
}

void demo_age(int pivot) {
    int birth, today;
    printf("\n[1] AGE CALCULATION\n");
    birth = read_number("Birth year: ", 0, 99);
    today = read_number("Current year: ", 0, 99);
    printf("Old method: %02d - %02d = %d\n",
        window_year(today, 0), window_year(birth, 0),
        window_year(today, 0) - window_year(birth, 0));
    printf("Windowing : %d - %d = %d\n",
        window_year(today, pivot), window_year(birth, pivot),
        window_year(today, pivot) - window_year(birth, pivot));
}

void demo_sort(int pivot) {
    int first, second;
    printf("\n[2] YEAR COMPARISON\n");
    first = read_number("First year: ", 0, 99);
    second = read_number("Second year: ", 0, 99);
    printf("Old method: %02d < %02d ? %s\n",
           window_year(first, 0), window_year(second, 0),
           window_year(first, 0) < window_year(second, 0) ? "TRUE" : "FALSE");
    printf("Windowing : %d < %d ? %s\n",
           window_year(first, pivot), window_year(second, pivot),
           window_year(first, pivot) < window_year(second, pivot) ? "TRUE" : "FALSE");
}

void demo_window(int pivot) {
    int yy;
    printf("\n[3] WINDOWING (pivot = %02d)\n", pivot);
    yy = read_number("Year: ", 0, 99);
    printf("YY=%02d -> %d\n", yy, window_year(yy, pivot));
    if (pivot == 0) {
        printf("Rule: all YY -> 1900..1999\n");
    } else {
        printf("Rule: %02d..99 -> 19xx, 00..%02d -> 20xx\n",
               pivot, pivot - 1);
    }
}

int main(void) {
    int pivot, choice;
    printf("=== Y2K DEMO ===\n");
    pivot = read_number("Enter pivot year (0..99): ", 0, 99);

    while (1) {
        printf("\n========== MENU (pivot = %02d) ==========\n", pivot);
        printf("1. Age calculation\n");
        printf("2. Year comparison\n");
        printf("3. Windowing conversion\n");
        printf("4. Run all 3 demos\n");
        printf("5. Change pivot\n");
        printf("0. Exit\n");
        choice = read_number("Choose (0..5): ", 0, 5);
        switch (choice) {
            case 1: demo_age(pivot); break;
            case 2: demo_sort(pivot); break;
            case 3: demo_window(pivot); break;
            case 4:
                demo_age(pivot);
                demo_sort(pivot);
                demo_window(pivot);
                break;
            case 5:
                pivot = read_number("New pivot year (0..99): ", 0, 99);
                break;
            case 0:
                return 0;
        }
    }
}
