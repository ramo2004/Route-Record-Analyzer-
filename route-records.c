//createRecords 
RouteRecord* createRecords(FILE* fileIn) {
    char buffer[MAX_LINE_LENGTH];
    int count = 0;
    // Count the number of records
    fgets(buffer, MAX_LINE_LENGTH, fileIn); // skip header
    while (fgets(buffer, MAX_LINE_LENGTH, fileIn) != NULL) {
        count++;
    }

    
    RouteRecord* records = malloc(count * sizeof(RouteRecord));
    if (records == NULL) { // Allocate memory
        printf("Error! Failed to allocate memory for RouteRecord\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < count; i++) {
        records[i].numPassengers[0] = 0; //1-6
        records[i].numPassengers[1] = 0;
        records[i].numPassengers[2] = 0;
        records[i].numPassengers[3] = 0;
        records[i].numPassengers[4] = 0;
        records[i].numPassengers[5] = 0;
    }
    rewind(fileIn);     // Rewind file pointer
    fgets(buffer, MAX_LINE_LENGTH, fileIn);
    return records;
}

//fillRecords 
int fillRecords(RouteRecord* r, FILE* fileIn) {
    char line[MAX_LINE_LENGTH];
    int numRecords = 0;
    while (fgets(line, MAX_LINE_LENGTH, fileIn)) {
        char* token = strtok(line, ",");
        if (!token) {
            continue;
        }
        char* origin = token;
        token = strtok(NULL, ",");
        char* destination = token;
        token = strtok(NULL, ",");
        char* airline = token;
        token = strtok(NULL, ",");
        int passengers[6];
        for (int i = 0; i < 6; i++) {
            passengers[i] = atoi(token);
            token = strtok(NULL, ",");
        }
        int index = findAirlineRoute(r, numRecords, origin, destination, airline, 0);
        if (index != -1) {
            // update passengerdata
            for (int i = 0; i < 6; i++) {
                r[index].passengers[i] += passengers[i];
            }
        } else {
            // add new record if record doesnt exist
            if (numRecords < MAX_RECORDS) {
                strcpy(r[numRecords].origin, origin);
                strcpy(r[numRecords].destination, destination);
                strcpy(r[numRecords].airline, airline);
                for (int i = 0; i < 6; i++) {
                    r[numRecords].passengers[i] = passengers[i];
                }
                numRecords++;
            }
        }
    }
    return numRecords;
}

// findAirlineRoute 
int findAirlineRoute(RouteRecord* r, int length, const char* origin, const char* destination, const char* airline, int curIdx) {
    if (curIdx >= length) {  // base case
        return -1;
    }
    
    if (strcmp(r[curIdx].origin, origin) == 0 &&
        strcmp(r[curIdx].destination, destination) == 0 &&
        strcmp(r[curIdx].airline, airline) == 0) {
        return curIdx; // match
    }
    
    // recursive case
    return findAirlineRoute(r, length, origin, destination, airline, curIdx + 1);
}
// searchRecords // 
void searchRecords(RouteRecord* r, int length, const char* key1, const char* key2, SearchType st) {
    int i;
    int found = 0; //if any matches were found
    int totalPassengers = 0; // total number of passengers
    int totalPassengersByMonth[6] = {0}; // total number of passengers by month

    printf("\nResults:\n");

    for (i = 0; i < length; i++) {
        int match = 0; // if the current record matches the search

        if (st == ROUTE && strcmp(key1, r[i].origin) == 0 && strcmp(key2, r[i].destination) == 0) {
            match = 1;
        } else if (st == ORIGIN && strcmp(key1, r[i].origin) == 0) {
            match = 1;
        } else if (st == DESTINATION && strcmp(key1, r[i].destination) == 0) {
            match = 1;
        } else if (st == AIRLINE && strcmp(key1, r[i].airline) == 0) {
            match = 1;
        }

        if (match) {
            found = 1; //match was found
            printf("%s %s (%s) %d passengers\n", r[i].origin, r[i].destination, r[i].airline, r[i].totalPassengers);
            totalPassengers += r[i].totalPassengers;

            // add passengers by month
            for (int j = 0; j < 6; j++) {
                totalPassengersByMonth[j] += r[i].passengers[j];
            }
        }
    }

    if (found) {
        printf("\n Total passengers across all matching records: %d\n", totalPassengers);
        printf("Total passengers by month across all matching records:\n");
        for (int i = 0; i < 6; i++) {
            printf("Month %d: %d passengers\n", i+1, totalPassengersByMonth[i]);
        }
        printf("Average passengers per month: %.2f\n", (double)totalPassengers / found / 6);
    } else {
        printf("No records found.\n");
    }
}

//void printMenu // 

void printMenu() {
    printf("\n\n######### Airline Route Records Database MENU #########\n");
    printf("1. Search by Route\n");
    printf("2. Search by Origin Airport\n");
    printf("3. Search by Destination Airport\n");
    printf("4. Search by Airline\n");
    printf("5. Quit\n");
    printf("Enter your selection: ");
}