//
// Created by Maxwell Lenker on 1/23/21.
//

#ifndef LEXER_AUTOSINGLE_H
#define LEXER_AUTOSINGLE_H

#include <string>
#include "Automaton.h"
#include "Token.h"

class AutoSingle : public Automaton {
private:
    char symbol1;
    int read = 0;
public:
   AutoSingle(char symbol, TokenType tokenType):Automaton(tokenType){
       symbol1 = symbol;
   }
    int Start(const std::string& input) {
        read = 0;
        s0(input);
        return read;
    }

    void s0(const std::string& input) {
        if (input.at(0) == symbol1) {
            read++;
        }
    }
};
#endif //LEXER_AUTOSINGLE_H
