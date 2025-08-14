#include<iostream>
using namespace std;

class Burger {
public:
    virtual void prepare() = 0;
};

class VegBurger : public Burger {
public:
    void prepare() {
        cout<<"Preparing Veg Burger"<<endl;
    }
};

class NonVegBurger : public Burger {
public:
    void prepare() {
        cout<<"Preparing Non Veg Burger"<<endl;
    }
};

class PremiumBurger : public Burger {
public:
    void prepare() {
        cout<<"Preparing Premium Veg Burger"<<endl;
    }
};


class BurgerFactory {
public:
    virtual Burger* createBurger(int type) = 0;
};

class VegBurgerFactory : public BurgerFactory {
public:
    Burger* createBurger(int type) {
        if(type == 1) {
            return new VegBurger();
        }
        return new PremiumBurger();
    }
};

class NonVegBurgerFactory : public BurgerFactory {
public:
    Burger* createBurger(int type) {
        if(type == 1) {
            return new NonVegBurger();
        }
        return NULL;
    }
};

int main() {
    BurgerFactory *factory = new VegBurgerFactory();
    Burger *burger = factory->createBurger(1);
    burger->prepare();
    return 0;
}