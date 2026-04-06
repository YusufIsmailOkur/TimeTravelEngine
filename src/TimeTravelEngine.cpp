// Yusuf İsmail Okur Section1 22402939
#include "TimeTravelEngine.h"
#include <iostream>

TimeTravelEngine::TimeTravelEngine() {
    capacity = 4;
    count = 0;
    branches = new TimeBranch*[capacity];
    ids = new int[capacity];
}

TimeTravelEngine::~TimeTravelEngine() {
    for (int i = 0; i < count; i++) delete branches[i];
    delete[] branches;
    delete[] ids;
}

int TimeTravelEngine::findIndex(const int branchId) const {
    for (int i = 0; i < count; i++) {
        if (ids[i] == branchId) return i;
    }
    return -1;
}

void TimeTravelEngine::ensureCapacity() {
    if (count < capacity) return;

    int newCap = capacity * 2;
    TimeBranch** newBranches = new TimeBranch*[newCap];
    int* newIds = new int[newCap];

    for (int i = 0; i < count; i++) {
        newBranches[i] = branches[i];
        newIds[i] = ids[i];
    }

    delete[] branches;
    delete[] ids;

    branches = newBranches;
    ids = newIds;
    capacity = newCap;
}

void TimeTravelEngine::insertSorted(TimeBranch* b, int id) {
    ensureCapacity();

    int pos = 0;
    while (pos < count && ids[pos] < id) pos++;

    for (int i = count; i > pos; i--) {
        branches[i] = branches[i - 1];
        ids[i] = ids[i - 1];
    }

    branches[pos] = b;
    ids[pos] = id;
    count++;
}

void TimeTravelEngine::removeAt(int idx) {
    delete branches[idx];
    for (int i = idx; i < count - 1; i++) {
        branches[i] = branches[i + 1];
        ids[i] = ids[i + 1];
    }
    count--;
}

int TimeTravelEngine::createTimeBranch(const int pastCapacity,
                                      const int futureCapacity,
                                      const string startLocation,
                                      const int branchId) {
    if (findIndex(branchId) != -1) {
        std::cout << "Cannot create time branch. A branch with ID " << branchId << " already exists.\n";
        return -1;
    }

    TimeBranch* b = new TimeBranch(pastCapacity, futureCapacity, startLocation);
    insertSorted(b, branchId);

    std::cout << "Created time branch with ID " << branchId << ".\n";
    return branchId;
}

void TimeTravelEngine::deleteTimeBranch(const int branchId) {
    int idx = findIndex(branchId);
    if (idx == -1) {
        std::cout << "Cannot delete branch. There is no branch with ID " << branchId << ".\n";
        return;
    }
    removeAt(idx);
    std::cout << "Deleted time branch " << branchId << ".\n";
}

void TimeTravelEngine::printAllBranches() const {
    if (count == 0) {
        std::cout << "There are no time branches to show.\n";
        return;
    }

    std::cout << "Time branches in the system:\n";
    for (int i = 0; i < count; i++) {
        std::cout << "Branch " << ids[i] << ":\n";
        branches[i]->print();
        if (i != count - 1) std::cout << "\n";
    }
}

void TimeTravelEngine::travelTo(const int branchId, const string newLocation) {
    int idx = findIndex(branchId);
    if (idx == -1) {
        std::cout << "Cannot travel. There is no branch with ID " << branchId << ".\n";
        return;
    }

    if (branches[idx]->travelTo(newLocation)) {
        std::cout << "Traveled to " << newLocation << " in branch " << branchId << ".\n";
    } else {
        std::cout << "Cannot travel to " << newLocation << " in branch " << branchId << ". Past stack capacity exceeded.\n";
    }
}

void TimeTravelEngine::fastForward(const int branchId, const int k) {
    int idx = findIndex(branchId);
    if (idx == -1) {
        std::cout << "Cannot fast forward. There is no branch with ID " << branchId << ".\n";
        return;
    }
    int stepsTaken = 0;
    if (branches[idx]->fastForward(k, stepsTaken)) {
        std::cout << "Fast forwarded " << stepsTaken << " steps in branch " << branchId << ".\n";
    } else {
        std::cout << "Cannot fast forward " << k << " steps in branch " << branchId
                  << ". Past stack capacity exceeded.\n";
    }
}


