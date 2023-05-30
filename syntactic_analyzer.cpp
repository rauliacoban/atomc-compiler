#include "syntactic_analyzer.hpp"
#include <string.h>

void SyntacticAnalyzer::exitError(std::string msg){
    LOGLINE("Stopped at index " << index << " string: " << tokens[index].value.string_)
    LOGLINE(msg)
    exit(1);
}