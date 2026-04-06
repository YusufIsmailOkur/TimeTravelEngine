// Yusuf İsmail Okur Section1 22402939
#ifndef TIMETRAVELENGINE_H
#define TIMETRAVELENGINE_H

#include <iostream>
#include <string>
#include "TimeBranch.h"

using std::string;

class TimeTravelEngine
{
public:
    TimeTravelEngine();
    ~TimeTravelEngine();

    int createTimeBranch(const int pastCapacity,
                         const int futureCapacity,
                         const string startLocation,
                         const int branchId);

    void deleteTimeBranch(const int branchId);
    void printAllBranches() const;

    void travelTo(const int branchId, const string newLocation);

    void fastForward(const int branchId, const int k);
    void rewind(const int branchId, const int k);

    void placeTimeStone(const int branchId);
    void activateTimeStone(const int branchId);

    void printTimeBranch(const int branchId) const;

    int mergeBranches(const int branchId1,
                      const int branchId2,
                      const int newBranchId);

private:
    TimeBranch** branches;
    int* ids;
    int count;
    int capacity;

    int findIndex(const int branchId) const;
    void ensureCapacity();
    void insertSorted(TimeBranch* b, int id);
    void removeAt(int idx);

    void appendStack(Stack& dest, const Stack& src) const;
    void appendStones(UnboundedStack& dest, const UnboundedStack& src) const;
};

#endif
