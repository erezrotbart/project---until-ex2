#include "Executor.h"
// Executes the given command in a new detached thread
void Executor::execute(std::function<void()> command) {
    std::thread(command).detach();
}
