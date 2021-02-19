//
// Created by Maxwell Lenker on 2/6/21.
//

#ifndef LEXER_PARSER_H
#define LEXER_PARSER_H
#include "Token.h"
#include "Parameter.h"
#include "Rule.h"
#include "Predicate.h"
#include <vector>
#include <set>
using namespace std;

struct SortProductPointers
{
    // overload the function call operator
    bool operator()(const Parameter p1, const Parameter p2) const
    {
        // dereference the pointers to compare their targets
        // using the Product class's operator<(...) function
        return p1 < p2;
    }
};

class Parser{
private:
    vector<Token *> tokens;
    int i = 0;
    vector<Predicate>schemesList;
    vector<Predicate>factsList;
    vector<Predicate>queriesList;
    vector<Rule>rulesList;
    vector<Parameter> domain;
    vector<Parameter> factDomain;
    int numInPredicate = 0;
    //bool isExpression = false;
    vector<Predicate> bodyPredicates;

public:
    Parser(std::vector<Token *> tokenVector){
        tokens = tokenVector;
    }
    std::string Run(){
        std::string outPut;
        try{
            ParseTerminal("SCHEMES");
            ParseTerminal("COLON");
            ParseScheme();
            ParseSchemesList();
            ParseTerminal("FACTS");
            ParseTerminal("COLON");
            ParseFactList();
            ParseTerminal("RULES");
            ParseTerminal("COLON");
            ParseRuleList();
            ParseTerminal("QUERIES");
            ParseTerminal("COLON");
            ParseQuery();
            ParseQueryList();
            outPut = "Success!";
            outPut += getPredicates();

        }
        catch(int e){
            outPut = "Failure!\n";
            outPut += "\t(" + tokens.at(e)->getTokenType() + ",\"" + tokens.at(e)->getContent() + "\"," +
                      tokens.at(e)->getLine() + ")\n";
        }
        return outPut;

    }
    //PARSE LISTS
    //TODO: FILL LIST FUNCTIONS
    void ParseSchemesList(){
        if(tokens.at(i)->getTokenType() == "ID"){
            ParseScheme();
            ParseSchemesList();
        }
        else if(tokens.at(i)->getTokenType() == "FACTS"){

        }
        else{
            throw i;
        }
    }

    void ParseFactList(){
        if(tokens.at(i)->getTokenType() == "ID"){
            ParseFact();
            ParseFactList();
        }
        else if(tokens.at(i)->getTokenType() == "RULES"){

        }
        else{
            throw i;
        }
    }

    void ParseRuleList(){
        if(tokens.at(i)->getTokenType() == "ID"){
            ParseRule();
            ParseRuleList();
        }
        else if(tokens.at(i)->getTokenType() == "QUERIES"){

        }
        else{
            throw i;
        }
    }

    void ParseQueryList(){
        if(tokens.at(i)->getTokenType() == "ID"){
            ParseQuery();
            ParseQueryList();
        }
        else if(tokens.at(i)->getTokenType() == "EOF"){

        }
        else{
            throw i;
        }
    }

    void ParsePredicateList(){
        if(tokens.at(i)->getTokenType() == "COMMA"){
            ParseTerminal("COMMA");
            ParsePredicate();
            ParsePredicateList();
        }
        else if(tokens.at(i)->getTokenType() == "PERIOD"){

        }
        else{
            throw i;
        }
    }

    void ParseParameterList(){
        if(tokens.at(i)->getTokenType() == "COMMA"){
            ParseTerminal("COMMA");
            ParseParameter();
            ParseParameterList();
        }
        else if(tokens.at(i)->getTokenType() == "RIGHT_PAREN"){

        }
        else{
            throw i;
        }
    }

    void ParseStringList(){
        if(tokens.at(i)->getTokenType() == "COMMA"){
            ParseTerminal("COMMA");
            ParseParameterTerminal("STRING");
            ParseStringList();
        }
        else if(tokens.at(i)->getTokenType() == "RIGHT_PAREN"){

        }
        else{
            throw i;
        }
    }

    void ParseIdList(){
        if(tokens.at(i)->getTokenType() == "COMMA"){
            ParseTerminal("COMMA");
            ParseParameterTerminal("ID");
            ParseIdList();
        }
        else if(tokens.at(i)->getTokenType() == "RIGHT_PAREN"){

        }
        else{
            throw i;
        }
    }


