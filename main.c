#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#ifdef _WIN32
#define CLEAR_SCREEN "cls"
#else
#define CLEAR_SCREEN "clear"
#endif

#define MAX_STUDENTS 100

struct Student {
    char name[50];
    char fatherName[50];
    char phoneNumber[15];
    char faculty[50];
    int id;
};

struct Student students[MAX_STUDENTS];
int studentCount = 0;

// Function to check if a student ID already exists in the file
bool isStudentIdUniqueInFile(int id) {
    FILE *file = fopen("Storage/student.txt", "r");
    if (file != NULL) {
        struct Student student;

        while (fscanf(file, "%49s %49s %14s %49s %d\n", student.name, student.fatherName, student.phoneNumber, student.faculty, &student.id) == 5) {
            if (student.id == id) {
                fclose(file);
                return false; // ID already exists in the file
            }
        }

        fclose(file);
    }
    return true; // ID is unique in the file
}

// Function to add a student
void addStudent() {
    if (studentCount < MAX_STUDENTS) {
        struct Student newStudent;

        printf("\033[1;32m"); // Set text color to green
        printf("Add Student\n");
        printf("\033[0m"); // Reset text color

        printf("Name: ");
        scanf("%s", newStudent.name);

        printf("Father's Name: ");
        scanf("%s", newStudent.fatherName);

        printf("Phone Number: ");
        scanf("%s", newStudent.phoneNumber);

        printf("Faculty: ");
        scanf("%s", newStudent.faculty);

        // Check if the student ID is unique in the file
        do {
            printf("Student ID: ");
            scanf("%d", &newStudent.id);

            if (!isStudentIdUniqueInFile(newStudent.id)) {
                printf("\033[1;31m"); // Set text color to red
                printf("Error: Student ID already exists. Please enter a unique ID.\n");
                printf("\033[0m"); // Reset text color
            }
        } while (!isStudentIdUniqueInFile(newStudent.id));

        students[studentCount++] = newStudent;

        // Save to Storage/student.txt
        FILE *file = fopen("Storage/student.txt", "a");
        if (file != NULL) {
            fprintf(file, "%s %s %s %s %d\n", newStudent.name, newStudent.fatherName, newStudent.phoneNumber, newStudent.faculty, newStudent.id);
            fclose(file);
        } else {
            printf("Error: Unable to open file for writing.\n");
        }

        printf("\033[1;32m"); // Set text color to green
        printf("Student added successfully.\n");
        printf("\033[0m"); // Reset text color
    } else {
        printf("Error: Maximum number of students reached.\n");
    }
}

// Function to view a student by name
void viewStudentByName() {
    char searchName[50];
    printf("Enter student name to search: ");
    
    // Read the full line, including spaces, and store it in searchName
    scanf(" %49[^\n]", searchName);

    bool found = false;  // Flag to indicate if the student was found

    // Open the student.txt file for reading
    FILE *file = fopen("Storage/student.txt", "r");
    if (file != NULL) {
        struct Student student;  // Temporary variable to store student data while reading

        // Read data from the file and search for the student by name
        while (fscanf(file, "%49s %49s %14s %49s %d\n", student.name, student.fatherName, student.phoneNumber, student.faculty, &student.id) == 5) {
            if (strcmp(student.name, searchName) == 0) {
                printf("\033[1;32m"); // Set text color to green
                printf("Student Details\n");
                printf("\033[0m"); // Reset text color

                printf("Name: %s\n", student.name);
                printf("Father's Name: %s\n", student.fatherName);
                printf("Phone Number: %s\n", student.phoneNumber);
                printf("Faculty: %s\n", student.faculty);
                printf("ID: %d\n", student.id);

                found = true;  // Student found
                break;
            }
        }

        fclose(file);  // Close the file
    } else {
        printf("Error: Unable to open file for reading.\n");
    }

    if (!found) {
        printf("\033[1;31m"); // Set text color to red
        printf("Student with name '%s' not found.\n", searchName);
        printf("\033[0m"); // Reset text color
    }

    // Wait for the user to press Enter before returning
    printf("Press Enter to continue...");
    while (getchar() != '\n');  // Clear input buffer
    getchar();  // Wait for Enter
}

// Function to delete a student by ID
void deleteStudentById() {
    int deleteId;
    printf("Enter student ID to delete: ");
    scanf("%d", &deleteId);

    bool found = false;  // Flag to indicate if the student was found

    // Open the student.txt file for reading
    FILE *file = fopen("Storage/student.txt", "r");

    if (file != NULL) {
        struct Student student;  // Temporary variable to store student data while reading

        // Open the same file for writing (this will clear its content)
        FILE *tempFile = fopen("Storage/temp.txt", "w");

        if (tempFile != NULL) {
            // Read data from the file and copy to the temporary file while checking for the student to delete
            while (fscanf(file, "%49s %49s %14s %49s %d\n", student.name, student.fatherName, student.phoneNumber, student.faculty, &student.id) == 5) {
                if (student.id == deleteId) {
                    found = true;  // Student found, skip this entry (delete it)
                    continue;
                }

                fprintf(tempFile, "%s %s %s %s %d\n", student.name, student.fatherName, student.phoneNumber, student.faculty, student.id);
            }

            fclose(tempFile);  // Close the temporary file
        } else {
            printf("Error: Unable to open temporary file for writing.\n");
        }

        fclose(file);  // Close the original file

        // If the student was found, replace the original file with the temporary file
        if (found) {
            if (remove("Storage/student.txt") != 0) {
                printf("Error: Unable to delete the student data file.\n");
            } else if (rename("Storage/temp.txt", "Storage/student.txt") != 0) {
                printf("Error: Unable to update the student data file.\n");
            }
        }
    } else {
        printf("Error: Unable to open student data file for reading.\n");
    }

    if (found) {
        printf("\033[1;32m"); // Set text color to green
        printf("Student with ID %d deleted successfully.\n", deleteId);
        printf("\033[0m"); // Reset text color
    } else {
        printf("\033[1;31m"); // Set text color to red
        printf("Student with ID %d not found.\n", deleteId);
        printf("\033[0m"); // Reset text color
    }

    // Wait for the user to press Enter before returning
    printf("Press Enter to continue...");
    while (getchar() != '\n');  // Clear input buffer
    getchar();  // Wait for Enter
}

