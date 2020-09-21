#include <iostream>
#include "../include/ds.h"

// TODO: ERROR CHECKING

using namespace std;

static const char DOUBLE = 'd';

/**
 * // TODO: FIND WAY TO REDUCE IF STATEMENTS (new class, enum, etc.)
 * Method to get the precedence of a certain token (char)
 * @param c: Passes in the char
 * @return: Returns the precedence
 */
int getPrecedence(char c) {
    int precedence;
    if (c == '+' || c == '-') {
        precedence = 1;
    } else if (c == '*' || c == '/') {
        precedence = 2;
    } else if (c == '^') {
        precedence = 3;
    } else { // everything else (error check before called)
        precedence = 4;
    }
    return precedence;
}

/**
 * Calculates a numerical result from a postfix notation expression.
 * @param tokenArray: Passes in the postfix expression.
 * @return: Returns the numerical result
 */
double calculateFromPostfix(vector<Token> tokenArray) {
    int index = 0;
    Stack<double> stack;

    while (index != tokenArray.capacity()) {
        if (tokenArray[index].type == DOUBLE) { // token is a num
            stack.push(tokenArray[index].value);
        } else { // token is not a num
            double right = stack.pop();
            double left = stack.pop();
            switch(tokenArray[index].type) {
                case '+':
                    stack.push(left + right); // push back to stack
                    break;
                case '-':
                    stack.push(left - right);
                    break;
                case '*':
                    stack.push(left * right);
                    break;
                case '/':
                    stack.push(left / right);
                    break;
                default: // '^' operator
                    stack.push(pow(left, right));
            }
        }
        index++;
    }
    // by this point, we should be returning the correct thing.
    return stack.pop();
}

/**
 * Converts input Token array from infix to postfix (RPN) notation using the Shunting-Yard algorithm.
 * @param tokenArray: Passes in the array of tokens to be converted.
 * @return: Returns a token array in postfix notation.
 */
vector<Token> infixToPostfix(vector<Token> tokenArray) {
    const int MAX_PRECEDENCE = 4;
    int index = 1;
    vector<Token> result;
    Stack<Token> stack;

    // parse the first token
    if (tokenArray[0].type == DOUBLE) {
        result.push_back(tokenArray[0]);
    } else {
        stack.push(tokenArray[0]);
    }

    // parse all other tokens
    while (index != tokenArray.capacity()) {
        if (tokenArray[index].type == DOUBLE) { // token is a number
            result.push_back(tokenArray[index]);
        } else { // token is not a number
            bool peekIsOpening = !stack.empty() && (stack.peek().type == '(' || stack.peek().type == '[' || stack.peek().type == '{');
            // check if closing expression, keep popping until mirror is found (first precedence level 4)
            if (tokenArray[index].type == ')' || tokenArray[index].type == ']' || tokenArray[index].type == '}') {
                while (!stack.empty() && stack.peek().precedence != MAX_PRECEDENCE) {
                    result.push_back(stack.pop()); // pop to result vector
                }
                // by this point, stack.pop() should be at an operator of max precedence ( opening (, [, { )
                stack.pop();
            } else if (!stack.empty() && !peekIsOpening && (tokenArray[index].precedence <
                       stack.peek().precedence)) { // if not closing expression, compare precedences
                while (!stack.empty() && !peekIsOpening && tokenArray[index].precedence < stack.peek().precedence) {
                    result.push_back(stack.pop());
                }
                stack.push(tokenArray[index]);
            } else { // operator is neither closing expression or of lower precedence
                stack.push(tokenArray[index]);
            }
        }
        ++index;
    }

    // push everything at end
    while (!stack.empty()) {
        result.push_back(stack.pop());
    }
    return result;
}

/**
 * Tokenizes a string
 * @param input: Passes in the string to be tokenized
 * @return: Returns an array of tokens
 */
vector<Token> tokenize(string input) {
    // class constants
    const char SPACE = ' ';
    const int ASCII_NUM = 48;
    const int BASE_10 = 10;

    vector<Token> tokenArray;
    int index = 0;
    int opIndex;
    int tokenIndex = 0;

    while (index != input.length()) {
        opIndex = index;
        Token t;
        tokenArray.push_back(t);
        if (isdigit(input[index])) { // char at index is a digit
            tokenArray[tokenIndex].type = DOUBLE;
            while (opIndex != input.length() && isdigit(input[opIndex])) {
                ++opIndex;
            }
            int counter = 0;
            for (int i = (opIndex - 1) - index; i >= 0; --i) {
                tokenArray[tokenIndex].value += ((int) input[counter + index] - ASCII_NUM) * pow(BASE_10, i);
                ++counter;
            }
            index = opIndex;
        } else { // char at index is not digit
            tokenArray[tokenIndex].type = input[index]; // get operator
            tokenArray[tokenIndex].precedence = getPrecedence(tokenArray[tokenIndex].type); // add precedence to token
            ++index;
        }
        ++tokenIndex;
    }

    // remove spaces
    index = 0;
    for (auto &tok : tokenArray) {
        if (tok.type == SPACE) {
            tokenArray.erase(tokenArray.begin() + index);
        }
        ++index;
    }
    return tokenArray;
}

int main() {
    string input;
    vector<Token> tokenArray;

    while (input.compare("x") != 0) {
        cout << "What expression would you like to calculate? Or enter 'x' to exit the calculator." << endl;
        getline(cin, input);
        tokenArray = tokenize(input);
        tokenArray = infixToPostfix(tokenArray);
        cout << "Answer: " << calculateFromPostfix(tokenArray) << endl;
    }
    return 0;
}
