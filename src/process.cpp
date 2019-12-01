#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "linux_parser.h"
#include "process.h"

using std::string;
using std::to_string;
using std::vector;

// Constructor
Process::Process(int pid) {
  pid_ = pid;
  user_ = LinuxParser::User(pid_);
  command_ = LinuxParser::Command(pid_);
  ram_ = LinuxParser::Ram(pid_);
  this->SetCpuUtilization();
}

void Process::SetCpuUtilization() {
  std::vector<std::string> data = LinuxParser::CpuUtilization(pid_);
  int uTime, sTime, cuTime, csTime, startTime;
  int totalTime, seconds;
  long upTime;

  upTime = LinuxParser::UpTime();

  uTime = std::stoi(data[13]);
  sTime = std::stoi(data[14]);
  cuTime = std::stoi(data[15]);
  csTime = std::stoi(data[16]);
  startTime = std::stoi(data[21]);

  /* Calculations source
  https:stackoverflow.com/questions/16726779/how-do-i-get-the-total-cpu-usage-of-an-application-from-proc-pid-stat/16736599#16736599
  */
  seconds = upTime - (startTime / sysconf(_SC_CLK_TCK));
  if (seconds <= 0) {
    cpu_usage_ = 0.0;
  } else {
    totalTime = uTime + sTime;
    // Uncomment this line to include children processes
    totalTime = uTime + sTime + cuTime + csTime;
    cpu_usage_ = ((totalTime / sysconf(_SC_CLK_TCK)) / float(seconds));
  }
}

// TODO: Return this process's ID
int Process::Pid() const { return pid_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() const { return cpu_usage_; }

// TODO: Return the command that generated this process
string Process::Command() const { return command_; }

// TODO: Return this process's memory utilization
string Process::Ram() const { return ram_; }

// TODO: Return the user (name) that generated this process
string Process::User() const { return user_; }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::UpTime(pid_); }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const {
  return cpu_usage_ < a.cpu_usage_;
}