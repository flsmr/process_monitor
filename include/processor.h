#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp

  // TODO: Declare any necessary private members
 private:
    float userTime_{0.0f};
    float niceTime_{0.0f};
    float systemTime_{0.0f};
    float idleTime_{0.0f};
    float iowaitTime_{0.0f};
    float irqTime_{0.0f};
    float softirqTime_{0.0f};
    float stealTime_{0.0f};
    float guestTime_{0.0f};
    float guestNiceTime_{0.0f};
};

#endif