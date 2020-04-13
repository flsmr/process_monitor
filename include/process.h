#ifndef PROCESS_H
#define PROCESS_H

#include <string>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  Process(int pid);
  int Pid();                               
  std::string User();                      
  std::string Command();                   
  float CpuUtilization();                  
  std::string Ram();                       
  long int UpTime();                      
  bool operator<(Process const& a) const;
  bool operator>(Process const& a) const;

  // TODO: Declare any necessary private members
 private:
 int pid_{0};
 std::string user_{};
 std::string command_{};
 std::string ram_{};
 float processActiveTime_{0}; //seconds
 float processUpTime_{0}; //seconds
 float cpuUtilization_{0.0f};
 long int uptime{0};

};

#endif