void editStudentById() {
    int editId;
    printf("Enter student ID to edit: ");
    scanf("%d", &editId);

    bool found = false;  // Flag to indicate if the student was found

    // Open the student.txt file for reading
    FILE *file = fopen("Storage/student.txt", "r");

    if (file != NULL) {
        struct Student student;  // Temporary variable to store student data while reading

        // Open the same file for writing (this will clear its content)
        FILE *tempFile = fopen("Storage/temp.txt", "w");

        if (tempFile != NULL) {
            // Read data from the file and copy to the temporary file while checking for the student to edit
            while (fscanf(file, "%49s %49s %14s %49s %d\n", student.name, student.fatherName, student.phoneNumber, student.faculty, &student.id) == 5) {
                if (student.id == editId) {
                    // Student found, allow editing
                    printf("\033[1;32m"); // Set text color to green
                    printf("Edit Student\n");
                    printf("\033[0m"); // Reset text color

                    printf("Name: ");
                    scanf("%s", student.name);

                    printf("Father's Name: ");
                    scanf("%s", student.fatherName);

                    printf("Phone Number: ");
                    scanf("%s", student.phoneNumber);

                    printf("Faculty: ");
                    scanf("%s", student.faculty);

                    printf("\033[1;32m"); // Set text color to green
                    printf("Student with ID %d edited successfully.\n", editId);
                    printf("\033[0m"); // Reset text color

                    found = true;  // Student found and edited
                }

                fprintf(tempFile, "%s %s %s %s %d\n", student.name, student.fatherName, student.phoneNumber, student.faculty, student.id);
            }

            fclose(tempFile);  // Close the temporary file
        } else {
            printf("Error: Unable to open temporary file for writing.\n");
        }

        fclose(file);  // Close the original file

        // If the student was found and edited, replace the original file with the temporary file
        if (found) {
            if (remove("Storage/student.txt") != 0) {
                printf("Error: Unable to delete the student data file.\n");
            } else if (rename("Storage/temp.txt", "Storage/student.txt") != 0) {
                printf("Error: Unable to update the student data file.\n");
            }
        }
    } else {
        printf("Error: Unable to open student data file for reading.\n");
    }

    if (!found) {
        printf("\033[1;31m"); // Set text color to red
        printf("Student with ID %d not found.\n", editId);
        printf("\033[0m"); // Reset text color
    }

    // Wait for the user to press Enter before returning
    printf("Press Enter to continue...");
    while (getchar() != '\n');  // Clear input buffer
    getchar();  // Wait for Enter
}

void handleStudent() {
    printf("\033[1;32m"); // Set text color to green
    printf("KPS-system\n");
    printf("\033[0m"); // Reset text color

    int choice;

    while (1) {
        printf("\033[2J\033[H"); // Clear screen

        printf("\033[1;32m"); // Set text color to green
        printf("Student Menu\n");
        printf("\033[0m"); // Reset text color

        printf("1. Add Student\n");
        printf("2. View Student by Name\n");
        printf("3. Delete Student by ID\n");
        printf("4. Edit Student by ID\n");
        printf("5. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                viewStudentByName();
                break;
            case 3:
                deleteStudentById();
                break;
            case 4:
                editStudentById();
                break;
            case 5:
                return; // Return to the main menu
            default:
                printf("\033[1;31m"); // Set text color to red
                printf("Invalid choice. Please select a valid option.\n");
                printf("\033[0m"); // Reset text color
        }
    }
}

void handleAccount() {
    printf("Handling Account Section\n");
    // Call the account program from Programs folder
    system("./Programs/account");
}

void handleResult() {
    printf("Handling Result Section\n");
    // Call the result program from Programs folder
    system("./Programs/result");
}

void handleInformation() {
    printf("Handling Information Section\n");
    // Call the information program from Programs folder
    system("./Programs/information");
}

int main() {
    int choice;

    while (1) {
        printf("\033[2J\033[H"); // Clear screen

        printf("\033[1;32m"); // Set text color to green
        printf("KPS-system\n");
        printf("\033[0m"); // Reset text color

        printf("Menu:\n");
        printf("1. Student\n");
        printf("2. Account\n");
        printf("3. Result\n");
        printf("4. Information\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                handleStudent(); // Call the student handling function
                break;
            case 2:
                handleAccount();
                break;
            case 3:
                handleResult();
                break;
            case 4:
                handleInformation();
                break;
            case 5:
                printf("Exiting program.\n");
                exit(0);
            default:
                printf("\033[1;31m"); // Set text color to red
                printf("Invalid choice. Please select a valid option.\n");
                printf("\033[0m"); // Reset text color
        }
    }

    return 0;
}
