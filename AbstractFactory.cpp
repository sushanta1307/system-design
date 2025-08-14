#include<iostream>
using namespace std;

class Pizza {
public:
    virtual void prepare() = 0;
};

class VegPizza : public Pizza {
public:
    void prepare() {
        cout<<"Preparing Veg Pizza"<<endl;
    }
};

class NonVegPizza : public Pizza {
public:
    void prepare() {
        cout<<"Preparing Non Veg Pizza"<<endl;
    }
};

class PremiumPizza : public Pizza {
public:
    void prepare() {
        cout<<"Preparing Premium Veg Pizza"<<endl;
    }
};

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

class MealFactory {
public:
    virtual Burger* createBurger(int type) = 0;
    virtual Pizza* createPizza(int type) = 0;
};

class VegMealFactory : public MealFactory {
public:
    Burger* createBurger(int type) {
        if(type == 1) {
            return new VegBurger();
        }
        return new PremiumBurger();
    }

    Pizza* createPizza(int type) {
        if(type == 1) {
            return new VegPizza();
        }
        return new PremiumPizza();
    }
};

class NonVegMealFactory : public MealFactory {
public:
    Burger* createBurger(int type) {
        if(type == 1) {
            return new NonVegBurger();
        }
        return NULL;
    }

    Pizza* createPizza(int type) {
        if(type == 1) {
            return new NonVegPizza();
        }
        return NULL;
    }
};

int main() {
    MealFactory *factory = new NonVegMealFactory();
    Burger *burger = factory->createBurger(1);
    Pizza *pizza = factory->createPizza(1);
    burger->prepare();
    pizza->prepare();
    return 0;
}