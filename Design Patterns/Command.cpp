#include<iostream>

using namespace std;

// abstract command
class Command {
public:
    virtual void execute() = 0;
    virtual void undo() = 0;
};

// Receiver
class Light {
public:
    void turnOn() {
        cout<<"Light turned on"<<endl;
    }

    void turnOff() {
        cout<<"Light turned off"<<endl;
    }
};

// concrete command
class LightOnCommand: public Command {
    Light *light;
public:
    LightOnCommand(Light* l) : light(l) {}

    void execute() {
        light->turnOn();
    }

    void undo() {
        light->turnOff();
    }
};

class LightOffCommand: public Command {
    Light *light;
public:
    LightOffCommand(Light* l) : light(l) {}

    void execute() {
        light->turnOff();
    }

    void undo() {
        light->turnOn();
    }
};

class Remote {
    Command *command;
    stack<Command*> history;
public:
    void setCommand(Command *cmd){
        history.push(cmd);
        command = cmd;
    }

    void pressButton() {
        if(command) command->execute();
    }

    void undo() {
        if(!history.empty()) {
            auto& lastCmd = history.top();
            history.pop();
            lastCmd->undo();
        } else {
            cout<<"Nothing to undo\n";
        }
    }
};


int main() {
    Light light;
    Remote remote;

    LightOnCommand *lightOnCommand = new LightOnCommand(&light);
    LightOffCommand *lightOffCommand = new LightOffCommand(&light);

    remote.setCommand(lightOnCommand);
    remote.pressButton();

    remote.setCommand(lightOffCommand);
    remote.pressButton();

    remote.undo();
    remote.undo();
    remote.undo();

    return 0;
}