#pragma once
#include "tokens.hpp"
#include<string>
#include "log.hpp"

union Value{
public:
    Value(int x){
        int_ = x;
    };
    Value(float x){
        float_ = x;
    };
    Value(std::string x){
        string_ = x;
    };

    std::string string_;
    int int_;
    float float_;

    ~Value(){};
};

class Token{
public:
    Token(TOKENS type, int value):
        type{type},
        value{value}{
    };
    Token(TOKENS type, float value):
        type{type},
        value{value}{
    };
    Token(TOKENS type, std::string value):
        type{type},
        value{value}{
    };
    Token(TOKENS type):
        type{type},
        value{0}{
    };

    TOKENS type;
    Value value;
};