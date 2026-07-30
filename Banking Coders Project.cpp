/*  Group Name: Banking Coders
     Project Idea: Banking Management System 

    Student Name: Ahmad S F Almutairi 
    Student ID: 2241100095
    Student Name: Ahmed H J Alamiri
    Student ID: 2241100101
    Student Name: Yousef M M Alenezi
    Student ID: 2241100807
    Student Name: Hisham Abdalrahem Al Muzaini (Group Coordinator)
    Student ID:  2241100883
    Student Name: Ibrahim M A Alajman
    Student ID:  2241100930

*/

#include <iostream> // for input and output operations (like cout and cin)
#include <string> // for using the string data type to store names and passwords
#include <fstream> // for file handling operations (like ifstream and ofstream to read and write files)
#include <iomanip> // for formatting output (like setw, setprecision, and fixed to format the display of balances and transaction history)
using namespace std; // to avoid having to write std:: before every standard library function or object we use.


// Global constant integers
const int MAX_ACC = 100; // maximum number of accounts the system can handle, set to 100 for this project.
const int MAX_TRANS = 500; // maximum number of transactions the system can handle, set to 500 for this project. this is because we are saving all transactions in an array and we need a limit for that array.

// ===== STRUCTS =====

// struct creates a new data type that holds many different variables with different data types inside of it, so that they can be called.

//this struct is for the accounts array that holds all the info of the accounts, it has the account ID, balance, name, password and whether the account is active or not.
struct Account{
    int id; 
    float balance;
    string name;
    string password;
    bool active;
};

//this struct is for the transactions array that holds all the info of the transactions, it has the account ID, transaction type, and amount.
struct Transaction{
    int accID;
    string type;
    float amount;
};

// ===== GLOBAL =====

// Arrays
Account accounts[MAX_ACC]; // array that holds all the accounts, the size of this array is determined by the MAX_ACC constant.
Transaction transactions[MAX_TRANS]; // array that holds all the transactions, the size of this array is determined by the MAX_TRANS constant.

// integers for counting how many accounts created, and how many transactions done.
int accountCount = 0; // initializations
int transCount = 0; // initializations

// ===== FILE FUNCTIONS =====

/* These two functions create a database of all the accounts and their respective info, it will look like this in the "accounts.txt" file:
accountCount
id name password balance active
*/

// This function saves all account info into the "accounts.txt" file, it should be used after every account created and transactions are done.
// Function 1 of 16 functions.
void saveToFile(){
    ofstream outputFile("accounts.txt");

    if (!outputFile){ // checks if output file is opened
        cout << "Error saving accounts file." << endl;
        return; // if the file cannot be opened, it will print an error message and exit the function to avoid crashing the program.
    }

    outputFile << accountCount << endl; // first line in the accounts file is the account count so that future for loops work based on the account count limit.
    
    // simple for loop that saves all the account data into the file.
    for (int i = 0; i < accountCount; i++){
        outputFile << accounts[i].id << " "
            << accounts[i].name << " "
            << accounts[i].password << " "
            << accounts[i].balance << " "
            << accounts[i].active << endl;
    }

    outputFile.close(); // closes the file
}

// Function that Loads all info from the accounts file.
// Function 2 of 16 functions.
// This is a creative addition to the project.
void loadFromFile(){
    ifstream inputFile("accounts.txt");

    if (!inputFile){ // checks if the file has anything saved.
        cout << "No saved data for accounts found, starting with a new account file." <<endl;
        return;
    }

    inputFile >> accountCount; // the program will know the account count now

    for (int i = 0; i < accountCount; i++){ // for loop that places all the info from the file into the accounts array.
        inputFile >> accounts[i].id
           >> accounts[i].name
           >> accounts[i].password
           >> accounts[i].balance
           >> accounts[i].active;
    }

    inputFile.close();
}

/* These two functions also save all the transaction history into the file database, it will look like this 
transCount
ID type amount
*/

