#include <conio.h>
#include <stdio.h>
 
int main() {
    int choice;
    printf("Student Management System Menu\n1: Attandance Section\n2: Accounting Section\n3: Result Section\n4: Exit");
    printf("Enter Choice :");
    scanf("%d", &choice);
    switch(choice){
        case 1: goto Attandance;
        case 2: goto Accouunting;
        case 3: goto Result;
        case 4: exit();
        case 5: printf("Invalid Selection, Re-enter the choice");
    } 

    
    getch();
    return 0;
}
