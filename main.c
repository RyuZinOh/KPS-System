#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_STUDENTS 100
#define MAX_SUBJECTS 5
#define MAX_ATTEMPTS 5

struct userAccount {
    char username[100];
    char password[100];
    char securityAnswer[100];
};

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
char* subjectNames[] = {"Nepali", "English", "Math", "Science", "Computer"};

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

//shortcut 
void easy(){
    printf("Press Enter to continue...");
    while (getchar() != '\n');
    getchar();
}

//important checks
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
    int studentId;
    struct Student student;

    while (1) {
        system("cls");

        printf("Enter Student ID: ");
        scanf("%d", &studentId);

        if (isStudentIdExists(studentId)) {
            printf("Student with ID %d already exists.\n", studentId);
        } else {
            student.id = studentId;

            printf("Enter Name: ");
            scanf("%s", student.name);
            printf("Enter Father's Name: ");
            scanf("%s", student.fatherName);
            printf("Enter Phone Number: ");
            scanf("%s", student.phoneNumber);
            printf("Enter Faculty: ");
            scanf("%s", student.faculty);

            FILE *file = fopen("Storage/student.txt", "a");

            if (file != NULL) {
                fprintf(file, "%s %s %s %s %d\n", student.name, student.fatherName, student.phoneNumber, student.faculty, student.id);
                fclose(file);
                printf("Student record added successfully.\n");
                sleep(1);
            } else {
                printf("Error: Unable to open file for appending.\n");
                sleep(1);
            }
        }

        char choice;
        printf("Do you want to add another student? (Y/N): ");
        scanf(" %c", &choice);

        if (choice != 'Y' && choice != 'y') {
            break;
        }
    }
}
void viewStudentById() {
    system("cls");
    int studentId;
    printf("Enter Student ID: ");
    scanf("%d", &studentId);

    FILE *file = fopen("Storage/student.txt", "r");

    if (file != NULL) {
        struct Student student;
        int found = 0;

        while (fscanf(file, "%s %s %s %s %d\n", student.name, student.fatherName, student.phoneNumber, student.faculty, &student.id) == 5) {
            if (student.id == studentId) {
                found = 1;

                printf("--------------------------------\n");
                printf("Viewing Student ID: %d\n", student.id);
                printf("--------------------------------\n");
                printf("Name: %s\n", student.name);
                printf("Father's Name: %s\n", student.fatherName);
                printf("Phone Number: %s\n", student.phoneNumber);
                printf("Faculty: %s\n", student.faculty);
                printf("--------------------------------\n");
                break;
            }
        }

        fclose(file);

        if (!found) {
            printf("Student with ID %d not found.\n", studentId);
            sleep(1); 
        }
    } else {
        printf("Error: Unable to open file for reading.\n");
        sleep(1); 
    }
}
void editStudentById() {
    system("cls");
    int studentId;
    printf("Enter Student ID to edit: ");
    scanf("%d", &studentId);

    FILE *file = fopen("Storage/student.txt", "r+");

    if (file != NULL) {
        struct Student student;
        int found = 0;

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

        remove("Storage/student.txt");
        rename("Storage/student_temp.txt", "Storage/student.txt");

        if (!found) {
            printf("Student with ID %d not found.\n", studentId);
            sleep(1);
        } else {
            printf("Student record updated successfully.\n");
            sleep(1);
        }
    } else {
        printf("Error: Unable to open file for reading and writing.\n");
        sleep(1);
    }
}
void deleteStudentById() {
    system("cls");
    int studentId;
    printf("Enter Student ID to delete: ");
    scanf("%d", &studentId);

    FILE *file = fopen("Storage/student.txt", "r+");

    if (file != NULL) {
        struct Student student;
        int found = 0;

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

        remove("Storage/student.txt");
        rename("Storage/student_temp.txt", "Storage/student.txt");

        if (!found) {
            printf("Student with ID %d not found.\n", studentId);
            sleep(1);
        } else {
            printf("Student record deleted successfully.\n");
            sleep(1);
        }
    } else {
        printf("Error: Unable to open file for reading and writing.\n");
        sleep(1);
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
            sleep(1);
        } else {
            printf("Error: Unable to open result file for clearing data.\n");
            sleep(1);
        }
    } else {
        printf("Clearing result data canceled.\n");
        sleep(1);
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
            sleep(1);
        } else {
            printf("Error: Unable to open account file for writing.\n");
            sleep(1);
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
        int studentCount = 0;
        struct Student students[100]; // Adjust the array size as needed

        struct Student student;
        while (fscanf(file, "%49s %49s %14s %49s %d\n", student.name, student.fatherName, student.phoneNumber, student.faculty, &student.id) == 5) {
            if (studentCount < 100) { // Ensure we don't exceed the array size
                students[studentCount++] = student;
            }
        }
        fclose(file);

        qsort(students, studentCount, sizeof(struct Student), (int (*)(const void *, const void *))compareIntegers);

        // Print the table header
        printf("+----------------------+----------------------+----------------------+----------------------+----------+\n");
        printf("| %-20s | %-20s | %-20s | %-20s | %-8s |\n", "Name", "Father's Name", "Phone Number", "Faculty", "ID");
        printf("+----------------------+----------------------+----------------------+----------------------+----------+\n");

        // Print student data
        for (int i = 0; i < studentCount; i++) {
            printf("| %-20s | %-20s | %-20s | %-20s | %-8d |\n", students[i].name, students[i].fatherName, students[i].phoneNumber, students[i].faculty, students[i].id);
        }

        // Print the table footer
        printf("+----------------------+----------------------+----------------------+----------------------+----------+\n");
    } else {
        printf("Error: Unable to open file for reading.\n");
        sleep(1);
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
            sleep(1);
        } else {
            printf("Error: Unable to open file for clearing student data.\n");
            sleep(1);
        }
    } else {
        printf("Clearing student data canceled.\n");
        sleep(1);
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
            if (strcasecmp(student.faculty, faculty) == 0) {
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
            sleep(1);
        }
    } else {
        printf("Error: Unable to open file for reading.\n");
        sleep(1);
    }
}