// save it to the transactions file, exact same copy as saveToFile but with changed variable names.
// Function 3 of 16 functions.
// This is a creative addition to the project.
void saveTransactions(){
    ofstream outputFile("transactions.txt");

    if (!outputFile){ // checks if output file is opened
        cout << "Error saving transactions file." << endl;
        return;
    }

    outputFile << transCount << endl; // first line in the accounts file is the transaction count so that future for loops work based on the account count limit.
    
    // simple for loop that saves all the transaction data into the file.
    for (int i = 0; i < transCount; i++){
        outputFile << transactions[i].accID << " "
            << transactions[i].type << " "
            << transactions[i].amount << endl;
    }

    outputFile.close(); // closes the file
}

// Function that Loads all info from the transactions file.
// Function 4 of 16 functions.
void loadTransactions(){
    ifstream inputFile("transactions.txt");

    if (!inputFile){ // checks if the file has anything saved.
        cout << "No saved data found, starting with a new transaction history file." <<endl;
        return;
    }

    inputFile >> transCount; // the program will know the transaction count now

    for (int i = 0; i < transCount; i++){ // for loop that places all the info from the file into the transactions array.
        inputFile >> transactions[i].accID
           >> transactions[i].type
           >> transactions[i].amount;
    }

    inputFile.close();
}

// ===== HELPERS =====
// Function 5 of 16 functions.
bool isValidInput(float amount){ // makes sure the amount is a positive number
    return amount > 0;
}

// This will find the index of an accounts array based on the ID given.
// Function 6 of 16 functions.
int findAccount(int id){
    for (int i = 0; i < accountCount; i++){
        if (accounts[i].id == id && accounts[i].active) // finds the matching ID and makes sure its an active account
            return i; // returns that ID's index
    }
    return -1; // indices can never be -1 so we can catch errors in bug fixing.
}

// function will save the types of transactions (withdrawal, deposit, transfer out, transfer in) so it can be viewed in the account history.
// Function 7 of 16 functions.
void addTransaction(int id, string type, float amount){
    if (transCount < MAX_TRANS){
        transactions[transCount++] = {id, type, amount};
        saveTransactions();
    }
}

// ===== ACCOUNT =====

// function will create a new account with a unique id. the user will enter their name and password only, initial balance will be 0.
// Function 8 of 16 functions.
void createAccount(){
    
    // checks if the account count is bigger than the max number.
    if (accountCount >= MAX_ACC){
        cout <<"[Error] Maximum account limit reached. Cannot create more accounts.\n";
        return;
    }

    int newID = 0; // starting ID number, will be incremented to ensure uniqueness.
    
    // for loop finds the biggest ID value and makes it the value of newID
    for (int i = 0; i < accountCount; i++){
        if (accounts[i].id > newID)
            newID = accounts[i].id;
    }

    newID++; //increments newID by 1 so the ID is always unique. this also means that IDs start at 10001 and onwards.
    
    // user enters name and password, places them in their respective array variables
    cout << "  Enter Account Holder Full Name: ";
    cin.ignore(); // to clear the newline character from the input buffer before getline
    getline(cin, accounts[accountCount].name);


    cout << "  Set Account Password: ";
    getline(cin, accounts[accountCount].password);
   
    
    // saving the info of the account ID, balance and activity into the array.
    accounts[accountCount].id = newID;
    accounts[accountCount].balance = 0;
    accounts[accountCount].active = true;

    accountCount++; // increments account count

    saveToFile(); //saves the info into the file

    cout << "\n  [Success] Account created successfully!\n";
    cout << "  Account ID: " << newID << " | Holder: " << accounts[accountCount - 1].name << "\n";

}


// function that logs the user into their account
// Function 9 of 16 functions.
int login(){
    int id;
    string pass;
    
    // user enters their id here
    cout << "\n  --- Login ---\n";
    cout << "  Enter Account ID (numeric): ";
    cin >> id;
    
    // finds the index of that ID
    int i = findAccount(id);
    
    // the index returned a -1 meaning that there is no account with the ID the user entered.
    if (i == -1){
        cout << "[Error] Account not found. Please check your ID." << endl;
        return -1;
    }
    
    // the user enters their password.
    cout << "  Enter Account Password: ";
    cin >>pass;
    
    // if the password doesnt exactly match the array password it does not log them in.
    if (accounts[i].password != pass){
        cout << "[Error] Incorrect password. Access denied." <<endl;
        return -1;
    }
    
    // if it logged them in, it returns the array index.
    return i;
}

