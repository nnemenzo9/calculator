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
        Token current = tokenArray.at(index);
        if (current.type == DOUBLE) { // token is a num
            stack.push(current.value);
        } else { // token is not a num
            double right = stack.pop();
            double left = stack.pop();
            switch(current.type) {
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
    vector<Token> result;
    Stack<Token> stack;

    // parse the first token
    if (tokenArray.at(0).type == DOUBLE) {
        result.push_back(tokenArray.at(0));
    } else {
        stack.push(tokenArray.at(0));
    }

    // parse all other tokens
    int index = 1;
    while (index != tokenArray.capacity()) {
        Token current = tokenArray.at(index);
        if (current.type == DOUBLE) { // token is a number
            result.push_back(current);
        } else { // token is not a number
            bool peekIsOpening = !stack.empty() && (stack.peek().type == '(' || stack.peek().type == '[' || stack.peek().type == '{');
            // check if closing expression, keep popping until mirror is found (first precedence level 4)
            if (current.type == ')' || current.type == ']' || current.type == '}') {
                while (!stack.empty() && stack.peek().precedence != MAX_PRECEDENCE) {
                    result.push_back(stack.pop()); // pop to result vector
                }
                // by this point, stack.pop() should be at an operator of max precedence ( opening (, [, { )
                stack.pop();
            } else if (!stack.empty() && !peekIsOpening && (current.precedence <
                       stack.peek().precedence)) { // if not closing expression, compare precedences
                while (!stack.empty() && !peekIsOpening && current.precedence < stack.peek().precedence) {
                    result.push_back(stack.pop());
                }
                stack.push(current);
            } else { // operator is neither closing expression or of lower precedence
                stack.push(current);
            }
        }
        // print first thing in result for checking purposes
        cout << "STEP: " + to_string(index) + " ";
        if (!result.empty()) {
            cout << result.at(0).toString();
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
            tokenArray.at(tokenIndex).type = DOUBLE;
            while (opIndex != input.length() && isdigit(input[opIndex])) {
                ++opIndex;
            }
            int counter = 0;
            for (int i = (opIndex - 1) - index; i >= 0; --i) {
                tokenArray.at(tokenIndex).value += ((int) input[counter + index] - ASCII_NUM) * pow(BASE_10, i);
                ++counter;
            }
            index = opIndex;
        } else { // char at index is not digit
            tokenArray.at(tokenIndex).type = input[index]; // get operator
            tokenArray.at(tokenIndex).precedence = getPrecedence(tokenArray.at(tokenIndex).type); // add precedence to token
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
    vector<Token> infix;
    vector<Token> postfix;

    while (input.compare("x") != 0) {
        cout << "What expression would you like to calculate? Or enter 'x' to exit the calculator." << endl;
        getline(cin, input);
        if (input.compare("x") != 0) {
            // TODO: FIGURE OUT WHY DEBUG / RUN IS RETURNING DIFFERENT OUTPUT
            infix = tokenize(input); // can we pass vectors around like this?
            postfix = infixToPostfix(infix);
            cout << "Answer: " << calculateFromPostfix(postfix) << endl;
        }
    }
    return 0;
}
