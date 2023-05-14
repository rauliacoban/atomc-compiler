#include "lexical_analyzer.hpp"
#include<string.h>

LexicalAnalyzer::LexicalAnalyzer()
{
    
}

bool isAlpha_(char c){
    return (isalpha(c) or c == '_');
}

bool isDigit(char c){
    return isdigit(c);
}

void logIllegalInput(int iter, char c){
    LOGLINE("ERROR INVALID INPUT at char" << iter << "|" << c << "|")
    exit(1);
}

bool isKeyword(std::string std){
    return false;
}

void LexicalAnalyzer::parse(std::string input_file)
{
    tokens.resize(1);
    fin = std::ifstream(input_file);
    if(!fin){
        LOGLINE("ERROR COULD NOT OPEN FILE " << input_file)
    }
    
    int state = 0;
    std::string data;
    int iter = 0;
    bool get_new = 1;
    char c;

    while(!fin.eof()){
        if(get_new)
            fin.get(c);

        //LOGLINE(iter << " " << state << " " << c << " " << data)

        switch (state){
            case 0:
                data = "";
                if(isAlpha_(c)){
                    state = 1;
                    data += c;
                }
                else if(c == '0'){
                    data += c;
                    state = 4;
                }
                else if(c >= '1' && c <= '9'){
                    state = 7;
                    data += c;
                }
                else if(c == '\''){
                    state = 20;
                    data += c;
                }
                else if(c == '\"'){
                    state = 24;
                    data += c;
                }
                else if(c == '&'){
                    state = 30;
                    data += c;
                }
                else if(c == '|'){
                    state = 32;
                    data += c;
                }
                else if(c == '='){
                    state = 34;
                    data += c;
                }
                else if(c == '!'){
                    state = 37;
                    data += c;
                }
                else if(c == '<'){
                    state = 40;
                    data += c;
                }
                else if(c == '>'){
                    state = 43;
                    data += c;
                }
                else if(isspace(c)){
                    state = 0;
                    //tokens.emplace_back(TOKENS::SPACE, c);
                }
                else if(c == '/'){
                    state = 52;
                    data += c;
                }
                else if(c == '+'){
                    state = 0;
                    tokens.emplace_back(TOKENS::ADD, "+");
                }
                else if(c == '-'){
                    state = 0;
                    tokens.emplace_back(TOKENS::SUB, "-");
                }
                else if(c == '*'){
                    state = 0;
                    tokens.emplace_back(TOKENS::MUL, "*");
                }
                else if(c == '.'){
                    state = 0;
                    tokens.emplace_back(TOKENS::DOT, ".");
                }
                else if(c == ','){
                    state = 0;
                    tokens.emplace_back(TOKENS::COMMA, ",");
                }
                else if(c == ';'){
                    state = 0;
                    tokens.emplace_back(TOKENS::SEMICOLON, ";");
                }
                else if(c == '('){
                    state = 0;
                    tokens.emplace_back(TOKENS::LPAR, "(");
                }
                else if(c == ')'){
                    state = 0;
                    tokens.emplace_back(TOKENS::RPAR, ")");
                }
                else if(c == '['){
                    state = 0;
                    tokens.emplace_back(TOKENS::LBRACKET, "[");
                }
                else if(c == ']'){
                    state = 0;
                    tokens.emplace_back(TOKENS::RBRACKET, "]");
                }
                else if(c == '{'){
                    state = 0;
                    tokens.emplace_back(TOKENS::LACC, "{");
                }
                else if(c == '}'){
                    state = 0;
                    tokens.emplace_back(TOKENS::RACC, "}");
                }
                else{
                    logIllegalInput(iter, c);
                }
                get_new = true;
                break;
            case 1:
                if(isAlpha_(c) or isDigit(c)){
                    state = 1;
                    data += c;
                }
                else{
                    state = 0;
                    get_new = false;
                    if(isKeyword(data)){
                        //add keyword
                    }
                    tokens.emplace_back(TOKENS::ID, data);
                }
                break;
            case 4:
                if(c == 'x' or c == 'X'){
                    state = 6;
                    data += c;
                }
                else if(c >= '0' and c <= '7'){
                    state = 5;
                    data += c;
                }
                else if(c == 'e' or c == 'E'){
                    state = 12;
                    data += c;
                }
                else if(c == '.'){
                    state = 10;
                    data += c;
                }
                else{
                    state = 0;
                    get_new = false;
                    tokens.emplace_back(TOKENS::CT_INT, data);
                }
                break;
            case 5:
                if(c >= '0' and c <= '7'){
                    data += c;
                }
                else{
                    state = 0;
                    get_new = false;
                    tokens.emplace_back(TOKENS::CT_INT, data);
                }
                break;
            case 6:
                if((c >= '0' and c <= '9')
                        or (c >= 'a' and c <= 'z')
                        or (c >= 'A' and c <= 'Z')){
                    data += c;
                }
                else{
                    state = 0;
                    get_new = false;
                    tokens.emplace_back(TOKENS::CT_INT, data);
                }
                break;
            case 7:
                if(isDigit(c)){
                    data += c;
                }
                else if(c == '.'){
                    data += c;
                    state = 10;
                }
                else if(c == 'e' or c == 'E'){
                    data += c;
                    state = 12;
                }
                else{
                    state = 0;
                    get_new = false;
                    tokens.emplace_back(TOKENS::CT_INT, data);
                }
                break;
            case 10:
                if(isDigit(c)){
                    data += c;
                    get_new = true;
                    state = 11;
                }
                else{
                    logIllegalInput(iter, c);
                }
                break;
            case 11:
                if(isDigit(c)){
                    data += c;
                    get_new = true;
                }
                else if(c == 'e' or c == 'E'){
                    data += c;
                    get_new = true;
                    state = 12;
                }
                else{
                    get_new = false;
                    state = 0;
                    tokens.emplace_back(TOKENS::CT_REAL, data);
                }
                break;
            case 12:
                if(c == '-' or c == '+'){
                    data += c;
                    get_new = true;
                    state = 13;
                }
                else if(isDigit(c)){
                    data += c;
                    get_new = true;
                    state = 14;
                }
                else{
                    logIllegalInput(iter, c);
                }
                break;
            case 13:
                if(isDigit(c)){
                    data += c;
                    get_new = true;
                    state = 14;
                }
                else{
                    logIllegalInput(iter, c);
                }
                break;
            case 14:
                if(isDigit(c)){
                    data += c;
                    get_new = true;
                }
                else{
                    state = 0;
                    get_new = false;
                    tokens.emplace_back(TOKENS::CT_REAL, data);
                }
                break;
            case 20:
                if(c == '\\'){
                    data += c;
                    get_new = true;
                    state = 21;
                }
                else if(c != '\''){
                    data += c;
                    get_new = true;
                    state = 22;
                }
                else{
                    logIllegalInput(iter, c);
                }
                break;
            case 21:
                if(strchr("abfnrtv'?\"0\\", c)){
                    data += c;
                    get_new = true;
                    state = 22;
                }
                else{
                    logIllegalInput(iter, c);
                }
                break;
            case 22:
                if(c == '\''){
                    data += c;
                    get_new = true;
                    state = 0;
                    tokens.emplace_back(TOKENS::CT_CHAR, data);
                }
                else{
                    logIllegalInput(iter, c);
                }
            case 24:
                if(c == '\\'){
                    data += c;
                    get_new = true;
                    state = 25;
                }
                else if(c == '\"'){
                    data += c;
                    get_new = true;
                    state = 0;
                    tokens.emplace_back(TOKENS::CT_STRING, data);
                }
                else{
                    data += c;
                }
                break;
            case 25:
                if(strchr("abfnrtv'?\"0\\", c)){
                    data += c;
                    get_new = true;
                    state = 24;
                }
                else{
                    logIllegalInput(iter, c);
                }
                break;
            case 30:
                if(c == '&'){
                    state = 0;
                    get_new = true;
                    tokens.emplace_back(TOKENS::AND, "&&");
                }
                else{
                    logIllegalInput(iter, c);
                }
                break;
            case 32:
                if(c == '|'){
                    state = 0;
                    get_new = true;
                    tokens.emplace_back(TOKENS::OR, "||");
                }
                else{
                    logIllegalInput(iter, c);
                }
                break;
            case 34:
                if(c == '='){
                    state = 0;
                    get_new = true;
                    tokens.emplace_back(TOKENS::EQUAL, "==");
                }
                else{
                    state = 0;
                    get_new = false;
                    tokens.emplace_back(TOKENS::ASSIGN, "=");
                }
                break;
            case 37:
                if(c == '='){
                    state = 0;
                    get_new = true;
                    tokens.emplace_back(TOKENS::NOTEQ, "!=");
                }
                else{
                    state = 0;
                    get_new = false;
                    tokens.emplace_back(TOKENS::NOT, "!");
                }
                break;
            case 40:
                if(c == '='){
                    state = 0;
                    get_new = true;
                    tokens.emplace_back(TOKENS::LESSEQ, "<=");
                }
                else{
                    state = 0;
                    get_new = false;
                    tokens.emplace_back(TOKENS::LESS, "<");
                }
                break;
            case 43:
                if(c == '='){
                    state = 0;
                    get_new = true;
                    tokens.emplace_back(TOKENS::GREATER_EQ, ">=");
                }
                else{
                    state = 0;
                    get_new = false;
                    tokens.emplace_back(TOKENS::GREATER, ">");
                }
                break;
            case 52:
                if(c == '/'){
                    data += c;
                    get_new = true;
                    state = 53;
                }
                else if(c == '*'){
                    data += c;
                    get_new = true;
                    state = 55;
                }
                else{
                    get_new = false;
                    state = 0;
                    tokens.emplace_back(TOKENS::DIV, "/");
                }
                break;
            case 53:
                if(!strchr("\n\r\0", c)){
                    data += c;
                    get_new = true;
                }
                else{
                    state = 0;
                    get_new = false;
                    //tokens.emplace_back(TOKENS::LINECOMMENT, data);
                }
                break;
            case 55:
                if(c == '*'){
                    get_new = true;
                    state = 56;
                }
                else{
                    data += c;
                    get_new = true;
                }
                break;
            case 56:
                if(c == '/'){
                    data += c;
                    state = 0;
                    get_new = true;
                    //tokens.emplace_back(TOKENS::COMMENT, data);
                }
                else{
                    data += c;
                    get_new = true;
                    state = 55;
                }
                break;

            default:
                break;
        }

        iter++;
    }

    fin.close();
}