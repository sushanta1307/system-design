#include<iostream>
#include<unordered_map>

using namespace std;

class Spotify {
    unordered_map<int, string> songIdToName;
    unordered_map<int, vector<int>> userToSongs;
    unordered_map<int, int> playCount;
    vector<int> globalSongs;
    int songId = 0;
    int k = 3;

public:
    void addSong(string songName) {
        songIdToName[songId++] = songName;
    }

    void playSong(int songId, int userId) {
        if(songIdToName.find(songId) == songIdToName.end()) {
            cout<<"Song not available";
            return;
        }

        cout<<"playing song "<<songIdToName[songId]<<endl;

        userToSongs[userId].push_back(songId);
        globalSongs.push_back(songId);
        playCount[songId]++;
    }

    // print how much a song is played
    void printAnalytics() {
        for(auto [id, song]: songIdToName) {
            cout<<"Song "<<song<<" played "<< playCount[id]<<endl;
        }
    }

    void lastKPlayed(int userId) {
        int n = userToSongs[userId].size();
        int start = max(0, n-k);
        for(;start<n;start++) {
            cout << "Song " << songIdToName[userToSongs[userId][start]] << endl;
        }
    }

    void lastKPlayedGlobal() {
        int n = globalSongs.size();
        int start = max(0, n-k);
        for(;start<n;start++) {
            cout << "Song " << songIdToName[globalSongs[start]] << endl;
        }
    }
    
};