#ifndef TASK_H
#define TASK_H

#include <future>


class task {
private:
    std::promise<void> exit_contract;
    std::future<void> exit_signal;

public:
    task() : exit_signal(exit_contract.get_future()) {};

    task(task && t) : exit_contract(std::move(t.exit_contract)), exit_signal(std::move(t.exit_signal)) {};

    task & operator=(task && t) {
        exit_contract = std::move(t.exit_contract);
        exit_signal = std::move(t.exit_signal);
        return *this;
    }

    virtual void run() = 0;

    void operator()() {
        run();
    }

    bool stop_requested() {
        if (exit_signal.wait_for(std::chrono::milliseconds(0)) == std::future_status::timeout)
            return false;
        return true;
    }

    virtual void stop() {
        exit_contract.set_value();
    }

};

#endif  /* TASK_H */
