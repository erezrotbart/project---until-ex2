#ifndef EXECUTOR_H
#define EXECUTOR_H

#include <thread>
#include <functional>
//handles new thread
class Executor {
public:
    void execute(std::function<void()> command);
};

#endif
