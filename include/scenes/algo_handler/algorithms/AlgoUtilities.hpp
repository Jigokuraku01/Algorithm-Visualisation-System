#pragma once

#include "IAlgoObject.hpp"

#include <atomic>
#include <chrono>
#include <functional>
#include <iostream>
#include <thread>

// namespace for algorithm utilities 
namespace algo {
    // some trivial functions
    const std::atomic<bool>& get_stop_flag();
    const std::atomic<bool>& get_stop_program_flag();
    void set_stop_flag(bool value);
    void set_stop_program_flag(bool value);
    std::chrono::milliseconds get_delay_time();
    std::thread& get_working_thread();
    void stop_working_thread_from_within();
    void start_working_thread() noexcept;
    void end_working_thread() noexcept;

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
            set_stop_flag(true);
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
        // like a basic swap:.?V
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

    // set lambda to working thread
    template <typename ReturnTypes, typename... Args>
    void set_function_for_thread(std::function<ReturnTypes(Args...)>&& func,
                                 Args&&... args) {
        get_working_thread() = std::thread(func, std::forward<Args>(args)...);
    }
} // namespace algo
