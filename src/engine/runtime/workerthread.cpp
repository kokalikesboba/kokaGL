#include "workerthread.h"

WorkerThread::WorkerThread()
{
    maxThreads = std::thread::hardware_concurrency();
}
