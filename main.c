#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STUDENTS 100
#define MAX_SUBJECTS 5

struct Student {
    char name[50];
    char fatherName[50];
    char phoneNumber[15];
    char faculty[50];
    int id;
};

struct Result {
    int studentId;
    char subjectNames[MAX_SUBJECTS][50];
    double marks[MAX_SUBJECTS];
    double totalMarks;
    double gpa;
};

struct Account {
    int studentId;
    double feeAmount;
    double feePaid;
};

// Define subject names
char* subjectNames[] = {"Nepali", "English", "Math", "Science", "C Programming"};

struct Student students[MAX_STUDENTS];
int studentCount = 0;

//help setings 
void showHelp() {
    system("cls");
    FILE *helpFile = fopen("Storage/help.txt", "r");

    if (helpFile != NULL) {
        char line[1000];

        while (fgets(line, sizeof(line), helpFile) != NULL) {
            printf("%s", line);
        }

        fclose(helpFile);
    } else {
        printf("Error: Unable to open help file.\n");
    }
}

//check student
int isStudentIdExists(int studentId) {
    FILE *file = fopen("Storage/student.txt", "r");

    if (file != NULL) {
        struct Student student;

        while (fscanf(file, "%s %s %s %s %d\n", student.name, student.fatherName, student.phoneNumber, student.faculty, &student.id) == 5) {
            if (student.id == studentId) {
                fclose(file);
                return 1; // Student ID exists
            }
        }

        fclose(file);
    }

    return 0; // Student ID does not exist
}
//check result
int isResultIdExists(int studentId) {
    FILE *file = fopen("Storage/result.txt", "r");
    if (file == NULL) {
        return 0; // File doesn't exist; student ID is not found
    }

    int id;
    while (fscanf(file, "%d", &id) == 1) {
        if (id == studentId) {
            fclose(file);
            return 1; // Found the student ID
        }
        // Skip the rest of the line
        while (fgetc(file) != '\n') {
            if (feof(file)) {
                break;
            }
        }
    }

    fclose(file);
    return 0; // Student ID not found
}
//check account
int isStudentIdUniqueInAccountFile(int studentId) {
    FILE *accountFile = fopen("Storage/account.txt", "r");

    if (accountFile != NULL) {
        struct Account account;

        while (fscanf(accountFile, "%d %lf %lf\n", &account.studentId, &account.feeAmount, &account.feePaid) == 3) {
            if (account.studentId == studentId) {
                fclose(accountFile);
                return 0;
            }
        }

        fclose(accountFile);
    }

    return 1;
}