void TimeTravelEngine::rewind(const int branchId, const int k) {
    int idx = findIndex(branchId);
    if (idx == -1) {
        std::cout << "Cannot rewind. There is no branch with ID " << branchId << ".\n";
        return;
    }

    int stepsTaken = 0;
    if (branches[idx]->rewind(k, stepsTaken)) {
        std::cout << "Rewound " << stepsTaken << " steps in branch " << branchId << ".\n";
    } else {
        std::cout << "Cannot rewind " << k
                  << " steps in branch " << branchId
                  << ". Future stack capacity exceeded.\n";
    }
}




void TimeTravelEngine::placeTimeStone(const int branchId) {
    int idx = findIndex(branchId);
    if (idx == -1) return;

    branches[idx]->placeTimeStone();
    std::cout << "Time stone placed at " << branches[idx]->getCurrent() << ".\n";
}

void TimeTravelEngine::activateTimeStone(const int branchId) {
    int idx = findIndex(branchId);
    if (idx == -1) return;

    if (!branches[idx]->hasTimeStone()) {
        std::cout << "Cannot activate time stone. No time stones available.\n";
        return;
    }

    if (branches[idx]->activateTimeStone()) {
        std::cout << "Time stone activated. The traveler is now at " << branches[idx]->getCurrent() << ".\n";
    } else {
        std::cout << "Time stone discarded. The recorded moment is no longer reachable.\n";
    }
}

void TimeTravelEngine::printTimeBranch(const int branchId) const {
    int idx = findIndex(branchId);
    if (idx == -1) return;
    branches[idx]->print();
}

void TimeTravelEngine::appendStack(Stack& dest, const Stack& src) const {
    Stack copy = src;
    Stack tmp(copy.size());
    std::string x;

    while (copy.pop(x)) tmp.push(x);
    while (tmp.pop(x)) dest.push(x);
}

void TimeTravelEngine::appendStones(UnboundedStack& dest, const UnboundedStack& src) const {
    UnboundedStack copy = src;
    UnboundedStack tmp;
    std::string x;

    while (copy.pop(x)) tmp.push(x);
    while (tmp.pop(x)) dest.push(x);
}

int TimeTravelEngine::mergeBranches(const int branchId1,
                                   const int branchId2,
                                   const int newBranchId) {
    int i1 = findIndex(branchId1);
    int i2 = findIndex(branchId2);

    if (i1 == -1 || i2 == -1) {
        std::cout << "Cannot merge branches. Missing branch IDs.\n";
        return -1;
    }

    if (findIndex(newBranchId) != -1) {
        std::cout << "Cannot merge branches. A branch with ID " << newBranchId << " already exists.\n";
        return -1;
    }

    if (branches[i1]->current != branches[i2]->current) {
        std::cout << "Cannot merge branches. Current locations do not match.\n";
        return -1;
    }

    int newPastCap = branches[i1]->past.getCapacity() + branches[i2]->past.getCapacity();
    int newFutureCap = branches[i1]->future.getCapacity() + branches[i2]->future.getCapacity();
    std::string common = branches[i1]->current;

    TimeBranch* nb = new TimeBranch(newPastCap, newFutureCap, common);

    appendStack(nb->past, branches[i1]->past);
    appendStack(nb->past, branches[i2]->past);

    appendStack(nb->future, branches[i1]->future);
    appendStack(nb->future, branches[i2]->future);

    appendStones(nb->stones, branches[i1]->stones);
    appendStones(nb->stones, branches[i2]->stones);

    int first = (i1 < i2) ? i2 : i1;
    int second = (i1 < i2) ? i1 : i2;

    removeAt(first);
    removeAt(second);

    insertSorted(nb, newBranchId);

    std::cout << "Time branches " << branchId1 << " and " << branchId2
              << " merged into new branch " << newBranchId << ".\n";
    return newBranchId;
}
