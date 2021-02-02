//
// Created by Maxwell Lenker on 1/23/21.
//

#ifndef LEXER_AUTOMATON_H
#define LEXER_AUTOMATON_H
//template<typename TokenType>
#include "Token.h"

class Automaton
{
protected:
    int inputRead = 0;
    int newLines = 0;
    TokenType type;
public:
    Automaton(TokenType type) { this->type = type; }
// Start the automaton and return the number of characters read
// read == 0 indicates the input was rejected
// read > 0 indicates the input was accepted
    virtual int Start(const std::string& input)=0;
    virtual Token* CreateToken( std::string input, int lineNumber) {
        return new Token(type, input, lineNumber); }
    virtual int NewLinesRead() const { return newLines; }
};

#endif //LEXER_AUTOMATON_H
