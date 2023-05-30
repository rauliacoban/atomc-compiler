#pragma once
#include "token.hpp"
#include <vector>
#include <list>

void exitError(std::string msg);
class SyntacticAnalyzer{
public:
    void exitError(std::string msg);
    std::vector<Token> &tokens;
    int index = 0;
    int consumed = -1;

    SyntacticAnalyzer(std::vector<Token> &tokens):
        tokens(tokens){
    }
    
    bool consume(TOKENS code){
        if(tokens[index].type == code){
            consumed = index;
            index++;
            return true;
        }
        return false;
    }

    bool unit(){
        while(true){
            if(declStruct()){}
            else if(declFunc()){}
            else if(declVar()){}
            else break;
        }
        if(!consume(TOKENS::END))
            exitError("[unit] missing END");
        return true;
    }

    bool declStruct(){
        int fallback = index;
        if(consume(TOKENS::STRUCT)){
            if(consume(TOKENS::ID)){
                if(consume(TOKENS::LACC)){
                    while(true){
                        if(declVar()){}
                        else break;
                    }
                    if(consume(TOKENS::RACC)){
                        if(consume(TOKENS::SEMICOLON)){
                            return true;
                        }
                        else exitError("[declStruct] missing SEMICOLON");
                    }
                    else exitError("[declStruct] missing RACC");
                }
                else{
                    index = fallback;
                    return false;
                };
            }
            else exitError("[declStruct] missing STRUCT");
        }
        return false;
    }

    bool declVar(){
        if(typeBase()){
            if(consume(TOKENS::ID)){
                if(arrayDecl()){}
                while(1){
                    if(consume(TOKENS::COMMA)){
                        if(consume(TOKENS::ID)){
                            if(arrayDecl()){}
                        }
                        else exitError("[declVar] missing ID");
                    }
                    else break;
                }
                if(consume(TOKENS::SEMICOLON)){
                    return true;
                }
                else exitError("[declVar] missing SEMICOLON");
            }
            else exitError("[declVar] missing ID");
        }
        return false;
    }

    bool typeBase(){
        if(consume(TOKENS::INT)){ return true;}
        else if(consume(TOKENS::DOUBLE)){ return true;}
        else if(consume(TOKENS::CHAR)){ return true;}
        else if(consume(TOKENS::STRUCT)){ 
            if(consume(TOKENS::ID)){ 
                return true;
            }
            else exitError("[typeBase] missing ID");   
        }
        return false;
    }

    bool arrayDecl(){
        if(consume(TOKENS::LBRACKET)){
            if(expr()){}
            if(consume(TOKENS::RBRACKET)){
                return true;
            }
            else exitError("[arrayDecl] missing RBRACKET");
        }
        return false;
    }

    bool typeName(){
        if(typeBase()){
            if(arrayDecl()){}
            return true;
        }
        else return false;
    }

    bool declFunc(){
        int fallback = index;

        if(typeBase()){
            if(consume(TOKENS::MUL)){} 
        }
        else if(consume(TOKENS::VOID)){}
        else return false;

        if(consume(TOKENS::ID)){
            if(consume(TOKENS::LPAR)){
                if(funcArg()){
                    while(true){
                        if(consume(TOKENS::COMMA)){
                            if(funcArg()){}
                            else exitError("[declFunc] missing funcArg");
                        }
                        else break;
                    }
                }
                if(consume(TOKENS::RPAR)){
                    if(stmCompound()){
                        return true;
                    }
                    else exitError("[declFunc] missing stmCompound");
                }
                else exitError("[declFunc] missing RPAR");
            }
            else{
                index = fallback;
                return false;
            }

        }
        else exitError("[declFunc] missing ID");

        return false; //make compiler stop crying
    }

    bool funcArg(){
        if(typeBase()){
            if(consume(TOKENS::ID)){
                if(arrayDecl()){}
            }
            else exitError("[funcArg] missing ID");
        }
        return false;
    }

    bool stm(){
        if(stmCompound())
            return true;
        else if(consume(TOKENS::IF)){
            if(consume(TOKENS::LPAR)){
                if(expr()){
                    if(consume(TOKENS::RPAR)){
                        if(stm()){
                            if(consume(TOKENS::ELSE)){
                                if(stm()){}
                                else exitError("[stm] missing stm");
                            }
                            return true;
                        }
                        else exitError("[stm] missing stm");
                    }
                    else exitError("[stm] missing RPAR1");
                }
                else exitError("[stm] missing expr");
            }
            else exitError("[stm] missing LPAR");
        }
        else if(consume(TOKENS::WHILE)){
            if(consume(TOKENS::LPAR)){
                if(expr()){
                    if(consume(TOKENS::RPAR)){
                        if(stm()){
                            return true;
                        }
                        else exitError("[stm] missing stm");
                    }
                    else exitError("[stm] missing RPAR2");
                }
                else exitError("[stm] missing expr");
            }
            else exitError("[stm] missing LPAR");
        }
        else if(consume(TOKENS::FOR)){
            if(consume(TOKENS::LPAR)){
                if(expr()){}
                if(consume(TOKENS::SEMICOLON)){
                    if(expr()){}
                    if(consume(TOKENS::SEMICOLON)){
                        if(expr()){}
                        if(consume(TOKENS::RPAR)){
                            if(stm()){
                                return true;
                            }
                            else exitError("[stm] missing stm");
                        }
                        else exitError("[stm] missing RPAR3");
                    }
                    else exitError("[stm] missing SEMICOLON1");
                }
                else exitError("[stm] missing SEMICOLON2");
            }
            else exitError("[stm] missing LPAR");
        }
        else if(consume(TOKENS::BREAK)){
            if(consume(TOKENS::SEMICOLON)){
                return true;
            }
            else exitError("[stm] missing SEMICOLON3");
        }
        else if(consume(TOKENS::RETURN)){
            if(expr()){}
            if(consume(TOKENS::SEMICOLON)){
                return true;
            }
            else exitError("[stm] missing SEMICOLON4");
        }
        else if(expr()){
                if(consume(TOKENS::SEMICOLON)){
                    return true;
                }
                else exitError("[stm] missing SEMICOLON5");
        }
        else if(consume(TOKENS::SEMICOLON)){
            return true;
        }
        return false;
    }

