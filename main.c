#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "route-records.h"

int main(int argc, char *argv[]) {
    FILE *file;
    RouteRecord *records = NULL;
    int num_records = 0;
    

    if (argc != 2) {
        printf("ERROR: Missing file name\n");
        return 1;
    }
    
    printf("Opening %s...\n", argv[1]); // attempting to open file
    file = fopen(argv[1], "r");
    
    /* 4. Check to see if the file opens. If it does not open, print out ERROR: Could not open file and end the program. */
    if (file == NULL) {
        printf("ERROR: Could not open file\n");
        return 1;
    }

    num_records = createRecords(file);
    if (num_records == 0) {
        printf("ERROR: No records found in file\n");
        return 1;
    }
    records = (RouteRecord*) malloc(num_records * sizeof(RouteRecord));
    if (records == NULL) {
        printf("ERROR: Memory allocation failed\n");
        return 1;
    }
    rewind(file);
    
    int num_unique_routes = fillRecords(file, records, num_records);
    printf("Unique routes operated by airlines: %d\n", num_unique_routes);
    
  // close the file
    fclose(file);
    
 // infinite loop
    while (1) {

        printMenu();
        
  // ask user to input value for the menu
        int choice = 0;
        printf("Enter a choice: ");
        scanf("%d", &choice);
        
     // non-integer value is entered //
        if (choice == 0 && !isdigit(choice)) {
            printf("Invalid choice. Enter a number from the menu.\n");
            continue;
        }
        
        /* 6.4 Create a switch/case statement to handle all the menu options */
        switch (choice) {
            /* 6.4.1 Each option requires the user to enter a search key */
            case 1: {
                char airline[3];
                printf("Enter an airline code (two letters): ");
                scanf("%s", airline);
                printRoutesByAirline(records, num_records, airline);
                break;
           
            case 2: {
                char origin[4];
                printf("Enter an origin airport code (three letters): ");
                scanf("%s", origin);
                printRoutesByOrigin(records, num_records, origin);
                break;
                }
        case 3: {
                char destination[4];
                printf("Enter a destination airport code (three letters): ");
                scanf("%s", destination);
                printRoutesByDestination(records, num_records, destination);
                break;
                }
        case 4: {
                char airline[3];
                char origin[4];
                char destination[4];
                printf("Enter an airline code (two letters): ");
                scanf("%s", airline);
                printf("Enter an origin airport code (three letters): ");
                scanf("%s", origin);
                printf("Enter a destination airport code (three letters): ");
                scanf("%s", destination);
                printRouteDetails(records, num_records, airline, origin, destination);
                break;
                }
        case 5: {
                    printAllRoutes(records, num_records);
                    break;
                    }
        case 6: {
                printf("Exiting...\n");
                // free memory used by the RouteRecords array and exit the program//
                free(records);
                exit(0);
                }
        default:
        printf("Invalid choice. Enter a number from the menu.\n");
        }
        }