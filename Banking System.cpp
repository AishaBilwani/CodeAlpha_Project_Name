#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Transaction {
public:
    // Constructor for Transaction class
    Transaction(const string& type, double amount)
        : type(type), amount(amount) {}

    // Method to print transaction details
    void print() const {
        cout << type << ": $" << amount << endl;
    }

private:
    string type; // Type of transaction (Deposit or Withdrawal)
    double amount; // Amount of transaction
};

class Account {
public:
    // Constructor to initialize account with account number and initial balance
    Account(const string& accNumber, double initialBalance)
        : accNumber(accNumber), balance(initialBalance) {}

    // Getter for account number
    string getAccountNumber() const { return accNumber; }

    // Getter for balance
    double getBalance() const { return balance; }

    // Method to deposit money
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            transactions.push_back(Transaction("Deposit", amount));
            cout << "Deposited $" << amount << " into account " << accNumber << endl;
        } else {
            cout << "Deposit amount must be positive." << endl;
        }
    }

    // Method to withdraw money
    void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            transactions.push_back(Transaction("Withdrawal", amount));
            cout << "Withdrew $" << amount << " from account " << accNumber << endl;
        } else {
            cout << "Invalid withdrawal amount or insufficient funds." << endl;
        }
    }

    // Method to transfer money to another account
    void transfer(Account& toAccount, double amount) {
        if (amount > 0 && amount <= balance) {
            withdraw(amount);
            toAccount.deposit(amount);
            cout << "Transferred $" << amount << " from account " << accNumber
                 << " to account " << toAccount.getAccountNumber() << endl;
        } else {
            cout << "Invalid transfer amount or insufficient funds." << endl;
        }
    }

    // Method to print all transactions
    void printTransactions() const {
        cout << "Transactions for account " << accNumber << ":" << endl;
        for (size_t i = 0; i < transactions.size(); ++i) {
            transactions[i].print();
        }
    }

private:
    string accNumber; // Account number
    double balance;   // Account balance
    vector<Transaction> transactions; // List of transactions
};

class Customer {
public:
    // Constructor to initialize customer with name
    Customer(const string& name) : name(name) {}

    // Getter for customer name
    string getName() const { return name; }

    // Method to add an account to the customer
    void addAccount(const Account& account) {
        accounts.push_back(account);
    }

    // Method to get account by account number
    Account* getAccount(const string& accNumber) {
        for (size_t i = 0; i < accounts.size(); ++i) {
            if (accounts[i].getAccountNumber() == accNumber) {
                return &accounts[i];
            }
        }
        return NULL; // Return NULL if account not found
    }

    // Method to print account information
    void printAccountInfo() const {
        cout << "Customer: " << name << endl;
        for (size_t i = 0; i < accounts.size(); ++i) {
            cout << "Account Number: " << accounts[i].getAccountNumber()
                 << ", Balance: $" << accounts[i].getBalance() << endl;
        }
    }

private:
    string name; // Customer name
    vector<Account> accounts; // List of accounts
};

int main() {
    // Create customers
    Customer customer1("Alice");
    Customer customer2("Bob");

    // Create accounts
    Account acc1("123456", 1000.0);
    Account acc2("654321", 500.0);

    // Add accounts to customers
    customer1.addAccount(acc1);
    customer2.addAccount(acc2);

    // Display initial information
    cout << "Initial Information:" << endl;
    customer1.printAccountInfo();
    customer2.printAccountInfo();

    // Perform transactions
    Account* aliceAcc = customer1.getAccount("123456");
    Account* bobAcc = customer2.getAccount("654321");

    if (aliceAcc != NULL && bobAcc != NULL) {
        aliceAcc->deposit(200.0);
        aliceAcc->withdraw(150.0);
        aliceAcc->transfer(*bobAcc, 100.0);

        cout << "\nAccount Information After Transactions:" << endl;
        customer1.printAccountInfo();
        customer2.printAccountInfo();

        cout << "\nTransaction History:" << endl;
        aliceAcc->printTransactions();
        bobAcc->printTransactions();
    } else {
        cout << "Error: One or more accounts not found." << endl;
    }

    return 0;
}

