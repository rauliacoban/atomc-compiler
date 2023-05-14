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
    Value(char x){
        char_ = x;
    };
    Value(std::string x){
        string_ = x;
    };
    Value(){}

    std::string string_;
    int int_;
    float float_;
    char char_;

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
    Token(TOKENS type, char value):
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
    Token():
        type{TOKENS::NONETYPE},
        value{0}{
    }

    Token(const Token &token):
        type{token.type}{
            switch (type)
            {
            case TOKENS::CT_INT:
                value.int_ = token.value.int_;
                break;
            case TOKENS::CT_REAL:
                value.float_ = token.value.float_;
                break;
            case TOKENS::CT_CHAR:
                value.char_ = token.value.char_;
                break;
            case TOKENS::CT_STRING:
                value.string_ = token.value.string_;
                break;
            default:
                value.int_ = token.value.int_;
                break;
            }
    };

    TOKENS type;
    Value value;
};