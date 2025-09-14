#include<iostream>
#include<thread>

using namespace std;

class Singleton {
protected:
    static Singleton* instance;
    Singleton(int v) : val(v) {}
    
public:
    int val;
    static Singleton* getInstance(int v) {
        if(instance == NULL) {
            instance = new Singleton(v);
        }
        return instance;
    }

    // Not cloneable
    Singleton(Singleton &other) = delete;

    // Not assignable
    void operator=(const Singleton &) = delete;

};

Singleton *Singleton::instance = NULL;

int main() {
    thread thread1([] {
        this_thread::sleep_for(chrono::milliseconds(30));
        Singleton *instance = Singleton::getInstance(5);
        cout<<"calling thread1, "<<instance->val<<endl;
    });

    thread thread2([]{
        this_thread::sleep_for(chrono::milliseconds(40));
        Singleton *instance = Singleton::getInstance(10);
        cout<<"calling thread2, "<<instance->val<<endl;
    });

    thread1.join();
    thread2.join();

    return 0;
}