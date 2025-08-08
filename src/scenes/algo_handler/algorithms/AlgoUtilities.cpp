#include "AlgoUtilities.hpp"

namespace algo {
    // WorkingThreadInfo implementation
    const std::atomic<bool>&
            WorkingThreadInfo::get_stop_flag() const noexcept {
        return stop_flag;
    }

    const std::atomic<bool>&
            WorkingThreadInfo::get_stop_program_flag() const noexcept {
        return is_program_stopped;
    }

    void WorkingThreadInfo::set_stop_flag(bool value) {
        stop_flag = value;
    }

    void WorkingThreadInfo::set_stop_program_flag(bool value) {
        is_program_stopped = value;
    }

    std::thread& WorkingThreadInfo::get_working_thread() {
        return working_thread;
    }

    bool WorkingThreadInfo::get_is_auto() const noexcept {
        return is_auto;
    }

    int WorkingThreadInfo::get_time_for_auto() const noexcept {
        return time_for_auto;
    }

    void WorkingThreadInfo::set_is_auto(bool value) {
        is_auto = value;
    }

    void WorkingThreadInfo::set_time_for_auto(int value) {
        time_for_auto = value;
    }

    // info about working thread
    WorkingThreadInfo thread_info;

    // info about algorithm steps
    AlgoStepsInfo steps_info;

    // delay time for flags check
    inline const auto delay_time = std::chrono::milliseconds(10);

    // implementations of trivial functions

    std::chrono::milliseconds get_delay_time() {
        return delay_time;
    }

    void stop_working_thread_from_within() {
        thread_info.set_stop_flag(true);
        auto delay_time = get_delay_time();
        auto last_check = std::chrono::steady_clock::now();
        while (thread_info.get_stop_flag()) {
            if (thread_info.get_stop_program_flag()) {
                // need for correct thread stop when program end
                throw std::logic_error("Program is over.");
            }
            std::this_thread::sleep_for(delay_time);
            if (thread_info.get_is_auto() &&
                std::chrono::steady_clock::now() - last_check >
                    std::chrono::milliseconds(
                        thread_info.get_time_for_auto())) {
                thread_info.set_stop_flag(false);
            }
        }
    }
    
    void start_working_thread() noexcept {
        thread_info.set_stop_flag(false);
    }

    void end_working_thread() noexcept {
        thread_info.set_stop_program_flag(true);
        thread_info.get_working_thread().join();
    }

    void set_automatic_mode() noexcept {
        thread_info.set_is_auto(true);
    }

    void remove_automatic_mode() noexcept {
        thread_info.set_is_auto(false);
    }

    void speed_up() noexcept {
        auto time_for_auto = thread_info.get_time_for_auto();
        if (time_for_auto < max_milliseconds_time_for_auto) {
            thread_info.set_time_for_auto(time_for_auto / 2);
        }
    }

    void speed_down() noexcept {
        auto time_for_auto = thread_info.get_time_for_auto();
        if (time_for_auto > min_milliseconds_time_for_auto) {
            thread_info.set_time_for_auto(time_for_auto * 2);
        }
    }
} // namespace algo
