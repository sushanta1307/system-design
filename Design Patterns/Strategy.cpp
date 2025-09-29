#include<iostream>

using namespace std;

class PaymentStrategy {
    public:
    virtual void pay(int amount) = 0;
};

class UPIPaymentStrategy : public PaymentStrategy {
    string upiId;
    public:
    UPIPaymentStrategy(string id) : upiId(id) {}
    
    void pay(int amount) {
        cout<<"Paying amount: "<<amount<<" via UPI id: "<<upiId<<endl;
    }
};

class CardPaymentStrategy : public PaymentStrategy {
    string cardNo, CVV, name;
    public:
    CardPaymentStrategy(string cNo, string cvv, string nm) : 
    cardNo(cNo), CVV(cvv), name(nm) {}
    
    void pay(int amount) {
        cout<<"Paying amount: "<<amount<<" via Card: "<<cardNo<<endl;
    }
};

class NetBankingStrategy : public PaymentStrategy {
    string netBankingId, password;
    public:
    NetBankingStrategy(string nbId, string passwd) : 
    netBankingId(nbId), password(passwd) {}
    
    void pay(int amount) {
        cout<<"Paying amount: "<<amount<<" via net banking: "<<netBankingId<<endl;
    }
};

// prefer composition over inheritance
class PaymentContext {
    PaymentStrategy *paymentStrategy;
public:
    PaymentContext(PaymentStrategy *ps) : paymentStrategy(ps) {}

    void payment(int amount) {
        paymentStrategy->pay(amount);
    }
};

int main() {
    UPIPaymentStrategy ups("sk@paytm.com");
    PaymentContext paymentContext(&ups);

    paymentContext.payment(1000);

    return 0;
}