    void ParseScheme(){
        if(tokens.at(i)->getTokenType() == "ID"){
            Predicate newScheme;
            int f = i;
            numInPredicate = 0;
            ParseTerminal("ID");
            newScheme.setName(tokens.at(f)->getContent());
            ParseTerminal("LEFT_PAREN");
            ParseParameterTerminal("ID");
            ParseIdList();
            ParseTerminal("RIGHT_PAREN");
            for(int j = numInPredicate; j > 0; j--){
                newScheme.addParam(domain.at((int)domain.size()-j));
            }
            schemesList.push_back(newScheme);
        }
        else {
            throw i;
        }
    }
    void ParseFact(){
        if(tokens.at(i)->getTokenType() == "ID"){
            Predicate newFact;
            numInPredicate = 0;
            int f = i;
            ParseTerminal("ID");
            newFact.setName(tokens.at(f)->getContent());
            ParseTerminal("LEFT_PAREN");
            ParseParameterTerminal("STRING");
            ParseStringList();
            ParseTerminal("RIGHT_PAREN");
            ParseTerminal("PERIOD");
            for(int j = numInPredicate; j > 0; j--){
                newFact.addParam(domain.at((int)domain.size()-j));
                bool alreadyUsed = false;
                for(int i = 0; i < (int)factDomain.size(); i++){
                    if(factDomain.at(i).getParam() == domain.at((int)domain.size()-j).getParam()){
                        alreadyUsed = true;
                    }
                }
                if(!alreadyUsed) {
                    factDomain.push_back(domain.at((int)domain.size() - j));
                }
            }
            factsList.push_back(newFact);
        }
        else {
            throw i;
        }
    }
    void ParseRule(){
        if(tokens.at(i)->getTokenType() == "ID") {
            Rule newRule;
            newRule.setHead(ParseHeadPredicate());
            ParseTerminal("COLON_DASH");
            ParsePredicate();
            ParsePredicateList();
            ParseTerminal("PERIOD");
            newRule.setBody(bodyPredicates);
            rulesList.push_back(newRule);
            bodyPredicates.clear();
        }
        else {
            throw i;
        }
    }
    void ParseQuery(){
        if(tokens.at(i)->getTokenType() == "ID") {
            Predicate newQuery;
            numInPredicate = 0;
            newQuery.setName(tokens.at(i)->getContent());
            ParsePredicate();
            ParseTerminal("Q_MARK");
            for(int j = numInPredicate; j > 0; j--){
                newQuery.addParam(domain.at((int)domain.size()-j));
            }
            queriesList.push_back(newQuery);
        }
        else{
            throw i;
        }
    }
    Predicate ParseHeadPredicate(){
        if(tokens.at(i)->getTokenType() == "ID"){
            Predicate headPredicate;
            numInPredicate = 0;
            headPredicate.setName(tokens.at(i)->getContent());
            ParseTerminal("ID");
            ParseTerminal("LEFT_PAREN");
            ParseParameterTerminal("ID");
            ParseIdList();
            ParseTerminal("RIGHT_PAREN");
            for(int j = numInPredicate; j > 0; j--){
                headPredicate.addParam(domain.at((int)domain.size()-j));
            }
            return headPredicate;
        }
        else {
            throw i;
        }
    }
    void ParsePredicate(){
        if(tokens.at(i)->getTokenType() == "ID"){
            Predicate newPredicate;
            numInPredicate = 0;
            newPredicate.setName(tokens.at(i)->getContent());
            ParseTerminal("ID");
            ParseTerminal("LEFT_PAREN");
            ParseParameter();
            ParseParameterList();
            ParseTerminal("RIGHT_PAREN");
            for(int j = numInPredicate; j > 0; j--){
                newPredicate.addParam(domain.at((int)domain.size()-j));
            }
            bodyPredicates.push_back(newPredicate);
        }
        else {
            throw i;
        }
    }
    void ParseParameter(){

        if(tokens.at(i)->getTokenType() == "STRING" || tokens.at(i)->getTokenType() == "ID" ||
           tokens.at(i)->getTokenType() == "LEFT_PAREN" ){
            if(tokens.at(i)->getTokenType() == "LEFT_PAREN"){
                Parameter newExp = ParseExpression();
                domain.push_back(newExp);
                numInPredicate++;
            }
            else if(tokens.at(i)->getTokenType() == "STRING"){
                ParseParameterTerminal("STRING");
            }
            else{
                ParseParameterTerminal("ID");
            }
        }
        else{
            throw i;
        }
    }

