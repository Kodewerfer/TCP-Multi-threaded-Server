#pragma once

#include <atomic>
#include <condition_variable>
#include <functional>
#include <string>
#include <thread>
#include <vector>

#include "../Lib.hpp"
#include "../ServerUtils.hpp"

class ThreadsMan {
   private:
    static std::atomic<int> ThreadsCount;
    static std::atomic<int> ThreadsActive;

   public:
    static std::vector<std::thread> ThreadStash;
    static std::condition_variable condCreateMore;

    static void incrThreadsCount();
    static void decrThreadsCount();
    static int getThreadsCount() { return ThreadsCount; }

    static void setActiveAndNotify();
    static void notActive();
    static int getActiveThreads() { return ThreadsActive; }

    /**
     * Thread initialize with this function,
     * invokes other functions
     * */
    static void ForeRunner(ServerSockets ServSockets,
                           std::function<void(const int)> ShellCallback,
                           std::function<void(const int)> FileCallback);
};