#pragma once
#include "tokens.hpp"
#include<string>
#include "log.hpp"

class Value{
public:
    Value(TOKENS type, std::string x){
        switch (type){
            case TOKENS::CT_INT:
                //int_ = stoi(x);
                int_ = 1;
                break;
            case TOKENS::CT_REAL:
                //float_ = stof(x);
                float_ = 2.0;
                break;
            case TOKENS::CT_CHAR:
                //char_ = x.c_str()[0];
                char_ = 'a';
                break;
            case TOKENS::CT_STRING:
                string_ = x;
                break;
            default:
                string_ = x;
                break;
        }
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
    Token(TOKENS type, std::string val_string):
        type{type},
        as_string{val_string},
        value(type, val_string){
    }
    Token():
        type{TOKENS::NONETYPE},
        as_string{"NOVALUE"},
        value{TOKENS::CT_INT, "1"}{
    }

    Token(const Token &token):
        type{token.type},
        as_string{token.as_string}{
            switch (type){
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
                    value.string_ = token.value.string_;
                    break;
            }
    }

    TOKENS type;
    std::string as_string;
    Value value;
};