#pragma once
#include "token.hpp"
#include <vector>
#include <list>

class LexicalAnalyzer{
public:
    std::vector<Token> tokens;
    std::ifstream fin;

    LexicalAnalyzer();

    void parse(std::string input_file);
};