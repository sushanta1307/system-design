#include<iostream>
#include<unordered_map>
#include<set>

using namespace std;

class Booking {
public:
    int id;
    int start, end;
    int userId;

    Booking(int id, int start, int end, int userId) {
        id = id;
        start = start;
        end = end;
        userId = userId;
    }

    bool operator<(const Booking &other) {
        return start < other.start;
    }

};


class MeetingScheduler {
    unordered_map<int, set<Booking>> roomBookings;
    unordered_map<int, pair<int, Booking>> bookingIndex;
    int nextId = 0;
public:
    void addRoom(int roomId) {
        if(!roomBookings.count(roomId)) {
            roomBookings[roomId] = set<Booking>{};
        }
    }

    int book(int userId, int start, int end, int roomId) {
        if(start > end or !roomBookings.count(roomId)) return -1;

        auto &bk = roomBookings[roomId];
        
        auto it = bk.lower_bound(Booking{-1, start, end, userId});

        if(it != bk.end() and it->start <= end) return -1;

        if(it != bk.begin()) {
            auto p = prev(it);
            if(p->end > start) return -1;
        }

        Booking b{nextId++, start, end, userId};
        bk.insert(b);

        bookingIndex[b.id] = {roomId, b};

        return b.id;
    }

    bool cancel(int bookingId) {
        auto it = bookingIndex.find(bookingId);
        if (it == bookingIndex.end()) return false;  // not found

        const int &roomId = it->second.first;
        const Booking &b = it->second.second;

        auto &bk = roomBookings[roomId];
        auto bit = bk.find(b);
        if (bit != bk.end()) {
            bk.erase(bit);            // remove from set
        }
        bookingIndex.erase(it);       // remove from index

        return true;

    }

    vector<int> listAvailable(int start, int end) {
        vector<int> res;
        for (auto &p : roomBookings) {
            const auto &roomId = p.first;
            const auto &bk = p.second;

            bool ok = true;
            auto it = bk.lower_bound(Booking{-1, start, end, 0});

            // check prev
            if (it != bk.begin()) {
                auto p = prev(it);
                if (p->end > start) ok = false;
            }

            // check next
            if (it != bk.end() && it->start < end) ok = false;

            if (ok) res.push_back(roomId);
        }
        return res;
    }
};