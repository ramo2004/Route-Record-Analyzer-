#ifndef ROUTE_RECORDS_H
#define ROUTE_RECORDS_H

#include <stdio.h>
#include <stdlib.h>

typedef enum SearchType { ROUTE, ORIGIN, DESTINATION, AIRLINE } SearchType;

typedef struct RouteRecord {
    char origin[4]; // origin code
    char destination[4]; // dest airport code
    char airline[3]; // code
    int passengers[6]; // six months worth of data for each route
} RouteRecord;

RouteRecord* createRecords(FILE* fileIn);
// header guards and protypes for the functions 
int fillRecords(RouteRecord* r, FILE* fileIn);

int findAirlineRoute(RouteRecord* r, int length, const char* origin, const char* destination, const char* airline, int curIdx);

void searchRecords(RouteRecord* r, int length, const char* key1, const char* key2, SearchType st);

void printMenu();

#endif