#include "processor.h"
#include <string>
#include "linux_parser.h"


using std::string;
using std::stoi;

// TODO: Return the aggregate CPU utilization

float PrevIdle, Idle, PrevNonIdle, NonIdle, PrevTotal, Total, totald, idled;
float CPU_Percentage;

float Processor::Utilization() { 
    std::vector <std::string> utilization = LinuxParser::CpuUtilization();

    //float cpu = stof(utilization[0]);
    float user = stof(utilization[1]);
    float nice = stof(utilization[2]);
    float system = stof(utilization[3]);
    float idle = stof(utilization[4]);
    float iowait = stof(utilization[5]);
    float irq = stof(utilization[6]);
    float softirq =stof(utilization[7]);
    float steal = stof(utilization[8]);
    //float guest = stof(utilization[9]);
    //float guest_nice = stof(utilization[10]);

    PrevIdle = previdle + previowait;
    Idle = idle + iowait;

    PrevNonIdle = prevuser + prevnice + prevsystem + previrq + prevsoftirq + prevsteal;
    NonIdle = user + nice + system + irq + softirq + steal;
    PrevTotal = PrevIdle + PrevNonIdle;
    Total = Idle + NonIdle;
        // differentiate: actual value minus the previous one
    totald = Total - PrevTotal;
    idled = Idle - PrevIdle;

    CPU_Percentage = (totald - idled)/totald;
        
        //save current values.
    previdle = idle;
    previowait = iowait;
    prevuser = user;
    prevnice = nice;
    prevsystem = system;
    previrq = irq;
    prevsoftirq = softirq;
    prevsteal = steal;
        
    return CPU_Percentage;
   
}