#pragma once

#include "PossibleAlgos.hpp"
#include <iterator>
#include <string>
#include <vector>
class ParserCommand {
  public:
    [[nodiscard]] std::size_t get_window_h() const;
    [[nodiscard]] std::size_t get_window_w() const;
    [[nodiscard]] PossibleAlgorithms get_algo() const;
    [[nodiscard]] std::string get_file_path() const;
    [[nodiscard]] bool is_file_path_exists() const;
    [[nodiscard]] bool is_auto() const;

  // private:
    std::size_t window_h_;
    std::size_t window_w_;
    PossibleAlgorithms algo_;
    std::string file_path_;
    bool is_file_path_exists_;
    bool is_auto_;
};

class Parser {};
