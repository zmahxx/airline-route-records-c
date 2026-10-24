#include "route-records.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h> // For toupper

#define MAX_RECORDS 100000

RouteRecord* createRecords(FILE* fileIn) {

    int count = 0;
    char buffer[1024];

    while (fgets(buffer, sizeof(buffer), fileIn)) {
        count++;
    }

    rewind(fileIn);

    RouteRecord* records = (RouteRecord*)malloc(count * sizeof(RouteRecord));

    if (!records) {
        printf("ERROR: Memory allocation failed.\n");
        exit(1);
    }

    return records;
}

int fillRecords(RouteRecord* records, FILE* fileIn) {
    char buffer[2048];
    int index = 0;

    // Skip header row
    fgets(buffer, sizeof(buffer), fileIn);

    while (fgets(buffer, sizeof(buffer), fileIn)) {
        char origin[4], destination[4], airline[4];
        int month, passengers;

        // Clean and parse input
        buffer[strcspn(buffer, "\r\n")] = '\0';
        if (sscanf(buffer, "%d,%[^,],%[^,],%[^,],%d", &month, origin, destination, airline, &passengers) != 5) {
            printf("Skipping invalid record: %s\n", buffer);
            continue;
        }

        // Skip invalid airline codes
        if (strlen(airline) < 2 || strlen(airline) > 3) {
            printf("Skipping record with invalid airline code: %s\n", buffer);
            continue;
        }

        // Check if record exists
        int found = findAirlineRoute(records, index, origin, destination, airline, 0);
        if (found == -1) {
            // Add new record
            strcpy(records[index].origin, origin);
            strcpy(records[index].destination, destination);
            strcpy(records[index].airline, airline);
            memset(records[index].passengers, 0, sizeof(records[index].passengers));
            records[index].passengers[month - 1] = passengers;
            index++;
        } else {
            // Update existing record
            records[found].passengers[month - 1] += passengers;
        }
    }

    return index;
}



int findAirlineRoute(RouteRecord* records, int length, const char* origin, const char* destination, const char* airline, int curIdx) {

    if (curIdx >= length) return -1;

    if (strcmp(records[curIdx].origin, origin) == 0 &&
        strcmp(records[curIdx].destination, destination) == 0 &&
        strcmp(records[curIdx].airline, airline) == 0) {
        return curIdx;
    }

    return findAirlineRoute(records, length, origin, destination, airline, curIdx + 1);
}

void searchRecords(RouteRecord* records, int length, const char* key1, const char* key2, SearchType st) {
    int totalPassengers = 0, monthlyTotals[6] = {0}, matchCount = 0;
    char cleanKey1[4], cleanKey2[4];

    // Normalize and clean key1
    strncpy(cleanKey1, key1, 3);
    cleanKey1[3] = '\0';
    for (int i = 0; i < 3; i++) cleanKey1[i] = toupper(cleanKey1[i]);

    // Normalize and clean key2 if present
    if (key2) {
        strncpy(cleanKey2, key2, 3);
        cleanKey2[3] = '\0';
        for (int i = 0; i < 3; i++) cleanKey2[i] = toupper(cleanKey2[i]);
    }

    for (int i = 0; i < length; i++) {
        int match = 0;

        switch (st) {
            case ROUTE:
                if (strcmp(records[i].origin, cleanKey1) == 0 && strcmp(records[i].destination, cleanKey2) == 0) {
                    match = 1;
                }
            break;
            case ORIGIN:
                if (strcmp(records[i].origin, cleanKey1) == 0) {
                    match = 1;
                }
            break;
            case DESTINATION:
                if (strcmp(records[i].destination, cleanKey1) == 0) {
                    match = 1;
                }
            break;
            case AIRLINE:
                if (strcmp(records[i].airline, cleanKey1) == 0) {
                    match = 1;
                }
            break;
        }

        if (match) {
            matchCount++;
            for (int j = 0; j < 6; j++) {
                monthlyTotals[j] += records[i].passengers[j];
                totalPassengers += records[i].passengers[j];
            }
        }
    }

    // Display results
    printf("\n%d matches were found.\n\nStatistics\n", matchCount);
    printf("Total Passengers: %d\n", totalPassengers);
    for (int i = 0; i < 6; i++) {
        printf("Total Passengers in Month %d: %d\n", i + 1, monthlyTotals[i]);
    }
    printf("Average Passengers per Month: %d\n", matchCount > 0 ? totalPassengers / matchCount : 0);
}


void printMenu() {
    printf("\n\n######### Airline Route Records Database MENU #########\n");
    printf("1. Search by Route\n");
    printf("2. Search by Origin Airport\n");
    printf("3. Search by Destination Airport\n");
    printf("4. Search by Airline\n");
    printf("5. Quit\n");
    printf("Enter your selection: ");
}
