#include<iostream>

using namespace std;

class Computer {
public:
    string cpu, gpu;
    int ram, storage;

    Computer(string cpu, string gpu, int ram, int storage) :cpu(cpu), gpu(gpu), storage(storage), ram(ram) {}

    void specs() const {
        cout << "CPU: " << cpu << "\n";
        cout << "GPU: " << gpu << "\n";
        cout << "RAM: " << ram << " GB\n";
        cout << "Storage: " << storage << " GB\n";
    }
};

class ComputerBuilder {
    string cpu, gpu;
    int ram, storage;
public:
    ComputerBuilder& setCPU(string cpu) {
        this->cpu = cpu;
        return *this;
    }

    ComputerBuilder& setGPU(string gpu) {
        this->gpu = gpu;
        return *this;
    }

    ComputerBuilder& setRAM(int ram) {
        this->ram = ram;
        return *this;
    }

    ComputerBuilder& setStorage(int storage) {
        this->storage = storage;
        return *this;
    }

    Computer build() {
        return Computer(cpu, gpu, ram, storage);
    }
};


// Builder interface
// class ComputerBuilder {
// public:
//     virtual ~ComputerBuilder() = default;
//     virtual void buildCPU() = 0;
//     virtual void buildGPU() = 0;
//     virtual void buildRAM() = 0;
//     virtual void buildStorage() = 0;
//     virtual Computer* getComputer() = 0;
// };

// Concrete Builder
// class GamingComputerBuilder : public ComputerBuilder {
// private:
//     Computer* computer;
// 
// public:
//     GamingComputerBuilder() { computer = new Computer(); }
//     void buildCPU() override { computer->setCPU("Intel Core i9"); }
//     void buildGPU() override { computer->setGPU("NVIDIA RTX 4090"); }
//     void buildRAM() override { computer->setRAM("32GB DDR5"); }
//     void buildStorage() override { computer->setStorage("2TB NVMe SSD"); }
//     Computer* getComputer() override { return computer; }
// };

// Director
// class Director {
// private:
//     ComputerBuilder* builder;

// public:
//     void setBuilder(ComputerBuilder* b) { builder = b; }
//     Computer* buildComputer() {
//         builder->buildCPU();
//         builder->buildGPU();
//         builder->buildRAM();
//         builder->buildStorage();
//         return builder->getComputer();
//     }
// };


int main() {
    Computer gamingPC = ComputerBuilder()
                            .setCPU("Intel i9")
                            .setGPU("NVIDIA RTX 4090")
                            .setRAM(64)
                            .setStorage(2000)
                            .build();

    gamingPC.specs();

    std::cout << "\n";

    Computer officePC = ComputerBuilder()
                            .setCPU("Intel i5")
                            .setRAM(16)
                            .build();

    officePC.specs();
    return 0;
}