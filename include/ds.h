#ifndef UNTITLED_DS_H
#define UNTITLED_DS_H

#include <vector>

using namespace std;

/* *********************** */
// stack data structure implementation (templates included in header) (no stack overflow)
template <class T>
class Stack {
public:
            Stack();
            ~Stack();
    void    push(T);
    T       pop();
    T       peek();
    bool    empty();

private:
    int     head;
    int     size;
    void    resize();
    T       *con;
};

template <class T>
Stack<T>::Stack() {
    const int INITIAL_CAP = 30;
    con = new T[INITIAL_CAP];
    size = 0;
    head = -1;
}

template <class T>
void Stack<T>::push(T val) {
    // resize
    if (size == sizeof(*con)/sizeof(con[0])) {
        resize();
    }

    // push onto the stack
    head = head + 1;
    con[head] = val;
    ++size;
}

template <class T>
T Stack<T>::pop() {
    if (head < 0) {
        throw out_of_range("Stack underflow.");
    }

    // pop off of the stack
    T popped = con[head];
    con[head] = T();
    head = head - 1;
    --size;
    return popped;
}

template <class T>
void Stack<T>::resize() {
    const int CAP_MULTIPLIER = 2;
    T *temp = new T[CAP_MULTIPLIER * size];
    for (int i = 0; i < size; ++i) {
        temp[i] = con[i];
    }
    delete [] con;
    con = temp;
}

template <class T>
T Stack<T>::peek() {
    if (head < 0) {
        throw std::out_of_range("Stack underflow.");
    }
    return con[head];
}

template<class T>
Stack<T>::~Stack() {
    if (con) delete [] con;
}

template<class T>
bool Stack<T>::empty() {
    return (size == 0);
}

/* *********************** */

class Token {
public:
    char type; // contains operators + parentheses
    double value; // contains value only if type is a double, null if anything else
};

#endif //UNTITLED_DS_H
