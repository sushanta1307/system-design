#include<iostream>

using namespace std;


class Account {
    string accountNo;
    string accountHolder;
    int balance;
    public:
    Account(string accNo, string name, int bal = 0) :
    accountNo(accNo), accountHolder(name), balance(bal) {}
    
    int getBalance() {
        return balance;
    }
    
    string getAccountNo() {
        return accountNo;
    }
    
    string getAccountHolder() {
        return accountHolder;
    }
    
    void credit(int amt) {
        balance += amt;
    }
    
    void debit(int amt) {
        balance -= amt;
    }
};

class Transaction {
protected:
    string transactionId;
    Account* account;
    int amount;
    
public:
    Transaction(string id, Account* acc, int amt) :
        transactionId(id), account(acc), amount(amt) {}

    virtual void execute() = 0;
};

class WithdrawTransaction : public Transaction {
public:
    WithdrawTransaction(string id, Account* acc, int amt) :
        Transaction(id, acc, amt) {}

    void execute() override {
        account->debit(amount);
    }
};

class DepositTransaction : public Transaction {
public:
    DepositTransaction(string id, Account* acc, int amt) :
        Transaction(id, acc, amt) {}

    void execute() override {
        account->credit(amount);
    }
};

class Card {
    string cardNo;
    string pin;

public:
    Card(string cardNo, string pin) :
        cardNo(cardNo), pin(pin) {}

    void setPin(string newPin) {
        pin = newPin;
    }

    string getPin() {
        return pin;
    }
};

class BankingService {
    unordered_map<string, Account*> accounts;
    unordered_map<string, Card*> cards;

    unordered_map<string, string> cardToAccountMap;

public:
    BankingService() {}

    void createAccount(string accountNo, string name, int initBal) {}

    Account* getAccount(string accNo) {
        return accounts[accNo];
    }

    void linkCardToAcc() {}

    Card* getCard(string cardNo) {
        return cards[cardNo];
    }

    bool authenticate() {}

    void processTransaction(Transaction* transaction) {
        transaction->execute();
    }

};

class CashDispenser {
    int availableCash;
public:
    CashDispenser(int bal = 0) : 
        availableCash(bal) {}

    // add balance
    void addBalance(int bal) {
        availableCash += bal;
    }

    // dispense
    bool dispense(int amt) {
        if(amt < availableCash) {
            cout<<"Insufficient balance in the dispenser\n";
            return false;
        }

        cout<<"Please collect your cash and take your card\n";
        availableCash -= amt;
        return true;
    }

};

class ATM {
    BankingService* bankingService;
    CashDispenser* cashDispenser;
public:
    ATM(BankingService* bs, CashDispenser* cd) :
        bankingService(bs), cashDispenser(cd) {}

    bool authenticateUser(Card* card) {
        return bankingService->authenticate();
    }

    void deposit(string accountNo, int amount) {}

    void withdraw(string accountNo, int amount) {}

    int checkBalance(string accountNo) {return 0;}

};

int main() {
    BankingService bankingService;
    CashDispenser cashDispenser(10000);
    ATM atm = ATM(&bankingService, &cashDispenser);

    // Create sample accounts
    bankingService.createAccount("1234567890", "Sushanta", 1000);
    bankingService.createAccount("9876543210", "Sen", 500);

    // Perform ATM operations
    Card card = Card("1234567890", "1234");
    atm.authenticateUser(&card);

    double balance = atm.checkBalance("1234567890");
    cout<<"Account balance: "<< balance<<endl;

    atm.withdraw("1234567890", 500.0);
    atm.deposit("9876543210", 200.0);

    balance = atm.checkBalance("1234567890");
    cout<<"Account balance: "<< balance <<endl;

    return 0;
}

