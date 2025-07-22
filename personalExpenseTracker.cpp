// This is a practice console app called Personal Expense Tracker.
// You will be able to record, view, and summarize your daily expenses.
#include <iostream>  // Include the Input Output streams library.
#include <fstream>   // Include the file stream library for file operations.
#include <string>    // Include the string library for string operations.
#include <cstdlib>   // Include for exit() function.
#include <map>       // Provides access to the map container, which stores key-value pairs with unique keys.
                     // In this program, it's used to simulate a user database where the username is the key
                     // and the password is the value.
#include <cctype>    // Provides functions for character classifictions and conversion, such as isupper(),
                     // isdigit(), isalpha(), etc. In this program, it's used to check if a password contains
                     // uppercase letters and digits for validation.
#include <vector>    // Include the vector library allowing for the use of arrays that can grow in size or shrink.
#include <limits>    // Include the limits library for numeric_limits.
using namespace std; // Use the standard namespace for convenience.

// Function prototypes for the menu options.
char promptForContinuation();                                   // Function to prompt the user for continuation input (y/n)
void saveUser(const string &username, const string &password);  // Function to save a new user's credentails to a file
bool isValidPassword(const string &password);                   // Function to check if a password meets basic security requirements
void loginUser(string &, string &);                             // Function for login security
void continueValidation();                                      // Function to process if the user wants to continue.
void newFileOpenFile(string &, ofstream &, ifstream &, char &); // Function to open a new or existing file.
void menuChoice(char &);                                        // Function to get user menu choice.
void addNewExpense(ofstream &, string);                         // Fucntion to add a new expense.
void viewAllExpense();                                          // Function to view all expenses.
void viewExpenseByCategory();                                   // Function to view expenses by category.

// Main function: Entry point of the program.
// This function initializes the program and handles user interactions.
// It calls necessary functions for login and registration processes.
int main()
{ // This is the beginning of the main function scope.
    // Declare constants for menu options.
    const char ADD = '1',
               VIEW = '2',
               TOTAL = '3',
               EXIT = '4';

    string fileName;           // Variable to hold the user's new file name.
    string openFile;           // Variable to hold the user's file name to open.
    string username, password; // Variable to hold the username and password.
    char usersChoice;          // Variable to hold the user's menu choice.
    char userSelection;        // Variable to hold the user's menu selection.

    ifstream inputFile;  // Input file stream for reading from files.
    ofstream outputFile; // Output file stream for writing to files.

    loginUser(username, password); // Function to handle user login or registration

    newFileOpenFile(fileName, outputFile, inputFile, userSelection); // Call function to open a new file or open a file.

    do // do-while loop for the options menu.
    {  // Beginning of the do-while loop's scope.
        // Display welcome message and main menu options.
        cout << "   Welcome to Michaels' Personal Expense Tracker\n"
             << "-------------------------------------------------\n"
             << "Main Menu:\n"
             << "1. Add a new expense\n"
             << "2. View all expenses\n"
             << "3. View total expenses by category\n"
             << "4. Exit program\n";
        menuChoice(usersChoice); // Get user choice from menu.

        switch (usersChoice)                     // Switch based on user choice.
        {                                        // Beginning of the scope for the switch menu.
        case ADD:                                // Case for adding a new expense.
        {                                        // Beginning of the case ADD menu choice.
            addNewExpense(outputFile, fileName); // Call function to add a new expense.
            break;                               // Break out of switch.
        } // Closing brace for the ADD menu choice.
        case VIEW:            // Case for viewing all expenses.
        {                     // Beginning of the case VIEW menu choice
            viewAllExpense(); // Call function to view all expenses.
            break;            // Break out of switch.
        } // Closing brace for the VIEW menu choice.
        case TOTAL:                  // Case for viewing expenses by category.
        {                            // Beginning of the case TOTAL menu choice
            viewExpenseByCategory(); // Call function to view expense by category.
            break;                   // Break out of switch.
        } // Closing brace for the TOTAL menu choice.
        default:                                // Default case for exiting the program.
        {                                       // Beginning of the case EXIT menu choice
            cout << "Thank you and Goodbye!\n"; // Thank the user and exit.
        } // Closing brace for the EXIT menu choice.
        } // Closing brace for the menu choice.
    } while (usersChoice != EXIT); // Continue looping until user chooses to exit.
    return 0; // Return 0 to indicate successful completion.
} // Closing brace for the end of the main() function.

