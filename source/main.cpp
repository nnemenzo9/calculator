#include <iostream>
#include "../include/ds.h"

using namespace std;

/**
 * Calculates a numerical result from a postfix notation expression.
 * @param tokenArray: Passes in the postfix expression.
 * @return: Returns the numerical result
 */
double calculateFromPostfix(vector<Token> tokenArray) {

}

/**
 * Converts input Token array from infix to postfix (RPN) notation using the Shunting-Yard algorithm.
 * @param tokenArray: Passes in the array of tokens to be converted.
 * @return: Returns a token array in postfix notation.
 */
vector<Token> infixToPostfix(vector<Token> tokenArray) {

}

/**
 * Tokenizes a string
 * @param input: Passes in the string to be tokenized
 * @return: Returns an array of tokens
 */
vector<Token> tokenize(string input) {
    int index = 0;
    vector<Token> tokenArray;
    while (index != input.length()) {
        char c = input[index];

    }
}




int main() {
    string input;
    while (input.compare("x") != 0) {
        cout << "What expression would you like to calculate? Enter 'x' to exit the calculator." << endl;
        getline(cin, input);
    }
    return 0;
}
