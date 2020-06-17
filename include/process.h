#ifndef PROCESS_H
#define PROCESS_H

#include "linux_parser.h"
#include <string>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  int Pid();                               // TODO: See src/process.cpp
  std::string User();                      // TODO: See src/process.cpp
  std::string Command();                   // TODO: See src/process.cpp
  float CpuUtilization();                  // TODO: See src/process.cpp
  std::string Ram();                       // TODO: See src/process.cpp
  long int UpTime();                       // TODO: See src/process.cpp
  bool operator<(Process const& a) const;  // TODO: See src/process.cpp
  
  Process(int Pid){
      pid_ = Pid;
      user_ = User();
      command_ = Command();
      cpuutilization_ = CpuUtilization();
      ram_ = Ram();
      uptime = UpTime();
  }
  // TODO: Declare any necessary private members
 private:
  int pid_;
  std::string user_;
  std::string command_;
  float cpuutilization_;
  std::string ram_;
  long int uptime;
  float CpuProc_; 
  float TUsageTime_; //prev
  float TTime_; //prev

    

};

#endif