// Yusuf İsmail Okur Section1 22402939
#include "UnboundedStack.h"
#include <iostream>

UnboundedStack::UnboundedStack(int initialCap) {
    if (initialCap <= 0) initialCap = 4;
    capacity = initialCap;
    top = -1;
    arr = new std::string[capacity];
}

UnboundedStack::UnboundedStack(const UnboundedStack& other) {
    capacity = other.capacity;
    top = other.top;
    arr = new std::string[capacity];
    for (int i = 0; i <= top; i++) {
        arr[i] = other.arr[i];
    }
}

UnboundedStack& UnboundedStack::operator=(const UnboundedStack& other) {
    if (this != &other) {
        delete[] arr;
        capacity = other.capacity;
        top = other.top;
        arr = new std::string[capacity];
        for (int i = 0; i <= top; i++) {
            arr[i] = other.arr[i];
        }
    }
    return *this;
}

UnboundedStack::~UnboundedStack() {
    delete[] arr;
}

bool UnboundedStack::isEmpty() const {
    return top == -1;
}

int UnboundedStack::size() const {
    return top + 1;
}

void UnboundedStack::grow() {
    int newCap = capacity * 2;
    std::string* newArr = new std::string[newCap];

    for (int i = 0; i <= top; i++) {
        newArr[i] = arr[i];
    }

    delete[] arr;
    arr = newArr;
    capacity = newCap;
}

void UnboundedStack::push(const std::string& value) {
    if (top == capacity - 1) {
        grow();
    }
    arr[++top] = value;
}

bool UnboundedStack::pop(std::string& out) {
    if (isEmpty()) return false;
    out = arr[top--];
    return true;
}

bool UnboundedStack::peek(std::string& out) const {
    if (isEmpty()) return false;
    out = arr[top];
    return true;
}

void UnboundedStack::clear() {
    top = -1;
}

void UnboundedStack::print() const {
    std::cout << "[ ";
    for (int i = 0; i <= top; i++) {
        std::cout << arr[i];
        if (i != top) std::cout << ", ";
    }
    std::cout << " ]";
}
