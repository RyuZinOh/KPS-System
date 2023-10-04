
# KPS-PROJECT: Student Data Management System

KPS-PROJECT is a versatile command-line program designed for efficient student data management. It empowers users to store, organize, and manipulate student records, academic results, and user accounts.

## Main ALgorithm
```bash
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
    - If the user chooses "Student," go to the Student Menu (`handleStudent` function).
    - If the user chooses "Account," go to the Account Menu (`handleAccount` function).
    - If the user chooses "Result," go to the Result Menu (`handleResult` function).
    - If the user chooses "Information," go to the Information Menu (`handleInformation` function).
    - If the user chooses "Help," display helpful information.
    - If the user chooses "Exit," exit the program.

### Step 2.2: Menu Continuation

12. After executing a menu option, prompt the user to press Enter to continue.
13. Clear the screen and return to the main menu loop.

## Step 3: Student Menu (`handleStudent` function)

14. Enter the Student Menu loop.
15. Display the following student-related options:
    - Add Student (`addStudent` function)
    - View Student by ID (`viewStudentById` function)
    - Delete Student by ID (`deleteStudentById` function)
    - Edit Student by ID (`editStudentById` function)
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

## Step 4: Account Menu (`handleAccount` function)

20. Enter the Account Menu loop.
21. Display the following account-related options:
    - Add Account (`addAccount` function)
    - View Account (`viewAccount` function)
    - Delete Account (`deleteAccount` function)
    - Edit Account (`editAccount` function)
    - Update Account (`updateAccount` function)
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

## Step 5: Result Menu (`handleResult` function)

26. Enter the Result Menu loop.
27. Display the following result-related options:
    - Add Result (`addResult` function)
    - View Result (`viewResult` function)
    - Delete Result (`deleteResult` function)
    - Edit Result (`editResult` function)
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

## Step 6: Information Menu (`handleInformation` function)

32. Enter the Information Menu loop.
33. Display the following information-related options:
    - View All Students (`viewAllStudents` function)
    - Delete Student Data (`deleteStudentData` function)
    - Clear Result Data (`clearResultData` function)
    - Clear Account Data (`clearAccountData` function)
    - Information Separation (`infoSeparation` function)
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


## License

This project is licensed under the MIT License. For more details, see the [LICENSE](LICENSE) file.

## Contributing

Contributions are welcome! Please feel free to open an issue or submit a pull request.

## Contact

If you have questions or need assistance, please contact [Safal Lama](safalisgod@gmail.com).

