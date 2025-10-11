#include<iostream>
#include<ctime>
#include<map>
#include<unistd.h>
using namespace std;

enum Size {
    SMALL,
    MEDIUM,
    LARGE
};

class Vehicle {
    string licenseNumber;
    Size size;
public:
    Vehicle(string ln, Size sz) : licenseNumber(ln), size(sz) {}

    string getLicenseNumber() {
        return licenseNumber;
    }

    Size getSize() {
        return size;
    }

    void displayInfo() {
        cout<<"LicenseNumber: "<<licenseNumber<<endl;
        cout<<"Size: "<<size<<endl;
        cout<<"------"<<endl;
    }
};

class Bike : public Vehicle {
public:
    Bike(string licenseNumber) : Vehicle(licenseNumber, Size::SMALL) {} 
};

class Car : public Vehicle {
public:
    Car(string licenseNumber) : Vehicle(licenseNumber, Size::MEDIUM) {} 
};

class Truck : public Vehicle {
public:
    Truck(string licenseNumber) : Vehicle(licenseNumber, Size::LARGE) {} 
};

class ParkingSpot {
    int spotId;
    Size vehicleSize;
    bool isOccupied;
    Vehicle* parkedVehicle;

public:
    ParkingSpot(int id, Size size): spotId(id), vehicleSize(size), isOccupied(false), parkedVehicle(NULL) {}

    bool canFitVehicle(Vehicle* vehicle) {
        Size size = vehicle->getSize();
        if(size <= vehicleSize) {
            return true;
        }

        return false;
    }

    bool isAvailable() {
        return !isOccupied;
    }

    Vehicle* getVehicle() {
        return parkedVehicle;
    }

    bool parkVehicle(Vehicle* vehicle) {
        if(isOccupied or !canFitVehicle(vehicle)) return false;
        isOccupied = true;
        parkedVehicle = vehicle;
        return true;
    }

    Vehicle* unparkVehicle() {
        if(!isOccupied) return NULL;
        isOccupied = false;
        auto temp = parkedVehicle;
        parkedVehicle = NULL;

        return temp;
    }

    void displayInfo() {
        cout<<"spotId: "<<spotId<<endl;
        cout<<"isOccupied: "<<isOccupied<<endl;
        cout<<"Size: "<<vehicleSize<<endl;
        
        if(isOccupied) {
            cout<<"Vehicle Number: "<<parkedVehicle->getLicenseNumber()<<endl;
        }

        cout<<"---------"<<endl;
    }
};

class ParkingFloor {
    vector<ParkingSpot*> parkingSpots;
    int floorNumber;
public:
    ParkingFloor(int fn) : floorNumber(fn) {
        for(int spot=0;spot<3;spot++) {
            parkingSpots.push_back(new ParkingSpot(spot, Size::SMALL));
        }
        for(int spot=3;spot<6;spot++) {
            parkingSpots.push_back(new ParkingSpot(spot, Size::MEDIUM));
        }
        for(int spot=6;spot<10;spot++) {
            parkingSpots.push_back(new ParkingSpot(spot, Size::LARGE));
        }
    }

    void addParkingSpots(ParkingSpot* parkingSpot) {
        parkingSpots.push_back(parkingSpot);
    }

    ParkingSpot* findAvailableSpot(Vehicle* vehicle) {
        vector<ParkingSpot*>::iterator it = find_if(parkingSpots.begin(), parkingSpots.end(), 
            [vehicle](ParkingSpot* spot) {
                return spot->isAvailable() and spot->canFitVehicle(vehicle);
            });

        return it != parkingSpots.end() ? *it : NULL;
    }

    void displayInfo() {
        cout<<"Displaying info of the parking spots of the floor "<<floorNumber<<endl;
        for(auto spot: parkingSpots) {
            spot->displayInfo();
            cout<<endl;
        }
    }
};

class ParkingTicket {
    int ticketId;
    long long startTime;
    ParkingSpot *parkingSpot;
    Vehicle* vehicle;

public:
    ParkingTicket(int id, long long start, ParkingSpot* spot, Vehicle* vh) :
        ticketId(id), startTime(start), parkingSpot(spot), vehicle(vh) {}

    ParkingSpot* getSpot() {
        return parkingSpot;
    }

    Vehicle* getVehicle() {
        return vehicle;
    }

    long long getStartTime() {
        return startTime;
    }
};


