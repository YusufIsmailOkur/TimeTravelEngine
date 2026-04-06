// Yusuf İsmail Okur Section1 22402939
#ifndef STACK_H
#define STACK_H

#include <string>

class Stack {
private:
    std::string* arr;
    int top;
    int capacity;

public:
    Stack(int cap = 0);
    Stack(const Stack& other);
    Stack& operator=(const Stack& other);
    ~Stack();

    bool isEmpty() const;
    bool isFull() const;
    int size() const;
    int getCapacity() const;

    bool push(const std::string& value);
    bool pop(std::string& out);
    bool peek(std::string& out) const;

    void clear();
    void print() const;
};

#endif
