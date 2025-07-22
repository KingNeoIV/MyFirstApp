# MyFirstApp
Personal Expense Tracker

Overview

Personal Expense Tracker is a C++ console application designed to help users manage their daily expenses. 
It allows users to add, view, and summarize expenses by category, with user authentication for secure access.
The application stores data in files for persistence and provides a simple menu-driven interface.

Features

User authentication with login and registration
Add new expenses with details like amount, category, and date
View all recorded expenses
View expenses filtered by category
Data persistence using file storage
Input validation for robust user interaction

Requirements

C++ compiler (e.g., g++, MinGW, or MSVC)
Standard C++ libraries
Operating system: Windows, Linux, or macOS

Setup Instructions

Clone or Download the Project
Copy the source code files to your local machine.
Compile the Program
Use a C++ compiler to build the application.

Example for g++:

g++ -o expense_tracker main.cpp

Ensure all necessary libraries are available.

Run the Program

Execute the compiled binary:

./expense_tracker

On Windows, run:

expense_tracker.exe

Usage

Launch the Application
Run the program to access the main menu.
User Authentication
Choose to log in or register a new user.
Enter a username and password. Passwords are validated for basic security.

Main Menu Options
Add New Expense: Input expense details (amount, category, date).
View All Expenses: Display a list of all recorded expenses.
View Expenses by Category: Filter and view expenses for a specific category.
Exit: Save data and close the application.

Data Storage

Expenses and user credentials are saved to files for persistence.
Ensure write permissions in the directory where the program is run.

Example

Welcome to Personal Expense Tracker
1. Login
2. Register
3. Exit
Enter choice: 1
Enter username: john_doe
Enter password: mypassword
Login successful!
Main Menu:
1. Add New Expense
2. View All Expenses
3. View Expenses by Category
4. Exit
Enter choice: 1
Enter amount: 50.75
Enter category: Food
Enter date (YYYY-MM-DD): 2025-07-22
Expense added successfully!

Notes
The application uses a vector to store expenses dynamically, ensuring flexibility and safety.
Basic input validation is implemented to handle invalid inputs (e.g., non-numeric values for amounts).
Passwords are stored in plain text; consider adding hashing (e.g., using a library like OpenSSL) for enhanced security in future versions.
File handling ensures data persistence but requires proper directory permissions.

Troubleshooting

Compilation Errors: Ensure your compiler supports C++11 or later and all standard libraries are accessible.
File Access Issues: Check that the program has read/write permissions in the working directory.
Invalid Input Handling: If the program behaves unexpectedly, verify that inputs match expected formats (e.g., integers for menu choices).

Future Improvements

Implement password hashing for secure user authentication.
Add support for editing or deleting expenses.
Include summary statistics (e.g., total expenses, monthly reports).
Enhance the interface with a GUI using a library like wxWidgets.

License

This project is for personal use and learning purposes. No formal license is applied.

Contact

For questions or suggestions, feel free to reach out via email or project repository (if applicable).
