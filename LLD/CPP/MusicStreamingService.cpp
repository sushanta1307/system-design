#include<iostream>
#include<list>

using namespace std;

enum Genre {
    POP,
    HIPHOP, 
    DEVOTIONAL,
    ROCK,
    CLASSICAL
};

class Song {
    string songId;
    string title;
    string artist;
    Genre genre;
    int durationInSeconds;
public:
    Song(string id, string title, string artist, Genre genre, int duration) :
        songId(id), title(title), artist(artist), genre(genre), durationInSeconds(duration) {}

    string getSongId() {
        return songId;
    }

    string getTitle() {
        return title;
    }

    string getArtist() {
        return artist;
    }

    Genre getGenre() {
        return genre;
    }

    int getDuration() { 
        return durationInSeconds;
    }

    void displayInfo() {
        cout << "Song: " << title << " (ID: " << songId << ")" << endl;
        cout << "Artist: " << artist << endl;
        cout << "Genre: ";
        switch (genre) {
            case Genre::POP: cout << "Pop"; break;
            case Genre::ROCK: cout << "Rock"; break;
            case Genre::CLASSICAL: cout << "Classical"; break;
            case Genre::HIPHOP: cout << "Hip Hop"; break;
            case Genre::DEVOTIONAL: cout << "Devotional"; break;
        }
        cout<<endl;
        cout << "Duration: " << durationInSeconds << " seconds" << endl;
    }
};

class Artist {
    string artistId;
    string name;
    list<Song*> songsByArtist;
public:
    Artist(string id, string name) : artistId(id), name(name) {}

    string getArtistId() {
        return artistId;
    }

    string getName() {
        return name;
    }

    list<Song*> getSongs() {
        return songsByArtist;
    }

    void addSong(Song* song) {
        songsByArtist.push_back(song);
    }

    void removeSong(Song* song) {
        songsByArtist.remove(song);
    }

    void displayInfo() {
        cout<<"Artist: "<< name<< " (ID: " << artistId << ")" << endl;
        cout<<"Listing down the songs: \n";
        for(auto song: songsByArtist) {
            cout<<".......\n";
            song->displayInfo();
            cout<<"-----------\n\n";
        }
    }
};

class Playlist {
    string playlistId;
    string name;
    list<Song*> songs;
    bool isPublic;
public:
    Playlist(string id, string name, bool isPublic = true) :
        playlistId(id), name(name), isPublic(isPublic) {}

    string getPlaylistId() {
        return playlistId;
    }

    string getPlaylistName() {
        return name;
    }

    list<Song*> getSongs() {
        return songs;
    }

    void addSong(Song* song) {
        auto it = find(songs.begin(), songs.end(), song);
        if(it != songs.end()) {
            cout<<"Song already exists\n";
            return;
        }
        songs.push_back(song);
    }

    void removeSong(Song* song) {
        auto it = find(songs.begin(), songs.end(), song);
        if(it == songs.end()) {
            cout<<"Song doesn't exists\n";
            return;
        }
        songs.erase(it);
    }

    void displayInfo() {
        cout << "\nPlaylist: " << name << " (ID: " << playlistId << ")" << endl;
        cout << "Visibility: " << (isPublic ? "Public" : "Private") << endl;
        cout << "Number of Songs: " << songs.size() << endl;

        if (!songs.empty()) {
            cout << "\nSongs:" << endl;
            for (const auto& song : songs) {
                cout << "- " << song->getTitle() << " by " << song->getArtist() << endl;
            }
        }
    }
    
};

enum UserType {
    FREE,
    PREMIUM
};

class User {
    string userId;
    string userName;
    string email;
    UserType type;
    vector<Playlist*> playlists;
public:
    User(string id, string name, string email, UserType type = UserType::FREE) :
        userId(id), userName(name), email(email), type(type) {}

    string getUserId() {
        return userId;
    }

    string getUserName() {
        return userName;
    }

    string getEmail() {
        return email;
    }

    UserType getType() {
        return type;
    }

    void addPlaylist(Playlist* playlist) {
        playlists.push_back(playlist);
    }

    void removePlaylist(Playlist* playlist) {
        auto it = find(playlists.begin(), playlists.end(), playlist);

        if(it == playlists.end()) {
            cout<<"Palylist not found"<<endl;
            return;
        }

        playlists.erase(it);
    }

    void upgradeToPremium() {
        if(type == UserType::PREMIUM) {
            cout<<"Already a premium user"<<endl;
            return;
        }
        type = UserType::PREMIUM;
    }

    vector<Playlist*> getPlaylists() {
        return playlists;
    }

    void displayInfo() const {
        cout << "User: " << userName << " (ID: " << userId << ")" << endl;
        cout << "Email: " << email << endl;
        cout << "Type: " << (type == UserType::PREMIUM ? "Premium" : "Free") << endl;
        cout << "Number of Playlists: " << playlists.size() << endl;
    } 

};

class MusicStreamingService {
    vector<User*> users;
    vector<Artist*> artists;
    vector<Song*> songs;
    int playlistId = 1;

    Playlist* findPlaylist(const std::string& playlistId) const {
        for (auto& user : users) {
            for (auto& playlist : user->getPlaylists()) {
                if (playlist->getPlaylistId() == playlistId) {
                    return playlist;
                }
            }
        }
        return nullptr;
    }

