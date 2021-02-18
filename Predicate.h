//
// Created by Maxwell Lenker on 2/6/21.
//

#ifndef LEXER_PREDICATE_H
#define LEXER_PREDICATE_H
#include "Parser.h"
#include "Parameter.h"
#include <vector>
using namespace std;

class Predicate{
private:
    string predicateName;
    vector<Parameter> parameterList;
public:
    Predicate(){

    }
    void addParam(Parameter newParam){
        parameterList.push_back(newParam);
    }
    void setName(string newName){
        predicateName = newName;
    }
    string getPredicate(){
        string outPut;
        outPut+= predicateName;
        outPut += "(";
        for(int i = 0; i < (int)parameterList.size(); i++){
            outPut += parameterList.at(i).getParam();
            if(i+1 < (int)parameterList.size()){
                outPut +=",";
            }
        }
        outPut += ")";
        return outPut;
    }
};


#endif //LEXER_PREDICATE_H