// Function to prompt the user for continuation input (y/n)
char promptForContinuation()
{
    string checkBuffer;      // Buffer to hold user input
    char continueInput;      // Variable to store the user's choice
    bool validInput = false; // Flag to check if input is valid

    do
    {
        cout << "Would you like to continue? (y/n): ";
        getline(cin, checkBuffer); // Read user input

        // Check if input is empty
        if (checkBuffer.empty())
        {
            cout << "You pressed Enter without typing anything!\n";
            continue; // Prompt again
        }

        // Validate that input is a single character
        if (checkBuffer.length() == 1)
        {
            continueInput = checkBuffer[0]; // Store the first character
            if (continueInput == 'y' || continueInput == 'Y' || continueInput == 'n' || continueInput == 'N')
                validInput = true; // Mark input as valid
        }

        // Notify user of invalid input
        if (!validInput)
            cout << "Invalid input. Please enter 'y' or 'n'\n";
    } while (!validInput); // Repeat until valid input is received
    return continueInput; // Return the valid input
}

// Function to check if a password meets basic security requirements
bool isValidPassword(const string &password)
{
    // Flags to track if the password contains at least one uppercase letter and on digit
    bool hasUpper = false,
         hasDigit = false;

    // Check if the password is at least 8 characters long
    if (password.length() < 8)
        return false; // Immediately return false if it's too short

    // Loop through each character in the password
    for (char ch : password)
    {
        // Check if the character is an uppercase letter (A-Z)
        if (isupper(ch))
            hasUpper = true;
        // Check if the character is a digit (0-9)
        if (isdigit(ch))
            hasDigit = true;
    }

    // Return true only if both conditions are met:
    // - At least one uppercase letter
    // - At least one digit
    return hasUpper && hasDigit;
}

// Function to save a new user's credentails to a file
void saveUser(const string &username, const string &password)
{
    // Open the file "users.txt" in append mode so new users are added to the end
    ofstream file("users.txt", ios::app);

    // Check if the file opened successfully
    if (file.is_open())
    {
        // Write the username and password to the file, separated by a space
        // Each user is stored on a new line
        file << username << " " << password << endl;

        // Close the file to ensure data is saved and resources are released
        file.close();

        // Notify the user that the save was successful
        cout << "User saved Successfully.\n";
    }
    else
    {
        // If the file couldn't be opened, display an error message
        cout << "Could not open file to save user.\n";
    }
}

// Function to handle user login or registration
void loginUser(string &username, string &password)
{
    // Constants representing menu choices
    const char login = '1',
               newUser = '2';

    string loginOrRegister;      // Holds the user's menu input
    bool validInput = false;     // Flag to track if input is valid
    char loginNewUser;           // Stores the validated menu choice
    string loginUser, loginPass; // Temporary variables for login credentials

    map<string, string> userDatabase; // Map to store username-password pairs

    // Open the user database file and load existing users into the map
    ifstream inputFile("users.txt");
    string fileUser, filePass;

    // Load existing users into the map
    while (inputFile >> fileUser >> filePass)
    {
        userDatabase[fileUser] = filePass;
    }
    inputFile.close();

    do
    {
        // Display the login/register menu
        cout << "1. Login\n"
             << "2. Register\n"
             << "3. Exit\n";

        // Input validation loop for menu selection
        do
        {
            cout << "Please enter your choice (1-3): "; // Prompt for user input.
            getline(cin, loginOrRegister);              // Read user input.

            if (loginOrRegister.empty()) // Check if input is empty.
            {
                cout << "You pressed Enter without typing anything!\n"; // Notify user.
                continue;                                               // Skip the rest of the loop and promt agian.
            }

            if (loginOrRegister.length() == 1) // Check if input length is 1.
            {
                loginNewUser = loginOrRegister[0];                                     // Store the first character.
                if (loginNewUser == '1' || loginNewUser == '2' || loginNewUser == '3') // Validate Input.
                {
                    validInput = true; // Mark input as valid.
                }
            }

            if (loginNewUser < '1' || loginNewUser > '3') // Validate user selection range.
            {
                cout << "Invalid input!\n"; // Notify user of invalid input.
                continue;                   // Skip to next iteration.
            }

            if (!validInput) // If input is still invalid
            {
                cin.ignore();               // Clear input buffer.
                cout << "Invalid input!\n"; // Notify user of invalid input.
            }
            else if (loginNewUser == '3') // If user chooses to exit.
            {
                cout << "Thank You! Goodbye.\n"; // Thank the user
                exit(0);                         // Exit the program.
            }
        } while (!validInput || (loginNewUser != '1' && loginNewUser != '2' && loginNewUser != '3')); // Repeat until valid input.

        switch (loginNewUser) // Switch statement to handle user choices for user operations.
        {
        case login: // If the user chooses to login.
        {
            bool invalid = false;
            int attempts = 0;

            do
            {
                cout << "---Login---\n";
                cout << "username: ";
                getline(cin, loginUser); // Get login username
                cout << "password: ";
                getline(cin, loginPass); // Get login password

                // Check if username exist and password matches
                if (userDatabase.count(loginUser) && userDatabase[loginUser] == loginPass)
                {
                    // Successful login
                    cout << "Login successful. Welcome, " << loginUser << "!\n";
                    username = loginUser;
                    password = loginPass;
                    return;
                }
                else
                {
                    // Failed login attempt
                    cout << "Invalid username or password.\n";
                    invalid = true;
                    attempts++;

                    if (attempts > 2)
                    {
                        cout << "You have reached the allowed amount of attempts!\n\n";
                        break;
                    }
                }
            } while (invalid);
            break; // Exit the switch case.
        }
        case newUser: // If the user chooses to create a new account.
        {
            bool invalidUser = false;
            do
            {
                // ---- User Registration Section ----
                cout << "--- User Registration ---\n";
                cout << "Enter a username: ";
                getline(cin, username); // Read full line to allow spaces in username

                if (userDatabase.count(username))
                {
                    cout << "Username already exists. Try again.\n";
                    invalidUser = true;
                    break;
                }

                while (true)
                {
                    // Prompt user to create a password with specific requirements
                    cout << "Create a password (min 8 chars, 1 uppercase, 1 digit): ";
                    getline(cin, password);

                    // Check if password meets security requirments
                    if (isValidPassword(password))
                    {
                        // Store the username and password in the map
                        saveUser(username, password);
                        // cout << "Registration successful!\n";
                        return; // Exit loop after successful registration
                    }
                    else
                    {
                        // Inform user of invalid password and retry
                        cout << "Password does not meet requirments. Try again.\n";
                    }
                    break; // Exit the switch case.
                }
            } while (!invalidUser);
        }
            cout << endl; // Add a newline for formatting.
        }
    } while (true);
}

