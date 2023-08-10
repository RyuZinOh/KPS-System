#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

//main functions
void attendance();
void accounting();
void result();
void view();
void showLoadingScreen();
void displayHeader();

//kabish functions
void a_attendance();
void v_attendance();
void d_attendance();
void s_attendance(); 

//pragyan functions
void a_result();
void v_result();
void d_ressult();
void s_result();

//safal functions
void a_accoutning();
void v_accoutning();
void d_accoutning();
void s_accoutning();

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
                attendance();
                break;
            case 2:
                accounting();
                break;
            case 3:
                result();
                break;
            case 4:
                view();
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

void attendance() {
    system("cls");
    int choice_1;

    printf("1: Add Attendance\n2: View Attendance\n3: Delete Attendance\n4: Search Attendance\n5: Back to Main Menu\n");
    printf("Selection: ");
    scanf("%d", &choice_1);

    switch (choice_1) {
        case 1:
            a_attendance();
            break;
        case 2:
            v_attendance();
            break;
        case 3:
            d_attendance();
            break;
        case 4:
            s_attendance();
            break;
        case 5:
            printf("Going back to the Main Menu.....\n");
            break;
        default:
            printf("Invalid Selection, please re-enter the choice.\n");
    }
}

void accounting() {
    system("cls");
    int choice_2;

    printf("1: Add Accounting\n2: View Accounting\n3: Delete Accounting\n4: Search Accounting\n5: Back to Main Menu\n");
    printf("Selection: ");
    scanf("%d", &choice_2);

    switch (choice_2) {
        case 1:
          a_accounting();
            break;
        case 2:
            v_accounting();
            break;
        case 3:
            d_accounting();
            break;
        case 4:
            s_accounting();
            break;
        case 5:
            printf("Going back to the Main Menu.....\n");
            break;
        default:
            printf("Invalid Selection, please re-enter the choice.\n");
    }
}

void result() {
    system("cls");
    int choice_3;

    printf("1: Add Result\n2: View Result\n3: Delete Result\n4: Search Result\n5: Back to Main Menu\n");
    printf("Selection: ");
    scanf("%d", &choice_3);

    switch (choice_3) {
        case 1:
            a_result();
            break;
        case 2:
            v_result();
            break;
        case 3:
            d_result();
            break;
        case 4:
            s_result();
            break;
        case 5:
            printf("Going back to the Main Menu.....\n");
            break;
        default:
            printf("Invalid Selection, please re-enter the choice.\n");
    }
}

void view() {
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




//kabish section

//pragyan section 

//safql section

//overall section