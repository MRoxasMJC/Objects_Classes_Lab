#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <cstdlib>

class BankAccount {
    private:
        std::string accountNumber;
        std::string accountHolderName;
        double balance; // in dollars
    public:
        BankAccount();
        BankAccount(std::string accHolderNameInp, double balanceInp = 0.00);
        
        void setAccountHolderName(std::string accHolderNameInp);
        void deposit(double depositAmount);
        void withdraw(double withdrawAmount);
        
        std::string getAccountNumber() const;
        std::string getAccountHolderName() const;
        double getBalance() const;
};


// define constructors of BankAccount
BankAccount::BankAccount() { // default constructor sets accountHolderName, accountNumber, and balance
    accountNumber = std::to_string(rand() + 1000000);  //generate a random account number starting at 100000
    
    accountHolderName = "No Name";
    balance = 0.00;
}

BankAccount::BankAccount(std::string accHolderNameInp, double balanceInp) {
    accountNumber = std::to_string(rand() + 1000000); // again, generate a random account number for the user starting at 1000000. The user does not get to determine their account holder number.
    
    accountHolderName = accHolderNameInp;
    balance = balanceInp;
}

// define member functions of BankAccount
// --- mutators
void BankAccount::setAccountHolderName(std::string accHolderNameInp) { accountHolderName = accHolderNameInp; }
void BankAccount::deposit(double depositAmount) { balance += depositAmount; }
void BankAccount::withdraw(double withdrawAmount) { 
    if ((balance - withdrawAmount) < 0) {
        std::cout << "Insufficient Funds!" << std::endl;
        return; 
    }
    
    balance -= withdrawAmount; 
    std::cout << "Withdrawal of " << withdrawAmount << " successful." << std::endl;
}
// --- accessors
std::string BankAccount::getAccountNumber() const { return accountNumber; }
std::string BankAccount::getAccountHolderName() const { return accountHolderName; }
double BankAccount::getBalance() const { return balance; }


// testers
void testBankAccountClass() {
    BankAccount Melvino; // default
    // BankAccount Ning("Ning", 500); 
    // BankAccount Ning("Ning"); // exclude the second parameter (balance)
    
    Melvino.setAccountHolderName("Melvino Roxas");
    std::cout << "account name: " << Melvino.getAccountHolderName() << std::endl;
    std::cout << "account number: " << Melvino.getAccountNumber() << std::endl;
    
    Melvino.deposit(500.45);
    std::cout << "Total balance after deposit: " << Melvino.getBalance() << std::endl;
    
    Melvino.withdraw(500);
    std::cout << "Total balance after withdrawal: " << Melvino.getBalance() << std::endl;
}

void createAccount(std::vector<BankAccount> &Bank, bool isLogged) {
    BankAccount account; 
    std::string nameInp;
    
    if (!isLogged) {
        std::cout << "Enter New User Name: " << std::endl;
        std::getline(std::cin, nameInp);
        std::cout << "--Account Creation Successful." << std::endl;
        
        // validate input
        if (std::cin.fail()) {
            std::cin.clear(); // clear the error flags  
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "--Invalid input Not a Valid User Name. Try again." << std::endl;
            return;
        }
        
        account.setAccountHolderName(nameInp);
        Bank.push_back(account); // push to the vector
    } else {
        std::cout << "--You are already logged in! Logout to create a new account." << std::endl;
    }
}

void selectAccount(std::vector<BankAccount> &Bank, BankAccount *&currentUser, bool &isLogged) { 
    if (isLogged) {
        std::cout << "Already logged in. Log out if you wish to switch accounts." << std::endl;
        return;
    }
    
    std::cout << "Enter User Name: " << std::endl;
    std::string userLoginInp;
    std::getline(std::cin, userLoginInp);
    
    for (int i = 0; i < Bank.size(); i++) {
        if ((Bank.at(i).getAccountHolderName() == userLoginInp) && !isLogged) {
            currentUser = &Bank.at(i); // point to the actual account, not the account object itself.  
            isLogged = true;
            std::cout << "--Successful. Welcome, " << currentUser->getAccountHolderName() << "." << std::endl;
            return; 
        }
    }
    
    std::cout << "--User Does Not Exist" << std::endl;
}

void logout(BankAccount *&currentUser, bool &isLogged) {
    if ((currentUser != nullptr) && (isLogged == true)) {
        currentUser = nullptr; // logout
        isLogged = false;
        std::cout << "--Successfully Logged Out" << std::endl;
    } else {
        std::cout << "--You are not logged in!" << std::endl;
    }
}

