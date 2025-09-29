#include<iostream>

using namespace std;

// homeTheatre
class DVDPlayer {
public:
    void on() {
        cout<<"DVD Player ON\n";
    }

    void off() {
        cout<<"DVD Player OFF\n";
    }

    void playMovie(string movie) {
        cout<<"Playing movie "<<movie<<endl;
    }
};

class SoundSystem {
public:
    void on() {
        cout<<"Sound System ON\n";
    }

    void off() {
        cout<<"Sound System OFF\n";
    }

    void setVolume(int level) {
        cout<<"Setting volume level to "<<level<<endl;
    }
};

class Projector {
public:

    void on() {
        cout<<"Projector ON\n";
    }

    void off() {
        cout<<"Projector OFF\n";
    }
};

class HomeTheatreFacade {
    Projector *projector;
    SoundSystem *soundSystem;
    DVDPlayer *dvdPlayer;
public:
    HomeTheatreFacade(Projector* p, SoundSystem *ss, DVDPlayer* dp) :
        projector(p), soundSystem(ss), dvdPlayer(dp) {}

    void watchMovie(string movie) {
        cout << "Get ready to watch a movie..." << endl;
        projector->on();
        soundSystem->on();
        soundSystem->setVolume(10);
        dvdPlayer->on();
        dvdPlayer->playMovie(movie);
        cout<<endl;
    }

    void endMovie() {
        cout << "Shutting movie theater down..." << endl;
        projector->off();
        dvdPlayer->off();
        soundSystem->off();
        cout<<endl;
    }
};

int main() {
    Projector projector;
    SoundSystem soundSystem;
    DVDPlayer dvdPlayer;
    HomeTheatreFacade homeTheatre(&projector, &soundSystem, &dvdPlayer);

    homeTheatre.watchMovie("Saiyara");
    homeTheatre.endMovie();

    return 0;
}