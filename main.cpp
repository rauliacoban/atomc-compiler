#include <iostream>
#include "log.hpp"
#include "lexical_analyzer.hpp"
#include <list>

//#include <boost/format.hpp>
//#include <boost/lexical_cast.hpp>
//#include <boost/program_options.hpp>

int main(){
    LOGLINE("merrydo")

    std::list<Token> tokens;
    tokens.emplace_back(TOKENS::INT);

    LOGLINE(tokens.front().value.int_)

    LexicalAnalyzer analyzer("./tests/0.c");
}