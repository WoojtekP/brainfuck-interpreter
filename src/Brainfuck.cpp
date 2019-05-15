#include "Brainfuck.hpp"
#include "Memory.hpp"
#include <iostream>
#include <stack>

std::string Brainfuck::interpret(Code const& code, Input const& input) const {
    Memory memory;
    std::string result;
    auto inputIt = input.begin();
    std::stack<int> leftBrackets;
    const int codeSize = code.size();

    for (int i = 0; i < codeSize; ++i) {
        switch (code[i]) {
            case '.':
                result += memory.get();
                break;

            case ',':
                if (inputIt == input.end())
                    throw std::string("Input is empty");
                memory.set(*inputIt);
                inputIt++;
                break;

            case '+' :
                memory.increment();
                break;

            case '-':
                memory.decrement();
                break;

            case '>':
                memory.moveRight();
                break;

            case '<':
                memory.moveLeft();
                break;

            case '[':
                if (memory.get() == 0) {
                    //go to the end of current loop
                    int bracketCounter = 1;
                    while (bracketCounter && ++i < codeSize) {
                        if (code[i] == '[')
                            bracketCounter++;
                        else if (code[i] == ']')
                            bracketCounter--;
                    }
                    if (i >= codeSize)
                        throw std::string("Syntax error: There is no end of current loop");
                }
                else
                    leftBrackets.push(i);
                
                break;

            case ']':
                if (leftBrackets.empty())
                    throw std::string ("Syntax error: There is no beggining of current loop");
                
                if (memory.get() != 0)
                    i = leftBrackets.top();
                else
                    leftBrackets.pop();
                break;
        }
    }
    
    return result;
}