//student settings
void addStudent() {
    system("cls");
    int studentId;
    printf("Enter Student ID: ");
    scanf("%d", &studentId);

    // Check if the student ID already exists
    if (isStudentIdExists(studentId)) {
        printf("Student with ID %d already exists.\n", studentId);
        return;
    }

    struct Student student;
    student.id = studentId;

    printf("Enter Name: ");
    scanf("%s", student.name);
    printf("Enter Father's Name: ");
    scanf("%s", student.fatherName);
    printf("Enter Phone Number: ");
    scanf("%s", student.phoneNumber);
    printf("Enter Faculty: ");
    scanf("%s", student.faculty);

    // Open the student.txt file for appending
    FILE *file = fopen("Storage/student.txt", "a");

    if (file != NULL) {
        fprintf(file, "%s %s %s %s %d\n", student.name, student.fatherName, student.phoneNumber, student.faculty, student.id);
        fclose(file);
        printf("Student record added successfully.\n");
    } else {
        printf("Error: Unable to open file for appending.\n");
    }
}
void viewStudentById() {
    system("cls");
    int studentId;
    printf("Enter Student ID: ");
    scanf("%d", &studentId);

    // Open the student.txt file for reading
    FILE *file = fopen("Storage/student.txt", "r");

    if (file != NULL) {
        struct Student student;
        int found = 0;

        while (fscanf(file, "%s %s %s %s %d\n", student.name, student.fatherName, student.phoneNumber, student.faculty, &student.id) == 5) {
            if (student.id == studentId) {
                found = 1;
                printf("Student ID: %d\n", student.id);
                printf("Name: %s\n", student.name);
                printf("Father's Name: %s\n", student.fatherName);
                printf("Phone Number: %s\n", student.phoneNumber);
                printf("Faculty: %s\n", student.faculty);
                break;
            }
        }

        fclose(file);

        if (!found) {
            printf("Student with ID %d not found.\n", studentId);
        }
    } else {
        printf("Error: Unable to open file for reading.\n");
    }
}
void editStudentById() {
    system("cls");
    int studentId;
    printf("Enter Student ID to edit: ");
    scanf("%d", &studentId);

    // Open the student.txt file for reading and writing
    FILE *file = fopen("Storage/student.txt", "r+");

    if (file != NULL) {
        struct Student student;
        int found = 0;

        // Create a temporary file to copy non-edited records
        FILE *tempFile = fopen("Storage/student_temp.txt", "w");

        while (fscanf(file, "%s %s %s %s %d\n", student.name, student.fatherName, student.phoneNumber, student.faculty, &student.id) == 5) {
            if (student.id == studentId) {
                found = 1;
                printf("Editing Student with ID: %d\n", student.id);
                printf("Enter new name: ");
                scanf("%s", student.name);
                printf("Enter new father's name: ");
                scanf("%s", student.fatherName);
                printf("Enter new phone number: ");
                scanf("%s", student.phoneNumber);
                printf("Enter new faculty: ");
                scanf("%s", student.faculty);
            }
            fprintf(tempFile, "%s %s %s %s %d\n", student.name, student.fatherName, student.phoneNumber, student.faculty, student.id);
        }

        fclose(file);
        fclose(tempFile);

        // Rename the temporary file to overwrite the original file
        remove("Storage/student.txt");
        rename("Storage/student_temp.txt", "Storage/student.txt");

        if (!found) {
            printf("Student with ID %d not found.\n", studentId);
        } else {
            printf("Student record updated successfully.\n");
        }
    } else {
        printf("Error: Unable to open file for reading and writing.\n");
    }
}
void deleteStudentById() {
    system("cls");
    int studentId;
    printf("Enter Student ID to delete: ");
    scanf("%d", &studentId);

    // Open the student.txt file for reading and writing
    FILE *file = fopen("Storage/student.txt", "r+");

    if (file != NULL) {
        struct Student student;
        int found = 0;

        // Create a temporary file to copy non-deleted records
        FILE *tempFile = fopen("Storage/student_temp.txt", "w");

        while (fscanf(file, "%s %s %s %s %d\n", student.name, student.fatherName, student.phoneNumber, student.faculty, &student.id) == 5) {
            if (student.id == studentId) {
                found = 1;
                printf("Deleting Student with ID: %d\n", student.id);
            } else {
                fprintf(tempFile, "%s %s %s %s %d\n", student.name, student.fatherName, student.phoneNumber, student.faculty, student.id);
            }
        }

        fclose(file);
        fclose(tempFile);

        // Rename the temporary file to overwrite the original file
        remove("Storage/student.txt");
        rename("Storage/student_temp.txt", "Storage/student.txt");

        if (!found) {
            printf("Student with ID %d not found.\n", studentId);
        } else {
            printf("Student record deleted successfully.\n");
        }
    } else {
        printf("Error: Unable to open file for reading and writing.\n");
    }
}

