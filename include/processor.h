#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp
  
  // TODO: Declare any necessary private members
 private:
    float previdle,previowait, prevuser, prevnice, prevsystem, previrq, prevsoftirq, prevsteal = 0;
};

#endif