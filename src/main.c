#include "route-records.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {

    if (argc != 2) {
        printf("ERROR: Missing file name\n");
        return 1;
    }

    printf("Opening %s...\n", argv[1]);

    FILE* file = fopen(argv[1], "r");

    if (!file) {
        printf("ERROR: Could not open file\n");
        return 1;
    }

    RouteRecord* records = createRecords(file);
    int recordCount = fillRecords(records, file);

    printf("Unique routes operated by airlines: %d\n", recordCount);

    fclose(file);

    int choice;
    while (1) {

        printMenu();

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Try again.\n");
            while (getchar() != '\n'); // Clear invalid input
            continue;
        }

        if (choice == 5) break;

        char key1[4], key2[4];
        SearchType st;

        switch (choice) {
            case 1:
                st = ROUTE;
                printf("Enter origin: ");
                scanf("%3s", key1);
                printf("Enter destination: ");
                scanf("%3s", key2);
                searchRecords(records, recordCount, key1, key2, st);
                break;

            case 2:
                st = ORIGIN;
                printf("Enter origin: ");
                scanf("%3s", key1);
                searchRecords(records, recordCount, key1, NULL, st);
                break;

            case 3:
                st = DESTINATION;
                printf("Enter destination: ");
                scanf("%3s", key1);
                searchRecords(records, recordCount, key1, NULL, st);
                break;

            case 4:
                st = AIRLINE;
                printf("Enter airline: ");
                scanf("%2s", key1);
                searchRecords(records, recordCount, key1, NULL, st);
                break;

            default:
                printf("Invalid selection. Try again.\n");
        }
    }

    free(records);
    printf("Good-bye!\n");
    return 0;
}
