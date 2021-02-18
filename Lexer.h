//
// Created by Maxwell Lenker on 1/23/21.
//

#ifndef LEXER_LEXER_H
#define LEXER_LEXER_H
#include "Token.h"
#include "Automaton.h"
#include "AutoSingle.h"
#include "AutoCommand.h"
#include "AutoID.h"
#include "AutoString.h"
#include "AutoComment.h"
#include "AutoBlock.h"

#include <string>
#include <vector>

class Lexer {
private:
    std::vector<Token *> tokens;
    std::vector<Automaton *> automata;


public:
    Lexer() {
// Add all of the Automaton instances
        automata.push_back(new AutoSingle(',', COMMA));
        automata.push_back(new AutoSingle('.', PERIOD));
        automata.push_back(new AutoSingle('?', Q_MARK));
        automata.push_back(new AutoSingle('(', LEFT_PAREN));
        automata.push_back(new AutoSingle(')', RIGHT_PAREN));
        automata.push_back(new AutoSingle(':', COLON));
        automata.push_back(new AutoSingle('*', MULTIPLY));
        automata.push_back(new AutoSingle('+', ADD));
        automata.push_back(new AutoCommand(":-", COLON_DASH));
        automata.push_back(new AutoCommand("Schemes", SCHEMES));
        automata.push_back(new AutoCommand("Facts", FACTS));
        automata.push_back(new AutoCommand("Rules", RULES));
        automata.push_back(new AutoCommand("Queries", QUERIES));
        automata.push_back(new AutoID(ID));
        automata.push_back(new AutoString(STRING));
        automata.push_back(new AutoComment(COMMENT));
        automata.push_back(new AutoBlock(COMMENT));
    }
    void Run(std::string input) {
        tokens.clear();
        int maxRead;
        Token *newToken;
        int lineNumber = 1;


// While there are more characters to tokenize
        try{
            while (input.size() > 0) {
            maxRead = 0;
            Automaton *maxAutomaton = automata[0];


// TODO: you need to handle whitespace inbetween tokens
            while (isspace(input.at(0))) {
                if(input.at(0) == '\n'){
                    lineNumber++;
                }
                input.erase(0, 1);
            }

// Here is the "Parallel" part of the algorithm
// Each automaton runs with the same input
            for (int i = 0; i < (int)automata.size(); i++) {
                int inputRead = automata[i]->Start(input);
                if (inputRead > maxRead) {
                    maxRead = inputRead;
                    maxAutomaton = automata[i];
                } else if (inputRead == -1) {
                    maxRead = -1;
                }
            }
            if (input.at(0) == 04) {
                maxRead = -2;
            }


// Here is the "Max" part of the algorithm
            if (maxRead > 0) {
                newToken = maxAutomaton->CreateToken(input.substr(0, maxRead), lineNumber);
                lineNumber += maxAutomaton->NewLinesRead();
                tokens.push_back(newToken);
                for(int f = 0; f < (int)input.substr(0,maxRead).size(); f++){
                    if(input.at(f) == '\n'){
                        lineNumber++;
                    }
                }
            }
                /* else if(maxRead == -1){
                     newToken = new Token(UNDEFINED, input, lineNumber);
                     tokens.push_back(newToken);
                 }*/
            else if (maxRead == -2) {
                newToken = new Token(ENDOF, "", lineNumber);
                tokens.push_back(newToken);
            }


// No automaton accepted input; create invalid token
            else {
                maxRead = 1;
                newToken = new Token(UNDEFINED, input.substr(0,1), lineNumber);
                tokens.push_back(newToken);
            }


// Update ‘input‘ by removing characters read to create Token
            input.erase(0, maxRead);
        }
    }
        catch(int e){
            newToken = new Token(UNDEFINED, input.substr(0,input.size()-1), lineNumber);
            tokens.push_back(newToken);
            for(int f = 0; f < (int)input.size(); f++){
                if(input.at(f) == '\n'){
                    lineNumber++;
                }
            }
            newToken = new Token(ENDOF, "", lineNumber);
            tokens.push_back(newToken);
        }
    }


    std::vector<Token*> getTokens(){
        return tokens;
    }
    std::string printTokens(){
        std::string toPrint;
        for(int i = 0; i < (int)tokens.size(); i++){

                toPrint += "(" + tokens.at(i)->getTokenType() + ",\"" + tokens.at(i)->getContent() + "\"," +
                           tokens.at(i)->getLine() + ")\n";
        }
        toPrint += "Total Tokens = " + std::to_string(tokens.size()) + "\n";
        return toPrint;
    }
};
#endif //LEXER_LEXER_H
