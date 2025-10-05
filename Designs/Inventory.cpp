#include<iostream>
#include<unordered_map>

using namespace std;

class Item {
public:
    int id;
    int quantity;
    double price;

    Item(int id, int qt, int p) : id(id), price(p), quantity(qt) {}
};

class Inventory {
    unordered_map<int, Item> items;

public:
    void addItem(int id, int price, int quantity) {
        if(items.count(id)) {
            items[id].price = price;
            items[id].quantity += quantity;
        } else {
            items[id] = Item{id, quantity, price};
        }
    }

    void removeItem(int id) {
        items.erase(id);
    }

    bool sell(int id, int quantity, string paymentMethod) {
        if(!items.count(id)) {
            cout<<"Item doesn't exist"<<endl;
            return false;
        }
        if(items[id].quantity < quantity) {
            cout<<"Insufficient quantity"<<endl;
        }
        items[id].quantity -= quantity;

        double amount = items[id].price * quantity;
        cout<<"Please pay Rs."<<amount<<endl;

        Payment *payment = PaymentFactory::createPayment(paymentMethod);
        payment->doPayment(amount);

        return true;
    }

};

class PaymentFactory {
public:
    static Payment* createPayment(string method) {
        if(method == "cash") {
            return new CashPayment();
        } else if(method == "card") {
            return new CashPayment();
        }

        return NULL;
    }

};

class Payment {
public:
    virtual void doPayment(double amt) = 0;
};

class CashPayment: public Payment {
public:
    void doPayment(double amt) {
        cout<<"Paid "<<amt<<" via cash"<<endl;
    }
};

class CardPayment: public Payment {
public:
    void doPayment(double amt) {
        cout<<"Paid "<< amt <<" via card"<<endl;
    }
};