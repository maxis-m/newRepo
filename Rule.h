//
// Created by Maxwell Lenker on 2/6/21.
//

#ifndef LEXER_RULE_H
#define LEXER_RULE_H
#include "Parser.h"
#include "Predicate.h"
#include "Parameter.h"
#include <vector>
using namespace std;

class Rule{
private:
    Predicate headPredicate;
    vector<Predicate> bodyPredicates;

public:
    Rule()= default;
    void setHead(Predicate newHead){
        headPredicate = newHead;
    }
    void setBody(vector<Predicate> newBody){
        bodyPredicates = newBody;
       /** for(int i = 0; i < newBody.size(); i++){
            bodyPredicates.push_back(newBody.at(i));
        }**/
    }
    string getRule(){
        string outPut;
        outPut += headPredicate.getPredicate();
        outPut += " :- ";
            for(int i = 0; i < (int)bodyPredicates.size(); i++){
                outPut += bodyPredicates.at(i).getPredicate();
                if(i+1 < (int)bodyPredicates.size()){
                    outPut+=",";
                }
            }
            return outPut;
    }
};

#endif //LEXER_RULE_H
