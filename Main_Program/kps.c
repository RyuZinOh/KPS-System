#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

struct student {
    char name[50];
    char address[50];
    char f_name[50];
    int age;
    char ph_no[50];
} f[100];

struct student_result {
    int math;
    int business;
    int account;
    int c;
    int electricity;
    int practical;
    char grade[2];
} g[100];

struct student_balance {
    int paid;
    int discount;
    int balance;
} h[100];

// Function prototypes
void attendance();
void accounting();
void result();
void view();
void showLoadingScreen();
void displayHeader();

// Kabish functions
int a_attendance();
int v_attendance();
int d_attendance();
int s_attendance();

// Pragyan functions
int a_result();
int v_result();
int d_result();
int s_result();

// Safal functions
int a_accounting();
int v_accounting();
int d_accounting();
int s_accounting();

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

//kabish functions
int a_attendance(){
    system("cls");
    FILE *hero;
    int n;
    printf("Enter the number of students: ");
    scanf("%d", &n);
    // Input information for each student
    for (int i = 0; i < n; i++) {
        printf("Student %d:\n", i + 1);
        printf("Name: ");
        scanf("%s", f[i].name);
        printf("Age: ");
        scanf("%d", &f[i].age);
        printf("Address: ");
        scanf("%s", f[i].address);
        printf("Father's Name: ");
        scanf("%s", f[i].f_name);
        printf("Phone Number: ");
        scanf("%s", f[i].ph_no);
    }

    // Write information to file
    hero = fopen("../Project_Data/attendance_cart.txt", "w");
    if (hero == NULL) {
        printf("File could not be opened.\n");
        return 1; // Exit with an error code
    }

    for (int i = 0; i < n; i++) {
        fprintf(hero, "%s %d %s %s %s\n", f[i].name, f[i].age, f[i].address, f[i].f_name, f[i].ph_no);
    }
    fclose(hero);
    return 0;
}

int v_attendance() {
    system("cls");
    FILE *hero;
    int n;
    hero = fopen("../Project_Data/attendance_cart.txt", "r"); // Corrected file path
    
    if (hero == NULL) {
        printf("File could not be opened.\n");
        return 1; // Exit with an error code
    }

    fscanf(hero, "%d", &n); // Read the number of students from the file

    for (int i = 0; i < n; i++) {
        fscanf(hero, "%s %d %s %s %s", f[i].name, &f[i].age, f[i].address, f[i].f_name, f[i].ph_no);
        printf("Student %d:\n", i + 1);
        printf("Name: %s\n", f[i].name);
        printf("Age: %d\n", f[i].age);
        printf("Address: %s\n", f[i].address);
        printf("Father's Name: %s\n", f[i].f_name);
        printf("Phone Number: %s\n", f[i].ph_no);
        printf("\n");
    }

    fclose(hero);
    return 0;
}


int d_attendance(){
    system("cls");
    printf("Delete Attendance (Under Construction)\n");
    return 0;
}

int s_attendance(){
    system("cls");
    printf("Search Attendance (Under Construction)\n");
    return 0;
}

//pragyan functions
int a_result() {
    system("cls");
    printf("Add Result (Under Construction)\n");
    return 0;
}

int v_result() {
    system("cls");
    printf("View Result (Under Construction)\n");
    return 0;
}

int d_result() {
    system("cls");
    printf("Delete Result (Under Construction)\n");
    return 0;
}

int s_result() {
    system("cls");
    printf("Search Result (Under Construction)\n");
    return 0;
}

//safal functions
int a_accounting() {
    system("cls");
    printf("Add Accounting (Under Construction)\n");
    return 0;
}

int v_accounting() {
    system("cls");
    printf("View Accounting (Under Construction)\n");
    return 0;
}

int d_accounting() {
    system("cls");
    printf("Delete Accounting (Under Construction)\n");
    return 0;
}

int s_accounting() {
    system("cls");
    printf("Search Accounting (Under Construction)\n");
    return 0;
}







