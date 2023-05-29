#pragma once
#include "token.hpp"
#include <vector>
#include <list>

class SyntacticAnalyzer{
public:
    std::vector<Token> &tokens;

    SyntacticAnalyzer(std::vector<Token> &tokens);

    bool consume(int code);
};