// wap to keep record, name, age, address and insert record into a file and display it into a secreen
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
void f(); 
void display();

struct safal{
   char name[10];
   char address[10];
   int roll, age;
}x[100];
int main() {
    f();
    //display
    printf("DISPLAYIMG :\n");
    display();
    getch();
    return 0;
}


//entering infile
void f(){
    FILE *xe;
    xe = fopen("C:\\Users\\Whysa\\OneDrive\\Desktop\\Happilli_project\\Bca2Sem\\super/marks.txt","w");
    if(xe){
     printf("ENter Name  Adress Age Roll \n");
        for (int i=0; i<=2 ;i++){
            scanf("%s%s%d%d",x[i].name, x[i].address, &x[i].roll, &x[i].age);
        }
     fprintf(xe,"NAME\tADDRESS\tAGE\tROLL\n");
        for (int i=0; i<=3 ;i++){
            fprintf(xe,"%s\t%s\t%d\t%d\n",x[i].name, x[i].address, x[i].age, x[i].roll);
        }
    fclose(xe);      

    }else{
        printf("hello eych");
    }
    
}

//shwinf file
void display() {
    FILE *headerFile;
    char filename[] = "C:\\Users\\Whysa\\OneDrive\\Desktop\\Happilli_project\\Bca2Sem\\super/marks.txt";
    char character;

    headerFile = fopen(filename, "r");
    if (headerFile == NULL) {
        printf("Couldn't find the file.\n");
        return;
    }

  
    while ((character = fgetc(headerFile)) != EOF) {
        putchar(character);
    }


    fclose(headerFile);
}