//information settings
void clearResultData() {
    printf("Warning: This will clear all result data. Are you sure you want to proceed? (Y/N): ");

    char choice;
    scanf(" %c", &choice);

    if (choice == 'Y' || choice == 'y') {
        FILE *resultFile = fopen("Storage/result.txt", "w");

        if (resultFile != NULL) {
            fclose(resultFile);
            printf("Result data cleared successfully.\n");
        } else {
            printf("Error: Unable to open result file for clearing data.\n");
        }
    } else {
        printf("Clearing result data canceled.\n");
    }
}
void clearAccountData() {
    printf("Warning: This action will clear all account data. Do you want to continue? (yes/no): ");

    char response[10];
    scanf("%9s", response);

    if (strcmp(response, "yes") == 0 || strcmp(response, "Yes") == 0 || strcmp(response, "YES") == 0) {
        FILE *accountFile = fopen("Storage/account.txt", "w");

        if (accountFile != NULL) {
            fclose(accountFile);
            printf("Account data cleared successfully.\n");
        } else {
            printf("Error: Unable to open account file for writing.\n");
        }
    } else {
        printf("Clearing account data canceled.\n");
    }
}
int compareIntegers(void *a, void *b) {
    struct Student *studentA = (struct Student *)a;
    struct Student *studentB = (struct Student *)b;
    return studentA->id - studentB->id;
}
void viewAllStudents() {
    FILE *file = fopen("Storage/student.txt", "r");

    if (file != NULL) {
        studentCount = 0;
        memset(students, 0, sizeof(students));

        struct Student student;

        while (fscanf(file, "%49s %49s %14s %49s %d\n", student.name, student.fatherName, student.phoneNumber, student.faculty, &student.id) == 5) {
            students[studentCount++] = student;
        }

        fclose(file);

        qsort(students, studentCount, sizeof(struct Student), (int (*)(const void *, const void *))compareIntegers);

        printf("%-20s%-20s%-20s%-20s%-10s\n", "Name", "Father's Name", "Phone Number", "Faculty", "ID");

        for (int i = 0; i < studentCount; i++) {
            printf("%-20s%-20s%-20s%-20s%-10d\n", students[i].name, students[i].fatherName, students[i].phoneNumber, students[i].faculty, students[i].id);
        }
    } else {
        printf("Error: Unable to open file for reading.\n");
    }
}
void deleteStudentData() {
    printf("Warning: This will clear all student data. Are you sure you want to proceed? (Y/N): ");

    char choice;
    scanf(" %c", &choice);

    if (choice == 'Y' || choice == 'y') {
        FILE *file = fopen("Storage/student.txt", "w");

        if (file != NULL) {
            fclose(file);
            printf("Student data cleared successfully.\n");
        } else {
            printf("Error: Unable to open file for clearing student data.\n");
        }
    } else {
        printf("Clearing student data canceled.\n");
    }
}
void infoSeparation() {
    char faculty[50];
    int studentCount = 0;

    printf("Enter faculty name: ");
    scanf(" %[^\n]s", faculty);

    FILE *file = fopen("Storage/student.txt", "r");

    if (file != NULL) {
        struct Student student;

        while (fscanf(file, "%49s %49s %14s %49s %d\n", student.name, student.fatherName, student.phoneNumber, student.faculty, &student.id) == 5) {
            if (strcmp(student.faculty, faculty) == 0) {
                if (studentCount == 0) {
                    printf("Name: ");
                }
                printf("%s, ", student.name);
                studentCount++;
            }
        }

        fclose(file);

        if (studentCount > 0) {
            printf("\nTotal students with faculty '%s': %d\n", faculty, studentCount);
        } else {
            printf("No students found with faculty '%s'.\n", faculty);
        }
    } else {
        printf("Error: Unable to open file for reading.\n");
    }
}

