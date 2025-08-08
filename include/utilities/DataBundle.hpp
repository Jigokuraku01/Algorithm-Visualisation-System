#pragma once
#include "PossibleAlgos.hpp"
#include <Parser.hpp>
#include <iterator>
#include <string>
#include <vector>

class DataBundle {
  public:
    [[nodiscard]] std::size_t get_window_h() const;
    [[nodiscard]] std::size_t get_window_w() const;
    [[nodiscard]] PossibleAlgorithms get_algo() const {
        return parser_command_.algo_;
    }
    [[nodiscard]] const std::vector<int>& get_array() const {
        return parser_command_.array_;
    }
    [[nodiscard]] std::string get_file_path() const;
    [[nodiscard]] bool is_file_path_exists() const;
    [[nodiscard]] bool is_auto() const {
      return parser_command_.is_auto_;
    }

  // private:
    ParserCommand parser_command_;
};