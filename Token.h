//
// Created by Maxwell Lenker on 1/23/21.
//

#ifndef LEXER_TOKEN_H
#define LEXER_TOKEN_H
#include <string>
enum TokenType{COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON, COLON_DASH, MULTIPLY, ADD, SCHEMES, FACTS, RULES,
    QUERIES, ID, STRING, COMMENT, UNDEFINED, ENDOF, INVALID};
class Token{
private:
    TokenType tokenType;
    std::string content;
    int lineNum;
public:
    Token(TokenType tokenType1, std::string content1, int lineNum1){
        tokenType = tokenType1;
        content = content1;
        lineNum = lineNum1;
    }
    std::string getTokenType(){
        if(tokenType == COMMA){
            return "COMMA";
        }
        else if(tokenType == PERIOD){
            return "PERIOD";
        }
        else if(tokenType == Q_MARK){
            return "Q_MARK";
        }
        else if(tokenType == LEFT_PAREN){
            return "LEFT_PAREN";
        }
        else if(tokenType == RIGHT_PAREN){
            return "RIGHT_PAREN";
        }
        else if(tokenType == COLON){
            return "COLON";
        }
        else if(tokenType == COLON_DASH){
            return "COLON_DASH";
        }
        else if(tokenType == MULTIPLY){
            return "MULTIPLY";
        }
        else if(tokenType == ADD){
            return "ADD";
        }
        else if(tokenType == SCHEMES){
            return "SCHEMES";
        }
        else if(tokenType == QUERIES) {
            return "QUERIES";
        }
        else if(tokenType == FACTS){
            return "FACTS";
        }
        else if(tokenType == RULES){
            return "RULES";
        }
        else if(tokenType == ID){
            return "ID";
        }
        else if(tokenType == STRING){
            return "STRING";
        }
        else if(tokenType == COMMENT){
            return "COMMENT";
        }
        else if(tokenType == INVALID){
            return "INVALID";
        }
        else if(tokenType == UNDEFINED){
            return "UNDEFINED";
        }
        else if(tokenType == ENDOF){
            return "ENDOF";
        }
    }
    std::string getContent(){
        return content;
    }
    std::string getLine(){
        std::string lineGetter = std::to_string(lineNum);
        return lineGetter;
    }

};

#endif //LEXER_TOKEN_H
