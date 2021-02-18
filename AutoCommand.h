//
// Created by Maxwell Lenker on 1/23/21.
//

#ifndef LEXER_AUTOCOMMAND_H
#define LEXER_AUTOCOMMAND_H

#include <string>
#include "Automaton.h"

class AutoCommand : public Automaton {
private:
    std::string symbol1;
    int read = 0;

public:
    AutoCommand(std::string symbol2, TokenType tokenType):Automaton(tokenType){
        symbol1 = symbol2;
    }
    int Start(const std::string& input) {
        read = 0;
        s0(input);
        if(read != (int)symbol1.size()){
            read = 0;
        }
        return read;
    }
void s0(const std::string& input) {
    if(read < (int)(symbol1.length()) && (int)input.length() > 1){
        if (input.at(read) == symbol1.at(read)) {
            read++;
            s0(input);
        }
    }
   // else{
       //read++;
   // }
    }
};

#endif //LEXER_AUTOCOMMAND_H
