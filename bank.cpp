#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Customer {
public:
    string customerID;
    string name;
    string email;

    Customer(string id, string n, string e) : customerID(id), name(n), email(e) {}
};

class Account {
public:
    string accountNumber;
    Customer* customer;
    double balance;
    vector<string> transactions;

    Account(string accNum, Customer* cust, double bal = 0.0)
        : accountNumber(accNum), customer(cust), balance(bal) {
        transactions.push_back("Account created with ₹" + to_string(bal));
    }

    void deposit(double amount) {
        balance += amount;
        cout << "✅ Deposited ₹" << amount << " to account " << accountNumber << endl;
        transactions.push_back("Deposited ₹" + to_string(amount));
    }

    bool withdraw(double amount) {
        if (amount > balance) {
            cout << "❌ Insufficient balance!" << endl;
            return false;
        }
        balance -= amount;
        cout << "✅ Withdrew ₹" << amount << " from account " << accountNumber << endl;
        transactions.push_back("Withdrew ₹" + to_string(amount));
        return true;
    }

    void display() {
        cout << "\n📄 Account Info:\n";
        cout << "Customer Name: " << customer->name << endl;
        cout << "Account Number: " << accountNumber << endl;
        cout << "Balance: ₹" << balance << endl;
    }

    void showTransactions() {
        cout << "\n📜 Transaction History for Account " << accountNumber << ":\n";
        for (const string& t : transactions) {
            cout << "- " << t << endl;
        }
    }
};
bool isValidNumber(const string& s, int requiredLength) {
    if (s.length() != requiredLength) return false;
    for (char c : s) {
        if (!isdigit(c)) return false;
    }
    return true;
}

bool isValidGmail(const string& email) {
    string domain = "@gmail.com";
    if (email.length() < domain.length()) return false;
    return email.substr(email.length() - domain.length()) == domain;
}
double totalBankBalance = 0.0;

int main() {
    string custId, name, email;

    // Customer ID (10 digits)
    do {
        cout << "👤 Enter 10-digit customer ID: ";
        cin >> custId;
        if (!isValidNumber(custId, 10)) {
            cout << "❌ Invalid ID! It must be exactly 10 digits.\n";
        }
    } while (!isValidNumber(custId, 10));

    cin.ignore(); 

    cout << "👤 Enter customer name: ";
    getline(cin, name);

    do {
        cout << "📧 Enter Gmail ID (must end with '@gmail.com'): ";
        getline(cin, email);
        if (!isValidGmail(email)) {
            cout << "❌ Invalid Gmail! It must end with '@gmail.com'.\n";
        }
    } while (!isValidGmail(email));

    Customer customer1(custId, name, email);

    string accNum;
    double initialBalance;

    do {
        cout << "\n🏦 Enter 14-digit account number: ";
        cin >> accNum;
        if (!isValidNumber(accNum, 14)) {
            cout << "❌ Invalid Account Number! It must be exactly 14 digits.\n";
        }
    } while (!isValidNumber(accNum, 14));

    cout << "💰 Enter initial balance: ₹";
    cin >> initialBalance;

    Account account1(accNum, &customer1, initialBalance);
    totalBankBalance += initialBalance;

    int choice;
    do {
        cout << "\n📋 --- Banking Menu ---\n";
        cout << "1. Deposit\n2. Withdraw\n3. Display Account\n4. Show Transactions\n5. Show Total Bank Balance\n6. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                double amt;
                cout << "💵 Enter amount to deposit: ₹";
                cin >> amt;
                account1.deposit(amt);
                totalBankBalance += amt;
                break;
            }
            case 2: {
                double amt;
                cout << "💸 Enter amount to withdraw: ₹";
                cin >> amt;
                if (account1.withdraw(amt)) {
                    totalBankBalance -= amt;
                }
                break;
            }
            case 3:
                account1.display();
                break;
            case 4:
                account1.showTransactions();
                break;
            case 5:
                cout << "\n🏦 Total Bank Balance (all accounts): ₹" << totalBankBalance << endl;
                break;
            case 6:
                cout << "👋 Exiting. Thank you!\n";
                break;
            default:
                cout << "❗ Invalid option.\n";
        }

    } while (choice != 6);

    return 0;
}
