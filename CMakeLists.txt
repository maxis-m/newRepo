cmake_minimum_required(VERSION 3.17)
project(Lexer)

set(CMAKE_CXX_STANDARD 14)

add_executable(Lexer main.cpp Automaton.h Token.h Lexer.h AutoSingle.h AutoCommand.h AutoID.h AutoString.h AutoComment.h AutoBlock.h Parser.h DatalogProgram.h Predicate.h Rule.h Parameter.h)