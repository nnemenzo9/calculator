#ifndef UNTITLED_DS_H
#define UNTITLED_DS_H

#include <vector>

using namespace std;

struct Token {
    char type; // contains operators + parentheses
    double value; // contains value only if type is a double, null if anything else
    int precedence;

    string toString();
};

string Token::toString() {
    string result = "";
    result += "TYPE: " + string(1, type) + " | " + "VALUE: " + to_string(value) + " | " + "PRE: " +
              to_string(precedence) + "\n";
    return result;
}

/* *********************** */

#endif //UNTITLED_DS_H
