# Bank Management System Using C++

A console-based C++ application for managing bank clients, user accounts, and account transactions using text files for persistent storage.

## Overview

This project simulates a small bank management system that works through the terminal. It allows an authorized user to log in, manage client records, perform deposit and withdrawal operations, view total balances, and manage system users with permission-based access.

The program stores its data in:

- `client.txt` for client records
- `users.txt` for system users

## Features

- Login screen with username and password
- Client management
- Add new client
- List all clients
- Find client by account number
- Update client data
- Delete client
- Transactions
- Deposit money
- Withdraw money
- Show total balances of all clients
- User management
- List users
- Add new user
- Find user
- Update user
- Delete user
- Permission system using bitmask values

## Project Structure

```text

├── main.cpp
├── client.txt
├── users.txt
└── README.md
```

## Data Format

Both data files use the separator `#//#`.

### Client Record Format

```text
AccountNumber#//#PinCode#//#Name#//#Phone#//#Balance


### User Record Format

```text
Username#//#Password#//#Permission

## Sample Output

This is a real example of the current program flow after a successful login:

```text
----------------------------------------------
                Login Screen
---------------------------------------------
Enter User Name:
Enter Password:

===============================================
                 Main Menu Screen
===============================================
        [1] Show Client List.
        [2] Add New Client.
        [3] Delete Client.
        [4] Update Client Info.
        [5] Find Client.
        [6] Transactions.
        [7] Manage Users.
        [8] Logout.
===============================================
Choose What do you want to do ? [1 - 8] :
```


## Screenshots

### Login Screen
![Login Screen](assets/images/login-screen.png)

### Main Menu
![Main Menu](assets/images/main-menu.png)

### Clients List
![Clients List](assets/images/client-list.png)

### Transactions Menu
![Transactions Menu](assets/images/transactions-menu.png)

### Manage Users
![Manage Users](assets/images/manage-users.png)
```


### Recommended video topics:

- Project idea and purpose
- How the login system works
- How client records are stored in file
- How permissions are calculated
- Add, update, find, and delete client demo
- Deposit and withdraw demo
- Manage users demo
- Problems faced during development
- Future improvements

## Full Presentation Script

You can use this script while recording your explanation video:

```text
Hello everyone, this project is a Bank Management System built using C++.

The idea of the project is to simulate a simple banking system using a console application.
It allows the user to log in, manage clients, perform transactions, and manage system users.

The main file of the project is main.cpp, and the program uses text files to store data permanently.
The client data is stored in client.txt, and the user login data is stored in users.txt.

When the program starts, it first displays the login screen.
The user must enter a valid username and password to access the system.
After successful login, the program shows the main menu.

From the main menu, the user can display all clients, add a new client, delete a client, update client information, find a client, open the transactions menu, or manage users.

The client management part includes the main CRUD operations:
create, read, update, and delete.
Each client has an account number, pin code, name, phone, and balance.

The transactions section allows the user to deposit money, withdraw money, and display the total balances of all clients in the system.

The project also includes a manage users section.
This part allows the admin or an authorized user to add users, list users, update users, delete users, and search for users.

One important idea in this project is the permission system.
Each user has a permission value.
This value controls which screens the user can access.
The permissions are stored as numbers using bitmask logic.

The project demonstrates several important C++ concepts:
structures, enums, vectors, file handling, string processing, functions, loops, conditions, and modular programming.

The data is saved in text files, which means the records remain available even after the program is closed.

There are also some areas that can be improved in future versions.
For example, the project can be split into multiple files, input validation can be improved, passwords can be encrypted, and the user interface can be made cleaner and more portable.

In general, this project is a good practice project for learning file handling, menus, permissions, and system design in C++.

Thank you for watching.
```



- Repository: https://github.com/YOUR_USERNAME/Bank-Management-System-Using-CPP
- Video Explanation: https://youtube.com/
- LinkedIn Post: https://linkedin.com/
- C++ File Handling Reference: https://cplusplus.com/doc/tutorial/files/
- C++ Strings Reference: https://cplusplus.com/reference/string/string/
- C++ Vectors Reference: https://cplusplus.com/reference/vector/vector/
```

## Strengths Of The Current Project

- Covers many practical C++ basics in one application
- Uses persistent file storage
- Includes authentication and permissions
- Implements CRUD operations for clients and users
- Demonstrates menu-based program flow clearly

## Current Limitations

- Everything is inside one large source file
- Passwords are stored as plain text
- Input validation is limited
- The UI depends on `system("clear")`, which is platform-specific
- The file parser assumes every line is valid
- There are no automated tests

## Suggested Future Improvements

- Split the project into multiple files such as `Client.cpp`, `User.cpp`, `FileManager.cpp`, and `UI.cpp`
- Add validation for all numeric and string inputs
- Prevent invalid transaction amounts
- Hash passwords instead of storing them as plain text
- Add exception-safe file parsing
- Replace recursive screen navigation with a loop-based application controller
- Add unit tests

## Author

-Hesham Mahmoud Ali


## Teacher

- Programming Advices - Mohamed Abu-Hadhoud


