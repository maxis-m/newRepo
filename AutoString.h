//
// Created by Maxwell Lenker on 1/23/21.
//

#ifndef LEXER_AUTOSTRING_H
#define LEXER_AUTOSTRING_H

#include <string>
#include "Automaton.h"

class AutoString : public Automaton {
private:
    int read = 0;

public:
    AutoString(TokenType tokenType):Automaton(tokenType){}

    int Start(const std::string& input) {
        read = 0;
        s0(input);
        return read;
    }

    void s0(const std::string& input) {
        if (input.at(read) == '\'') {
            read++;
            s1(input);
        }
    }

    void s1(const std::string& input) {
        if(read < input.length()) {
            if (input.at(read) == '\'') {
                read++;
                s2(input);
            }
            /**else if (input.at(read) == '\'') {
                read++;
                s1(input);
            }**/
            else if(input.at(read) == 04){
                throw -1;
            }
            else if (input.at(read) != '\'' && read < input.length()) {
                read++;
                s1(input);
            }

        }
    }
    void s2(const std::string& input){
        if(read < input.length()) {
            if(input.at(read) == '\''){
                read++;
                s1(input);
            }
        }
    }

};

#endif //LEXER_AUTOSTRING_H
