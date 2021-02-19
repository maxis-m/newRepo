//
// Created by Maxwell Lenker on 2/6/21.
//

#ifndef LEXER_PARAMETER_H
#define LEXER_PARAMETER_H
#include "Parser.h"
//#include "Expression.h"
#include <vector>
using namespace std;


class Parameter{
private:
    vector<Parameter> expressionString;
    //Expression expressionParam;
    string stringParam;
    bool isExpression = false;


public:
    Parameter(){

    }
    //void setExpression(Expression newExp){
       // Expression expressionParam;
        //expressionParam = newExp;
    //}
    void newExpression(Parameter var1, Parameter var2, Parameter var3){
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
            outPut +="(";
            outPut += expressionString.at(0).getParam();
            outPut += expressionString.at(1).getParam();
            outPut += expressionString.at(2).getParam();
            outPut +=")";
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