//result settings
void addResult() {
    while (1) {
        system("cls");
        struct Result result;

        printf("Enter student ID: ");
        scanf("%d", &result.studentId);

        if (!isStudentIdExists(result.studentId)) {
            printf("Student with ID %d does not exist.\n", result.studentId);
            sleep(1);
            break;
        }

        FILE *file = fopen("Storage/result.txt", "a");
        if (file == NULL) {
            printf("Result file does not exist or could not be opened.\n");
            sleep(1);
            break;
        }

        if (isResultIdExists(result.studentId)) {
            printf("Result for student ID %d already exists.\n", result.studentId);
            sleep(1);
            fclose(file);
            break;
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

        result.totalMarks = 0.0;
        for (int i = 0; i < MAX_SUBJECTS; i++) {
            result.totalMarks += result.marks[i];
        }

        result.gpa = (result.totalMarks / (MAX_SUBJECTS * 100.0)) * 4.0;

        fprintf(file, "%d ", result.studentId);
        for (int i = 0; i < MAX_SUBJECTS; i++) {
            fprintf(file, "%.2f ", result.marks[i]);
        }
        fprintf(file, "%.2f %.2f\n", result.totalMarks, result.gpa);

        fclose(file);

        printf("Result added successfully.\n");
        sleep(1);

        char choice;
        printf("Do you want to add another result? (Y/N): ");
        scanf(" %c", &choice);

        if (choice != 'Y' && choice != 'y') {
            break;
        }
    }
}
void viewResult() {
    system("cls");
    int id;
    printf("Enter the student ID to view results: ");
    scanf("%d", &id);

    FILE *resultFile = fopen("Storage/result.txt", "r");
    if (resultFile == NULL) {
        printf("Result file does not exist or could not be opened.\n");
        sleep(1);
        return;
    }

    FILE *studentFile = fopen("Storage/student.txt", "r");
    if (studentFile == NULL) {
        printf("Student file does not exist or could not be opened.\n");
        sleep(1);
        fclose(resultFile);
        return;
    }

    int found = 0;
    int studentId;
    struct Result result;

    while (fscanf(resultFile, "%d", &studentId) == 1) {
        if (studentId == id) {
            result.studentId = studentId;
            for (int i = 0; i < MAX_SUBJECTS; i++) {
                fscanf(resultFile, "%lf", &result.marks[i]);
            }
            fscanf(resultFile, "%lf %lf", &result.totalMarks, &result.gpa);

            char studentName[50];
            while (fscanf(studentFile, "%s", studentName) == 1) {
                fscanf(studentFile, "%*s %*s %*s %*s %d", &studentId);
                if (studentId == id) {
                    break;
                }
            }

            found = 1;

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
            break;
        }

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
        sleep(1);
    }
}
void editResult() {
    system("cls");
    int id;
    printf("Enter the student ID to edit results: ");
    scanf("%d", &id);

    FILE *file = fopen("Storage/result.txt", "r");
    if (file == NULL) {
        printf("Result file does not exist or could not be opened.\n");
        sleep(1);
        return;
    }

    FILE *tempFile = fopen("Storage/temp_result.txt", "w");
    if (tempFile == NULL) {
        fclose(file);
        printf("Error creating temporary file.\n");
        sleep(1);
        return;
    }

    int found = 0;
    int studentId;
    struct Result result;

    while (fscanf(file, "%d", &studentId) == 1) {
        if (studentId == id) {
            result.studentId = studentId;
            for (int i = 0; i < MAX_SUBJECTS; i++) {
                fscanf(file, "%lf", &result.marks[i]);
            }
            fscanf(file, "%lf %lf", &result.totalMarks, &result.gpa);

            printf("Editing marks for Student ID: %d\n", result.studentId);
            for (int i = 0; i < MAX_SUBJECTS; i++) {
                printf("Enter new marks for %s: ", subjectNames[i]);
                scanf("%lf", &result.marks[i]);
                while (result.marks[i] < 0 || result.marks[i] > 100) {
                    printf("Marks must be between 0 and 100. Please re-enter marks for %s: ", subjectNames[i]);
                    scanf("%lf", &result.marks[i]);
                }
            }

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

            found = 1;
        } else {
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
        remove("Storage/result.txt");
        rename("Storage/temp_result.txt", "Storage/result.txt");

        printf("Result edited successfully.\n");
        sleep(1);
    }
}
void deleteResult() {
    system("cls");
    int id;
    printf("Enter the student ID to delete results: ");
    scanf("%d", &id);

    FILE *file = fopen("Storage/result.txt", "r");
    if (file == NULL) {
        printf("Result file does not exist or could not be opened.\n");
        sleep(1);
        return;
    }

    FILE *tempFile = fopen("Storage/temp_result.txt", "w");
    if (tempFile == NULL) {
        fclose(file);
        printf("Error creating temporary file.\n");
        sleep(1);
        return;
    }

    int found = 0;
    int studentId;
    struct Result result;

    while (fscanf(file, "%d", &studentId) == 1) {
        if (studentId == id) {
            found = 1;
        } else {
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
        sleep(1);
    } else {
        remove("Storage/result.txt");
        rename("Storage/temp_result.txt", "Storage/result.txt");

        printf("Result deleted successfully.\n");
        sleep(1);
    }
}

//account settings 
void addAccount() {
    while (1) {
        system("cls");
        struct Account newAccount;
        int studentId;
        int studentIdValid = 0;

        do {
            printf("Enter Student ID: ");
            scanf("%d", &studentId);

            if (!isStudentIdExists(studentId)) {
                printf("Error: Student ID does not exist. Please enter a valid ID.\n");
                getchar();
            } else if (!isStudentIdUniqueInAccountFile(studentId)) {
                printf("Error: Account already exists for Student ID %d.\n", studentId);
                getchar();
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
            sleep(1);
        } else {
            printf("Error: Unable to open account file for writing.\n");
            sleep(1);
        }

        char choice;
        printf("Do you want to add another account? (Y/N): ");
        scanf(" %c", &choice);

        if (choice != 'Y' && choice != 'y') {
            break;
        }
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
        int foundStudent = 0;

        while (fscanf(studentFile, "%s %s %s %s %d\n", student.name, student.fatherName, student.phoneNumber, student.faculty, &student.id) == 5) {
            if (student.id == studentId) {
                foundStudent = 1;
                break;
            }
        }

        fclose(studentFile);

        if (foundStudent) {
            FILE *accountFile = fopen("Storage/account.txt", "r");
            if (accountFile != NULL) {
                struct Account account;
                int foundAccount = 0;

                while (fscanf(accountFile, "%d %lf %lf\n", &account.studentId, &account.feeAmount, &account.feePaid) == 3) {
                    if (account.studentId == studentId) {
                        foundAccount = 1;
                        double feeRemaining = account.feeAmount - account.feePaid;

                        printf("--------------------------------------\n");
                        printf("            Account Details           \n");
                        printf("--------------------------------------\n");
                        printf(" Student ID: %d\n", studentId);
                        printf(" Student Name: %s\n", student.name);
                        printf(" Fee Paid: Rs %lf           \n", account.feePaid);
                        printf(" Total Fee: Rs %lf          \n", account.feeAmount);
                        printf(" Fee Remaining: Rs %lf      \n", feeRemaining);
                        printf("--------------------------------------\n");
                        printf("\n");

                        break;
                    }
                }

                fclose(accountFile);

                if (!foundAccount) {
                    printf("No account found for Student ID %d.\n", studentId);
                    sleep(1); 
                }
            } else {
                printf("Error: Unable to open account file for reading.\n");
                sleep(1); 
            }
        } else {
            printf("Student with ID %d not found.\n", studentId);
            sleep(1); 
        }
    } else {
        printf("Error: Unable to open student file for reading.\n");
        sleep(1); 
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
                    sleep(1);
                } else if (rename("Storage/temp_account.txt", "Storage/account.txt") != 0) {
                    printf("Error: Unable to update the account file.\n");
                    sleep(1);
                } else {
                    printf("Account for Student ID %d deleted successfully.\n", studentId);
                    sleep(1);
                }
            } else {
                printf("No account found for Student ID %d.\n", studentId);
                sleep(1);
            }
        } else {
            printf("Error: Unable to open temporary account file for writing.\n");
            sleep(1);
        }
    } else {
        printf("Error: Unable to open account file for reading.\n");
        sleep(1);
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
                    sleep(1);
                } else if (rename("Storage/temp_account.txt", "Storage/account.txt") != 0) {
                    printf("Error: Unable to update the account file.\n");
                    sleep(1);
                } else {
                    printf("Total fee for Student ID %d updated successfully.\n", studentId);
                    sleep(1);
                }
            } else {
                printf("No account found for Student ID %d.\n", studentId);
                sleep(1);
            }
        } else {
            printf("Error: Unable to open temporary account file for writing.\n");
            sleep(1);
        }
    } else {
        printf("Error: Unable to open account file for reading.\n");
        sleep(1);
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
                    sleep(1);
                } else if (rename("Storage/temp_account.txt", "Storage/account.txt") != 0) {
                    printf("Error: Unable to update the account file.\n");
                    sleep(1);
                } else {
                    printf("Account for Student ID %d updated successfully.\n", studentId);
                    sleep(1);
                }
            } else {
                printf("No account found for Student ID %d.\n", studentId);
                sleep(1);
            }
        } else {
            printf("Error: Unable to open temporary account file for writing.\n");
            sleep(1);
        }
    } else {
        printf("Error: Unable to open account file for reading.\n");
        sleep(1);
    }
}

