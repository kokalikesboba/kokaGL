#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H

#include <thread>
#include <vector>

class WorkerThread {
public:
    WorkerThread();
    ~WorkerThread();
private:
    int maxThreads;
    std::vector<std::thread> workers;
};

#endif