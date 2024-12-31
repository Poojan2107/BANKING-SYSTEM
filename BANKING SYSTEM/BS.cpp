#include <iostream>
#include <vector>
using namespace std;

class BankAccount {
protected:
    string accountNumber;
    string accountHolderName;
    double balance;

public:
    BankAccount(string accNo, string accHolder, double bal)
        : accountNumber(accNo), accountHolderName(accHolder), balance(bal) {}

    virtual void deposit(double amount) {
        balance += amount;
        cout << "Deposit successful!\n";
    }

    virtual void withdraw(double amount) {
        if (amount <= balance) {
            balance -= amount;
            cout << "Withdrawal successful!\n";
        } else {
            cout << "Insufficient balance!\n";
        }
    }

    double getBalance() const {
        return balance;
    }

    virtual void displayAccountInfo() const {
        cout << "Account Number: " << accountNumber << endl;
        cout << "Account Holder: " << accountHolderName << endl;
        cout << "Balance: " << balance << endl;
    }

    virtual void calculateInterest() {} 

    virtual ~BankAccount() {}
};

class SavingsAccount : public BankAccount {
private:
    double interestRate;

public:
    SavingsAccount(string accNo, string accHolder, double bal, double rate)
        : BankAccount(accNo, accHolder, bal), interestRate(rate) {}

    void calculateInterest() override {
        double interest = balance * (interestRate / 100);
        cout << "Interest (Savings Account): " << interest << endl;
    }
};

class CheckingAccount : public BankAccount {
private:
    double overdraftLimit;

public:
    CheckingAccount(string accNo, string accHolder, double bal, double limit)
        : BankAccount(accNo, accHolder, bal), overdraftLimit(limit) {}

    void withdraw(double amount) override {
        if (amount <= balance + overdraftLimit) {
            balance -= amount;
            cout << "Withdrawal successful with overdraft!\n";
        } else {
            cout << "Withdrawal exceeds overdraft limit!\n";
        }
    }

    void calculateInterest() override {
        cout << "No interest for Checking Account.\n";
    }
};

class FixedDepositAccount : public BankAccount {
private:
    int term;
    double interestRate;

public:
    FixedDepositAccount(string accNo, string accHolder, double bal, int duration, double rate)
        : BankAccount(accNo, accHolder, bal), term(duration), interestRate(rate) {}

    void calculateInterest() override {
        double interest = balance * (interestRate / 100) * (term / 12.0);
        cout << "Interest (Fixed Deposit): " << interest << endl;
    }
};

void displayMenu() {
    cout << "\nBanking System Menu:\n";
    cout << "1. Deposit\n";
    cout << "2. Withdraw\n";
    cout << "3. Display Account Info\n";
    cout << "4. Calculate Interest\n";
    cout << "5. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    vector<BankAccount*> accounts;
    accounts.push_back(new SavingsAccount("SA123", "Palak Shrivastav", 5000.0, 3.5));
    accounts.push_back(new CheckingAccount("CA123", "Paavan Shrivastav", 3000.0, 1000.0));
    accounts.push_back(new FixedDepositAccount("FD123", "Poojan Shrivastav", 10000.0, 12, 5.0));

    int choice;
    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
        case 1: {
            int accIndex;
            double amount;
            cout << "Enter account index (0 for Savings, 1 for Checking, 2 for Fixed Deposit): ";
            cin >> accIndex;
            cout << "Enter amount to deposit: ";
            cin >> amount;
            accounts[accIndex]->deposit(amount);
            break;
        }
        case 2: {
            int accIndex;
            double amount;
            cout << "Enter account index (0 for Savings, 1 for Checking, 2 for Fixed Deposit): ";
            cin >> accIndex;
            cout << "Enter amount to withdraw: ";
            cin >> amount;
            accounts[accIndex]->withdraw(amount);
            break;
        }
        case 3: {
            int accIndex;
            cout << "Enter account index (0 for Savings, 1 for Checking, 2 for Fixed Deposit): ";
            cin >> accIndex;
            accounts[accIndex]->displayAccountInfo();
            break;
        }
        case 4: {
            int accIndex;
            cout << "Enter account index (0 for Savings, 1 for Checking, 2 for Fixed Deposit): ";
            cin >> accIndex;
            accounts[accIndex]->calculateInterest();
            break;
        }
        case 5:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice!\n";
        }
    } while (choice != 5);

    for (BankAccount* account : accounts) {
        delete account;
    }

    return 0;
}