//result settings
void addResult() {
    system("cls");
    struct Result result;

    printf("Enter student ID: ");
    scanf("%d", &result.studentId);

    // Check if the student ID exists in student.txt
    if (!isStudentIdExists(result.studentId)) {
        printf("Student with ID %d does not exist.\n", result.studentId);
        return;
    }

    // Check if the result file exists
    FILE *file = fopen("Storage/result.txt", "a");
    if (file == NULL) {
        printf("Result file does not exist or could not be opened.\n");
        return;
    }

    // Check if the student ID already exists in result.txt
    if (isResultIdExists(result.studentId)) {
        printf("Result for student ID %d already exists.\n", result.studentId);
        fclose(file);
        return;
    }

    printf("Enter marks for the following subjects:\n");

    for (int i = 0; i < MAX_SUBJECTS; i++) {
        printf("Enter marks for %s: ", subjectNames[i]);
        scanf("%lf", &result.marks[i]);
        while (result.marks[i] < 0 || result.marks[i] > 100) {
            printf("Marks must be between 0 and 100. Please re-enter marks for %s: ", subjectNames[i]);
            scanf("%lf", &result.marks[i]);
        }
    }

    // Calculate total marks
    result.totalMarks = 0.0;
    for (int i = 0; i < MAX_SUBJECTS; i++) {
        result.totalMarks += result.marks[i];
    }

    // Calculate GPA
    result.gpa = (result.totalMarks / 500.0 * 100.0) / 25.0;

    // Append the result to the file
    fprintf(file, "%d ", result.studentId);
    for (int i = 0; i < MAX_SUBJECTS; i++) {
        fprintf(file, "%.2f ", result.marks[i]);
    }
    fprintf(file, "%.2f %.2f\n", result.totalMarks, result.gpa);

    fclose(file);

    printf("Result added successfully.\n");
}
void viewResult() {
    system("cls");
    int id;
    printf("Enter the student ID to view results: ");
    scanf("%d", &id);

    // Check if the result file exists
    FILE *resultFile = fopen("Storage/result.txt", "r");
    if (resultFile == NULL) {
        printf("Result file does not exist or could not be opened.\n");
        return;
    }

    // Check if the student file exists
    FILE *studentFile = fopen("Storage/student.txt", "r");
    if (studentFile == NULL) {
        printf("Student file does not exist or could not be opened.\n");
        fclose(resultFile);
        return;
    }

    int found = 0; // Flag to indicate if the ID was found
    int studentId;
    struct Result result;

    // Read data from the result file
    while (fscanf(resultFile, "%d", &studentId) == 1) {
        if (studentId == id) {
            // Found the matching ID
            result.studentId = studentId;
            for (int i = 0; i < MAX_SUBJECTS; i++) {
                fscanf(resultFile, "%lf", &result.marks[i]);
            }
            fscanf(resultFile, "%lf %lf", &result.totalMarks, &result.gpa);

            // Read the student name from student.txt
            char studentName[50];
            while (fscanf(studentFile, "%s", studentName) == 1) {
                fscanf(studentFile, "%*s %*s %*s %*s %d", &studentId);
                if (studentId == id) {
                    break;
                }
            }

            found = 1; // ID found

            // Print the result details with larger and centered borders
            printf("+--------------------------------------------+\n");
            printf("|                Student Results             |\n");
            printf("+--------------------------------------------+\n");
            printf("| Student Name: %-29s|\n", studentName);
            printf("| Student ID  : %-29d|\n", result.studentId);
            printf("+-------------------+------------------------+\n");
            printf("| Subject           | Marks                  |\n");
            printf("+-------------------+------------------------+\n");
            for (int i = 0; i < MAX_SUBJECTS; i++) {
                printf("| %-17s | %-12.2f           |\n", subjectNames[i], result.marks[i]);
            }
             printf("+-------------------+------------------------+\n");
            printf("| Total Marks       | %-12.2f           |\n", result.totalMarks);
            printf("+-------------------+------------------------+\n");
            printf("| GPA               | %-12.2f           |\n", result.gpa);
            printf("+--------------------------------------------+\n");
            printf("\n");
            break; // No need to continue searching
        }

        // Skip the rest of the line in result.txt
        while (fgetc(resultFile) != '\n') {
            if (feof(resultFile)) {
                break;
            }
        }
    }

    fclose(resultFile);
    fclose(studentFile);

    if (!found) {
        printf("Student with ID %d not found in results.\n", id);
    }
}
void editResult() {
    system("cls");
    int id;
    printf("Enter the student ID to edit results: ");
    scanf("%d", &id);

    // Check if the result file exists
    FILE *file = fopen("Storage/result.txt", "r");
    if (file == NULL) {
        printf("Result file does not exist or could not be opened.\n");
        return;
    }

    // Create a temporary file to store edited results
    FILE *tempFile = fopen("Storage/temp_result.txt", "w");
    if (tempFile == NULL) {
        fclose(file);
        printf("Error creating temporary file.\n");
        return;
    }

    int found = 0; // Flag to indicate if the ID was found
    int studentId;
    struct Result result;

    // Read data from the result file, edit the result if found
    while (fscanf(file, "%d", &studentId) == 1) {
        if (studentId == id) {
            // Found the matching ID
            result.studentId = studentId;
            for (int i = 0; i < MAX_SUBJECTS; i++) {
                fscanf(file, "%lf", &result.marks[i]);
            }
            fscanf(file, "%lf %lf", &result.totalMarks, &result.gpa);

            // Edit marks
            printf("Editing marks for Student ID: %d\n", result.studentId);
            for (int i = 0; i < MAX_SUBJECTS; i++) {
                printf("Enter new marks for %s: ", subjectNames[i]);
                scanf("%lf", &result.marks[i]);
                while (result.marks[i] < 0 || result.marks[i] > 100) {
                    printf("Marks must be between 0 and 100. Please re-enter marks for %s: ", subjectNames[i]);
                    scanf("%lf", &result.marks[i]);
                }
            }

            // Recalculate total marks and GPA
            result.totalMarks = 0.0;
            for (int i = 0; i < MAX_SUBJECTS; i++) {
                result.totalMarks += result.marks[i];
            }
            result.gpa = (result.totalMarks / 500.0 * 100.0) / 25.0;

            fprintf(tempFile, "%d ", result.studentId);
            for (int i = 0; i < MAX_SUBJECTS; i++) {
                fprintf(tempFile, "%.2f ", result.marks[i]);
            }
            fprintf(tempFile, "%.2f %.2f\n", result.totalMarks, result.gpa);

            found = 1; // ID found, edited, and written to temp file
        } else {
            // Copy the non-matching result to the temp file
            fprintf(tempFile, "%d ", studentId);
            for (int i = 0; i < MAX_SUBJECTS; i++) {
                double marks;
                fscanf(file, "%lf", &marks);
                fprintf(tempFile, "%.2f ", marks);
            }
            double totalMarks, gpa;
            fscanf(file, "%lf %lf", &totalMarks, &gpa);
            fprintf(tempFile, "%.2f %.2f\n", totalMarks, gpa);
        }

        // Skip the rest of the line
        while (fgetc(file) != '\n') {
            if (feof(file)) {
                break;
            }
        }
    }

    fclose(file);
    fclose(tempFile);

    if (!found) {
        printf("Student with ID %d not found in results.\n", id);
    } else {
        // Replace the original result file with the temp file
        remove("Storage/result.txt");
        rename("Storage/temp_result.txt", "Storage/result.txt");

        printf("Result edited successfully.\n");
    }
}
void deleteResult() {
    system("cls");
    int id;
    printf("Enter the student ID to delete results: ");
    scanf("%d", &id);

    // Check if the result file exists
    FILE *file = fopen("Storage/result.txt", "r");
    if (file == NULL) {
        printf("Result file does not exist or could not be opened.\n");
        return;
    }

    // Create a temporary file to store results after deletion
    FILE *tempFile = fopen("Storage/temp_result.txt", "w");
    if (tempFile == NULL) {
        fclose(file);
        printf("Error creating temporary file.\n");
        return;
    }

    int found = 0; // Flag to indicate if the ID was found
    int studentId;
    struct Result result;

    // Read data from the result file, skip the result if found
    while (fscanf(file, "%d", &studentId) == 1) {
        if (studentId == id) {
            // Found the matching ID, skip this result
            found = 1; // ID found and skipped
        } else {
            // Copy the non-matching result to the temp file
            fprintf(tempFile, "%d ", studentId);
            for (int i = 0; i < MAX_SUBJECTS; i++) {
                double marks;
                fscanf(file, "%lf", &marks);
                fprintf(tempFile, "%.2f ", marks);
            }
            double totalMarks, gpa;
            fscanf(file, "%lf %lf", &totalMarks, &gpa);
            fprintf(tempFile, "%.2f %.2f\n", totalMarks, gpa);
        }

        // Skip the rest of the line
        while (fgetc(file) != '\n') {
            if (feof(file)) {
                break;
            }
        }
    }

    fclose(file);
    fclose(tempFile);

    if (!found) {
        printf("Student with ID %d not found in results.\n", id);
    } else {
        // Replace the original result file with the temp file
        remove("Storage/result.txt");
        rename("Storage/temp_result.txt", "Storage/result.txt");

        printf("Result deleted successfully.\n");
    }
}

