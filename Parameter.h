//
// Created by Maxwell Lenker on 2/6/21.
//

#ifndef LEXER_PARAMETER_H
#define LEXER_PARAMETER_H
#include "Parser.h"
#include <vector>
using namespace std;


class Parameter{
private:
    vector<string> expressionString;
    string stringParam;
    bool isExpression = false;

public:
    Parameter(){

    }
    void newExpression(string var1, string var2, string var3){
        expressionString.push_back(var1);
        expressionString.push_back(var2);
        expressionString.push_back(var3);
        isExpression = true;
    }
    void newStringParam(string newParam){
        stringParam = newParam;
    }
    string getParam(){
        string outPut;
        if(isExpression){
            outPut += expressionString.at(0);
            outPut += expressionString.at(1);
            outPut += expressionString.at(2);
        }
        else{
            outPut = stringParam;
        }
        return outPut;
    }
    bool operator<(const Parameter& p) const
    {
        return stringParam < p.stringParam; // order by name
    }
};

#endif //LEXER_PARAMETER_H
