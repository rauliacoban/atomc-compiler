#pragma once
#include "token.hpp"
#include <list>

class LexicalAnalyzer{
public:
    std::list<Token> tokens;
    std::ifstream fin;

    LexicalAnalyzer();

    void parse(std::string input_file);
};