// Yusuf İsmail Okur Section1 22402939

#include "Stack.h"
#include <iostream>

Stack::Stack(int cap){
    capacity = cap;
    top = -1;
    if (cap > 0){
        arr = new std::string[cap];
    }
    else {
        arr = nullptr;
    }
}
Stack::Stack(const Stack& other){
    capacity = other.capacity;
    top = other.top;
    if (capacity > 0){
        arr = new std::string[capacity];
    }
    else {
        arr = nullptr;
    }
    for (int i = 0; i <= top ; i++){
        arr[i] = other.arr[i];
    }
}
Stack& Stack::operator=(const Stack& other){
    if (this != &other){
        delete[] arr;
        capacity = other.capacity;
        top = other.top;
        if (capacity > 0){
            arr = new std::string[capacity];
        }
        else {
            arr = nullptr;
        }
        for (int i = 0; i <= top ; i++){
            arr[i] = other.arr[i];
        }
    }
    return *this;
}
Stack::~Stack(){
    delete[] arr;
}
bool Stack::isEmpty()const{
    return top == -1;
}
bool Stack::isFull() const{
    return top == capacity-1;
}
int Stack::size() const{
    return top + 1;
}
int Stack::getCapacity() const{
    return capacity;    
}
bool Stack::push(const std::string& value){
    if (isFull()) return false;
    top++;
    arr[top] = value;
    return true;
}
bool Stack::pop(std::string& out){
    if (isEmpty()) return false;
    out = arr[top];
    top--;
    return true;
}
bool Stack::peek(std::string& out)const{
    if (isEmpty()) return false;
    out = arr[top];
    return true;
}
void Stack::clear(){
    top = -1;
}
void Stack::print() const {
    std::cout << "[ ";
    for (int i = 0; i <= top; i++) {
        std::cout << arr[i];
        if (i != top) std::cout << ", ";
    }
    std::cout << " ]";
}