//
// Created by Maxwell Lenker on 1/23/21.
//

#ifndef LEXER_AUTOCOMMENT_H
#define LEXER_AUTOCOMMENT_H

#include <string>
#include "Automaton.h"

class AutoComment : public Automaton {
private:
    int read = 0;

public:
    AutoComment(TokenType tokenType):Automaton(tokenType){}

    int Start(const std::string& input) {
        read = 0;
        s0(input);
        return read;
    }

    void s0(const std::string& input) {
        if (input.at(read) == '#') {
            read++;
            s1(input);
        }
    }

    void s1(const std::string& input) {
if(read < input.length()){
        if (/*!input.eof() &&*/ input.at(read) != '\n' && input.at(read) != '|') {
            read++;
            s1(input);
        }

        //else {
            //read++;
        //}
    }}
};
#endif //LEXER_AUTOCOMMENT_H