// Singleton
// we assume there are 2 floors, each with 10 (3 + 3 + 4) parking spots
class ParkingLotSystem {
    static ParkingLotSystem* instance;
    vector<ParkingFloor*> parkingFloors;
    int capacity = 20;
    int availableSpots = 20;
    int ticketId = 0;
    map<string, ParkingSpot*> occupiedSpots;
    map<string, ParkingTicket*> vehicleToTicketMap;

    ParkingLotSystem() {
        for(int floor=0;floor<2;floor++) {
            parkingFloors.emplace_back(new ParkingFloor(floor));
        }
    }

public:
    static ParkingLotSystem* getInstance() {
        if(!instance) {
            instance = new ParkingLotSystem();
        }
        return instance;
    }

    // void addFloor(ParkingFloor* floor) {
    //     parkingFloors.emplace_back(floor);
    // }

    bool parkVehicle(Vehicle* vehicle) {
        if(!vehicle) return false;

        ParkingSpot* spot = NULL;
        for(auto floors: parkingFloors) {
            spot = floors->findAvailableSpot(vehicle);
            if(spot) break;
        }

        if(!spot) return false;

        if(spot->parkVehicle(vehicle)) {
            ParkingTicket* ticket = new ParkingTicket(ticketId++, time(0), spot, vehicle);
            occupiedSpots[vehicle->getLicenseNumber()] = spot;
            vehicleToTicketMap[vehicle->getLicenseNumber()] = ticket;
            availableSpots--;
            return true;
        }

        return false;
    }

    Vehicle* unParkVehicle(string licenseNumber) {
        auto it = occupiedSpots.find(licenseNumber);
        if(it == occupiedSpots.end()) return NULL;

        ParkingSpot* spot = it->second;
        Vehicle* vehicle = spot->unparkVehicle();
        if(vehicle) {
            availableSpots++;
            auto ticket = vehicleToTicketMap[licenseNumber];
            long long duration = time(0) - ticket->getStartTime();
            cout<<"Please pay $"<<duration*0.2<<endl;
            occupiedSpots.erase(licenseNumber);
            vehicleToTicketMap.erase(licenseNumber);
        }

        return vehicle;
    }
    
    void displayInfo() const {
        cout << "\nParking Lot Status:" << endl;
        cout << "Total Capacity: " << capacity << endl;
        cout << "Available Spots: " << availableSpots << endl;
        cout<<"<><><><<><><><><><><><<<><><><>"<<endl;
        // for(auto floor: parkingFloors) {
        //     floor->displayInfo();
        // }
    }
};

ParkingLotSystem* ParkingLotSystem::instance = NULL;

int main() {
     // Create parking lot with different types of spots
    ParkingLotSystem *parkingLot = ParkingLotSystem::getInstance();  // 2 compact, 3 regular, 2 large spots
    
    std::cout << "Initial parking lot status:" << std::endl;
    parkingLot->displayInfo();
    
    // Create vehicles
    Vehicle* car1 = new Car("CAR001");
    Vehicle* car2 = new Car("CAR002");
    Vehicle* motorcycle = new Bike("MOTO001");
    Vehicle* truck = new Truck("TRUCK001");
    
    // Park vehicles
    std::cout << "\nParking vehicles..." << std::endl;
    
    if (parkingLot->parkVehicle(car1)) {
        std::cout << "Parked successfully: ";
        car1->displayInfo();
    }
    
    if (parkingLot->parkVehicle(motorcycle)) {
        std::cout << "Parked successfully: ";
        motorcycle->displayInfo();
    }
    
    if (parkingLot->parkVehicle(truck)) {
        std::cout << "Parked successfully: ";
        truck->displayInfo();
    }
    
    // Display current status
    parkingLot->displayInfo();

    sleep(3);
    
    // Remove a vehicle
    std::cout << "\nRemoving vehicle CAR001..." << std::endl;
    Vehicle* removed = parkingLot->unParkVehicle("CAR001");
    if (removed) {
        std::cout << "Removed successfully: ";
        removed->displayInfo();
        delete removed;
    }
    
    // Try to park another car
    if (parkingLot->parkVehicle(car2)) {
        std::cout << "Parked successfully: ";
        car2->displayInfo();
    }
    
    // Final status
    std::cout << "\nFinal parking lot status:" << std::endl;
    parkingLot->displayInfo();
    
    // Cleanup remaining vehicles
    delete car2;
    delete motorcycle;
    delete truck;
    
    return 0;
}