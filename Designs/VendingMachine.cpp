#include<iostream> 
#include<iomanip>
#include<ctime>

using namespace std;


class Product {
    int id;
    int quantity;
    double price;
    string name;
    bool available;
public:
    Product(int id, string name, double p, int q) :
        id(id), name(name), quantity(q), price(p), available(true) {}

    int getProductId() {
        return id;
    }
    
    string getName() {
        return name;
    }

    double getPrice() {
        return price;
    }

    int getQuantity() {
        return quantity;
    }

    bool isAvailable() {
        return available;
    }

    void setPrice(double newPrice) {
        price = newPrice;
    }

    void addQuantity(int q) {
        quantity += q;
    }

    bool removeQuantity(int q) {
        if(quantity >= q) {
            quantity -= q;
            return true;
        }
        return false;
    }

    void setAvaialble(bool status) {
        available = status;
    }

    void displayInfo() {
        cout << "Product: " << name << " (ID: " << id << ")" << endl;
        cout << "Price: $" << fixed << setprecision(2) << price << endl;
        cout << "Quantity: " << quantity << endl;
        cout << "Status: " << (isAvailable() ? "Available" : "Not Available") << endl;
    }
};

class Transaction {
    int id;
    int productId;
    int quantity;
    double amount;
    time_t timestamp;
    bool successful;
public:
    Transaction(int id, int pId, int q, double amt) {
        id = id;
        productId = pId;
        quantity = q;
        amount = amt;
        timestamp = time(0);
        successful = false;
    }

    int getTransactionId() {
        return id;
    }

    int getProductId() {
        return productId;
    }

    bool isSuccessful() {
        return successful;
    }

    double getAmount() {
        return amount;
    }

    time_t getTimestamp() {
        return timestamp;
    }

    int getQuantity() { 
        return quantity;
    }

    void setSuccessful(bool status) {
        successful = status;
    }

    void displayInfo() {
        cout << "Transaction " << id << ":" << endl;
        cout << "Product ID: " << productId << endl;
        cout << "Quantity: " << quantity << endl;
        cout << "Amount: $" << fixed << setprecision(2) << amount << endl;
        cout << "Status: " << (successful ? "Successful" : "Failed") << endl;
        cout << "Time: " << ctime(&timestamp);
    }
};

class VendingMachine {
    int id;
    bool operational;
    double balance;
    int tId;
    unordered_map<int, Product*> productIdToProductMap;
    vector<Transaction*> transactions;
public:
    VendingMachine(int id) : id(id), operational(true), balance(0), tId(0) {}

    Product* addProduct(int id, string name, double price, int quantity) {
        if(productIdToProductMap.count(id)) {
            cout<<"Product already exists\n";
            return NULL;
        }
        Product* product = new Product(id, name, price, quantity);
        productIdToProductMap[id] = product;
        return product;
    }

    bool removeProduct(int pId) {
        if(!productIdToProductMap.count(pId)) {
            cout<<"Product doesn't exist\n";
            return false;
        }
        productIdToProductMap.erase(pId);
        return true;
    }

    int getMachineId() {
        return id;
    }

    double getCashBalance() {
        return balance;
    }

    bool isOperational()  {
        return operational;
    }

    bool restockProduct(int productId, int quantity) {
        if(!productIdToProductMap.count(productId)) {
            cout<<"Product doesn't exist\n";
            return false;
        }

        Product* product = productIdToProductMap[productId];
        product->addQuantity(quantity);
        return true;
    }

    bool updatePrice(int productId, double price) {
        if(!productIdToProductMap.count(productId)) {
            cout<<"Product doesn't exist\n";
            return false;
        }

        Product* product = productIdToProductMap[productId];
        product->setPrice(price);
        return true;
    }

    void setOperational(bool status) {
        operational = status;
    }

    Transaction* purchaseProduct(int productId, int quantity, double payment) {
        Product* p = productIdToProductMap[productId];
        if(!p or !p->isAvailable() or p->getQuantity() < quantity) {
            cout<<"Product not available\n";
            return NULL;
        }
        double totalCost = p->getPrice()*quantity;
        if(totalCost > payment) {
            cout<<"Insufficient Payment"<<endl;
            return NULL;
        }
        Transaction *t = new Transaction(tId++, productId, quantity, totalCost);
        if(p->removeQuantity(quantity)) {
            balance += totalCost;
            t->setSuccessful(true);
            transactions.push_back(t);
            return t;
        }
        return NULL;
    }

    void addCash(double amount) {
        balance += amount;
    }

    bool withdrawCash(double amount) {
        if(balance < amount) return false;

        balance -= amount;

        return true;
    }
    
    void displayInventory() {
        for(auto [id, product] :  productIdToProductMap) {
            product->displayInfo();
            cout<<"----------"<<endl;
        }
    }
    void displayTransactions() {
        for(auto t: transactions) {
            t->displayInfo();
            cout<<"----------"<<endl;
        }
    }

    void displayMachineInfo() {
        cout << "\nVending Machine Info:" << endl;
        cout << "ID: " << id << endl;
        cout << "Status: " << (operational ? "Operational" : "Out of Service") << endl;
        cout << "Cash Balance: $" << fixed << setprecision(2) << balance << endl;
        cout << "Products Available: " << productIdToProductMap.size() << endl;
        cout << "Total Transactions: " << transactions.size() << endl;
    }


};

int main() { 
    VendingMachine machine(1);
    
    // Add products
    Product* cola = machine.addProduct(1, "Cola", 2.50, 10);
    Product* chips = machine.addProduct(2, "Chips", 1.50, 15);
    Product* candy = machine.addProduct(3, "Candy", 1.00, 20);
    
    // Display initial inventory
    cout << "Initial machine status:" << endl;
    machine.displayMachineInfo();
    machine.displayInventory();
    
    // Make some purchases
    cout << "\nMaking purchases..." << endl;
    Transaction* t1 = machine.purchaseProduct(cola->getProductId(), 2, 5.00);
    Transaction* t2 = machine.purchaseProduct(chips->getProductId(), 3, 5.00);
    
    // Display transactions
    machine.displayTransactions();
    
    // Restock a product
    cout << "\nRestocking Cola..." << endl;
    machine.restockProduct(cola->getProductId(), 5);
    
    // Update price
    cout << "\nUpdating Candy price..." << endl;
    machine.updatePrice(candy->getProductId(), 1.25);
    
    // Display final status
    cout << "\nFinal machine status:" << endl;
    machine.displayMachineInfo();
    machine.displayInventory();
    
    return 0;
    return 0;
}