void makeDeposit(BankAccount *&currentUser, bool isLogged) {
    if (isLogged) {
        double depositInp;
        std::cout << "--Amount: " << std::endl;
        std::cin >> depositInp;
        
        if (std::cin.fail()) {
            std::cin.clear(); // clear the error flags  
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "--Invalid input. Not a number. Try again." << std::endl;
            return;
        }
        
        currentUser->deposit(depositInp);
        std::cout << "--Deposit of " << depositInp << " successful." << std::endl;
    } else {
        std::cout << "--You are not logged in!" << std::endl;
    }
}

void makeWithdrawal(BankAccount *&currentUser, bool isLogged) {
    if (!isLogged) {
        std::cout << "--You are not logged in!" << std::endl;
        return;
    }
    
    double withdrawInp;
    
    std::cout << "--Amount: " << std::endl;
    std::cin >> withdrawInp ;
    
    if (std::cin.fail()) {
            std::cin.clear(); // clear the error flags  
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "--Invalid input. Not a number. Try again." << std::endl;
            return;
    }
        
    currentUser->withdraw(withdrawInp);
}

void printUserBalance(const BankAccount *currentUser, bool isLogged) {
    if (!isLogged) {
        std::cout << "--You are not logged in!" << std::endl;
        return;
    }
    
    std::cout << "Balance: " << currentUser->getBalance() << std::endl;
}

void printAllUsers(const std::vector<BankAccount> &Bank) { 
    if (Bank.size() == 0) {
        std::cout << "No accounts in this bank" << std::endl;
        return ;
    }
    
    for (int i = 0; i < Bank.size(); i++) {
        std::cout << "Account holder name: " << Bank.at(i).getAccountHolderName() << std::endl;
        std::cout << "Account holder balance: $" << Bank.at(i).getBalance() << std::endl;
        std::cout << std::endl;
    }
}

void printMenuChoices(const BankAccount *currentUser, bool isLogged) {
        std::cout << "---------------------------" << std::endl;
        std::cout << "Welcome to the Bank!" << std::endl;
        std::cout << "User: " << (isLogged ? currentUser->getAccountHolderName() : "Not Logged In") << std::endl;
        std::cout << "Services:" << std::endl;
        std::cout << "Enter 1: Create an Account" << std::endl;
        std::cout << "Enter 2: Login" << std::endl;
        std::cout << "Enter 3: Logout" << std::endl;
        std::cout << "Enter 4: Deposit" << std::endl;
        std::cout << "Enter 5: Withdraw" << std::endl;
        std::cout << "Enter 6: Get Balance" << std::endl;
        std::cout << "Enter 7: Print all Users" << std::endl;
}

int getMenuChoice(int choice) {
    std::cout << "===> " ; 

    while (!(std::cin >> choice)) {
        std::cin.clear(); // clear the error flags  
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "--Invalid input. Not a Valid Option. Try again." << std::endl;
        std::cout << "===> " ; 
    }
    
    // std::cin leaves a \n in the input buffer, so, when a user chooses option 1 to create an account, 
    // getline() will immediately read that newline and result in an empty string.
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // so clear the input buffer. 

    return choice;
}

int main() {
    srand(time(NULL));
    std::vector<BankAccount> TheBank;
    BankAccount* currentUser = nullptr; // we're gonna make this point to an actual account in TheBank vector so we can save changes to an actual account, not a copy. 
    int choice = 0; 
    bool isLogged = false; 
    
    do {
       printMenuChoices(currentUser, isLogged);
        choice = getMenuChoice(choice);
        
        switch(choice) {
            case 1:
                createAccount(TheBank, isLogged);
                break;
            case 2: 
                selectAccount(TheBank, currentUser, isLogged);
                break;
            case 3:
                logout(currentUser, isLogged);
                break;
            case 4:
                makeDeposit(currentUser, isLogged);
                break;
            case 5: 
                makeWithdrawal(currentUser, isLogged);
                break;
            case 6: 
                printUserBalance(currentUser, isLogged);
                break;
            case 7:
                printAllUsers(TheBank);
                break;
            default: 
                std::cout << "--Please Choose from Options 1 to 7" << std::endl;
                break;
        }
    } while (choice != -1);
    
    return 0;  
}
