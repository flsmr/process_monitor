#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include <unistd.h> // cpu speed

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

//constructor
Process::Process(int pid) {
    pid_ = pid;
    //command_ = ;
    user_ = LinuxParser::User(pid);
}
// TODO: Return this process's ID
int Process::Pid() { return pid_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() {
    vector<string> timings{LinuxParser::CpuUtilization(pid_)};

   // calculate timings of previous read
   if (timings.size() >= 22) {
       // calcualtion follows the procedure given in
       // https://stackoverflow.com/questions/16726779/how-do-i-get-the-total-cpu-usage-of-an-application-from-proc-pid-stat/16736599#16736599
        float prevTotalProcessCPUTime = totalProcessCPUTime_; // active cpu time used by process since start
        float prevProcessUpTime = processUpTime_; // time process is running

        float systemUptime = LinuxParser::UpTime();

        float uTime     = stof(timings[13]);
        float sTime     = stof(timings[14]);
        float cuTime    = stof(timings[15]);
        float csTime    = stof(timings[16]);
        float startTime = stof(timings[21]);

        float cpuSpeed   = sysconf(_SC_CLK_TCK); // Hz

        totalProcessCPUTime_ = (uTime + sTime + cuTime + csTime) / cpuSpeed;  // seconds
        processUpTime_ = systemUptime - (startTime / cpuSpeed); // seconds

        float totalProcessCPUTimeDelta = totalProcessCPUTime_ - prevTotalProcessCPUTime;
        float processUpTimeDelta  = processUpTime_ - prevProcessUpTime;
        cpuUtilization_ = totalProcessCPUTimeDelta/processUpTimeDelta;
//        return (processUpTimeDelta - totalProcessCPUTimeDelta)/processUpTimeDelta; // cpu utilization
        return cpuUtilization_; // cpu utilization
    } else {
        return 0.0f;
    }
}

// TODO: Return the command that generated this process
string Process::Command() { return command_; }

// TODO: Return this process's memory utilization
string Process::Ram() { return string(); }

// TODO: Return the user (name) that generated this process
string Process::User() { return user_; }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return processUpTime_; }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const {
//     return cpuUtilization_ < a.cpuUtilization_;
     return processUpTime_ < a.processUpTime_;
}