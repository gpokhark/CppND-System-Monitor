#include "processor.h"

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() {
  // Updating previous state members
  prevuser = user;
  prevnice = nice;
  prevsystem = system;
  previdle = idle;
  previowait = iowait;
  previrq = irq;
  prevsoftirq = softirq;
  prevsteal = steal;

  std::ifstream stream(LinuxParser::kProcDirectory +
                       LinuxParser::kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> s >> user >> nice >> system >> idle >> iowait >> irq >>
        softirq >> steal;
  }

  /* Formula taken from here:
  https://stackoverflow.com/questions/23367857/accurate-calculation-of-cpu-usage-given-in-percentage-in-linux
  */
  PrevIdle = previdle + previowait;
  Idle = idle + iowait;

  PrevNonIdle =
      prevuser + prevnice + prevsystem + previrq + prevsoftirq + prevsteal;
  NonIdle = user + nice + system + irq + softirq + steal;

  PrevTotal = PrevIdle + PrevNonIdle;
  Total = Idle + NonIdle;

  totald = Total - PrevTotal;
  idled = Idle - PrevIdle;

  return (totald - idled) / float(totald);
}