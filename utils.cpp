#include "utils.hpp"
#include <iostream>

void utils::show_help() {
    std::cout << "Usage:" << std::endl;
    std::cout << "    jsoner <file> <element_path>" << std::endl;
}

void utils::show_error(const std::string& message) {
    std::cerr << message << std::endl;
    exit(1);
}
