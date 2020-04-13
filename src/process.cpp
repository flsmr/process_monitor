#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include <unistd.h>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

// Constructor
Process::Process(int pid) {
    // set private members
    pid_ = pid;
    command_ = LinuxParser::Command(pid);
    user_ = LinuxParser::User(pid);
    ram_ = to_string(stoi(LinuxParser::Ram(pid_))/1024).c_str();

   // calculate cpu time utilization
    vector<string> timings{LinuxParser::CpuUtilization(pid_)};
    if (timings.size() >= 22) {
       // calcualtion follows the procedure given in
       // https://stackoverflow.com/questions/16726779/how-do-i-get-the-total-cpu-usage-of-an-application-from-proc-pid-stat/16736599#16736599
        float  systemUptime = LinuxParser::UpTime();
        float  cpuSpeed     = sysconf(_SC_CLK_TCK); // Hz
        float  uTime        = stoi(timings[13]);
        float  sTime        = stoi(timings[14]);
        float  cuTime       = stoi(timings[15]);
        float  csTime       = stoi(timings[16]);
        float  startTime    = stoi(timings[21]);
        processActiveTime_  = ((uTime + sTime + cuTime + csTime) / cpuSpeed);  // seconds
        processUpTime_      = (systemUptime - (startTime / cpuSpeed)); // seconds
        cpuUtilization_     = processActiveTime_/processUpTime_;
    }
}
// Return this process's ID
int Process::Pid() { return pid_; }

// Return this process's CPU utilization (lifetime average)
float Process::CpuUtilization() {
    return cpuUtilization_;
}

// Return the command that generated this process
string Process::Command() { return command_; }

// Return this process's memory utilization
string Process::Ram() { return ram_; // MB
}

// Return the user (name) that generated this process
string Process::User() { return user_; }

// Return the age of this process (in seconds)
long int Process::UpTime() { return processUpTime_; }

// Overload the "less than" comparison operator for Process objects
bool Process::operator<(Process const& a) const {
     return cpuUtilization_ < a.cpuUtilization_;
}

// Overload the "greater than" comparison operator for Process objects
bool Process::operator>(Process const& a) const {
     return cpuUtilization_ > a.cpuUtilization_;
}