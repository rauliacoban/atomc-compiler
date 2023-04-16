#include "lexical_analyzer.hpp"

LexicalAnalyzer::LexicalAnalyzer(std::string input_file):
        fin(input_file)
{
    if(!fin)
        LOGLINE("ERROR COULD NOT OPEN FILE")
}

