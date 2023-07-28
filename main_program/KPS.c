#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h> 

void s_view();
void s_result();
void s_attendance();
void s_accounting();
void showLoadingScreen();

int main() {
    int choice;

    do {
        showLoadingScreen();
        system("cls");
        printf("Student Management System Menu\n1: Attendance Section\n2: Accounting Section\n3: Result Section\n4: View Student Basic Information\n5: Exit\n");
        printf("Enter Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                showLoadingScreen();
                s_attendance();
                break;
            case 2:
                showLoadingScreen();
                s_accounting();
                break;
            case 3:
                showLoadingScreen();
                s_result();
                break;
            case 4:
                showLoadingScreen();
                s_view();
                break;
            case 5:
                printf("Exiting the program.....\n");
                return 0;
                break;
            default:
                printf("Invalid Selection, please re-enter the choice.\n");
        }
    } while (choice != 5);

    getch();
    return 0;
}




void s_attendance() {
    system("cls");
    int choice_1;
    printf("1: Add Attendance\n2: View Attendance\n3: Delete Attendance\n4: Search Attendance\n5: Exit\n");
    printf("Selection: ");
    scanf("%d", &choice_1);

    switch (choice_1) {
        case 1:
            printf("this module is under Kabish\n");
            break;
        case 2:
            printf("this module is under Kabish\n");
            break;
        case 3:
            printf("this module is under Kabish\n");
            break;
        case 4:
            printf("this module is under Kabish\n");
            break;
        case 5:
            printf("Exiting Attendance Section.....\n");
            break;
        default:
            printf("Invalid Selection, please re-enter the choice.\n");
    }
     if (choice_1 != 5) {
        getch(); 
    } 
}

void s_accounting() {
    system("cls");
    int choice_2;
    printf("1: Add Accounting\n2: View Accounting\n3: Delete Accounting\n4: Search Accounting\n5: Exit\n");
    printf("Selection: ");
    scanf("%d", &choice_2);

    switch (choice_2) {
        case 1:
            printf("this moduel is under Safal\n");
            break;
        case 2:
            printf("this moduel is under Safal\n");
            break;
        case 3:
            printf("this moduel is under Safal\n");
            break;
        case 4:
            printf("this moduel is under Safal\n");
            break;
        case 5:
            printf("Exiting Accounting Section.....\n");
            return; // Exit from the function
        default:
            printf("Invalid Selection, please re-enter the choice.\n");
    }
    if (choice_2 != 5) {
        getch(); 
    } 
}

void s_result() {
    system("cls");
    int choice_3;
    printf("1: Add Result\n2: View Result\n3: Delete Result\n4: Search Result\n5: Exit\n");
    printf("Selection: ");
    scanf("%d", &choice_3);

    switch (choice_3) {
        case 1:
            printf("this module is under pragyan\n");
            break;
        case 2:
            printf("this module is under pragyan\n");
            break;
        case 3:
            printf("this module is under pragyan\n");
            break;
        case 4:
            printf("this module is under pragyan\n");
            break;
        case 5:
            printf("Exiting Result Section.....\n");
            return; // Exit from the function
        default:
            printf("Invalid Selection, please re-enter the choice.\n");
    }
    if (choice_3 != 5) {
        getch(); 
    } 
}

void s_view() {
    system("cls");
    printf("View Student Basic Information (Under Construction)\n");
}

void showLoadingScreen() {
    printf("Loading ");
    for (int i = 0; i < 3; i++) {
        Sleep(1000); // Wait for 1 second (Windows)
        printf(".");
    }
    printf("\n");
}
