#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "linux_parser.h"


using std::string;
using std::to_string;
using std::vector;

// TODO: Return this process's ID
int Process::Pid() { return pid_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { 
    float totalTimeJiffs = LinuxParser::ActiveJiffies(pid_);
    float totalUsageTime = totalTimeJiffs/sysconf(_SC_CLK_TCK);
    float totalTime = LinuxParser::UpTime() - LinuxParser::UpTime(pid_)/sysconf(_SC_CLK_TCK);
    float cpuUsage = (totalUsageTime - TUsageTime_)/(totalTime - TTime_);
    CpuProc_ = cpuUsage;
    TUsageTime_ = totalUsageTime;
    TTime_ = totalTime;
    return cpuUsage;
}

// TODO: Return the command that generated this process
string Process::Command() { return LinuxParser::Command(pid_); }

// TODO: Return this process's memory utilization
string Process::Ram() { 
    
    std::string mem = LinuxParser::Ram(pid_); 
    float a = std::stoi(mem)/1024;
    int b=a;
    return mem = to_string(b);
}

// TODO: Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(pid_); }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return (LinuxParser::UpTime()-LinuxParser::UpTime(pid_)); }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const { 
  return std::stoi(a.ram_) < std::stoi(ram_); 
}