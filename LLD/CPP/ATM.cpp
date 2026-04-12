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

    string getCardNo() {
        return cardNo;
    }
};

class BankingService {
    unordered_map<string, Account*> accounts;
    unordered_map<string, Card*> cards;

    unordered_map<string, string> cardToAccountMap;

public:
    BankingService() {}

    void createAccount(string accountNo, string name, int initBal = 0) {
        Account* account = new Account(accountNo, name, initBal);

        accounts[accountNo] = account;
    }

    Account* getAccount(string accNo) {
        return accounts[accNo];
    }

    void linkCardToAcc(string cardNo, string pin, string accountNo) {
        if(!accounts.count(accountNo)) {
            cout<<"Account doesn;t exist"<<endl;
            return;
        }

        Card* card = new Card(cardNo, pin);
        cards[cardNo] = card;

        cardToAccountMap[cardNo] = accountNo;
    }

    Card* getCard(string cardNo) {
        return cards[cardNo];
    }

    bool authenticate(string cardNo, string pin) {
        if(!cards.count(cardNo)) {
            cout<<"Card is not active\n";
            return false;
        }

        Card* card = cards[cardNo];
        if(card->getPin() != pin) {
            cout<<"Invalid pin\n";
            return false;
        }

        cout<<"Authenticated successfully\n";
        return true;
    }

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
        if(amt > availableCash) {
            cout<<"Insufficient balance in the dispenser\n";
            return false;
        }

        cout<<"Please collect your cash and take your card\n";
        availableCash -= amt;
        return true;
    }

    int getBalance() {
        return availableCash;
    }

};

class ATM {
    BankingService* bankingService;
    CashDispenser* cashDispenser;
public:
    ATM(BankingService* bs, CashDispenser* cd) :
        bankingService(bs), cashDispenser(cd) {}

    bool authenticateUser(Card* card) {
        return bankingService->authenticate(card->getCardNo(), card->getPin());
    }

    void deposit(string accountNo, int amount) {
        Account* account = bankingService->getAccount(accountNo);

        if(account) {
            Transaction* t = new DepositTransaction("12", account, amount);

            t->execute();
            cout<<"Amount Deposited successfully\n";

        }
    }

    void withdraw(string accountNo, int amount) {
        Account* account = bankingService->getAccount(accountNo);

        if(account and account->getBalance() >= amount) {
            Transaction* t = new WithdrawTransaction("12", account, amount);

            t->execute();
            cout<<"Amount Withdrawn successfully\n";

            cashDispenser->dispense(amount);

        }
    }

    int checkBalance(string accountNo) {
        Account* account = bankingService->getAccount(accountNo);

        if(account) {
            return account->getBalance();
        }

        return 0;
    }

};

int main() {
    BankingService bankingService;
    CashDispenser cashDispenser(10000);
    ATM atm = ATM(&bankingService, &cashDispenser);

    // cout<<cashDispenser.getBalance() <<endl;

    // Create sample accounts
    bankingService.createAccount("1234567890", "Sushanta", 1000);
    // bankingService.createAccount("9876543210", "Sen", 500);

    bankingService.linkCardToAcc("1234567890", "1234", "9876543210");

    // Perform ATM operations
    Card card = Card("1234567890", "1234");
    atm.authenticateUser(&card);

    double balance = atm.checkBalance("1234567890");
    cout<<"Account balance: "<< balance<<endl;

    atm.withdraw("1234567890", 100);
    // atm.deposit("9876543210", 200.0);

    balance = atm.checkBalance("1234567890");
    cout<<"Account balance: "<< balance <<endl;

    return 0;
}

