#ifndef UNLOAD_STATION_METRICS_HPP
#define UNLOAD_STATION_METRICS_HPP

#include <iostream>
#include <queue>

class UnloadStationMetrics {
private:
    // Statistics and Efficiency
    int numberOfTrucksUnloaded;
    int timeTrucksInQueue;
    int timeIdle;
    int maxNumberOfTrucksInQueue;

public:
    UnloadStationMetrics() : 
        numberOfTrucksUnloaded(0),
        timeTrucksInQueue(0),
        timeIdle(0),
        maxNumberOfTrucksInQueue(0) {};

    void increaseIdleTime();
    void increaseTimeTrucksInQueue();
    void increaseNumberOfTrucksUnloaded();
    void updateMaxTrucksInQueue(int queueSize);
    void displayStationMetrics(int stationId);

#ifdef UNIT_TESTING
    int getNumberOfTrucksUnloaded() const {
        return numberOfTrucksUnloaded;
    }

    int getTimeTrucksInQueue() const {
        return timeTrucksInQueue;
    }

    int getTimeIdle() const {
        return timeIdle;
    }

    int getMaxNumberOfTrucksInQueue() const {
        return maxNumberOfTrucksInQueue;
    }
#endif
};

#endif