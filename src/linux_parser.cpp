#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>
#include <unistd.h>
#include <sstream>

#include "linux_parser.h"

using std::cout;
using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, version, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 
  string mem, value;
  string line;
  float tot, free, used;
  std::ifstream filestream(kProcDirectory + kMeminfoFilename);

  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      
      std::istringstream linestream(line);
      linestream >> mem >> value; 
      if( mem == "MemTotal:"){
        tot = std::stof(value);
      }
      if (mem == "MemAvailable:"){
        free = std::stof(value);
      }
    }
    
    used = tot - free;
    return used/tot;
  }
  return 0.0;
  }

// TODO: Read and return the system uptime
long LinuxParser::UpTime() { 
  string uptime;
  string line;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> uptime;
  }
  return atol(uptime.c_str());
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid) { 
  string line;
  string x;
  int utime=0;
  int stime=0;
  int cutime=0;
  int cstime=0;

  std::ifstream stream(kProcDirectory+std::to_string(pid)+kStatFilename);

  if (stream.is_open())
  {
    std::getline(stream, line);
    std::istringstream linestream(line);

    for (int i=0; i < 23; i++)
    {
      linestream >> x;
      if (i == 12)
      {
        linestream >> utime >> stime >> cutime >> cstime;
        break;
      }
    }
    
    return (utime + stime + cutime + cstime);
    //return utime;
  }
  return 0; 


}

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { 
  string cpu, user, nice, system, idle, iowait, irq, softirq, steal, guest, guest_nice;
  string line;
  vector<string> cpu_data;
  std::ifstream stream(kProcDirectory + kStatFilename);

  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> cpu >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal >> guest >> guest_nice;
    cpu_data.push_back(cpu);
    cpu_data.push_back(user);
    cpu_data.push_back(nice);
    cpu_data.push_back(system);
    cpu_data.push_back(idle);
    cpu_data.push_back(iowait);
    cpu_data.push_back(irq);
    cpu_data.push_back(softirq);
    cpu_data.push_back(steal);
    cpu_data.push_back(guest);
    cpu_data.push_back(guest_nice);
  }
  return cpu_data; 

}

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
  
  string line, token, value;
  int processes=-1;
  std::ifstream filestream(kProcDirectory + kStatFilename);

  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      
      std::istringstream linestream(line);
      linestream >> token >> value; 
      if( token == "processes"){
        processes = std::stoi(value);
      }
    }
  }
  return processes; 
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
  string line, token, token2, value;
  int running=-1;
  std::ifstream filestream(kProcDirectory + kStatFilename);

  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), '_', ' ');
      std::istringstream linestream(line);
      
      linestream >> token >> token2 >> value; 
      if( token2 == "running"){
        running = std::stoi(value);
      }
    }
  }
  return running; 
}



// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) { 
  
  string line;
  
  std::ifstream stream(kProcDirectory + to_string(pid) + "/" + kCmdlineFilename);

  if (stream.is_open()) {
    std::getline(stream, line);
  }
  return line;
}



// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) { 
  string line, token, memory;
  std::ifstream stream(kProcDirectory + to_string(pid) + "/" + kStatusFilename);
  if (stream.is_open()){
    while (std::getline(stream,line)){
      std::istringstream linestream(line);
      linestream >> token >> memory;
      if (token == "VmSize:"){
        return memory;
      }

    }
  }
  return string(); 
}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) { 
  string line, uid, value;
  std::ifstream stream(kProcDirectory + to_string(pid) + "/" + kStatusFilename);
  if (stream.is_open()){
    while (std::getline(stream,line)){
      std::istringstream linestream(line);
      linestream >> uid >> value;
      if(uid == "Uid:"){
        return value;
      }

    }
  }
  return string();
 }

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) { 
  string uid = Uid(pid);
  string line, user, right, value;
  std::ifstream stream(kPasswordPath);
  if (stream.is_open()){
    while (std::getline(stream,line)){
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      linestream >> user >> right >> value;
      if(value == uid){
        return user;
      }

    }
  }
  return string();

}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) { 
  string line, token;
  std::ifstream stream(kProcDirectory + to_string(pid) + "/" + kStatFilename);
  if(stream.is_open()){
    std::getline(stream,line);
    std::istringstream linestream(line);
    int a = 0;
    while (a < 22){
      linestream >> token;
      a++;
    }
    return stol(token)/sysconf(_SC_CLK_TCK);
  }
  return -1;

}