#include<iostream>

using namespace std;

// Target Interface
class USBDevice {
public:
    virtual void connectWithUSB() = 0;
};

// Incompatible Device (Adaptee)
class SDCard {
public:
    void insertSDCard() {
        cout << "SD Card inserted." << endl;
    }
    void transferData() {
        cout << "Transferring data from SD Card..." << endl;
    }
};

// Adapter
class CardReaderAdapter : public USBDevice {
    SDCard* sdCard;
public:
    CardReaderAdapter(SDCard* sdc) : sdCard(sdc) {}

    void connectWithUSB() {
        cout << "Card Reader is transferring data via USB." << endl;
        sdCard->insertSDCard();
        sdCard->transferData();
    }
};

// Client
class Laptop {
public:
    void plugInUSB(USBDevice* device) {
        cout << "Laptop: USB device detected." << endl;
        device->connectWithUSB();
    }
};

int main() {
    Laptop laptop;
    SDCard sdCard;
    CardReaderAdapter device(&sdCard);
    
    laptop.plugInUSB(&device);

    return 0;
}
