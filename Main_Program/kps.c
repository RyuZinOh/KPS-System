#include <stdio.h>
#include <stdlib.h>

// Data structures
struct Student {
    char name[50];
    char address[50];
    char f_name[50];
    int age;
    char ph_no[50];
};

struct StudentResult {
    int math;
    int business;
    int account;
    int c;
    int electricity;
    int practical;
    char grade[3]; // Make space for null terminator
};

struct StudentBalance {
    int paid;
    int discount;
    int balance;
};

// Function prototypes
void displayHeader();
void menu();

// Individual section functions
void manageAttendance();
void manageAccounting();
void manageResults();
void viewBasicInfo();

// Functions for each action within sections
void addAttendance();
void viewAttendance();
void deleteAttendance();
void searchAttendance();

void addAccounting();
void viewAccounting();
void deleteAccounting();
void searchAccounting();

void addResult();
void viewResult();
void deleteResult();
void searchResult();

int main() {
    displayHeader();
    menu();
    return 0;
}

void displayHeader() {
    FILE *headerFile;
    char filename[] = "../Assets/logo.txt";
    char character;

    headerFile = fopen(filename, "r");
    if (headerFile == NULL) {
        printf("Couldn't find the related ASCII heading.\n");
        return;
    }

    printf("\033[31m"); // Set text color to red
    while ((character = fgetc(headerFile)) != EOF) {
        putchar(character);
    }
    printf("\033[0m"); // Reset text color

    fclose(headerFile);
}

void menu() {
    int choice;
    do {
        printf("\nStudent Management System Menu\n"
               "1: Attendance Section\n"
               "2: Accounting Section\n"
               "3: Result Section\n"
               "4: View Student Basic Information\n"
               "5: Exit\n"
               "Enter Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                system("cls");
                manageAttendance();
                break;
            case 2:
                system("cls");
                manageAccounting();
                break;
            case 3:
                system("cls");
                manageResults();
                break;
            case 4:
                system("cls");
                viewBasicInfo();
                break;
            case 5:
                system("cls");
                printf("Exiting the program.....\n");
                break;
            default:
                system("cls");
                printf("Invalid Selection, please re-enter the choice.\n");
        }

        if (choice != 5) {
            printf("Press Enter to continue...\n");
            getchar(); // Consume newline
            getchar(); // Wait for user input before clearing the screen
            system("cls");
        }

    } while (choice != 5);
}

void manageAttendance() {
    int choice;
    do {
        printf("Attendance Section\n"
               "1: Add Attendance\n"
               "2: View Attendance\n"
               "3: Delete Attendance\n"
               "4: Search Attendance\n"
               "5: Back to Main Menu\n"
               "Selection: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                system("cls");
                addAttendance();
                break;
            case 2:
                system("cls");
                viewAttendance();
                break;
            case 3:
                system("cls");
                deleteAttendance();
                break;
            case 4:
                system("cls");
                searchAttendance();
                break;
            case 5:
                system("cls");
                printf("Going back to the Main Menu.....\n");
                break;
            default:
                system("cls");
                printf("Invalid Selection, please re-enter the choice.\n");
        }

        if (choice != 5) {
            printf("Press Enter to continue...\n");
            getchar(); // Consume newline
            getchar(); // Wait for user input before clearing the screen
            system("cls");
        }

    } while (choice != 5);
}

void addAttendance() {
    printf("Add attendance (under construction)\n");
}

void viewAttendance() {
    printf("View attendance (under construction)\n");
}

void deleteAttendance() {
    printf("Delete Attendance (Under Construction)\n");
}

void searchAttendance() {
    printf("Search Attendance (Under Construction)\n");
}

void manageAccounting() {
    int choice;
    do {
        printf("Accounting Section\n"
               "1: Add Accounting\n"
               "2: View Accounting\n"
               "3: Delete Accounting\n"
               "4: Search Accounting\n"
               "5: Back to Main Menu\n"
               "Selection: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                system("cls");
                addAccounting();
                break;
            case 2:
                system("cls");
                viewAccounting();
                break;
            case 3:
                system("cls");
                deleteAccounting();
                break;
            case 4:
                system("cls");
                searchAccounting();
                break;
            case 5:
                system("cls");
                printf("Going back to the Main Menu.....\n");
                break;
            default:
                system("cls");
                printf("Invalid Selection, please re-enter the choice.\n");
        }

        if (choice != 5) {
            printf("Press Enter to continue...\n");
            getchar(); // Consume newline
            getchar(); // Wait for user input before clearing the screen
            system("cls");
        }

    } while (choice != 5);
}

void addAccounting() {
    printf("Add Accounting (Under Construction)\n");
}

void viewAccounting() {
    printf("View Accounting (Under Construction)\n");
}

void deleteAccounting() {
    printf("Delete Accounting (Under Construction)\n");
}

void searchAccounting() {
    printf("Search Accounting (Under Construction)\n");
}

void manageResults() {
    int choice;
    do {
        printf("Result Section\n"
               "1: Add Result\n"
               "2: View Result\n"
               "3: Delete Result\n"
               "4: Search Result\n"
               "5: Back to Main Menu\n"
               "Selection: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                system("cls");
                addResult();
                break;
            case 2:
                system("cls");
                viewResult();
                break;
            case 3:
                system("cls");
                deleteResult();
                break;
            case 4:
                system("cls");
                searchResult();
                break;
            case 5:
                system("cls");
                printf("Going back to the Main Menu.....\n");
                break;
            default:
                system("cls");
                printf("Invalid Selection, please re-enter the choice.\n");
        }

        if (choice != 5) {
            printf("Press Enter to continue...\n");
            getchar(); // Consume newline
            getchar(); // Wait for user input before clearing the screen
            system("cls");
        }

    } while (choice != 5);
}

void addResult() {
    printf("Add Result (Under Construction)\n");
}

void viewResult() {
    printf("View Result (Under Construction)\n");
}

void deleteResult() {
    printf("Delete Result (Under Construction)\n");
}

void searchResult() {
    printf("Search Result (Under Construction)\n");
}

void viewBasicInfo() {
    printf("View Student Basic Information (Under Construction)\n");
}
