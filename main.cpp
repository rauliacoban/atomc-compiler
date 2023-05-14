#include <iostream>
#include "log.hpp"
#include "lexical_analyzer.hpp"
#include <list>
#include <vector>

//#include <boost/format.hpp>
//#include <boost/lexical_cast.hpp>
//#include <boost/program_options.hpp>

int main(){
    LOGLINE("merrydo")

    //LOGLINE(tokens.front().value.int_)

    LexicalAnalyzer analyzer;
    std::vector<std::string> test_files = {
        "./tests/0.c",
        "./tests/1.c",
        "./tests/2.c",
        "./tests/3.c",
        "./tests/4.c",
        "./tests/5.c",
        "./tests/6.c",
        "./tests/7.c",
        "./tests/8.c",
        "./tests/9.c"
    };

    for(size_t i = 0; i < test_files.size(); i ++)
        analyzer.parse(test_files[i]);

    //for(int i = 0; i < analyzer.tokens.size(); i++){
        
    //}
}