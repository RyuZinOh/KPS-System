
# KPS-PROJECT: Student Data Management System

KPS-PROJECT is a versatile command-line program designed for efficient student data management. It empowers users to store, organize, and manipulate student records, academic results, and user accounts.

## Main ALgorithm

```Bash
# Main Program Algorithm

## Step 1: User Authentication

1. Prompt the user to enter a username and password.
2. Read the entered username and password from the standard input.

### Step 1.1: Check Credentials

3. Open the `admin.txt` file for reading.
4. If the file does not exist or cannot be opened, display an error message and exit.
5. Read the correct username and password from the file.

### Step 1.2: Compare Credentials

6. Compare the entered username and password with the correct credentials.
7. If the credentials match, proceed to the main menu. Otherwise, display an "Access Denied" message and exit.

## Step 2: Main Menu Loop

8. Enter an infinite loop for the main menu.
9. Display the following menu options:
   - Student
   - Account
   - Result
   - Information
   - Help
   - Exit
10. Accept the user's choice.

### Step 2.1: User Choice Handling

11. Based on the user's choice, execute the corresponding menu function or action:
    - If the user chooses "Student," go to the Student Menu.
    - If the user chooses "Account," go to the Account Menu.
    - If the user chooses "Result," go to the Result Menu.
    - If the user chooses "Information," go to the Information Menu.
    - If the user chooses "Help," display helpful information.
    - If the user chooses "Exit," exit the program.

### Step 2.2: Menu Continuation

12. After executing a menu option, prompt the user to press Enter to continue.
13. Clear the screen and return to the main menu loop.

## Step 3: Student Menu

14. Enter the Student Menu loop.
15. Display the following student-related options:
    - Add Student
    - View Student by ID
    - Delete Student by ID
    - Edit Student by ID
    - Back to Main Menu
16. Accept the user's choice.

### Step 3.1: User Choice Handling (Student Menu)

17. Based on the user's choice, execute the corresponding function or action:
    - If the user chooses "Add Student," execute the `addStudent` function.
    - If the user chooses "View Student by ID," execute the `viewStudentById` function.
    - If the user chooses "Delete Student by ID," execute the `deleteStudentById` function.
    - If the user chooses "Edit Student by ID," execute the `editStudentById` function.
    - If the user chooses "Back to Main Menu," return to the Main Menu.

### Step 3.2: Menu Continuation (Student Menu)

18. After executing a student menu option, prompt the user to press Enter to continue.
19. Clear the screen and return to the Student Menu loop.

## Step 4: Account Menu

20. Enter the Account Menu loop.
21. Display the following account-related options:
    - Add Account
    - View Account
    - Delete Account
    - Edit Account
    - Update Account
    - Back to Main Menu
22. Accept the user's choice.

### Step 4.1: User Choice Handling (Account Menu)

23. Based on the user's choice, execute the corresponding function or action:
    - If the user chooses "Add Account," execute the `addAccount` function.
    - If the user chooses "View Account," execute the `viewAccount` function.
    - If the user chooses "Delete Account," execute the `deleteAccount` function.
    - If the user chooses "Edit Account," execute the `editAccount` function.
    - If the user chooses "Update Account," execute the `updateAccount` function.
    - If the user chooses "Back to Main Menu," return to the Main Menu.

### Step 4.2: Menu Continuation (Account Menu)

24. After executing an account menu option, prompt the user to press Enter to continue.
25. Clear the screen and return to the Account Menu loop.

## Step 5: Result Menu

26. Enter the Result Menu loop.
27. Display the following result-related options:
    - Add Result
    - View Result
    - Delete Result
    - Edit Result
    - Back to Main Menu
28. Accept the user's choice.

### Step 5.1: User Choice Handling (Result Menu)

29. Based on the user's choice, execute the corresponding function or action:
    - If the user chooses "Add Result," execute the `addResult` function.
    - If the user chooses "View Result," execute the `viewResult` function.
    - If the user chooses "Delete Result," execute the `deleteResult` function.
    - If the user chooses "Edit Result," execute the `editResult` function.
    - If the user chooses "Back to Main Menu," return to the Main Menu.

### Step 5.2: Menu Continuation (Result Menu)

30. After executing a result menu option, prompt the user to press Enter to continue.
31. Clear the screen and return to the Result Menu loop.

## Step 6: Information Menu

32. Enter the Information Menu loop.
33. Display the following information-related options:
    - View All Students
    - Delete Student Data
    - Clear Result Data
    - Clear Account Data
    - Information Separation
    - Back to Main Menu
34. Accept the user's choice.

### Step 6.1: User Choice Handling (Information Menu)

35. Based on the user's choice, execute the corresponding function or action:
    - If the user chooses "View All Students," execute the `viewAllStudents` function.
    - If the user chooses "Delete Student Data," execute the `deleteStudentData` function.
    - If the user chooses "Clear Result Data," execute the `clearResultData` function.
    - If the user chooses "Clear Account Data," execute the `clearAccountData` function.
    - If the user chooses "Information Separation," execute the `infoSeparation` function.
    - If the user chooses "Back to Main Menu," return to the Main Menu.

### Step 6.2: Menu Continuation (Information Menu)

36. After executing an information menu option, prompt the user to press Enter to continue.
37. Clear the screen and return to the Information Menu loop.

```
## Prerequisites

Before using KPS-PROJECT, ensure you have the following prerequisites installed:

- **C Compiler:** You'll need a C compiler like GCC.
- **Terminal or Command Prompt:** A terminal or command prompt for running the program.

## Getting Started

Follow these steps to set up and run KPS-PROJECT on your system:

1. **Clone the Repository:** Clone this repository to your local machine.

   ```shell
   git clone https://github.com/your-username/KPS-PROJECT.git
   ```

2. **Navigate to the Project Directory:** Use the `cd` command to navigate to the project directory.

   ```shell
   cd KPS-PROJECT
   ```

3. **Compile the Program:** Compile the source code to create the executable.

   ```shell
   gcc main.c -o kps_project
   ```

4. **Run the Program:** Execute the program.

   ```shell
   ./main.exe or ./main.out
   ```

## Usage

KPS-PROJECT offers a user-friendly interface with multiple options for managing student data. Here's how to get the most out of the program:

- **Main Menu:** Upon running the program, you'll see a main menu with various options. Choose an option by entering the corresponding number.
- **Help Command:** In the main menu, use the `hhelp` command to access helpful tips and tricks for using the program efficiently.

## Main Menu Options

| Option | Description |
| ------ | ----------- |
| **1. Manage Student Data** | Access student data management features such as adding, viewing, and editing student records. |
| **2. Manage Academic Results** | Perform actions related to academic results, including adding, viewing, editing, and deleting. |
| **3. Account Management** | Create, manage, and secure user accounts. |
| **4. Information Separation** | Find and count students based on their faculty. |
| **5. Exit** | Quit the program. |

## Tips and Tricks

Here are some tips to make the most of KPS-PROJECT:

- To view all student records, select the "Manage Student Data" option and then choose "View All Students."
- Use the "Information Separation" feature to find students belonging to a specific faculty.
- Maintain data security by clearing account data when needed using the "Account Management" menu.

## License

This project is licensed under the MIT License. For more details, see the [LICENSE](LICENSE) file.

## Contributing

Contributions are welcome! Please feel free to open an issue or submit a pull request.

## Contact

If you have questions or need assistance, please contact [Safal Lama](safalisgod@gmail.com).

