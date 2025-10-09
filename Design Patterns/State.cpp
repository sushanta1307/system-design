#include<iostream>
using namespace std;

class ATMContext;

class ATMState {
public:
    ATMContext *context;
    ATMState(ATMContext *ctx) : context(ctx) {}

    virtual void insertCard() = 0;
    virtual void ejectCard() = 0;
    virtual void enterPin(int pin) = 0;
};

class NoCardState: public ATMState {
public:
    NoCardState(ATMContext *context) : ATMState(context) {}

    void insertCard();
    void ejectCard() {
        cout<<"No Card is inserted\n";
    }

    void enterPin(int pin) {
        cout<<"No card is inserted\n";
    }
};

class InsertedCardState: public ATMState {
public:
    InsertedCardState(ATMContext *context) : ATMState(context) {}

    void insertCard() {
        cout<<"Card is already inserted\n";
    }

    void ejectCard();

    void enterPin(int pin) {
        cout<<"Entered pin "<< pin << "\n";
    }
};

class ATMContext {
    ATMState *state;
    
public:
    ATMState *noCardState;
    ATMState *insertedCardState;
    
    ATMContext() {
        noCardState = new NoCardState(this);
        insertedCardState = new InsertedCardState(this);
        setState(noCardState);
    }

    void setState(ATMState *state) {
        this->state = state;
    }

    void insertCard() {
        state->insertCard();
    }

    void ejectCard() {
        state->ejectCard();
    }

    void enterPin(int pin) {
        state->enterPin(pin);
    }
};

void InsertedCardState::ejectCard() {
    cout<<"Card ejected\n";
    context->setState(context->noCardState);
}

void NoCardState::insertCard() {
    cout<<"Card is inserted\n";
    context->setState(context->insertedCardState);
}

int main() {
    ATMContext atm;

    atm.insertCard();   // transition NoCard -> CardInserted
    atm.enterPin(1111); // wrong PIN
    atm.enterPin(1234); // correct PIN
    atm.ejectCard();    // transition CardInserted -> NoCard
    atm.ejectCard();    // already no card

    return 0;
}