// Function to process if the user wants to continue.
void continueValidation()
{
    string input;            // String to hold user input.
    bool validInput = false; // Flag to track input validity.
    char addMore;            // Variable to check if the user wants to add more expenses.

    do
    {
        cout << "would you like to continue? (y/n): "; // Prompt for user input.
        getline(cin, input);                           // Read user input.

        if (input.length() == 1) // Check uf input length is 1.
        {
            addMore = input[0];                                                       // Store the first character.
            if (addMore == 'y' || addMore == 'Y' || addMore == 'n' || addMore == 'N') // Validate input.
            {
                validInput = true; // Mark input as valid.
            }
        }

        if (!validInput) // If input is not valid.
        {
            cout << "Invalid input. Please enter 'y' or 'n'\n"; // Notify user
        }
        else if (addMore == 'n' || addMore == 'N') // If user chooses not to continue.
        {
            // cout << "Back to main menu.\n\n"; // Exit loop.
            break;
        }
    } while (!validInput || (addMore == 'y' || addMore == 'Y')); // Repeat until valid input.
}

// Function to process the user's choice for opening a new or existing file.
void newFileOpenFile(string &fileName, ofstream &outputFile, ifstream &inputFile, char &userSelection)
{
    const char NEW = '1',
               OPEN = '2';

    string fileSelection;    // Variable to hold the user's file selection.
    bool validInput = false; // Flag to track input validity.

    // Display options for file selection.
    cout << "1. New File\n"
         << "2. Open File\n"
         << "3. Exit\n";

    do
    {
        cout << "Please enter your choice (1-3): "; // Prompt for user input.
        getline(cin, fileSelection);                // Read user input.

        if (fileSelection.empty()) // Check if input is empty.
        {
            cout << "You pressed Enter without typing anything!\n"; // Notify user.
            continue;                                               // Skip the rest of the loop and promt agian.
        }

        if (fileSelection.length() == 1) // Check if input length is 1.
        {
            userSelection = fileSelection[0];                                         // Store the first character.
            if (userSelection == '1' || userSelection == '2' || userSelection == '3') // Validate Input.
            {
                validInput = true; // Mark input as valid.
            }
        }

        if (userSelection < '1' || userSelection > '3') // Validate user selection range.
        {
            cout << "Invalid input!\n"; // Notify user of invalid input.
            continue;                   // Skip to next iteration.
        }

        if (!validInput) // If input is still invalid
        {
            cin.ignore();               // Clear input buffer.
            cout << "Invalid input!\n"; // Notify user of invalid input.
        }
        else if (userSelection == '3') // If user chooses to exit.
        {
            cout << "Thank You! Goodbye.\n"; // Thank the user
            exit(0);                         // Exit the program.
        }
    } while (!validInput || (userSelection != '1' && userSelection != '2' && userSelection != '3')); // Repeat until valid input.

    switch (userSelection) // Switch statement to hangle user choices for file operations.
    {
    case NEW: // If the user chooses to create a new file.
    {
        do // Start a loop to repeatedly prompt for file path until successful.
        {
            cout << "Please enter the name of the new file: "; // Prompt user.
            getline(cin, fileName);                            // Read the file path from user input.

            outputFile.open(fileName); // Attempt to open (create) the file.

            if (outputFile.is_open()) // Check if the file was successfully opened.
            {
                cout << "File created succesfully." << endl; // Notify user of success.
                outputFile.close();
                break;
            }
            else // If the file could not be opened.
            {
                cout << "Error creating file. Please check the path and try again." << endl; // Notify user of failure.
            }
        } while (!outputFile.is_open()); // Repeat until the file is successfully created.
        break; // Exit the switch case.
    }
    case OPEN: // If the user chooses to open an existing file.
    {
        do // Start a loop to repeatedly prompt for the file path until successful.
        {
            cout << "Please enter the filename that you wish to open: "; // Prompt user
            getline(cin, fileName);                                      // Read the file path from user input.

            inputFile.open(fileName); // Attempt to open the existing file.

            if (inputFile.is_open()) // Check if the file was successfully opened.
            {
                cout << "File was located." << endl; // Notify user of success.
                inputFile.close();
                break;
            }
            else // If the file could not be opened.
            {
                cout << "File could not be found." << endl; // Notify user of failure.
                break;
            }
        } while (!inputFile.is_open()); // Repeat until the file is successfully opened.
        break; // Exit the switch case.
    }
    }
    cout << endl; // Add a newline for formatting.
}

