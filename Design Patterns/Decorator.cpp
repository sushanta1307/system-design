#include<iostream>

using namespace std;

// Component interface
class Coffee {
public:
    virtual string getDescription() = 0;
    virtual double getCost() = 0;
};

// concrete component
class SimpleCoffe: public Coffee {
public:
    string getDescription() {
        return "Simple Coffe";
    }

    double getCost() {
        return 5.0;
    }
};

// Base Decorator 
class CoffeeDecorator : public Coffee {
protected:
    shared_ptr<Coffee> wrappedCoffee;
public:
    CoffeeDecorator(shared_ptr<Coffee> coffee) : wrappedCoffee(std::move(coffee)) {}
};

// Concrete Decorator
class MilkDecorator : public CoffeeDecorator {
public:
    MilkDecorator(shared_ptr<Coffee> coffee) : CoffeeDecorator(std::move(coffee)) {}

    string getDescription() {
        return wrappedCoffee->getDescription() + ", milk";
    }

    double getCost() {
        return wrappedCoffee->getCost() + 0.25;
    }
};

class SugarDecorator : public CoffeeDecorator {
public:
    SugarDecorator(shared_ptr<Coffee> coffee) : CoffeeDecorator(std::move(coffee)) {}

    string getDescription() {
        return wrappedCoffee->getDescription() + ", sugar";
    }

    double getCost() {
        return wrappedCoffee->getCost() + 1.5;
    }
};


int main() {
    shared_ptr<Coffee> coffee = make_shared<SimpleCoffe>();

    cout << coffee->getDescription() << " " << coffee->getCost()<<endl;

    coffee = make_shared<MilkDecorator>(coffee);
    cout << coffee->getDescription() << " " << coffee->getCost()<<endl;

}