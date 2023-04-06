#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#endif

// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


bool scheduleHelper(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    size_t day,
    map<Worker_T, int>& workerShifts
) {
    if (day == sched.size()) {
        return true;
    }

    for (Worker_T worker = 0; worker < avail[day].size(); worker++) {
        if (avail[day][worker] && workerShifts[worker] < (int) maxShifts) {
            sched[day].push_back(worker);
            workerShifts[worker]++;

            if (sched[day].size() == dailyNeed) {
                return scheduleHelper(avail, dailyNeed, maxShifts, sched, day + 1, workerShifts);
            } else {
                return scheduleHelper(avail, dailyNeed, maxShifts, sched, day, workerShifts);
            }

            sched[day].pop_back();
            workerShifts[worker]--;
        }
    }
    return false;
}

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
) {
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();

    const size_t n = avail.size(); // NUMBER OF DAYS
    const size_t k = avail[0].size(); // NUMBER OF PEOPLE NEEDED A DAY

    sched.resize(n, vector<Worker_T>());
    map<Worker_T, int> workerShifts;

    for (Worker_T worker = 0; worker < k; worker++) {
        workerShifts[worker] = 0;
    }

    return scheduleHelper(avail, dailyNeed, maxShifts, sched, 0, workerShifts);
}