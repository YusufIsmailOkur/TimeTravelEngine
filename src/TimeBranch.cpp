// Yusuf İsmail Okur Section1 22402939
#include "TimeBranch.h"
#include <iostream>

#include "Stack.h"
#include "UnboundedStack.h"

TimeBranch::TimeBranch(int pastCap, int futureCap, const std::string& startLocation)
    : current{startLocation},
      past{pastCap},
      future{futureCap},
      stones{}
{}

const std::string& TimeBranch::getCurrent() const {
    return current;
}

bool TimeBranch::travelTo(const std::string& newLocation) {
    if (past.isFull()) return false;
    past.push(current);
    current = newLocation;
    future.clear();
    return true;
}

bool TimeBranch::rewind(int k, int& stepsTaken) {
    stepsTaken = 0;
    if (k <= 0) return true;

    int steps;
    if (k < past.size()){
        steps = k;
    }
    else {
        steps = past.size();
    }

    if (future.size() + steps > future.getCapacity()) return false;

    for (int i = 0; i < steps; i++) {
        std::string prev;

        if (!future.push(current)) {
            return false;
        }

        if (!past.pop(prev)) {
            std::string dump;
            future.pop(dump);
            return false;
        }

        current = prev;
        stepsTaken++;
    }

    return true;
}


bool TimeBranch::fastForward(int k, int& stepsTaken) {
    stepsTaken = 0;
    if (k <= 0) return true;

    int steps;
    if (k < future.size()){
        steps = k;
    }
    else {
        steps = future.size();
    }

    if (past.size() + steps > past.getCapacity()) return false;

    for (int i = 0; i < steps; i++) {
        std::string next;

        if (!past.push(current)) {
            return false;
        }

        if (!future.pop(next)) {
            std::string dump;
            past.pop(dump);
            return false;
        }

        current = next;
        stepsTaken++;
    }

    return true;
}


void TimeBranch::placeTimeStone() {
    stones.push(current);
}

bool TimeBranch::hasTimeStone() const {
    return !stones.isEmpty();
}

int TimeBranch::distanceFromTop(Stack& s, const std::string& value) {
    Stack temp(s.size());
    std::string x;
    int dist = 0;
    int result = -1;

    while (s.pop(x)) {
        if (!temp.push(x)) {
            while (temp.pop(x)) s.push(x);
            return -1;
        }
        if (x == value) { result = dist; break; }
        dist++;
    }
    while (temp.pop(x)) s.push(x);
    return result;
}


bool TimeBranch::activateTimeStone() {
    std::string stone;
    if (!stones.pop(stone)) return false;

    if (current == stone) {
        future.clear();
        return true;
    }

    int dFuture = distanceFromTop(future, stone);
    if (dFuture != -1) {
        int steps = dFuture + 1;
        int dummy = 0;
        return fastForward(steps, dummy);
    }

    int dPast = distanceFromTop(past, stone);
    if (dPast != -1) {
        int steps = dPast + 1;
        int dummy = 0;
        return rewind(steps, dummy);
    }

    return false;
}


void TimeBranch::print() const {
    std::cout << "Past   : ";
    past.print();
    std::cout << "\n";

    std::cout << "Current: ( " << current << " )\n";

    std::cout << "Future : ";
    future.print();
    std::cout << "\n";

    std::cout << "Stones : ";
    stones.print();
    std::cout << "\n";
}

const Stack& TimeBranch::getPast() const {
    return past;
}

const Stack& TimeBranch::getFuture() const {
    return future;
}

const UnboundedStack& TimeBranch::getStones() const {
    return stones;
}
