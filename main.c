#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

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

// Student section
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
bool isStudentIdUniqueInAccountFile(int studentId) {
    // Check if the student ID exists in the account.txt file
    FILE *accountFile = fopen("Storage/account.txt", "r");
    if (accountFile != NULL) {
        struct Account account;
        while (fscanf(accountFile, "%d %lf %lf\n", &account.studentId, &account.feeAmount, &account.feePaid) == 3) {
            if (account.studentId == studentId) {
                fclose(accountFile);
                return false; // Student ID already exists in the account.txt file
            }
        }
        fclose(accountFile);
    }
    return true; // Student ID is unique
}

//Accounting section
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
            sleep(2); // Pause for 2 seconds to display the error message
        }
    } while (!studentIdValid);

    // Check if the student ID already exists in account.txt
    if (!isStudentIdUniqueInAccountFile(studentId)) {
        printf("\033[1;31m"); // Set text color to red
        printf("Error: Account already exists for Student ID %d.\n", studentId);
        printf("\033[0m"); // Reset text color
        sleep(2); // Pause for 2 seconds to display the error message
        return;
    }

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

//result section
void addResult() {
    printf("\033[1;32m"); // Set text color to green
    printf("Add Result\n");
    printf("\033[0m"); // Reset text color

    int studentId;
    printf("Enter Student ID: ");
    scanf("%d", &studentId);

    // Open student.txt to check if the student ID exists
    FILE *studentFile = fopen("Storage/student.txt", "r");
    if (studentFile != NULL) {
        struct Student student;
        bool found = false;

        while (fscanf(studentFile, "%49s %49s %14s %49s %d\n", student.name, student.fatherName, student.phoneNumber, student.faculty, &student.id) == 5) {
            if (student.id == studentId) {
                found = true;
                break; // Student ID found, break out of the loop
            }
        }

        fclose(studentFile);

        if (found) {
            // Check if a result already exists for this student ID in result.txt
            FILE *resultFile = fopen("Storage/result.txt", "r");
            bool resultExists = false;

            if (resultFile != NULL) {
                int existingStudentId;
                while (fscanf(resultFile, "%d", &existingStudentId) == 1) {
                    if (existingStudentId == studentId) {
                        resultExists = true;
                        break; // Result exists for this student ID
                    }
                    // Skip the rest of the line
                    int c;
                    while ((c = fgetc(resultFile)) != '\n' && c != EOF);
                }
                fclose(resultFile);
            } else {
                printf("Error: Unable to open result file for reading.\n");
            }

            if (resultExists) {
                // Ask the user if they want to delete the existing result
                char choice;
                printf("A result already exists for Student ID %d. Do you want to delete it and add a new one? (Y/N): ", studentId);
                scanf(" %c", &choice);

                if (choice == 'Y' || choice == 'y') {
                    // Delete the existing result
                    FILE *tempFile = fopen("Storage/temp_result.txt", "w");
                    if (tempFile != NULL) {
                        FILE *resultFile = fopen("Storage/result.txt", "r");
                        int existingStudentId;
                        while (fscanf(resultFile, "%d", &existingStudentId) == 1) {
                            if (existingStudentId == studentId) {
                                // Skip the existing result
                                fscanf(resultFile, "%*[^\n]\n");
                            } else {
                                // Copy other results to the temporary file
                                fprintf(tempFile, "%d", existingStudentId);
                                char c;
                                while ((c = fgetc(resultFile)) != EOF && c != '\n') {
                                    fputc(c, tempFile);
                                }
                                fputc('\n', tempFile);
                            }
                        }
                        fclose(resultFile);
                        fclose(tempFile);

                        // Rename the temporary file to result.txt
                        remove("Storage/result.txt");
                        rename("Storage/temp_result.txt", "Storage/result.txt");

                        printf("\033[1;32m"); // Set text color to green
                        printf("Existing result for Student ID %d deleted.\n", studentId);
                        printf("\033[0m"); // Reset text color
                    } else {
                        printf("Error: Unable to create temporary result file.\n");
                    }
                } else {
                    printf("\033[1;31m"); // Set text color to red
                    printf("Operation canceled. Existing result for Student ID %d was not deleted.\n", studentId);
                    printf("\033[0m"); // Reset text color
                    return; // Do not add a new result
                }
            }

            // Prompt the user to enter subject marks with input validation
            double math, english, cProgramming, physics, chemistry;
            
            do {
                printf("Enter Marks for Math (0-100): ");
                scanf("%lf", &math);
                if (math < 0 || math > 100) {
                    printf("Error: Marks must be between 0 and 100.\n");
                }
            } while (math < 0 || math > 100);

            do {
                printf("Enter Marks for English (0-100): ");
                scanf("%lf", &english);
                if (english < 0 || english > 100) {
                    printf("Error: Marks must be between 0 and 100.\n");
                }
            } while (english < 0 || english > 100);

            do {
                printf("Enter Marks for C Programming (0-100): ");
                scanf("%lf", &cProgramming);
                if (cProgramming < 0 || cProgramming > 100) {
                    printf("Error: Marks must be between 0 and 100.\n");
                }
            } while (cProgramming < 0 || cProgramming > 100);

            do {
                printf("Enter Marks for Physics (0-100): ");
                scanf("%lf", &physics);
                if (physics < 0 || physics > 100) {
                    printf("Error: Marks must be between 0 and 100.\n");
                }
            } while (physics < 0 || physics > 100);

            do {
                printf("Enter Marks for Chemistry (0-100): ");
                scanf("%lf", &chemistry);
                if (chemistry < 0 || chemistry > 100) {
                    printf("Error: Marks must be between 0 and 100.\n");
                }
            } while (chemistry < 0 || chemistry > 100);

            // Calculate total marks and GPA
            double totalMarks = math + english + cProgramming + physics + chemistry;
            double GPA = ((totalMarks / 500.0) * 100.0) / 25.0;

            // Append results to result.txt
            resultFile = fopen("Storage/result.txt", "a");
            if (resultFile != NULL) {
                fprintf(resultFile, "%d %.2lf %.2lf %.2lf %.2lf %.2lf %.2lf %.2lf\n", studentId, math, english, cProgramming, physics, chemistry, totalMarks, GPA);
                fclose(resultFile);

                printf("\033[1;32m"); // Set text color to green
                printf("Result added successfully for Student ID %d.\n", studentId);
                printf("\033[0m"); // Reset text color
            } else {
                printf("Error: Unable to open result file for writing.\n");
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
void viewResult() {
    printf("View Result\n");

    int studentId;
    printf("Enter Student ID: ");
    scanf("%d", &studentId);

    // Open student.txt to check if the student ID exists
    FILE *studentFile = fopen("Storage/student.txt", "r");
    if (studentFile != NULL) {
        struct Student student;
        bool found = false;

        while (fscanf(studentFile, "%49s %49s %14s %49s %d\n", student.name, student.fatherName, student.phoneNumber, student.faculty, &student.id) == 5) {
            if (student.id == studentId) {
                found = true;
                break; // Student ID found, break out of the loop
            }
        }

        fclose(studentFile);

        if (found) {
            // Open result.txt to check if results exist for this student ID
            FILE *resultFile = fopen("Storage/result.txt", "r");
            bool resultExists = false;

            if (resultFile != NULL) {
                int existingStudentId;
                double math, english, cProgramming, physics, chemistry, totalMarks, GPA;

                while (fscanf(resultFile, "%d %lf %lf %lf %lf %lf %lf %lf\n", &existingStudentId, &math, &english, &cProgramming, &physics, &chemistry, &totalMarks, &GPA) == 8) {
                    if (existingStudentId == studentId) {
                        resultExists = true;

                        printf("Result for Student ID %d:\n", studentId);
                        printf("+---------------------+------------+\n");
                        printf("| Student Name        | %s      |\n", student.name);
                        printf("| GPA                 | %.2lf       |\n", GPA);
                        printf("+---------------------+------------+\n");
                        printf("| Subject             | Marks      |\n");
                        printf("+---------------------+------------+\n");
                        printf("| Math                | %.2lf     |\n", math);
                        printf("| English             | %.2lf     |\n", english);
                        printf("| C Programming       | %.2lf     |\n", cProgramming);
                        printf("| Physics             | %.2lf     |\n", physics);
                        printf("| Chemistry           | %.2lf     |\n", chemistry);
                        printf("+---------------------+------------+\n");
                        printf("| Total Marks         | %.2lf     |\n", totalMarks);
                        printf("+---------------------+------------+\n");

                        break; // Displayed result, break out of the loop
                    }
                }

                fclose(resultFile);
            } else {
                printf("Error: Unable to open result file for reading.\n");
            }

            if (!resultExists) {
                printf("No result found for Student ID %d.\n", studentId);
            }
        } else {
            printf("Student with ID %d not found.\n", studentId);
        }
    } else {
        printf("Error: Unable to open student file for reading.\n");
    }

    // Wait for the user to press Enter before returning
    printf("Press Enter to continue...");
    while (getchar() != '\n'); // Clear input buffer
    getchar(); // Wait for Enter
}
void editResult() {
    printf("Edit Result\n");

    int studentId;
    printf("Enter Student ID: ");
    scanf("%d", &studentId);

    // Open student.txt to check if the student ID exists
    FILE *studentFile = fopen("Storage/student.txt", "r");
    if (studentFile != NULL) {
        struct Student student;
        bool found = false;

        while (fscanf(studentFile, "%49s %49s %14s %49s %d\n", student.name, student.fatherName, student.phoneNumber, student.faculty, &student.id) == 5) {
            if (student.id == studentId) {
                found = true;
                break; // Student ID found, break out of the loop
            }
        }

        fclose(studentFile);

        if (found) {
            // Open result.txt to check if results exist for this student ID
            FILE *resultFile = fopen("Storage/result.txt", "r");
            bool resultExists = false;

            if (resultFile != NULL) {
                int existingStudentId;
                double math, english, cProgramming, physics, chemistry, totalMarks, GPA;

                // Create a temporary file for editing
                FILE *tempFile = fopen("Storage/temp_result.txt", "w");

                if (tempFile != NULL) {
                    while (fscanf(resultFile, "%d %lf %lf %lf %lf %lf %lf %lf\n", &existingStudentId, &math, &english, &cProgramming, &physics, &chemistry, &totalMarks, &GPA) == 8) {
                        if (existingStudentId == studentId) {
                            resultExists = true;

                            // Prompt the user to enter new subject marks with input validation
                            do {
                                printf("Enter new Marks for Math (0-100): ");
                                scanf("%lf", &math);
                                if (math < 0 || math > 100) {
                                    printf("Error: Marks must be between 0 and 100.\n");
                                }
                            } while (math < 0 || math > 100);

                            do {
                                printf("Enter new Marks for English (0-100): ");
                                scanf("%lf", &english);
                                if (english < 0 || english > 100) {
                                    printf("Error: Marks must be between 0 and 100.\n");
                                }
                            } while (english < 0 || english > 100);

                            do {
                                printf("Enter new Marks for C Programming (0-100): ");
                                scanf("%lf", &cProgramming);
                                if (cProgramming < 0 || cProgramming > 100) {
                                    printf("Error: Marks must be between 0 and 100.\n");
                                }
                            } while (cProgramming < 0 || cProgramming > 100);

                            do {
                                printf("Enter new Marks for Physics (0-100): ");
                                scanf("%lf", &physics);
                                if (physics < 0 || physics > 100) {
                                    printf("Error: Marks must be between 0 and 100.\n");
                                }
                            } while (physics < 0 || physics > 100);

                            do {
                                printf("Enter new Marks for Chemistry (0-100): ");
                                scanf("%lf", &chemistry);
                                if (chemistry < 0 || chemistry > 100) {
                                    printf("Error: Marks must be between 0 and 100.\n");
                                }
                            } while (chemistry < 0 || chemistry > 100);

                            // Recalculate total marks and GPA
                            totalMarks = math + english + cProgramming + physics + chemistry;
                            GPA = ((totalMarks / 500.0) * 100.0) / 25.0;
                        }

                        // Write the result to the temporary file
                        fprintf(tempFile, "%d %.2lf %.2lf %.2lf %.2lf %.2lf %.2lf %.2lf\n", existingStudentId, math, english, cProgramming, physics, chemistry, totalMarks, GPA);
                    }

                    fclose(tempFile);

                    // Close and remove the original result file
                    fclose(resultFile);
                    remove("Storage/result.txt");

                    // Rename the temporary file to the original result file
                    rename("Storage/temp_result.txt", "Storage/result.txt");

                    printf("Result for Student ID %d edited successfully.\n", studentId);
                } else {
                    printf("Error: Unable to create temporary result file for editing.\n");
                }
            } else {
                printf("Error: Unable to open result file for reading.\n");
            }

            if (!resultExists) {
                printf("No result found for Student ID %d.\n", studentId);
            }
        } else {
            printf("Student with ID %d not found.\n", studentId);
        }
    } else {
        printf("Error: Unable to open student file for reading.\n");
    }

    // Wait for the user to press Enter before returning
    printf("Press Enter to continue...");
    while (getchar() != '\n'); // Clear input buffer
    getchar(); // Wait for Enter
}
void deleteResult() {
    printf("Delete Result\n");

    int studentId;
    printf("Enter Student ID: ");
    scanf("%d", &studentId);

    // Open student.txt to check if the student ID exists
    FILE *studentFile = fopen("Storage/student.txt", "r");
    if (studentFile != NULL) {
        struct Student student;
        bool found = false;

        while (fscanf(studentFile, "%49s %49s %14s %49s %d\n", student.name, student.fatherName, student.phoneNumber, student.faculty, &student.id) == 5) {
            if (student.id == studentId) {
                found = true;
                break; // Student ID found, break out of the loop
            }
        }

        fclose(studentFile);

        if (found) {
            // Open result.txt to check if results exist for this student ID
            FILE *resultFile = fopen("Storage/result.txt", "r");
            bool resultExists = false;

            if (resultFile != NULL) {
                int existingStudentId;
                double math, english, cProgramming, physics, chemistry, totalMarks, GPA;

                // Create a temporary file for storing the results without the deleted entry
                FILE *tempFile = fopen("Storage/temp_result.txt", "w");

                if (tempFile != NULL) {
                    while (fscanf(resultFile, "%d %lf %lf %lf %lf %lf %lf %lf\n", &existingStudentId, &math, &english, &cProgramming, &physics, &chemistry, &totalMarks, &GPA) == 8) {
                        if (existingStudentId == studentId) {
                            resultExists = true;

                            // Skip the entry to delete it
                            continue;
                        }

                        // Write the result to the temporary file
                        fprintf(tempFile, "%d %.2lf %.2lf %.2lf %.2lf %.2lf %.2lf %.2lf\n", existingStudentId, math, english, cProgramming, physics, chemistry, totalMarks, GPA);
                    }

                    fclose(tempFile);

                    // Close and remove the original result file
                    fclose(resultFile);
                    remove("Storage/result.txt");

                    // Rename the temporary file to the original result file
                    rename("Storage/temp_result.txt", "Storage/result.txt");

                    printf("Result for Student ID %d deleted successfully.\n", studentId);
                } else {
                    printf("Error: Unable to create temporary result file for deletion.\n");
                }
            } else {
                printf("Error: Unable to open result file for reading.\n");
            }

            if (!resultExists) {
                printf("No result found for Student ID %d.\n", studentId);
            }
        } else {
            printf("Student with ID %d not found.\n", studentId);
        }
    } else {
        printf("Error: Unable to open student file for reading.\n");
    }

    // Wait for the user to press Enter before returning
    printf("Press Enter to continue...");
    while (getchar() != '\n'); // Clear input buffer
    getchar(); // Wait for Enter
}

//Information section
void clearResultData() {
    printf("\033[1;33m"); // Set text color to yellow
    printf("Warning: This will clear all result data. Are you sure you want to proceed? (Y/N): ");
    printf("\033[0m"); // Reset text color

    char choice;
    scanf(" %c", &choice);

    if (choice == 'Y' || choice == 'y') {
        // Open the result file in write mode to clear its contents
        FILE *resultFile = fopen("Storage/result.txt", "w");

        if (resultFile != NULL) {
            fclose(resultFile);
            printf("\033[1;32m"); // Set text color to green
            printf("Result data cleared successfully.\n");
            printf("\033[0m"); // Reset text color
        } else {
            printf("\033[1;31m"); // Set text color to red
            printf("Error: Unable to open result file for clearing data.\n");
            printf("\033[0m"); // Reset text color
        }
    } else {
        printf("\033[1;33m"); // Set text color to yellow
        printf("Clearing result data canceled.\n");
        printf("\033[0m"); // Reset text color
    }

    // Wait for the user to press Enter before returning
    printf("Press Enter to continue...");
    while (getchar() != '\n'); // Clear input buffer
    getchar(); // Wait for Enter
}
void clearAccountData() {
    printf("\033[1;33m"); // Set text color to yellow
    printf("Warning: This action will clear all account data. Do you want to continue? (yes/no): ");
    printf("\033[0m"); // Reset text color

    char response[10];
    scanf("%9s", response);

    if (strcmp(response, "yes") == 0 || strcmp(response, "Yes") == 0 || strcmp(response, "YES") == 0) {
        // User confirmed to clear the account data
        FILE *accountFile = fopen("Storage/account.txt", "w");
        if (accountFile != NULL) {
            fclose(accountFile);
            printf("\033[1;32m"); // Set text color to green
            printf("Account data cleared successfully.\n");
            printf("\033[0m"); // Reset text color
        } else {
            printf("\033[1;31m"); // Set text color to red
            printf("Error: Unable to open account file for writing.\n");
            printf("\033[0m"); // Reset text color
        }
    } else {
        printf("\033[1;33m"); // Set text color to yellow
        printf("Clearing account data canceled.\n");
        printf("\033[0m"); // Reset text color
    }

    // Wait for the user to press Enter before returning
    printf("Press Enter to continue...");
    while (getchar() != '\n'); // Clear input buffer
    getchar(); // Wait for Enter
}

int compareIntegers(const void *a, const void *b) {
    const struct Student *studentA = (const struct Student *)a;
    const struct Student *studentB = (const struct Student *)b;
    return studentA->id - studentB->id;
}
void viewAllStudents() {
    printf("\033[1;32m"); // Set text color to green
    printf("View All Students\n");
    printf("\033[0m"); // Reset text color

    // Open the student.txt file for reading
    FILE *file = fopen("Storage/student.txt", "r");

    if (file != NULL) {
        // Reset the studentCount and students array
        studentCount = 0;
        memset(students, 0, sizeof(students));

        struct Student student; // Temporary variable to store student data while reading

        // Read data from the file and store it in the students array
        while (fscanf(file, "%49s %49s %14s %49s %d\n", student.name, student.fatherName, student.phoneNumber, student.faculty, &student.id) == 5) {
            students[studentCount++] = student; // Add the student data to the array
        }

        fclose(file); // Close the file

        // Sort the students array by ID in ascending order
        qsort(students, studentCount, sizeof(struct Student), compareIntegers);

        // Display the sorted student information
        printf("\033[1;32m"); // Set text color to green
        printf("%-20s%-20s%-20s%-20s%-10s\n", "Name", "Father's Name", "Phone Number", "Faculty", "ID");
        printf("\033[0m"); // Reset text color

        for (int i = 0; i < studentCount; i++) {
            printf("%-20s%-20s%-20s%-20s%-10d\n", students[i].name, students[i].fatherName, students[i].phoneNumber, students[i].faculty, students[i].id);
        }
    } else {
        printf("Error: Unable to open file for reading.\n");
    }

    // Wait for the user to press Enter before returning
    printf("Press Enter to continue...");
    while (getchar() != '\n'); // Clear input buffer
    getchar(); // Wait for Enter
}
void deleteStudentData() {
    printf("\033[1;33m"); // Set text color to yellow
    printf("Warning: This will clear all student data. Are you sure you want to proceed? (Y/N): ");
    printf("\033[0m"); // Reset text color

    char choice;
    scanf(" %c", &choice);

    if (choice == 'Y' || choice == 'y') {
        // Open the student.txt file for writing (clears its contents)
        FILE *file = fopen("Storage/student.txt", "w");

        if (file != NULL) {
            fclose(file);
            printf("\033[1;32m"); // Set text color to green
            printf("Student data cleared successfully.\n");
            printf("\033[0m"); // Reset text color
        } else {
            printf("\033[1;31m"); // Set text color to red
            printf("Error: Unable to open file for clearing student data.\n");
            printf("\033[0m"); // Reset text color
        }
    } else {
        printf("\033[1;33m"); // Set text color to yellow
        printf("Clearing student data canceled.\n");
        printf("\033[0m"); // Reset text color
    }

    // Wait for the user to press Enter before returning
    printf("Press Enter to continue...");
    while (getchar() != '\n'); // Clear input buffer
    getchar(); // Wait for Enter
}
void infoSeparation() {
    printf("\033[1;32m"); // Set text color to green
    printf("Information Separation\n");
    printf("\033[0m"); // Reset text color

    char faculty[50]; // Store faculty name entered by the user
    int studentCount = 0; // Count of students with the specified faculty

    printf("Enter faculty name: ");
    scanf(" %[^\n]s", faculty); // Read faculty name with spaces

    // Open the student.txt file for reading
    FILE *file = fopen("Storage/student.txt", "r");

    if (file != NULL) {
        struct Student student; // Temporary variable to store student data while reading

        // Read data from the file and check faculty
        while (fscanf(file, "%49s %49s %14s %49s %d\n", student.name, student.fatherName, student.phoneNumber, student.faculty, &student.id) == 5) {
            if (strcmp(student.faculty, faculty) == 0) {
                if (studentCount == 0) {
                    printf("Name: "); // Print "Name: " only once
                }
                printf("%s, ", student.name); // Print the student's name
                studentCount++;
            }
        }

        fclose(file); // Close the file

        if (studentCount > 0) {
            printf("\n\033[1;32m"); // Set text color to green
            printf("Total students with faculty '%s': %d\n", faculty, studentCount);
            printf("\033[0m"); // Reset text color
        } else {
            printf("\033[1;31m"); // Set text color to red
            printf("No students found with faculty '%s'.\n", faculty);
            printf("\033[0m"); // Reset text color
        }
    } else {
        printf("\033[1;31m"); // Set text color to red
        printf("Error: Unable to open file for reading.\n");
        printf("\033[0m"); // Reset text color
    }

    // Wait for the user to press Enter before returning
    printf("Press Enter to continue...");
    while (getchar() != '\n'); // Clear input buffer
    getchar(); // Wait for Enter
}



//handling section
void handleStudent() {
    int choice;

    while (1) {
        printf("\033[2J\033[H"); // Clear screen

        printf("\033[1;32m"); // Set text color to green
        printf("KPS-system\n");
        printf("\033[0m"); // Reset text color

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

                printf("Press Enter to continue...");
                getchar(); // Wait for Enter key press
                getchar(); // Consume the Enter key press
        }
    }
}
void handleAccount() {
    int choice;

    while (1) {
        printf("\033[2J\033[H"); // Clear screen

        printf("\033[1;32m"); // Set text color to green
        printf("KPS-system\n");
        printf("\033[0m"); // Reset text color

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

                printf("Press Enter to continue...");
                getchar(); // Wait for Enter key press
                getchar(); // Consume the Enter key press
        }
    }
}
void handleResult() {
    int choice;

    while (1) {
        printf("\033[2J\033[H"); // Clear screen

        printf("\033[1;32m"); // Set text color to green
        printf("KPS-system\n");
        printf("\033[0m"); // Reset text color

        printf("\033[1;32m"); // Set text color to green
        printf("Result Menu\n");
        printf("\033[0m"); // Reset text color

        printf("1. Add Result\n");
        printf("2. View Result\n");
        printf("3. Delete Result\n");
        printf("4. Edit Result\n");
        printf("5. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addResult();
                break;
            case 2:
                viewResult();
                break;
            case 3:
                deleteResult();
                break;
            case 4:
                editResult();
                break;
            case 5:
                return; // Return to the main menu
            default:
                printf("\033[1;31m"); // Set text color to red
                printf("Invalid choice. Please select a valid option.\n");
                printf("\033[0m"); // Reset text color

                printf("Press Enter to continue...");
                getchar(); // Wait for Enter key press
                getchar(); // Consume the Enter key press
        }
    }
}
void handleInformation() {
    int choice;

    while (1) {
        printf("\033[2J\033[H"); // Clear screen

        printf("\033[1;32m"); // Set text color to green
        printf("KPS-system\n");
        printf("\033[0m"); // Reset text color

        printf("\033[1;32m"); // Set text color to green
        printf("Information Menu\n");
        printf("\033[0m"); // Reset text color

        printf("1. View All Information\n");
        printf("2. Delete Student Data\n");
        printf("3. Clear Result Data\n");
        printf("4. Clear Account Data\n");
        printf("5. Information Separation\n"); // Option for information separation
        printf("6. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                viewAllStudents();
                break;
            case 2:
                deleteStudentData();
                break;
            case 3:
                clearResultData();
                break;
            case 4:
                clearAccountData();
                break;
            case 5:
                infoSeparation();
                break;
            case 6:
                return; // Return to the main menu
            default:
                printf("\033[1;31m"); // Set text color to red
                printf("Invalid choice. Please select a valid option.\n");
                printf("\033[0m"); // Reset text color

                printf("Press Enter to continue...");
                getchar(); // Wait for Enter key press
                getchar(); // Consume the Enter key press
        }
    }
}

//help section 
void showHelp() {
    printf("\nHelp - Tips and Tricks\n");

    printf("\n1. Student Information:\n");
    printf("- In the Student Information section, you can manage student data.\n");
    printf("- You can perform the following actions:\n");
    printf("    1. Add a new student record\n");
    printf("    2. View all students' information\n");
    printf("    3. Delete all student data (irreversible)\n");

    printf("\n2. Account:\n");
    printf("- In the Account section, you can manage user accounts.\n");
    printf("    - You can clear all account data (remove all user accounts), use with caution.\n");

    printf("\n3. Result Management:\n");
    printf("- In the Result Management section, you can manage student results.\n");
    printf("    1. Add a new result\n");
    printf("    2. View a student's result\n");
    printf("    3. Edit a student's result\n");
    printf("    4. Delete a student's result\n");
    printf("    5. Clear all result data (irreversible)\n");

    printf("\n4. Help:\n");
    printf("- You are here! This menu provides tips and tricks for using the program.\n");

    printf("\n5. Exit:\n");
    printf("- Use this option to exit the program.\n");


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
        printf("5. Help\n");
        printf("6. Exit\n");
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
                showHelp();
                break;
            case 6:
                printf("Exiting program.\n");
                exit(0);
            default:
                printf("\033[1;31m"); // Set text color to red
                printf("Invalid choice. Please select a valid option.\n");
                printf("\033[0m"); // Reset text color
        }

        printf("Press Enter to continue...");
        getchar(); // Wait for Enter key press
        getchar(); // Consume the Enter key press
    }

    return 0;
}