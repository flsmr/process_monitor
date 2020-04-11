#include "processor.h"
#include "linux_parser.h"
#include <string>

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() {
    std::vector<std::string> processorUtilization(LinuxParser::CpuUtilization());

    if(processorUtilization.size() >= 10) {
        // the following calculations directly follow:
        // https://stackoverflow.com/questions/23367857/accurate-calculation-of-cpu-usage-given-in-percentage-in-linux

        // calculate timings of previous read
        float prevIdleTime    = idleTime_ + iowaitTime_;
        float prevNonIdleTime = userTime_ + niceTime_ + systemTime_ + irqTime_ + softirqTime_ + stealTime_;
        float prevTotalTime   = prevIdleTime + prevNonIdleTime;

        // update timings with current read
        userTime_      = stof(processorUtilization[0]);
        niceTime_      = stof(processorUtilization[1]);
        systemTime_    = stof(processorUtilization[2]);
        idleTime_      = stof(processorUtilization[3]);
        iowaitTime_    = stof(processorUtilization[4]);
        irqTime_       = stof(processorUtilization[5]);
        softirqTime_   = stof(processorUtilization[6]);
        stealTime_     = stof(processorUtilization[7]);
        guestTime_     = stof(processorUtilization[8]);
        guestNiceTime_ = stof(processorUtilization[9]);

        // calculate timings with current read
        float idleTime    = idleTime_ + iowaitTime_;
        float nonIdleTime = userTime_ + niceTime_ + systemTime_ + irqTime_ + softirqTime_ + stealTime_;
        float totalTime   = idleTime + nonIdleTime;

        // calculate delta between previous and current timings
        float totalDeltaTime = totalTime - prevTotalTime;
        float idleDeltaTime  = idleTime - prevIdleTime;

        return (totalDeltaTime - idleDeltaTime)/totalDeltaTime; // cpu utilization
    } else {
        return 0.0f;
    }

}