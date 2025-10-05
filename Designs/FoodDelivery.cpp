#include<iostream>

using namespace std;

class FoodDelivery {
    unordered_map<int, int> DriverIdToPay;
    double toalCost = 0.0;
public:
    void addDriver(int id, int payPerHour) {
        DriverIdToPay[id] = payPerHour;
    }

    void removeDriver(int id) {
        DriverIdToPay.erase(id);
    }

    bool recordDelivery(int id, double startTime, double endTime) {
        if(startTime >= endTime) return false;
        if(DriverIdToPay.find(id) == DriverIdToPay.end()) return false;
        toalCost += (endTime - startTime) * DriverIdToPay[id];
        return true; 
    }

    double totalCost() {
        return toalCost;
    }
};