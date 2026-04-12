#include<iostream>
#include<queue>
#include<mutex>
#include<condition_variable>
#include<atomic>
#include<vector>
#include<thread>
#include<chrono>

using namespace std;

using TaskFn = function<void()>;
using TaskId = int;

class Task {
public:
    TaskId taskId;
    int priority;
    TaskFn fn;

    Task(){}

    Task(TaskId tId, int p, TaskFn fn) : taskId(tId), priority(p), fn(fn) {}

    bool operator<(const Task &other) const {
        if(priority == other.priority) {
            return taskId > other.taskId;
        }

        return priority < other.priority;
    }
};

class Scheduler {
    priority_queue<Task> pq;
    atomic<TaskId> nextId;
    bool stopFlag;
    mutex mu;
    condition_variable cv;
    vector<thread> workers;
public:

    Scheduler(int cnt) {
        nextId = 1;
        stopFlag = false;
        int workers_count = max(cnt, 1);
        for(int i=0;i<workers_count;i++) {
            // thread t(workerLoop, this, i);
            // workers.push_back(std::move(t));
            workers.emplace_back(&Scheduler::workerLoop, this, i); // emplace_back constructs the object inplace
        }
    }

    ~Scheduler() {
        stop();
    }

    void stop() {
        {
            lock_guard<mutex> lg(mu);
            stopFlag = true;
        }
        cv.notify_all();
        for(auto &th: workers) {
            if(th.joinable()) th.join();
        }
    }

    TaskId addTask(TaskFn fn, int priority) {
        lock_guard<mutex> lg(mu);
        Task t(nextId++, priority, std::move(fn));
        pq.push(std::move(t));
        cv.notify_one();
        return t.taskId;
    }


    void workerLoop(int idx){
        while(1) {
            Task task;
            {
                unique_lock<mutex> lk(mu);
                cv.wait(lk, [this] {
                    return stopFlag || !pq.empty();
                });

                if(stopFlag and pq.empty()) return;

                task = pq.top();
                pq.pop();
            }

            try {
                task.fn();
            } catch (exception &e) {
                cout<<"Error in worker "<<idx<<" : "<<e.what()<<endl;
            }
        }
    }

};

int main() {
    Scheduler sched(3);

    sched.addTask([] {
        cout << "[low ] long task start on thread " << this_thread::get_id() << "\n";
        this_thread::sleep_for(chrono::seconds(3));
        cout << "[low ] long task done\n";
    }, 1);

    this_thread::sleep_for(chrono::milliseconds(100));

    // high-priority short tasks should be picked by idle workers immediately
    for (int i = 0; i < 5; ++i) {
        sched.addTask([i] {
            cout << "[high] quick " << i << " on thread " << this_thread::get_id() << "\n";
            this_thread::sleep_for(chrono::milliseconds(200));
        }, 10);
    }

    // medium priority
    sched.addTask([] {
        cout << "[med ] medium task on thread " << this_thread::get_id() << "\n";
    }, 5);

    // allow tasks to run
    this_thread::sleep_for(chrono::seconds(5));
    sched.stop();

    cout << "Scheduler stopped\n";

    return 0;
}