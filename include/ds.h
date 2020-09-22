#ifndef UNTITLED_DS_H
#define UNTITLED_DS_H

#include <vector>

using namespace std;

/* *********************** */
// stack data structure implementation (templates included in header) (no stack overflow)
template<class T>
class Stack {
public:
            Stack();
    void    push(T);
    T       pop();
    T       peek();
    bool    empty();

private:
    int     head;
    int     size;
    void    resize();
    vector<T>   con;
};

template<class T>
Stack<T>::Stack() {
    size = 0;
    head = -1;
}

template<class T>
void Stack<T>::push(T val) {
    // push onto the stack
    head = head + 1;
    con.at(head) = val;
    ++size;
}

template<class T>
T Stack<T>::pop() {
    if (size == 0) {
        throw out_of_range("Stack underflow.");
    }

    // pop off of the stack
    T popped = con.at(head);
    con.erase(con.begin() + head);
    head = head - 1;
    --size;
    return popped;
}

template<class T>
T Stack<T>::peek() {
    if (size == 0) {
        throw std::out_of_range("Stack underflow.");
    }
    return con.at(head);
}


template<class T>
bool Stack<T>::empty() {
    return (size == 0);
}

/* *********************** */

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