    bool stmCompound(){
        if(consume(TOKENS::LACC)){
            while(true){
                if(declVar()){}
                else if(stm()){}
                else break;
            }
            if(consume(TOKENS::RACC)){
                return true;
            }
            else exitError("[stmCompound] missing RACC");
        }
        return false;
    }

    bool expr(){
        if(exprAssign()){
            return true;
        }
        return false;
    }

    bool exprAssign(){
        int fallback = index;
        bool go_back = false;
        if(exprUnary()){
            if(consume(TOKENS::ASSIGN)){
                if(exprAssign()){
                    return true;
                }
                else exitError("[exprAssign] missing exprAssign");
            }
            else{
                index = fallback;
                go_back = true;
            }
        }
        else if(exprOr()){
            return true;
        }
        if(go_back){
            if(exprOr()){
                return true;
            }
        }
        return false;
    }

    bool exprOr(){
        if(exprAnd()){
            while(true){
                if(consume(TOKENS::OR)){
                    if(exprAnd()){}
                    else exitError("[exprOr] missing exprAnd");
                }
                else break;
            }
            return true;
        }
        return false;
    }

    bool exprAnd(){
        if(exprEq()){
            while(true){
                if(consume(TOKENS::AND)){
                    if(exprEq()){}
                    else exitError("[exprAnd] missing exprEq");
                }
                else break;
            }
            return true;
        }
        return false;
    }

    bool exprEq(){
        if(exprRel()){
            while(true){
                if(consume(TOKENS::EQUAL) or consume(TOKENS::NOTEQ)){
                    if(exprRel()){}
                    else exitError("[exprEq] missing exprRel");
                }
                else break;
            }
            return true;
        }
        return false;
    }

    bool exprRel(){
        if(exprAdd()){
            while(true){
                if(consume(TOKENS::LESS) or consume(TOKENS::LESSEQ) or consume(TOKENS::GREATER) or consume(TOKENS::GREATER_EQ)){
                    if(exprAdd()){}
                    else exitError("[exprRel] missing exprAdd");
                }
                else break;
            }
            return true;
        }
        return false;
    }

    bool exprAdd(){
        if(exprMul()){
            while(true){
                if(consume(TOKENS::ADD) or consume(TOKENS::SUB)){
                    if(exprMul()){}
                    else exitError("[exprAdd] missing exprMul");
                }
                else break;
            }
            return true;
        }
        return false;
    }

    bool exprMul(){
        if(exprCast()){
            while(true){
                if(consume(TOKENS::MUL) or consume(TOKENS::DIV)){
                    if(exprCast()){}
                    else exitError("[exprMul] missing exprCast");
                }
                else break;
            }
            return true;
        }
        return false;
    }

    bool exprCast(){
        if(consume(TOKENS::LPAR)){
            if(typeName()){
                if(consume(TOKENS::RPAR)){
                    if(exprCast()){
                        return true;
                    }
                    else exitError("[exprCast] missing exprCast");
                }
                else exitError("[exprCast] missing RPAR");
            }
            else exitError("[exprCast] missing typeName");
        }
        else if(exprUnary()){
            return true;
        }
        return false;
    }

    bool exprUnary(){
        if(consume(TOKENS::SUB) or consume(TOKENS::NOT)){
            if(exprUnary()){
                return true;
            }
            else exitError("[exprUnary] missing exprUnary");
        }
        else if(exprPostfix()){
            return true;
        }
        return false;
    }

    bool exprPostfix(){
        if(exprPrimary()){
            while(true){
                if(consume(TOKENS::LBRACKET)){
                    if(expr()){
                        if(consume(TOKENS::RBRACKET)){}
                        else exitError("[exprPostfix] missing RBRACKET");
                    }
                    else exitError("[exprPostfix] missing expr");
                }
                else if(consume(TOKENS::DOT)){
                    if(consume(TOKENS::ID)){}
                    else exitError("[exprPostfix] missing ID");
                }
                else break;
            }
            return true;
        }
        return false;
    }

    bool exprPrimary(){
        if(consume(TOKENS::ID)){
            if(consume(TOKENS::LPAR)){
                if(expr()){
                    while(true){
                        if(consume(TOKENS::COMMA)){
                            if(expr()){}
                            else exitError("[exprPrimary] missing expr");
                        }
                        else break;
                    }
                }
                if(consume(TOKENS::RPAR)){
                    return true;
                }
                else exitError("[exprPrimary] missing RPAR");
            }
            return true;
        }
        else if(consume(TOKENS::CT_INT)){
            return true;
        }
        else if(consume(TOKENS::CT_REAL)){
            return true;
        }
        else if(consume(TOKENS::CT_CHAR)){
            return true;
        }
        else if(consume(TOKENS::CT_STRING)){
            return true;
        }
        else if(consume(TOKENS::LPAR)){
            if(expr()){
                if(consume(TOKENS::RPAR)){
                    return true;
                }
                else exitError("[exprPrimary] missing RPAR"); 
            }
            else exitError("[exprPrimary] missing expr");
        }
        return false;
    }
};