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
    double feeToBePaid;
    double feePaid;
};

struct Account {
    int studentId;
    double feeAmount;
    double feePaid;
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



void addAccount() {
    struct Account newAccount;

    printf("\033[1;32m"); // Set text color to green
    printf("Add Account\n");
    printf("\033[0m"); // Reset text color

    // Prompt the user to enter the student ID
    int studentId;
    bool studentIdValid = false;
    do {
        printf("Enter Student ID: ");
        scanf("%d", &studentId);

        // Check if the student ID exists in student.txt
        if (!isStudentIdUniqueInFile(studentId)) {
            studentIdValid = true;
        } else {
            printf("\033[1;31m"); // Set text color to red
            printf("Error: Student ID does not exist. Please enter a valid ID.\n");
            printf("\033[0m"); // Reset text color
        }
    } while (!studentIdValid);

    // Prompt the user to enter the fee amount
    printf("Enter Fee Amount: ");
    scanf("%lf", &newAccount.feeAmount);

    // Calculate the remaining fee (feeToBePaid - feePaid) and set feePaid to 0
    newAccount.feePaid = 0;
    newAccount.studentId = studentId;

    // Save the new account to account.txt
    FILE *accountFile = fopen("Storage/account.txt", "a");
    if (accountFile != NULL) {
        fprintf(accountFile, "%d %.2lf %.2lf\n", newAccount.studentId, newAccount.feeAmount, newAccount.feePaid);
        fclose(accountFile);

        printf("\033[1;32m"); // Set text color to green
        printf("Account added successfully.\n");
        printf("\033[0m"); // Reset text color
    } else {
        printf("Error: Unable to open account file for writing.\n");
    }
}

void viewAccount() {
    printf("\033[1;32m"); // Set text color to green
    printf("View Account\n");
    printf("\033[0m"); // Reset text color

    // Prompt the user to enter the student ID to view account details
    int studentId;
    printf("Enter Student ID: ");
    scanf("%d", &studentId);

    // Open the student.txt file to retrieve the student's name
    FILE *studentFile = fopen("Storage/student.txt", "r");
    if (studentFile != NULL) {
        struct Student student; // Temporary variable to store student data while reading

        // Search for the student with the specified ID
        bool found = false;
        while (fscanf(studentFile, "%49s %49s %14s %49s %d\n", student.name, student.fatherName, student.phoneNumber, student.faculty, &student.id) == 5) {
            if (student.id == studentId) {
                found = true;
                break;
            }
        }

        fclose(studentFile);

        if (found) {
            // Open the account.txt file to retrieve fee-related details
            FILE *accountFile = fopen("Storage/account.txt", "r");
            if (accountFile != NULL) {
                struct Account account; // Temporary variable to store account data while reading

                // Search for the account with the specified student ID
                found = false;
                while (fscanf(accountFile, "%d %lf %lf\n", &account.studentId, &account.feeAmount, &account.feePaid) == 3) {
                    if (account.studentId == studentId) {
                        found = true;

                        // Calculate the fee remaining (feeAmount - feePaid)
                        double feeRemaining = account.feeAmount - account.feePaid;

                        printf("\033[1;32m"); // Set text color to green
                        printf("Account Details for Student ID %d:\n", studentId);
                        printf("\033[0m"); // Reset text color
                        printf("Student Name: %s\n", student.name);
                        printf("Fee Paid: Rs %.2lf\n", account.feePaid);
                        printf("Total Fee: Rs %.2lf\n", account.feeAmount);
                        printf("Fee Remaining: Rs %.2lf\n", feeRemaining);

                        break;
                    }
                }

                fclose(accountFile);

                if (!found) {
                    printf("\033[1;31m"); // Set text color to red
                    printf("No account found for Student ID %d.\n", studentId);
                    printf("\033[0m"); // Reset text color
                }
            } else {
                printf("Error: Unable to open account file for reading.\n");
            }
        } else {
            printf("\033[1;31m"); // Set text color to red
            printf("Student with ID %d not found.\n", studentId);
            printf("\033[0m"); // Reset text color
        }
    } else {
        printf("Error: Unable to open student file for reading.\n");
    }

    // Wait for the user to press Enter before returning
    printf("Press Enter to continue...");
    while (getchar() != '\n'); // Clear input buffer
    getchar(); // Wait for Enter
}

void deleteAccount() {
    printf("\033[1;32m"); // Set text color to green
    printf("Delete Account\n");
    printf("\033[0m"); // Reset text color

    // Prompt the user to enter the student ID to delete the account
    int studentId;
    printf("Enter Student ID: ");
    scanf("%d", &studentId);

    // Open the account.txt file for reading
    FILE *accountFile = fopen("Storage/account.txt", "r");
    if (accountFile != NULL) {
        // Open a temporary file for writing
        FILE *tempFile = fopen("Storage/temp_account.txt", "w");
        if (tempFile != NULL) {
            struct Account account; // Temporary variable to store account data while reading

            // Search for the account with the specified student ID
            bool found = false;
            while (fscanf(accountFile, "%d %lf %lf\n", &account.studentId, &account.feeAmount, &account.feePaid) == 3) {
                if (account.studentId == studentId) {
                    found = true;
                } else {
                    // Write the account data to the temporary file
                    fprintf(tempFile, "%d %.2lf %.2lf\n", account.studentId, account.feeAmount, account.feePaid);
                }
            }

            fclose(tempFile); // Close the temporary file
            fclose(accountFile); // Close the original account file

            if (found) {
                // Replace the original account.txt file with the temporary file
                if (remove("Storage/account.txt") != 0) {
                    printf("Error: Unable to delete the account file.\n");
                } else if (rename("Storage/temp_account.txt", "Storage/account.txt") != 0) {
                    printf("Error: Unable to update the account file.\n");
                } else {
                    printf("\033[1;32m"); // Set text color to green
                    printf("Account for Student ID %d deleted successfully.\n", studentId);
                    printf("\033[0m"); // Reset text color
                }
            } else {
                printf("\033[1;31m"); // Set text color to red
                printf("No account found for Student ID %d.\n", studentId);
                printf("\033[0m"); // Reset text color
            }
        } else {
            printf("Error: Unable to open temporary account file for writing.\n");
        }
    } else {
        printf("Error: Unable to open account file for reading.\n");
    }

    // Wait for the user to press Enter before returning
    printf("Press Enter to continue...");
    while (getchar() != '\n'); // Clear input buffer
    getchar(); // Wait for Enter
}

void editAccount() {
    printf("\033[1;32m"); // Set text color to green
    printf("Edit Account\n");
    printf("\033[0m"); // Reset text color

    // Prompt the user to enter the student ID to edit the account
    int studentId;
    printf("Enter Student ID: ");
    scanf("%d", &studentId);

    // Open the account.txt file for reading
    FILE *accountFile = fopen("Storage/account.txt", "r");
    if (accountFile != NULL) {
        // Open a temporary file for writing
        FILE *tempFile = fopen("Storage/temp_account.txt", "w");
        if (tempFile != NULL) {
            struct Account account; // Temporary variable to store account data while reading

            // Search for the account with the specified student ID
            bool found = false;
            while (fscanf(accountFile, "%d %lf %lf\n", &account.studentId, &account.feeAmount, &account.feePaid) == 3) {
                if (account.studentId == studentId) {
                    found = true;

                    // Prompt the user to enter the new total fee
                    printf("Enter New Total Fee: ");
                    scanf("%lf", &account.feeAmount);
                }

                // Write the account data to the temporary file
                fprintf(tempFile, "%d %.2lf %.2lf\n", account.studentId, account.feeAmount, account.feePaid);
            }

            fclose(tempFile); // Close the temporary file
            fclose(accountFile); // Close the original account file

            if (found) {
                // Replace the original account.txt file with the temporary file
                if (remove("Storage/account.txt") != 0) {
                    printf("Error: Unable to delete the account file.\n");
                } else if (rename("Storage/temp_account.txt", "Storage/account.txt") != 0) {
                    printf("Error: Unable to update the account file.\n");
                } else {
                    printf("\033[1;32m"); // Set text color to green
                    printf("Total fee for Student ID %d updated successfully.\n", studentId);
                    printf("\033[0m"); // Reset text color
                }
            } else {
                printf("\033[1;31m"); // Set text color to red
                printf("No account found for Student ID %d.\n", studentId);
                printf("\033[0m"); // Reset text color
            }
        } else {
            printf("Error: Unable to open temporary account file for writing.\n");
        }
    } else {
        printf("Error: Unable to open account file for reading.\n");
    }

    // Wait for the user to press Enter before returning
    printf("Press Enter to continue...");
    while (getchar() != '\n'); // Clear input buffer
    getchar(); // Wait for Enter
}

void updateAccount() {
    printf("\033[1;32m"); // Set text color to green
    printf("Update Account\n");
    printf("\033[0m"); // Reset text color

    // Prompt the user to enter the student ID to update the account
    int studentId;
    printf("Enter Student ID: ");
    scanf("%d", &studentId);

    // Open the account.txt file for reading
    FILE *accountFile = fopen("Storage/account.txt", "r");
    if (accountFile != NULL) {
        // Open a temporary file for writing
        FILE *tempFile = fopen("Storage/temp_account.txt", "w");
        if (tempFile != NULL) {
            struct Account account; // Temporary variable to store account data while reading

            // Search for the account with the specified student ID
            bool found = false;
            while (fscanf(accountFile, "%d %lf %lf\n", &account.studentId, &account.feeAmount, &account.feePaid) == 3) {
                if (account.studentId == studentId) {
                    found = true;

                    // Prompt the user to enter the new fee paid
                    printf("Enter New Fee Paid: ");
                    scanf("%lf", &account.feePaid);
                }

                // Write the account data to the temporary file
                fprintf(tempFile, "%d %.2lf %.2lf\n", account.studentId, account.feeAmount, account.feePaid);
            }

            fclose(tempFile); // Close the temporary file
            fclose(accountFile); // Close the original account file

            if (found) {
                // Replace the original account.txt file with the temporary file
                if (remove("Storage/account.txt") != 0) {
                    printf("Error: Unable to delete the account file.\n");
                } else if (rename("Storage/temp_account.txt", "Storage/account.txt") != 0) {
                    printf("Error: Unable to update the account file.\n");
                } else {
                    printf("\033[1;32m"); // Set text color to green
                    printf("Account for Student ID %d updated successfully.\n", studentId);
                    printf("\033[0m"); // Reset text color
                }
            } else {
                printf("\033[1;31m"); // Set text color to red
                printf("No account found for Student ID %d.\n", studentId);
                printf("\033[0m"); // Reset text color
            }
        } else {
            printf("Error: Unable to open temporary account file for writing.\n");
        }
    } else {
        printf("Error: Unable to open account file for reading.\n");
    }

    // Wait for the user to press Enter before returning
    printf("Press Enter to continue...");
    while (getchar() != '\n'); // Clear input buffer
    getchar(); // Wait for Enter
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
    printf("\033[1;32m"); // Set text color to green
    printf("Account Menu\n");
    printf("\033[0m"); // Reset text color

    int choice;

    while (1) {
        printf("\033[2J\033[H"); // Clear screen

        printf("\033[1;32m"); // Set text color to green
        printf("Account Menu\n");
        printf("\033[0m"); // Reset text color

        printf("1. Add Account\n");
        printf("2. View Account\n");
        printf("3. Delete Account\n");
        printf("4. Edit Account\n");
        printf("5. Update Account\n");
        printf("6. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addAccount();
                break;
            case 2:
                viewAccount();
                break;
            case 3:
                deleteAccount();
                break;
            case 4:
               editAccount();
                break;
            case 5:
                updateAccount();
                break;
            case 6:
                return; // Return to the main menu
            default:
                printf("\033[1;31m"); // Set text color to red
                printf("Invalid choice. Please select a valid option.\n");
                printf("\033[0m"); // Reset text color
        }
    }
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
