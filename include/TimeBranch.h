// Yusuf İsmail Okur Section1 22402939
#ifndef TIMEBRANCH_H
#define TIMEBRANCH_H

#include <string>
#include "Stack.h"
#include "UnboundedStack.h"

class TimeTravelEngine;

class TimeBranch {
    friend class TimeTravelEngine;

private:
    std::string current;
    Stack past;
    Stack future;
    UnboundedStack stones;

    int distanceFromTop(Stack& s, const std::string& value);

public:
    TimeBranch(int pastCap, int futureCap, const std::string& startLocation);

    const std::string& getCurrent() const;

    bool travelTo(const std::string& newLocation);
    bool rewind(int k, int& stepsTaken);
    bool fastForward(int k, int& stepsTaken);

    void placeTimeStone();
    bool activateTimeStone();
    bool hasTimeStone() const;

    void print() const;

    const Stack& getPast() const;
    const Stack& getFuture() const;
    const UnboundedStack& getStones() const;
};

#endif
