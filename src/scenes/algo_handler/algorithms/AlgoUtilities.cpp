#include "AlgoUtilities.hpp"

namespace algo {
    // working thread in which the algorithm is executed
    std::thread working_thread;

    // flag for stopping working thread
    std::atomic<bool> stop_flag(false);

    // flag for correct working thread delete when program end
    std::atomic<bool> is_program_stopped(false);

    // delay time for flags check
    inline const auto delay_time = std::chrono::milliseconds(10);

    // implementations of trivial functions

    const std::atomic<bool>& get_stop_flag() {
        return stop_flag;
    }

    const std::atomic<bool>& get_stop_program_flag() {
        return is_program_stopped;
    }
    
    void set_stop_flag(bool value) {
        stop_flag = value;
    }

    void set_stop_program_flag(bool value) {
        is_program_stopped = value;
    }

    std::chrono::milliseconds get_delay_time() {
        return delay_time;
    }

    std::thread& get_working_thread() {
        return working_thread;
    }

    void stop_working_thread_from_within() {
        set_stop_flag(true);
        auto delay_time = get_delay_time();
        while (get_stop_flag()) {
            if (get_stop_program_flag()) {
                // need for correct thread stop when program end
                throw std::logic_error("Program is over.");
            }
            std::this_thread::sleep_for(delay_time);
        }
    }

    void start_working_thread() noexcept {
        set_stop_flag(false);
    }

    void end_working_thread() noexcept {
        set_stop_program_flag(true);
    }
} // namespace algo