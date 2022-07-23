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
int Process::Pid() { return this->pid_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() {
    long uptime;
    float seconds;
    vector<float> time = LinuxParser::CpuUtilization(Process::Pid());
    float totaltime;
    totaltime = time[0] + time[1] + time[2] + time[3];
    float hertz = sysconf(_SC_CLK_TCK);
    uptime = LinuxParser::UpTime();
    seconds = uptime - (time[4]/hertz);
    this-> cpu_ = (totaltime/hertz)/seconds;
    return this->cpu_;
}

// TODO: Return the command that generated this process
string Process::Command() { return LinuxParser::Command(pid_); }

// TODO: Return this process's memory utilization
string Process::Ram() { return LinuxParser::Ram(pid_); }

// TODO: Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(pid_); }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::UpTime() - LinuxParser::UpTime(pid_); }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const { return cpu_ < a.cpu_; }