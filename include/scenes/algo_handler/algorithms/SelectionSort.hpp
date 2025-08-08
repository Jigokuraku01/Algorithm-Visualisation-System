#pragma once

#include <concepts>
#include <vector>

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
class SelectionSort {
  public:
    SelectionSort() = default;

    explicit SelectionSort(std::vector<T>&& data) : data(std::move(data)) {}

    explicit SelectionSort(const std::vector<T>& data) : data(data) {}

    // main algorithm method
    void algorithm() try {
        // needed to notify about the start of the algorithm
        algo::StartAlgorithm::start();

        // selection sort:
        for (std::size_t i = 0; i < data.size(); ++i) {
            std::size_t min_index = i;
            for (std::size_t j = i + 1; j < data.size(); ++j) {
                if (data[min_index] > data[j]) {
                    min_index = j;
                }
            }
            if (i != min_index) {
                algo::swap(data[i], data[min_index]);
            }
        }
    // needed when the window is closed
    } catch (std::logic_error& e) {
        return;
    }

  private:
    std::vector<T> data;
};
