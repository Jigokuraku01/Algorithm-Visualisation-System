#pragma once

#include <concepts>
#include <vector>

#include "IVisualizedAlgorithm.hpp"
#include "AlgoUtilities.hpp"

// some cringe
// template <typename T>
// concept comparable = requires(const algo::remove_type_wrapper_t<T>& first,
//                   const algo::remove_type_wrapper_t<T>& second) {
//     { first == second } -> std::convertible_to<bool>;
//     { first != second } -> std::convertible_to<bool>;
//     { first <= second } -> std::convertible_to<bool>;
//     { first >= second } -> std::convertible_to<bool>;
//     { first < second } -> std::convertible_to<bool>;
//     { first > second } -> std::convertible_to<bool>;
// };

template <typename T>
class BubbleSort {
  public:
    BubbleSort() = default;

    explicit BubbleSort(std::vector<T>&& data) : data(std::move(data)) {}

    explicit BubbleSort(const std::vector<T>& data) : data(data) {}

    // main algorithm method
    void algorithm() try {
        // needed to notify about the start of the algorithm
        algo::StartAlgorithm::start();

        // bubble sort:
        bool swapped = false;
        for (std::size_t i = 0; i < data.size() - 1UL; ++i) {
            for (std::size_t j = 0; j < data.size() - 1UL - i; ++j) {
                if (data[j] > data[j + 1]) {
                    algo::swap(data[j], data[j + 1]);
                    swapped = true;
                }
            }
            if (!swapped) {
                break;
            }
        }
    // needed when the window is closed
    } catch (std::logic_error& e) {
        return;
    }

  private:
    std::vector<T> data;
};