//account settings 
void addAccount() {
    system("cls");
    struct Account newAccount;
    int studentId;
    int studentIdValid = 0;

    do {
        printf("Enter Student ID: ");
        scanf("%d", &studentId);

        if (!isStudentIdExists(studentId)) {
            printf("Error: Student ID does not exist. Please enter a valid ID.\n");
            getchar(); // Pause and wait for Enter
        } else if (!isStudentIdUniqueInAccountFile(studentId)) {
            printf("Error: Account already exists for Student ID %d.\n", studentId);
            getchar(); // Pause and wait for Enter
        } else {
            studentIdValid = 1;
        }
    } while (!studentIdValid);

    printf("Enter Fee Amount: ");
    scanf("%lf", &newAccount.feeAmount);
    newAccount.feePaid = 0;
    newAccount.studentId = studentId;

    FILE *accountFile = fopen("Storage/account.txt", "a");
    if (accountFile != NULL) {
        fprintf(accountFile, "%d %.2lf %.2lf\n", newAccount.studentId, newAccount.feeAmount, newAccount.feePaid);
        fclose(accountFile);
        printf("Account added successfully.\n");
    } else {
        printf("Error: Unable to open account file for writing.\n");
    }
}
void viewAccount() {
    system("cls");
    int studentId;
    printf("Enter Student ID: ");
    scanf("%d", &studentId);

    FILE *studentFile = fopen("Storage/student.txt", "r");
    if (studentFile != NULL) {
        struct Student student;
        int found = 0;

        while (fscanf(studentFile, "%s %s %s %s %d\n", student.name, student.fatherName, student.phoneNumber, student.faculty, &student.id) == 5) {
            if (student.id == studentId) {
                found = 1;
                break;
            }
        }

        fclose(studentFile);

        if (found) {
            FILE *accountFile = fopen("Storage/account.txt", "r");
            if (accountFile != NULL) {
                struct Account account;
                found = 0;

                while (fscanf(accountFile, "%d %lf %lf\n", &account.studentId, &account.feeAmount, &account.feePaid) == 3) {
                    if (account.studentId == studentId) {
                        found = 1;
                        double feeRemaining = account.feeAmount - account.feePaid;

                        printf("Account Details for Student ID %d:\n", studentId);
                        printf("Student Name: %s\n", student.name);
                        printf("Fee Paid: Rs %.2lf\n", account.feePaid);
                        printf("Total Fee: Rs %.2lf\n", account.feeAmount);
                        printf("Fee Remaining: Rs %.2lf\n", feeRemaining);

                        break;
                    }
                }

                fclose(accountFile);

                if (!found) {
                    printf("No account found for Student ID %d.\n", studentId);
                }
            } else {
                printf("Error: Unable to open account file for reading.\n");
            }
        } else {
            printf("Student with ID %d not found.\n", studentId);
        }
    } else {
        printf("Error: Unable to open student file for reading.\n");
    }
}
void deleteAccount() {
    system("cls");
    int studentId;
    printf("Enter Student ID: ");
    scanf("%d", &studentId);

    FILE *accountFile = fopen("Storage/account.txt", "r");
    if (accountFile != NULL) {
        FILE *tempFile = fopen("Storage/temp_account.txt", "w");
        if (tempFile != NULL) {
            struct Account account;
            int found = 0;

            while (fscanf(accountFile, "%d %lf %lf\n", &account.studentId, &account.feeAmount, &account.feePaid) == 3) {
                if (account.studentId == studentId) {
                    found = 1;
                } else {
                    fprintf(tempFile, "%d %.2lf %.2lf\n", account.studentId, account.feeAmount, account.feePaid);
                }
            }

            fclose(tempFile);
            fclose(accountFile);

            if (found) {
                if (remove("Storage/account.txt") != 0) {
                    printf("Error: Unable to delete the account file.\n");
                } else if (rename("Storage/temp_account.txt", "Storage/account.txt") != 0) {
                    printf("Error: Unable to update the account file.\n");
                } else {
                    printf("Account for Student ID %d deleted successfully.\n", studentId);
                }
            } else {
                printf("No account found for Student ID %d.\n", studentId);
            }
        } else {
            printf("Error: Unable to open temporary account file for writing.\n");
        }
    } else {
        printf("Error: Unable to open account file for reading.\n");
    }
}
void editAccount() {
    system("cls");
    int studentId;
    printf("Enter Student ID: ");
    scanf("%d", &studentId);

    FILE *accountFile = fopen("Storage/account.txt", "r");
    if (accountFile != NULL) {
        FILE *tempFile = fopen("Storage/temp_account.txt", "w");
        if (tempFile != NULL) {
            struct Account account;
            int found = 0;

            while (fscanf(accountFile, "%d %lf %lf\n", &account.studentId, &account.feeAmount, &account.feePaid) == 3) {
                if (account.studentId == studentId) {
                    found = 1;
                    printf("Enter New Total Fee: ");
                    scanf("%lf", &account.feeAmount);
                }

                fprintf(tempFile, "%d %.2lf %.2lf\n", account.studentId, account.feeAmount, account.feePaid);
            }

            fclose(tempFile);
            fclose(accountFile);

            if (found) {
                if (remove("Storage/account.txt") != 0) {
                    printf("Error: Unable to delete the account file.\n");
                } else if (rename("Storage/temp_account.txt", "Storage/account.txt") != 0) {
                    printf("Error: Unable to update the account file.\n");
                } else {
                    printf("Total fee for Student ID %d updated successfully.\n", studentId);
                }
            } else {
                printf("No account found for Student ID %d.\n", studentId);
            }
        } else {
            printf("Error: Unable to open temporary account file for writing.\n");
        }
    } else {
        printf("Error: Unable to open account file for reading.\n");
    }
}
void updateAccount() {
    system("cls");
    int studentId;
    printf("Enter Student ID: ");
    scanf("%d", &studentId);

    FILE *accountFile = fopen("Storage/account.txt", "r");
    if (accountFile != NULL) {
        FILE *tempFile = fopen("Storage/temp_account.txt", "w");
        if (tempFile != NULL) {
            struct Account account;
            int found = 0;

            while (fscanf(accountFile, "%d %lf %lf\n", &account.studentId, &account.feeAmount, &account.feePaid) == 3) {
                if (account.studentId == studentId) {
                    found = 1;
                    printf("Enter New Fee Paid: ");
                    scanf("%lf", &account.feePaid);
                }

                fprintf(tempFile, "%d %.2lf %.2lf\n", account.studentId, account.feeAmount, account.feePaid);
            }

            fclose(tempFile);
            fclose(accountFile);

            if (found) {
                if (remove("Storage/account.txt") != 0) {
                    printf("Error: Unable to delete the account file.\n");
                } else if (rename("Storage/temp_account.txt", "Storage/account.txt") != 0) {
                    printf("Error: Unable to update the account file.\n");
                } else {
                    printf("Account for Student ID %d updated successfully.\n", studentId);
                }
            } else {
                printf("No account found for Student ID %d.\n", studentId);
            }
        } else {
            printf("Error: Unable to open temporary account file for writing.\n");
        }
    } else {
        printf("Error: Unable to open account file for reading.\n");
    }
}

