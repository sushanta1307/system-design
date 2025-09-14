#include<iostream>
#include<unordered_map>
using namespace std;

// class KVStoreUnNested {
//     unordered_map<int, int> mainStore;
//     bool inTransaction = false;
//     unordered_map<int, int> tempStore;

// public:
//     pair<bool, int> get(int key) {
//         if(inTransaction) {
//             if(tempStore.find(key) != tempStore.end()) {
//                 return {true, tempStore[key]};
//             }
//         }

//         if(mainStore.find(key) != mainStore.end()) {
//             return {true, mainStore[key]};
//         }

//         return {false, -1};
//     }

//     void set(int key, int val) {
//         if(inTransaction) {
//             tempStore[key] = val;
//         } else {
//             mainStore[key] = val;
//         }
//     }

//     bool begin() {
//         if(inTransaction) return false;
//         inTransaction = true;
//         tempStore.clear();
//         return true;
//     }

//     bool commit() {
//         if(!inTransaction) return false;
//         for(auto &kv: tempStore) {
//             mainStore[kv.first] = kv.second;
//         }
//         tempStore.clear();
//         inTransaction = false;
//         return true;
//     }

//     bool rollback() {
//         if(!inTransaction) return false;
//         inTransaction = false;
//         tempStore.clear();
//         return true;
//     }

// };

class KVStore {
    unordered_map<int, int> mainStore;
    vector<unordered_map<int, int>> tempStore;

public:
    pair<bool, int> get(int key) {
        if(!tempStore.empty()) {
            for(auto it=tempStore.rbegin();it!=tempStore.rend();it++) {
                auto changes = *it;
                if(changes.find(key) != changes.end()) return {true, changes[key]};
            }
        }

        if(mainStore.find(key) != mainStore.end()) {
            return {true, mainStore[key]};
        }

        return {false, -1};
    }

    void set(int key, int val) {
        if(!tempStore.empty()) {
            tempStore.back()[key] = val;
        } else {
            mainStore[key] = val;
        }
    }

    void begin() {
        tempStore.emplace_back();
    }

    bool commit() {
        if(tempStore.empty()) return false;

        auto changes = move(tempStore.back());
        tempStore.pop_back();

        if(!tempStore.empty()) {
            auto &parent = tempStore.back();
            for(auto kv: changes) {
                parent[kv.first] = parent[kv.second];
            }
        } else {
            for(auto kv: changes) {
                mainStore[kv.first] = mainStore[kv.second];
            }
        }
    }

    bool rollback() {
        if(tempStore.empty()) return false;
        tempStore.pop_back();
        return true;
    }

    bool inTransaction() {
        return !tempStore.empty();
    }

};
