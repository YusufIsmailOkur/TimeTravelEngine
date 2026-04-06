// Yusuf İsmail Okur Section1 22402939
#ifndef UNBOUNDEDSTACK_H
#define UNBOUNDEDSTACK_H

#include <string>

class UnboundedStack {
private:
    std::string* arr;
    int top;
    int capacity;

    void grow();

public:
    UnboundedStack(int initialCap = 4);
    UnboundedStack(const UnboundedStack& other);
    UnboundedStack& operator=(const UnboundedStack& other);
    ~UnboundedStack();

    bool isEmpty() const;
    int size() const;

    void push(const std::string& value);
    bool pop(std::string& out);
    bool peek(std::string& out) const;

    void clear();
    void print() const;
};

#endif
