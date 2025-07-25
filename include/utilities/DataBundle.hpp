#pragma once
#include "PossibleAlgos.hpp"
#include <Parser.hpp>
#include <iterator>
#include <string>
#include <vector>

class DataBundle
{
    public:
        std::size_t get_window_h();
        std::size_t get_window_w();
        PossibleAlgorithms get_algo();
        std::string get_file_path();
        bool is_file_path_exists();
        bool is_auto();

    private:
        ParserCommand parser_command_;
};