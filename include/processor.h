#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <string>
#include "linux_parser.h"
class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp

  // TODO: Declare any necessary private members
 private:
  std::string line;
  // int user, nice, system, idle, iowait, irq, softirq, steal;
  std::istringstream linestream;
  std::string s;
  // current state
  int user, nice, system, idle, iowait, irq, softirq, steal;
  // previous state
  int prevuser, prevnice, prevsystem, previdle, previowait, previrq,
      prevsoftirq, prevsteal;
  // subtotal valued
  int PrevTotal, PrevNonIdle, Idle, NonIdle, PrevIdle, Total;
  // returned values
  int totald, idled, total, nonidle;
};

#endif