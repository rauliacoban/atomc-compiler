#pragma once
#include "token.hpp"
#include <list>

class LexicalAnalyzer{
public:
    std::list<Token> tokens;
    std::fstream fin;

    LexicalAnalyzer(std::string input_file);
};