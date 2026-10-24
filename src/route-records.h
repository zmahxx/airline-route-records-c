#ifndef ROUTE_RECORDS_H
#define ROUTE_RECORDS_H

#include <stdio.h>

typedef enum SearchType { ROUTE, ORIGIN, DESTINATION, AIRLINE } SearchType;

typedef struct {
    char origin[4];
    char destination[4];
    char airline[4];  // Airline code (2 or 3 characters)
    int passengers[6]; // Passenger count for each month (Jan to Jun)
} RouteRecord;

// Function prototypes
RouteRecord* createRecords(FILE* fileIn);
int fillRecords(RouteRecord* records, FILE* fileIn);
int findAirlineRoute(RouteRecord* records, int length, const char* origin, const char* destination, const char* airline, int curIdx);
void searchRecords(RouteRecord* records, int length, const char* key1, const char* key2, SearchType st);
void printMenu();

#endif // ROUTE_RECORDS_H
