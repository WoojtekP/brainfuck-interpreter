#define CATCH_CONFIG_MAIN
#include <string>
#include <catch.hpp>

#include "Brainfuck.hpp"

TEST_CASE( "Brainfuck interpreter test cases", "[interp]" ) {

    Brainfuck interpreter;

    SECTION( "empty code evaluates to empty result" ) {
        Code code{""};
        Input input{""};
        REQUIRE( interpreter.interpret(code, input) == "" );
    }

    SECTION( "outputting memory with one incrementation yields ones" ) {
        Code code{"+..."};
        Input input{""};
        std::string result = "\1\1\1";
        std::string s = interpreter.interpret(code, input);
        REQUIRE( s == result );
    }

    SECTION( "streaming input to output works correctly" ) {
        Code code{",.,..,...,...."};
        Input input{"abcd"};
        REQUIRE( interpreter.interpret(code, input) == "abbcccdddd" );
    }

    SECTION( "incrementing/decrementing at memory pointer results in correct numbers" ) {
        Code code{",.+.++.+++.---.--.-."};
        Input input{"\1"};
        REQUIRE( interpreter.interpret(code, input) == "\1\2\4\7\4\2\1" );
    }

    SECTION( "memory can be traversed" ) {
        Code code{",>,>,>,<<<.>.>.>.<.<.<."};
        Input input{"abcd"};
        REQUIRE( interpreter.interpret(code, input) == std::string{"abcdcba"} );
    }

    SECTION( "simple loops' steps are stepped through" ) {
        Code code{",[.-]"};
        Input input{"\5"};
        REQUIRE( interpreter.interpret(code, input) == "\5\4\3\2\1" );
    }

    SECTION( "loop with false at the beggining doesn't run" ) {
        Code code{"[+++]+."};
        Input input{""};
        REQUIRE( interpreter.interpret(code, input) == "\1");
    }

    SECTION( "nested loops' are evaluated in order" ) {
        Code code{",[.>+[.-]<-]"};
        Input input{"\5"};
        REQUIRE( interpreter.interpret(code, input) == "\5\1\4\1\3\1\2\1\1\1" );
    }

    SECTION( "hello world" ) {
        Code code{
                "++++++++++[>+++++++>++++++++++>+++>+<<<<-]"
                ">++.>+.+++++++..+++.>++.<<+++++++++++++++."
                ">.+++.------.--------.>+.>."};
        Input input{""};
        REQUIRE( interpreter.interpret(code, input) == "Hello World!\n" );
    }

    SECTION( "comments are ignored" ) {
        Code code{"qwertyuiopasdfghjklzxcvbnm,."};
        Input input{"a"};
        REQUIRE( interpreter.interpret(code, input) == "a" );
    }

    SECTION( "self interpreter" ) {
        Code code{
            ">>>+[[-]>>[-]++>+>+++++++[<++++>>++<-]++>>+>+>+++++[>++>++++++<<-]+>>>,<++[[>["
            "->>]<[>>]<<-]<[<]<+>>[>]>[<+>-[[<+>-]>]<[[[-]<]++<-[<+++++++++>[<->-]>>]>>]]<<"
            "]<]<[[<]>[[>]>>[>>]+[<<]<[<]<+>>-]>[>]+[->>]<<<<[[<<]<[<]+<<[+>+<<-[>-->+<<-[>"
            "+<[>>+<<-]]]>[<+>-]<]++>>-->[>]>>[>>]]<<[>>+<[[<]<]>[[<<]<[<]+[-<+>>-[<<+>++>-"
            "[<->[<<+>>-]]]<[>+<-]>]>[>]>]>[>>]>>]<<[>>+>>+>>]<<[->>>>>>>>]<<[>.>>>>>>>]<<["
            ">->>>>>]<<[>,>>>]<<[>+>]<<[+<<]<]"
        };
        Input input{",.!a"};
        REQUIRE( interpreter.interpret(code, input) == "a" );
    }

}



