#pragma once

#include "IAlgoObject.hpp"

#include <atomic>
#include <chrono>
#include <functional>
#include <iostream>
#include <thread>

// namespace for algorithm utilities 
namespace algo {
    
    // some constants 

    const int default_milliseconds_time_for_auto(1000);
    const int max_milliseconds_time_for_auto(8000);
    const int min_milliseconds_time_for_auto(125);

    // some trivial functions

    class WorkingThreadInfo {
      public:

        // some getters and setters

        [[nodiscard]] const std::atomic<bool>& get_stop_flag() const noexcept;
        [[nodiscard]] const std::atomic<bool>& get_stop_program_flag() const noexcept;
        void set_stop_flag(bool value);
        void set_stop_program_flag(bool value);
        std::thread& get_working_thread();    
        [[nodiscard]] bool get_is_auto() const noexcept;
        [[nodiscard]] int get_time_for_auto() const noexcept;
        void set_is_auto(bool value);
        void set_time_for_auto(int value);

        // set lambda to working thread
        template <typename ReturnTypes, typename... Args>
        void set_function_for_thread(std::function<ReturnTypes(Args...)>&& func,
                                    Args&&... args) {
            working_thread = std::thread(func, std::forward<Args>(args)...);
        }

      private:
        // working thread in which the algorithm is executed
        std::thread working_thread;

        // flag for stopping working thread
        std::atomic<bool> stop_flag = false;

        // flag for correct working thread delete when program end
        std::atomic<bool> is_program_stopped = false;

        // flag showing automatic algorithm or not
        bool is_auto = false;

        // time between algorithm steps for auto
        int time_for_auto = default_milliseconds_time_for_auto;
    };

    std::chrono::milliseconds get_delay_time();
    void stop_working_thread_from_within();
    void start_working_thread() noexcept;
    void end_working_thread() noexcept;
    void set_automatic_mode() noexcept;
    void remove_automatic_mode() noexcept;
    void speed_up() noexcept;
    void speed_down() noexcept;

    extern WorkingThreadInfo thread_info;

    template <typename T> 
    class TypeWrapper;

    template <typename T> 
    void swap(TypeWrapper<T>& first, TypeWrapper<T>& second) noexcept(false);

    // class for notification about the start of the algorithm 
    class StartAlgorithm {
      public:
        static void start() noexcept(false) {
            std::cout << "The algorithm has begun!!!" << std::endl;
            stop_working_thread_from_within();
        }
    };

    // class that passes information about operations on a type to AlgoObjects
    template <typename T>
    class TypeWrapper {
      public:
        // main constructor
        TypeWrapper(const T* value, IAlgoObject*& object)
            : value(value), object(object) {}  

        // friend declaration
        friend void swap<>(TypeWrapper<T>& first, 
            TypeWrapper<T>& second) noexcept(false);

        // compare operator (so far only one)
        bool operator>(TypeWrapper& other) noexcept(false) {
            CompareAnimation::run_compare_anim(object, other.object);
            stop_working_thread_from_within();
            return *value > *(other.value);
        }
    
      private:
        const T* value;
        IAlgoObject* object;
    };

    // swap array elements, run swap animation and stop working thread
    template <typename T>
    void swap(TypeWrapper<T>& first, TypeWrapper<T>& second) noexcept(false) {
        SwapAnimation::run_swap_anim(first.object, second.object);
        // like a basic swap
        std::swap(first.value, second.value);
        std::swap(first.object, second.object);
        stop_working_thread_from_within();
    }

    // metafunction to remove the wrapper
    // template <typename T>
    // struct remove_type_wrapper {
    //     using type = T;
    // };

    // template <typename T>
    // struct remove_type_wrapper<TypeWrapper<T>> {
    //     using type = T;
    // };

    // template <typename T>
    // using remove_type_wrapper_t = remove_type_wrapper<T>::type;
} // namespace algo