// ===== TRANSACTIONS =====

// Function that deposits money into the bank account.
// Function 10 of 16 functions.
void deposit(int id, float amount){
    
    // Finds the  array index for the account that holds the account's ID
    int i = findAccount(id);
    
    
    // ID wasn't found, so it returned -1 OR the amount was smaller than or equal to 0 so the input was invalid
    if (i == -1 || !isValidInput(amount)){
        cout << "[Error] Account not found or amount is not valid. Deposit cancelled.\n";
        return;
    }
    
    // Adds the amount that was deposited, (the amount will be entered by the user in main)
    accounts[i].balance += amount;
    
    // For the transaction history of this account
    addTransaction(id, "Deposit", amount);

    saveToFile();
    
    cout <<"Deposit Successful. \n";
}

// Function that withdraws money from the bank account.
// Function 11 of 16 functions.
void withdraw(int id, float amount){
    
    // Same thing, returns index.
    int i = findAccount(id);
    
    // ID wasn't found, returned -1. or the input was invalid.
    if (i == -1 || !isValidInput(amount)){
        cout << "[Error] Account not found or amount is not valid. Withdrawal cancelled.\n";
        return;
    }
    
    //  If the amount that the user was trying to withdraw was bigger than their balance, it will tell them that they dont have the balance to do that.
    if (accounts[i].balance < amount){
        cout <<"[Error] Insufficient balance. Withdrawal cancelled.\n";
        return;
    }
    
    //Negates the balance by the amount withdrawn.
    accounts[i].balance -= amount;
    //Saves the transaction in account history.
    addTransaction(id, "Withdraw", amount);

    saveToFile();

    cout << "Withdraw done.\n";
}

// This function transfers an amount from one account to the other
// Function 12 of 16 functions.
void transfer(int fromID, int toID, float amount){
    int from = findAccount(fromID); // finds the account of where that money is coming from. returns the index.
    int to = findAccount(toID); // finds the account of where that money is being transfered to. returns the index.
    
    //ID wasn't found for either case or the input was invalid.
    if (from == -1 || to == -1 || !isValidInput(amount)){
        cout << "[Error] Account not found or amount is not valid. Transfer cancelled.\n";
        return;
    }
    
    // makes sure that the account has the balance to transfer the amount the user asked for.
    if (accounts[from].balance < amount){
        cout << "[Error] Insufficient balance. Transfer cancelled.\n";
        return;
    }
    
    // Negates the balance of the transferor by that amount, and adds the balance of the receiver by that same amount.
    accounts[from].balance -= amount;
    accounts[to].balance += amount;
    
    // saves the transaction history.
    addTransaction(fromID, "Transfer_Out", amount);
    addTransaction(toID, "Transfer_In", amount);

    saveToFile();

    cout << "Transfer done\n";
}

// ===== QUERY =====

//simple function that checks the balance of the user
/*
 void checkBalance(int id){
    int i = findAccount(id); // returns index
    if (i != -1) // makes sure that the account is found
        cout << left <<  "Balance: " << setw(13) << fixed << setprecision(2) << accounts[i].balance << " KD "<< endl;
}
*/
// Function 13 of 16 functions.
void checkBalance(int id){
    int index = findAccount(id);

    if (index == -1){
        cout << "[Error] Account not found.\n";
        return;
    }

    cout << "\n  --- Account Information ---\n";
    cout << "  Account ID   : " << accounts[index].id << "\n";
    cout << "  Holder Name  : " << accounts[index].name << "\n";
    cout << "  Balance      : "
         << fixed << setprecision(2)
         << accounts[index].balance << " KD\n";
    cout << "  Status       : "
         << (accounts[index].active ? "Active" : "Inactive") << "\n";
}

// Shows the transaction history of an account
// Function 14 of 16 functions.
void viewTransactionHistory(int id){
    // for loop will print out the transaction history based on the account ID. the limit of this loop is the transaction count.
    for (int i = 0; i < transCount; i++){
        if (transactions[i].accID == id){
            cout << left << setw(13) << transactions[i].type << " - "
                 <<setw(9)<<fixed << setprecision(2)<< transactions[i].amount << endl;
        }
    }
}

