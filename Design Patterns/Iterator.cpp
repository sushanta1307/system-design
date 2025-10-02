#include<iostream>

using namespace std;

class Iterator {
public:
    virtual bool hasNext() = 0;
    virtual string next() = 0;
};

class Aggregate {
public:
    virtual Iterator* createIterator() = 0;
};

class ChannelIterator: public Iterator {
    vector<string> channels;
    int index = 0;
public:
    ChannelIterator(vector<string> channels) : channels(channels) {}

    bool hasNext() { 
        return index < channels.size();
    }

    string next() {
        if(hasNext()) {
            return channels[index++];
        }
        return "";
    }
};

class ChannelCollection : public Aggregate {
    vector<string> channels;
public:
    void addChannel(string channel) {
        channels.push_back(channel);
    }

    vector<string> getChannels() {
        return channels;
    }

    Iterator* createIterator() {
        return new ChannelIterator(channels);
    }
};

int main() {
    ChannelCollection channels;
    channels.addChannel("HBO");
    channels.addChannel("ESPN");
    channels.addChannel("Discovery");
    channels.addChannel("NatGeo");

    Iterator* it = channels.createIterator();

    cout << "TV Channels: " << endl;
    while (it->hasNext()) {
        cout << "- " << it->next() << endl;
    }

    return 0;
}