// Function to process the user's choice from the menu.
void menuChoice(char &usersInput)
{
    string tempInput;        // Temporary variable for user input.
    bool validInput = false; // Flag to track input validity.

    do
    {
        cout << "Please enter your choice (1-4): "; // Prompt for user input.
        getline(cin, tempInput);                    // Read user input.

        if (tempInput.empty()) // Check if input is empty.
        {
            cout << "You pressed Enter without typing anything!\n"; // Notify user.
            continue;                                               // Skip to next iteration.
        }

        if (tempInput.length() == 1) // Check if input length is 1.
        {
            usersInput = tempInput[0];                                                            // Store the first character.
            if (usersInput == '1' || usersInput == '2' || usersInput == '3' || usersInput == '4') // Validate input.
            {
                validInput = true; // Mark input as valid.
            }
        }

        if (usersInput < '1' || usersInput > '4') // Validate user selection range.
        {
            cout << "Invalid input!\n"; // Notify user of invalid input.
            continue;                   // Skip to next iteration.
        }

        if (!validInput) // If input is still invalid.
        {
            cout << "Invalid input!\n"; // Notify user of invalid input.
        }

    } while (!validInput || (usersInput != '1' && usersInput != '2' && usersInput != '3' && usersInput != '4')); // Repeat until valid input.
}

// Function to add new expense.
void addNewExpense(ofstream &outputFile, string fileName)
{
    vector<string> categories; // Vector to store category names
    vector<double> amounts;    // Vector to store corresponding amounts
    string categoryInput;      // Variable to hold user category input
    double amount;             // Variable to hold user amount input
    char continuation;

    cout << "Add a new expense!\n"; // Notify the user.
    cout << fileName << endl;

    // Open the outputfile in append mode
    outputFile.open(fileName, ios::app);
    if (!outputFile.is_open())
    {
        cerr << "Error opening file!" << endl; // Error message if file fails to open
        return;                                // Exit the funtion
    }

    // Loop to collect category and amount inputs
    do
    {
        cout << "Please enter a category: ";
        getline(cin, categoryInput);         // Read category input
        categories.push_back(categoryInput); // Store category in vector

        cout << "Enter the dollar amount for " << categoryInput << ": ";
        // Input validation for amount
        while (!(cin >> amount))
        {
            cin.clear();                                         // Clear the error flag for cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "Invalid input. Please enter a valid dollar amount: ";
        }
        amounts.push_back(amount);                           // Store amount in vector
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear newline from input buffer

        continuation = promptForContinuation();
    } while (continuation == 'y' || continuation == 'Y'); // Loop until user decides to stop

    // Write collected data to the file
    for (size_t index = 0; index < categories.size(); ++index)
        outputFile << (index + 1) << ". " << categories[index] << ": $" << amounts[index] << endl; // Format and write each entry

    outputFile.close(); // Close the file after writing
}

// Function to view all expenses.
void viewAllExpense()
{
    float usersInput; // Variable to hold the user's expense input.

    cout << "You are in viewAllExpense\n"; // Notify the user.

    continueValidation();
}

// Function to view expenses by category.
void viewExpenseByCategory()
{
    float usersInput; // Variable to hold the user's expense input.

    cout << "You are in the viewExpenseByCategory\n"; // Notify the user.

    continueValidation(); // Call function to continue
}