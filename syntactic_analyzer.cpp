#include "syntactic_analyzer.hpp"
#include <string.h>

void exitError(std::string msg){
    LOGLINE(msg)
    exit(1);
}