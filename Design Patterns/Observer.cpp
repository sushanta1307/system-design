#include<iostream>
#include <unordered_set>

using namespace std;

class Observer {
public:
    virtual void update(string msg) = 0;
};

class Subject {
public:
    virtual void subscribe(Observer* o) = 0; // addObserver
    virtual void unsubscribe(Observer* o) = 0; // removeObserver
    virtual void notifyObservers(string msg) = 0;
};

class Subscriber : public Observer {
    string name;
public:
    Subscriber(string nm) : name(nm) {}

    void update(string msg) {
        cout<<name<<" received notification ->"<<msg<<endl;
    }
};

class YoutubeChannel : public Subject {
    string channelName;
    unordered_set<Observer*> subscribers;
public:
    YoutubeChannel(string name) : channelName(name) {}

    void subscribe(Observer* o) {
        subscribers.insert(o);
    }

    void unsubscribe(Observer* o) {
        subscribers.erase(o);
    }

    void notifyObservers(string msg) {
        for(auto obs: subscribers) {
            obs->update(msg);
        }
    }

    void uploadVideo(string title) {
        cout<<"Uploaded video - "<<title<<endl;
        notifyObservers("New Video Uploaded: " + title);
    }
};


int main() {
    YoutubeChannel channel("YTChannel");

    Subscriber s1("subscriber1");
    Subscriber s2("subscriber2");

    channel.subscribe(&s1);
    channel.subscribe(&s2);

    channel.uploadVideo("Design Patterns");
    
    channel.unsubscribe(&s1);
    channel.uploadVideo("Solid Principles");
}