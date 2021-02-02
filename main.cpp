#include <iostream>
#include <fstream>
#include "Lexer.h"
using namespace std;

int main(int argc, char* argv[]) {

    //Opening Files
    if (argc < 2) {
        cerr << "Please provide name of input file";
        return 1;
    }
    cout << "Input file: " << argv[1] << endl;
    ifstream ins;
    ins.open(argv[1]);

    if (!ins.is_open()) {
        cerr << "Unable to open " << argv[1] << " for input";
        return 2;
    }
   /**
    string line = ":-";
    string line1 = "Facts";
    string line2 = " +";
    char ending = 04;
    string line3 = "#|Hello";
    line3.push_back(ending);
**/
    Lexer* lexer1 = new Lexer;

    /**
    lexer1->Run(line);
    cout << (lexer1->printTokens());
    lexer1->Run(line1);
    cout << (lexer1->printTokens());
    lexer1->Run(line2);
    cout << (lexer1->printTokens());
    lexer1->Run(line3);
    cout << (lexer1->printTokens());**/



    std::string content;
    content.assign((std::istreambuf_iterator<char>(ins)),
                         (std::istreambuf_iterator<char>()));
    char ending = 04;
    //content.push_back('\n');
    content.push_back(ending);
    lexer1->Run(content);
    cout << lexer1->printTokens();



}