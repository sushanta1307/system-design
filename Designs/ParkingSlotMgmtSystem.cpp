#include<iostream>
#include<unordered_set>
#include<unordered_map>
#include<queue>

using namespace std;

// add slot
// remove slot
// assign nearest slot to vehicle
class ParkingSlotMgmtSystem {
    unordered_set<int> slots;
    unordered_map<int, int> slotToVehicle;
    unordered_map<int, int> vehicleToSlot;
    priority_queue<int, vector<int>, greater<int>> freeSlots;

public:
    void addSlot(int slotId) {
        slots.insert(slotId);
        slotToVehicle[slotId] = 0;
    }

    int park(int vehicleId) {
        if(vehicleToSlot.find(vehicleId) != vehicleToSlot.end()) return vehicleToSlot[vehicleId];
        
        // remove any slots which are not there
        while(!freeSlots.empty() and slots.find(freeSlots.top()) == slots.end()) freeSlots.pop();
        
        if(freeSlots.empty()) return -1;

        int slotId = freeSlots.top();
        freeSlots.pop();

        vehicleToSlot[vehicleId] = slotId;
        slotToVehicle[slotId] = vehicleId;

        return slotId;
    }

    bool leave(int slotId) {
        if(!slots.count(slotId)) return false;
        if(slotToVehicle[slotId] == 0) return false; // no vehicle parked
        int vehicleId = slotToVehicle[slotId];
        slotToVehicle[slotId] = 0;
        vehicleToSlot.erase(vehicleId);
        freeSlots.push(slotId);

        return true;
    }

    int getSlot(int vehicleId) {
        if(vehicleToSlot.count(vehicleId)) return vehicleToSlot[vehicleId];
        return -1;
    }
};