//handle settings
void handleStudent() {
    int choice;

    while (1) {
        system("cls");
        printf("---------------------------------\n");
        printf("   KPS-system - Student Menu\n");
        printf("---------------------------------\n");
        printf("1. Add Student\n");
        printf("2. View Student by ID\n");
        printf("3. Delete Student by ID\n");
        printf("4. Edit Student by ID\n");
        printf("5. Back to Main Menu\n");
        printf("---------------------------------\n");  
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
                sleep(1);
        }
        easy();
    }
}
void handleAccount() {
    int choice;

    while (1) {
        system("cls");
        printf("---------------------------------\n");
        printf("   KPS-system - Account Menu\n");
        printf("---------------------------------\n");
        printf("1. Add Account\n");
        printf("2. View Account\n");
        printf("3. Delete Account\n");
        printf("4. Edit Account\n");
        printf("5. Update Account\n");
        printf("6. Back to Main Menu\n");
        printf("---------------------------------\n");
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
       easy();
    }
}
void handleResult() {
    int choice;
  
    while (1) {
        system("cls");
        printf("---------------------------------\n");
        printf("   KPS-system - Result Menu\n");
        printf("---------------------------------\n");
        printf("1. Add Result\n");
        printf("2. View Result\n");
        printf("3. Delete Result\n");
        printf("4. Edit Result\n");
        printf("5. Back to Main Menu\n");
        printf("---------------------------------\n");
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

     void easy();   
    }
}
void handleInformation() {
    int choice;

    while (1) {
        system("cls");
        printf("---------------------------------\n");
        printf("   KPS-system - Information Menu\n");
        printf("---------------------------------\n");
        printf("1. View All Students\n");
        printf("2. Delete Student Data\n");
        printf("3. Clear Result Data\n");
        printf("4. Clear Account Data\n");
        printf("5. Information Separation\n");
        printf("6. Back to Main Menu\n");
        printf("---------------------------------\n");
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
void mainMenu() {
    int choice;

    while (1) {
        system("cls");
        FILE *menuFile = fopen("UI/main.txt", "r");
        if (menuFile == NULL) {
            printf("Error opening the menu file.\n");
            sleep(1);
            return;
        }

        char line[256];
        while (fgets(line, sizeof(line), menuFile)) {
            printf("%s", line);
        }

        fclose(menuFile);

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
                sleep(1);
                exit(0);
            default:
                printf("Invalid choice. Please select a valid option.\n");
                sleep(1);
        }
     easy();
    }
}

//login panel settings 
int isUsernameTaken(char *username) {
    FILE *file = fopen("Administration/admin.txt", "r");
    if (file == NULL) {
        return 0;
    }

    char line[300];
    while (fgets(line, sizeof(line), file)) {
        char savedUsername[100];
        sscanf(line, "%s", savedUsername);
        if (strcmp(savedUsername, username) == 0) {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}
int containsUppercase(char *str) {
    for (int i = 0; str[i]; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            return 1;  // Uppercase character found
        }
    }
    return 0;  // No uppercase characters found
}
void resetPassword() {
    system("cls");
    struct userAccount user;
    char enteredUsername[100];
    char enteredSecurityAnswer[100];

    printf("Password Reset\n");
    printf("Enter your username: ");
    scanf("%s", enteredUsername);

    if (!isUsernameTaken(enteredUsername)) {
        printf("Username not found. Password reset failed.\n");
        sleep(1);
        return;
    }

    FILE *file = fopen("Administration/admin.txt", "r+");
    if (file == NULL) {
        printf("Error opening the file.\n");
        sleep(1);
        return;
    }

    int found = 0;
    while (fscanf(file, "%s %s %s", user.username, user.password, user.securityAnswer) != EOF) {
        if (strcmp(enteredUsername, user.username) == 0) {
            found = 1;
            break;
        }
    }

    if (found) {
        printf("Security Question: What is your favorite anime? ");
        scanf("%s", enteredSecurityAnswer);

        if (strcasecmp(enteredSecurityAnswer, user.securityAnswer) == 0) {
            printf("Security answer is correct. Please enter a new password: ");
            scanf("%s", user.password);

            // Rewind the file to the beginning
            rewind(file);

            // Update the password in the file
            fprintf(file, "%s %s %s\n", user.username, user.password, user.securityAnswer);

            printf("Password has been reset successfully.\n");
            sleep(1);
        } else {
            printf("Security answer is incorrect. Password reset failed.\n");
            sleep(1);
        }
    } else {
        printf("Username not found. Password reset failed.\n");
        sleep(1);
    }

    fclose(file);
}

//login main panel settings
void signUp() {
    system("cls");
    struct userAccount newUser;

    printf("Sign Up\n------------\n");

    do {
        printf("Enter a username :");
        scanf("%s", newUser.username);

        if (containsUppercase(newUser.username)) {
            printf("Error: Username must be in lowercase only. Please enter a valid username.\n");
        } else if (isUsernameTaken(newUser.username)) {
            printf("Error: Username already exists. Please choose a different username.\n");
        }
    } while (isUsernameTaken(newUser.username) || containsUppercase(newUser.username));

    printf("Enter a password :");
    scanf("%s", newUser.password);

    printf("What is your favorite anime? ");
    scanf("%s", newUser.securityAnswer);

    FILE *file = fopen("Administration/admin.txt", "a");
    if (file == NULL) {
        printf("Error opening the file.\n");
        sleep(1);
        return;
    }

    fprintf(file, "%s %s %s\n", newUser.username, newUser.password, newUser.securityAnswer);
    fclose(file);

    printf("Account created successfully.\n");
    sleep(1);
}
void signIn() {
    system("cls");
    struct userAccount user;
    char enteredUsername[100];
    char enteredPassword[100];
    int attempts = 0;

    printf("Sign In\n");
    printf("------------\n");

    while (attempts < MAX_ATTEMPTS) {
        printf("Enter your username: ");
        scanf("%s", enteredUsername);
        printf("Enter your password: ");
        scanf("%s", enteredPassword);

        FILE *file = fopen("Administration/admin.txt", "r");
        if (file == NULL) {
            printf("Error opening the file.\n");
            sleep(1);
            return;
        }

        int found = 0;
        while (fscanf(file, "%s %s %s", user.username, user.password, user.securityAnswer) != EOF) {
            if (strcasecmp(enteredUsername, user.username) == 0 && strcmp(enteredPassword, user.password) == 0) {
                found = 1;
                break;
            }
        }

        fclose(file);

        if (found) {
            printf("Sign-in successful. Welcome, %s!\n", user.username);
            sleep(1); 
            mainMenu();
            return;
        } else {
            printf("Invalid username or password. Please try again.\n");
            attempts++;
            if (attempts >= MAX_ATTEMPTS) {
                printf("You've exceeded the maximum number of sign-in attempts.\n");
                sleep(1);
                resetPassword(&user);
            }
        }
    }
}

//main function 
int main() {
    int choice;

    while (1) {
        system("cls"); // For Windows. Use "clear" for Linux/Mac.
        printf("*********************************************\n");
        printf("*                Login Panel                *\n");
        printf("*********************************************\n");
        printf("*                                           *\n");
        printf("* 1. Sign In (Already have an account?)     *\n");
        printf("* 2. Sign Up (Don't have an account?)       *\n");
        printf("* 3. Exit                                   *\n");
        printf("*                                           *\n");
        printf("*********************************************\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                signIn();
                break;
            case 2:
                signUp();
                break;
            case 3:
                printf("Exiting program.\n");
                sleep(1);
                exit(0);
            default:
                printf("Invalid choice. Please select a valid option.\n");
                sleep(1);
        }
    }

    return 0;
}