    //TODO create expression
    Parameter ParseExpression(){
        if(tokens.at(i)->getTokenType() == "LEFT_PAREN"){
            ParseTerminal("LEFT_PAREN");
            Parameter p1 = ParseExpressionParameter();
            Parameter p2 = ParseOperator();
            Parameter p3 = ParseExpressionParameter();
            ParseTerminal("RIGHT_PAREN");
            Parameter newParam;
            newParam.newExpression(p1,p2,p3);
            return newParam;
        }
        else{
            throw i;
        }
    }
    Parameter ParseExpressionParameter(){
        if(tokens.at(i)->getTokenType() == "STRING" || tokens.at(i)->getTokenType() == "ID" ||
           tokens.at(i)->getTokenType() == "LEFT_PAREN" ){
            if(tokens.at(i)->getTokenType() == "LEFT_PAREN"){
                return ParseExpression();
            }
            else if(tokens.at(i)->getTokenType() == "STRING"){
                Parameter stringParam;
                stringParam.newStringParam(tokens.at(i)->getContent());
                ParseTerminal("STRING");
                return stringParam;
            }
            else{
                Parameter stringParam;
                stringParam.newStringParam(tokens.at(i)->getContent());
                ParseTerminal("ID");
                return stringParam;
            }
        }
        else{
            throw i;
        }
    }
    Parameter ParseOperator(){
        if(tokens.at(i)->getTokenType() == "ADD" || tokens.at(i)->getTokenType() == "MULTIPLY"){
            Parameter stringParam;
            if(tokens.at(i)->getTokenType() == "ADD"){
                stringParam.newStringParam(tokens.at(i)->getContent());
                ParseTerminal("ADD");
            }
            else if(tokens.at(i)->getTokenType() == "MULTIPLY"){
                stringParam.newStringParam(tokens.at(i)->getContent());
                ParseTerminal("MULTIPLY");
            }
            return stringParam;
        }
        else{
            throw i;
        }
    }
    //TODO: CHECK TERMINAL PARSERS
    //DONE
    void ParseTerminal(std::string tType) {
        if(tokens.at(i)->getTokenType() == tType){
            i = i + 1;
        }
        else{
            throw i;
        }
    }
    void ParseParameterTerminal(std::string tType) {
        if(tokens.at(i)->getTokenType() == tType){

                Parameter newParam;
                newParam.newStringParam(tokens.at(i)->getContent());
                domain.push_back(newParam);
                numInPredicate++;

            i = i + 1;
        }
        else{
            throw i;
        }
    }
    string getPredicates(){
        string outPut;
        outPut+="\nSchemes(";
        outPut+=to_string((int)schemesList.size());
        outPut+="):\n";
        if((int)schemesList.size() > 0){

            for(int i = 0; i < (int)schemesList.size(); i++){
                outPut+="\t";
                outPut+=schemesList.at(i).getPredicate();
                outPut+="\n";
            }
        }
        outPut+="Facts(";
        outPut+=to_string((int)factsList.size());
        outPut+="):\n";
        if((int)factsList.size() > 0){

            for(int i = 0; i < factsList.size(); i++){
                outPut+="\t";
                outPut+=factsList.at(i).getPredicate();
                outPut+=".\n";
            }
        }
        outPut+="Rules(";
        outPut+=to_string((int)rulesList.size());
        outPut+="):\n";
        if((int)queriesList.size() > 0){

            for(int i = 0; i < (int)rulesList.size(); i++){
                outPut+="\t";
                outPut+=rulesList.at(i).getRule();
                outPut+=".\n";
            }
        }

        outPut+="Queries(";
        outPut+=to_string((int)queriesList.size());
        outPut+="):\n";
        if((int)queriesList.size() > 0){

            for(int i = 0; i < (int)queriesList.size(); i++){
                outPut+="\t";
                outPut+=queriesList.at(i).getPredicate();
                outPut+="?\n";
            }
        }
        outPut+="Domain(";
        outPut+=to_string((int)factDomain.size());
        outPut+="):\n";
        if((int)factsList.size() > 0){

            std::sort(factDomain.begin(), factDomain.end(), SortProductPointers());
            for(int i = 0; i < (int)factDomain.size(); i++){
                outPut+="\t";
                outPut+=factDomain.at(i).getParam();
                outPut+="\n";
            }
        }
        return outPut;
    }

};

//};
#endif //LEXER_PARSER_H


