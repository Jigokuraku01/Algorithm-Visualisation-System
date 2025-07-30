#include <Parser.hpp>

ParserCommand::ParserCommand(std::size_t window_h, std::size_t window_w,
                             PossibleAlgorithms algo, std::string&& file_path,
                             bool is_file_path_exists, bool is_auto)
    : window_h_(window_h), window_w_(window_w), algo_(algo),
      file_path_(std::move(file_path)),
      is_file_path_exists_(is_file_path_exists), is_auto_(is_auto){};

ParserCommand Parser::parse(int argc, char* argv[]) {
}