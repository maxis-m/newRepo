//
// Created by Maxwell Lenker on 1/23/21.
//

#ifndef LEXER_AUTOID_H
#define LEXER_AUTOID_H

#include <string>
#include "Automaton.h"

class AutoID : public Automaton {
private:
    int read = 0;

public:
    AutoID(TokenType tokenType):Automaton(tokenType){}

    int Start(const std::string& input) {
        read = 0;
        s0(input);
        return read;
    }
void s0(const std::string& input) {
    if (isalpha(input.at(0))) {
        if(input.length() == 1){
            read++;
        }
        else {
            read++;
            s1(input);
        }
    }
}
void s1(const std::string& input) {
    if (isalpha(input.at(read)) || isdigit(input.at(read))) {
        if(input.length()-1 == read){
            read++;
        }
        else {
            read++;
            s1(input);
        }
    }

}
};

#endif //LEXER_AUTOID_H