    User* findUser(string userId) {
        auto it = find_if(users.begin(), users.end(), [&userId](User* user) {
            return user->getUserId() == userId;
        });

        if(it == users.end()) {
            cout<<"user not found"<<endl;
            return NULL;
        }

        return *it;
    }

    Artist* findArtist(string artistId) {
        auto it = find_if(artists.begin(), artists.end(), [&artistId](Artist* artist) {
            return artist->getArtistId() == artistId;
        });

        if(it == artists.end()) {
            cout<<"user not found"<<endl;
            return NULL;
        }

        return *it;
    }

    Song* findSong(string songId) {
        auto it = find_if(songs.begin(), songs.end(), [&songId](Song* song) {
            return song->getSongId() == songId;
        });

        if(it == songs.end()) {
            cout<<"Song not found"<<endl;
            return nullptr;
        }

        return *it;
    }

public:
    void addUser(User* user) {
        users.push_back(user);
    }

    void addArtist(Artist* artist) {
        artists.push_back(artist);
    }

    void addSong(Song* song) {
        songs.push_back(song);
    }

    Playlist* createPlaylist(string name, string userId, bool isPublic = true) {
        User *user = findUser(userId);
        Playlist* playlist = new Playlist("playlistId" + to_string(playlistId), name, isPublic);
        playlistId++;

        user->addPlaylist(playlist);

        return playlist;
    }

    bool addSongToPlaylist(string playlistId, string songId) {
        Playlist* playlist = findPlaylist(playlistId);
        if(!playlist) {
            cout<<"Playlist not found"<<endl;
            return false;
        }

        Song* song = findSong(songId);
        if(!song) {
            cout<<"Song not found"<<endl;
            return false;
        }

        playlist->addSong(song);

        return true;
    }

    bool removeSongFromPlaylist(string playlistId, string songId) {
        Playlist* playlist = findPlaylist(playlistId);
        if(!playlist) {
            cout<<"Playlist not found"<<endl;
            return false;
        }

        Song* song = findSong(songId);
        if(!song) {
            cout<<"Song not found"<<endl;
            return false;
        }

        playlist->removeSong(song);

        return true;
    }
    
    // vector<Song*> searchSongs(const string& query) const;
    // vector<Artist*> searchArtists(const string& query) const;
    // vector<Playlist*> searchPlaylists(const string& query) const;
    
    // void displayAllSongs() const;
    // void displayAllArtists() const;
    // void displayUserPlaylists(string userId) const;
    // void displayArtistSongs(string artistId) const;
};

int main() {
    MusicStreamingService service;
    
    // Create users
    User* user1 = new User("U001", "john_doe", "john@email.com");
    User* user2 = new User("U002", "jane_smith", "jane@email.com", UserType::PREMIUM);
    service.addUser(user1);
    service.addUser(user2);
    
    // Create artists
    Artist* artist1 = new Artist("A001", "The Beatles");
    Artist* artist2 = new Artist("A002", "Queen");
    service.addArtist(artist1);
    service.addArtist(artist2);
    
    // Add songs
    Song* song1 = new Song("S001", "Hey Jude", "The Beatles", 
                          Genre::ROCK, 431);
    Song* song2 = new Song("S002", "Let It Be", "The Beatles",
                          Genre::ROCK, 243);
    Song* song3 = new Song("S003", "Bohemian Rhapsody", "Queen",
                          Genre::ROCK, 354);
    
    service.addSong(song1);
    service.addSong(song2);
    service.addSong(song3);
    
    // Display all songs and artists
    std::cout << "Initial catalog:" << std::endl;
    // service.displayAllSongs();
    // service.displayAllArtists();
    
    // Create playlists
    Playlist* playlist1 = service.createPlaylist("U001", "Rock Classics",
                                               "Best rock songs of all time");
    if (playlist1) {
        service.addSongToPlaylist(playlist1->getPlaylistId(), "S001");
        service.addSongToPlaylist(playlist1->getPlaylistId(), "S003");
    }
    
    Playlist* playlist2 = service.createPlaylist("U002", "Beatles Only", false);
    if (playlist2) {
        service.addSongToPlaylist(playlist2->getPlaylistId(), "S001");
        service.addSongToPlaylist(playlist2->getPlaylistId(), "S002");
    }
    
    // Display user playlists
    std::cout << "\nUser Playlists:" << std::endl;
    // service.displayUserPlaylists("U001");
    // service.displayUserPlaylists("U002");
    
    // Search functionality
    std::cout << "\nSearching for 'Beatles':" << std::endl;
    // auto songResults = service.searchSongs("Beatles");
    // for (const auto& song : songResults) {
    //     song->displayInfo();
    // }
    
    // Remove song from playlist
    std::cout << "\nRemoving 'Hey Jude' from Rock Classics playlist..." << std::endl;
    if (service.removeSongFromPlaylist(playlist1->getPlaylistId(), "S001")) {
        std::cout << "Song removed successfully" << std::endl;
        // service.displayUserPlaylists("U001");
    }
    
    // Upgrade user to premium
    std::cout << "\nUpgrading user john_doe to premium..." << std::endl;
    user1->upgradeToPremium();
    user1->displayInfo();
    
    return 0;
}