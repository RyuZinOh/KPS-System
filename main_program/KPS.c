#include <conio.h>
#include <stdio.h>
#include <stdlib.h>

void s_view();
void s_result();
void s_attandance();
void s_accounting();

int main() {
    int choice;
    printf("Student Management System Menu\n1: Attendance Section\n2: Accounting Section\n3: Result Section\n4: View Student Basic Information\n5: Exit\n");
    printf("Enter Choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            s_attandance();
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
