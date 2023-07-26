#include <conio.h>
#include <stdio.h>
#include <stdlib.h>

void s_view();
void s_result();
void s_attendance();
void s_accounting();

int main() {
    int choice;
    printf("Student Management System Menu\n1: Attendance Section\n2: Accounting Section\n3: Result Section\n4: View Student Basic Information\n5: Exit\n");
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
            printf("Exiting the program.\n");
            exit(0);
            break;
        default:
            printf("Invalid Selection, please re-enter the choice.\n");
    }

    getch();
    return 0;
}

void s_attendance() {
    int choice_1;
    printf("1: Add Attendance\n2: View Attendance\n3: Delete Attendance\n4: Search Attendance\n5: Exit\n");
    printf("Selection: ");
    scanf("%d", &choice_1);
}
void s_accounting() {
    int choice_2;
    printf("1: Add Accouting\n2: View Accounting\n3: Delete Accouting\n4: Search Accouting\n5: Exit\n");
    printf("Selection: ");
    scanf("%d", &choice_2);
}
void s_result() {
    int choice_3;
    printf("1: Add Result\n2: View Result\n3: Delete Result\n4: Search Result\n5: Exit\n");
    printf("Selection: ");
    scanf("%d", &choice_3);
}
void s_view() {
  
}
