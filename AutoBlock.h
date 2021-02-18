//
// Created by Maxwell Lenker on 1/23/21.
//

#ifndef LEXER_AUTOBLOCK_H
#define LEXER_AUTOBLOCK_H

#include <string>
#include "Automaton.h"

class AutoBlock : public Automaton {
private:
    int read = 0;

public:
    AutoBlock(TokenType tokenType):Automaton(tokenType){}

public:
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
        if (input.at(read) == '|') {
            read++;
            s2(input);
        }
    }

    void s2(const std::string& input) {
        if(read < (int)input.length()) {
            if (input.at(read) == '|') {
                read++;
                s3(input);
            } else if (input.at(read) != 04) {
                read++;
                s2(input);
            }
            else{
                throw -1;
            }
        }
    }

    void s3(const std::string& input) {
        if(read < (int)input.length()){
        if (input.at(read) == '#') {
            read++;
        } else {
            s2(input);
        }
    }}
};
#endif //LEXER_AUTOBLOCK_H