// ===== REPORT =====

// function that generates a report that shows the sum of all the balances in this bank and the account count.
// Function 15 of 16 functions.

// This is a creative addition to the project.

void generateReport(){
    float total = 0; // initialization of total variable that will hold the sum of all balances.
    
    // simple for loop that will find the sum of all balances.
    for (int i = 0; i < accountCount; i++){
        total += accounts[i].balance;
    }
    
    // prints out the report.
    cout << "Accounts: " << accountCount << endl;
    cout << "Total Money: " << fixed << setprecision(2) << total << " KD " << endl;
}

// ===== MAIN =====
// Function 16 of 16 functions. (Main Function)
int main(){
    loadFromFile(); //loads all account info
    loadTransactions(); // loads transaction history

    int choice;
    // main menu loop keeps running until the user selects exit.
    while (true){
        
        // gets the choice from the user for the menu.
        cout << "\n==========================================\n";
        cout << "   CCS120 Banking Management System       \n";
        cout << "   Abdullah Al-Salem University            \n";
        cout << "==========================================\n";
        cout << "  1. Create New Account\n";
        cout << "  2. Login to Existing Account\n";
        cout << "  3. Exit System\n";
        cout << "------------------------------------------\n";
        cout << "  Enter your choice: ";
        cin >> choice;
        
        // if statement for creating an account
        if (choice == 1){
            createAccount();
        }
        // else if statement for logging in and the branch that follows
        else if (choice == 2){
            int index = login(); // prompts user for ID and password.
            
            if (index != -1){ // index -1 means login failed (wrong ID or Wrong password)
                int option;
                
                //account menu Do while loop that shows the menu until the user exits the loop by picking 7.
                do{
                            cout << "\n  ==========================================\n";
                            cout << "              MAIN MENU                    \n";
                            cout << "  ==========================================\n";
                            cout << "  1. Deposit\n";
                            cout << "  2. Withdraw\n";
                            cout << "  3. Transfer\n";
                            cout << "  4. Check Balance\n";
                            cout << "  5. View Transaction History\n";
                            cout << "  6. Generate Report\n";
                            cout << "  7. Logout\n";
                            cout << "  ------------------------------------------\n";
                            cout << "  Enter your choice: ";
                            cin  >> option;

 
                    
                    //variables for the amount deposited/withdrawn/transfered and the ID to send it to if its a transfer
                    float amount;
                    int toID;
                    
                    // switch statement based on choice
                    switch (option){
                        case 1: // Deposit, asks for amount and then uses deposit function
                            cout << "Enter deposit amount (KD): ";
                            cin >> amount;
                            deposit(accounts[index].id, amount);
                            break;
                            
                        case 2: // withdraw. asks for amount and then uses the withdraw function
                            cout << "Enter withdrawal amount (KD): ";
                            cin >> amount;
                            withdraw(accounts[index].id, amount);
                            break;
                            
                        case 3: // Transfer, asks for the ID that the amount is gonna be transferred to, and then uses the transfer function.
                            cout << "To ID: ";
                            cin >> toID;
                            cout << "Enter transfer amount (KD): ";
                            cin >> amount;
                            transfer(accounts[index].id, toID, amount);
                            break;
                            
                        case 4: // uses the checkbalance function.
                            checkBalance(accounts[index].id);
                            break;
                            
                        case 5: // shows the transaction history of this account using the viewTransactionHistory function
                            viewTransactionHistory(accounts[index].id);
                            break;
                            
                        case 6: // Generates a report using the generate report function.
                            generateReport();
                            break;
                        case 7: break;
                            
                        default: // catches any input that isnt 1-7
                            cout << "Invalid option, please select any value that is 1-7";
                            break;
                        // case 7 is logout handled by the do while condition itself.
                    }
                    
                } while (option != 7); // exits account menu when user selects log out
            }
        }
        else{
            break; // any input that isnt 1 or 2 in the first menu logs out completely
        }
    }

    return 0;
}