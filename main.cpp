#include <iostream>
#include <fstream>
#include "log.hpp"
#include "lexical_analyzer.hpp"
#include "syntactic_analyzer.hpp"
#include <list>
#include <vector>

//#include <boost/format.hpp>
//#include <boost/lexical_cast.hpp>
//#include <boost/program_options.hpp>

int main(){
    LOGLINE("merrydo")

    //LOGLINE(tokens.front().value.int_)

    LexicalAnalyzer lexical;
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

    std::vector<std::string> output_files = {
        "./result/0.txt",
        "./result/1.txt",
        "./result/2.txt",
        "./result/3.txt",
        "./result/4.txt",
        "./result/5.txt",
        "./result/6.txt",
        "./result/7.txt",
        "./result/8.txt",
        "./result/9.txt"
    };

    for(size_t i = 0; i < test_files.size(); i ++){
        //LOGLINE("   --- " << i << " ---")
        lexical.parse(test_files[i]);

        std::ofstream out(output_files[i]);
        for(size_t k = 0; k < lexical.tokens.size(); k++)
            out << (int)lexical.tokens[k].type << " " << lexical.tokens[k].as_string << "\n";
        out.close();

        SyntacticAnalyzer syntactic(lexical.tokens);
        bool success = syntactic.unit();
        
        LOGLINE_CHANNEL(i, success);
    }
}