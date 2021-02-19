#include <iostream>
#include <fstream>
#include <vector>
#include "Lexer.h"
#include "Parser.h"
using namespace std;

int main(int argc, char* argv[]) {

    ifstream ins;
    ins.open(argv[1]);


    Lexer* lexer1 = new Lexer;



    std::string content;
    content.assign((std::istreambuf_iterator<char>(ins)),
                         (std::istreambuf_iterator<char>()));
    char ending = 04;
    //content.push_back('\n');
    content.push_back(ending);
    lexer1->Run(content);
    //cout << lexer1->printTokens();
    std::vector<Token*> tokens1 = lexer1->getTokens();
    for(int i = 0; i < (int)tokens1.size(); i++) {
        if (tokens1.at(i)->getTokenType() == ("COMMENT")) {
            tokens1.erase(tokens1.begin() + i);
            i--;
        }
    }
    Parser myParser(tokens1);
    cout << myParser.Run();
    //cout << myParser.getPredicates();

    }