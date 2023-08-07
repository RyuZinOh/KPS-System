#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void s_attendance();
void s_accounting();
void s_result();
void s_view();
void showLoadingScreen();
void displayHeader();
void Accounting_add();

int main() {
    int choice;
    showLoadingScreen();
    do {
        system("cls");
        displayHeader();

        printf("\nStudent Management System Menu\n1: Attendance Section\n2: Accounting Section\n3: Result Section\n4: View Student Basic Information\n5: Exit\n");
        printf("Enter Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                s_attendance();
                break;
            case 2:
                s_accounting();
                break;
            case 3:
                s_result();
                break;
            case 4:
                s_view();
                break;
            case 5:
                printf("Exiting the program.....\n");
                break;
            default:
                printf("Invalid Selection, please re-enter the choice.\n");
        }

        if (choice != 5) {
            printf("Press any key to continue...\n");
            getch(); // Wait for user input before clearing the screen
        }

    } while (choice != 5);

    return 0;
}

void s_attendance() {
    system("cls");
    int choice_1;

    printf("1: Add Attendance\n2: View Attendance\n3: Delete Attendance\n4: Search Attendance\n5: Back to Main Menu\n");
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
            printf("Going back to the Main Menu.....\n");
            break;
        default:
            printf("Invalid Selection, please re-enter the choice.\n");
    }
}

void s_accounting() {
    system("cls");
    int choice_2;

    printf("1: Add Accounting\n2: View Accounting\n3: Delete Accounting\n4: Search Accounting\n5: Back to Main Menu\n");
    printf("Selection: ");
    scanf("%d", &choice_2);

    switch (choice_2) {
        case 1:
          Accounting_add();
            break;
        case 2:
            printf("this module is under Safal\n");
            break;
        case 3:
            printf("this module is under Safal\n");
            break;
        case 4:
            printf("this module is under Safal\n");
            break;
        case 5:
            printf("Going back to the Main Menu.....\n");
            break;
        default:
            printf("Invalid Selection, please re-enter the choice.\n");
    }
}

void s_result() {
    system("cls");
    int choice_3;

    printf("1: Add Result\n2: View Result\n3: Delete Result\n4: Search Result\n5: Back to Main Menu\n");
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
            printf("Going back to the Main Menu.....\n");
            break;
        default:
            printf("Invalid Selection, please re-enter the choice.\n");
    }
}

void s_view() {
    system("cls");
    printf("View Student Basic Information (Under Construction)\n");
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

void showLoadingScreen() {
    printf("Loading ");
    for (int i = 0; i < 3; i++) {
        Sleep(1000); // Wait for 1 second (Windows)
        printf(".");
    }
    printf("\n");
}

//Accounting zone By safal 
void Accounting_add(){
    FILE *account_;
    char filename_a[] = "../Project_Data/accounts.txt";
    char a_name[100];
    account_ = fopen(filename_a, "w");
    if(account_){
    printf("Enter The Student Name to Add Balance : ");
    scanf("%s",a_name);
    fprintf(account_,"%s", a_name);
    fclose(account_);   
    }
    
}