//handle settings
void handleStudent() {
    int choice;

    while (1) {
        system("cls");
        printf("\nKPS-system\n");
        printf("Student Menu\n");
        printf("1. Add Student\n");
        printf("2. View Student by ID\n");
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
                viewStudentById();
                break;
            case 3:
                deleteStudentById();
                break;
            case 4:
                editStudentById();
                break;
            case 5:
                return;
            default:
                printf("Invalid choice. Please select a valid option.\n");
        }

        printf("Press Enter to continue...");
        while (getchar() != '\n');
        getchar();
    }
}
void handleAccount() {
    int choice;

    while (1) {
        system("cls");
        printf("\nKPS-system\n");
        printf("Account Menu\n");
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
                return;
            default:
                printf("Invalid choice. Please select a valid option.\n");
        }

        printf("Press Enter to continue...");
        while (getchar() != '\n');
        getchar();
    }
}
void handleResult() {
    int choice;
  
    while (1) {
        system("cls");
        printf("\nKPS-system\n");
        printf("Result Menu\n");
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
                return;
            default:
                printf("Invalid choice. Please select a valid option.\n");
        }

        printf("Press Enter to continue...");
        while (getchar() != '\n');
        getchar();
    }
}
void handleInformation() {
    int choice;

    while (1) {
        system("cls");
        printf("Information Menu\n");
        printf("1. View All Students\n");
        printf("2. Delete Student Data\n");
        printf("3. Clear Result Data\n");
        printf("4. Clear Account Data\n");
        printf("5. Information Separation\n");
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
                return;
            default:
                printf("Invalid choice. Please select a valid option.\n");
        }

        printf("Press Enter to continue...");
        getchar();
        getchar();
    }
}

// Function to check username and password
int checkCredentials(char *username, char *password) {
    FILE *adminFile = fopen("Administration/admin.txt", "r");
    if (adminFile == NULL) {
        printf("Error: Unable to open admin file.\n");
        return 0;
    }

    char correctUsername[100];
    char correctPassword[100];

    if (fscanf(adminFile, "%s %s", correctUsername, correctPassword) != 2) {
        printf("Error: Invalid admin file format.\n");
        fclose(adminFile);
        return 0;
    }

    fclose(adminFile);

    return (strcmp(username, correctUsername) == 0 && strcmp(password, correctPassword) == 0);
}

//main function
int main() {
    char username[100];
    char password[100];
    int choice;

    printf("Enter Username: ");
    scanf("%s", username);
    printf("Enter Password: ");
    scanf("%s", password);

    if (checkCredentials(username, password)) {
        printf("\nAccess Granted. Welcome!\n");
        while (1) {
            system("cls");
            printf("\nKPS-system\n");
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
                    handleStudent();
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
                    printf("Invalid choice. Please select a valid option.\n");
            }

            printf("Press Enter to continue...");
            while (getchar() != '\n');
            getchar();
        }
    } else {
        printf("Access Denied. Invalid username or password.\n");
    }

    return 0;
}  


