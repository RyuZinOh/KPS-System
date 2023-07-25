#include <conio.h>
#include <stdio.h>
void s_view(), s_result(), s_attandance(), s_accounting(), s_result();
 
int main() {
    int choice;
    printf("Student Management System Menu\n1: Attandance Section\n2: Accounting Section\n3: Result Section\n4: View Student Basic Information\n5: Exit");
    printf("Enter Choice :");
    scanf("%d", &choice);
    switch(choice){
        case 1: s_attandance();
                break;
        case 2: s_accounting();
                break;
        case 3: s_result();
                break;
        case 4: exit();
                break;
        case 5: printf("Invalid Selection, Re-enter the choice");
    } 

    
    getch();
    return 0;
}
