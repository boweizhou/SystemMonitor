#include <dirent.h>
#include <unistd.h>
#include <sstream>
#include <string>
#include <vector>
#include <format.h>
#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;
using std::string;
using std::getline;

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
  string os, kernel, version;
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

// Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 
  float MemTotal, MemFree, value;
  string key,line;
  std::ifstream stream(kProcDirectory+ kMeminfoFilename);
  if (stream.is_open()){
    while (std::getline(stream,line)){
      std::istringstream  linestream(line);
      linestream >> key >> value;
      if (key == filterMemTotalString) { MemTotal = value;}
      if (key == filterMemFreeString) { MemFree = value;}
    }
  }
  stream.close();
  return (MemTotal - MemFree)/MemTotal;
}


// Read and return the system uptime
long LinuxParser::UpTime() {
  string line;
  long uptime = 0;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> uptime;
  }
  stream.close();
  return uptime;
 }


// Read and return CPU utilization
vector<float> LinuxParser::CpuUtilization(int pid) {
  string line, time_str;
  vector<float> time;
  std::ifstream stream(kProcDirectory + to_string(pid) + kStatFilename);
  if (stream.is_open()){
    std::getline(stream, line);
    std::istringstream linestream(line);
    for (int i=0; i<22; i++){
      linestream >> time_str;
      if ((i==13) | (i==14) | (i==15) | (i==16) | (i==21)){
        time.push_back(stof(time_str));
      }
    }  
  }
  stream.close();
  return time;
}
  


// Read and return the total number of processes
int LinuxParser::TotalProcesses() {
  string line, key, value;
  int TotalNumberProcesses {0};
  std::ifstream stream(kProcDirectory + kStatFilename);
  
  if(stream.is_open()){
  	while(getline(stream, line)){
    	std::istringstream linestream(line);
      while(linestream >> key >> value){
        if(key == filterProcesses){
        	TotalNumberProcesses = stoi(value);
          break;
        }
      }
    }
  }
  stream.close();
  return TotalNumberProcesses;
}

// Read and return the number of running processes
int LinuxParser::RunningProcesses() {
  string line, key, value;
  int TotalNumberRunningPro {};
  std::ifstream stream(kProcDirectory + kStatFilename);
  
  if(stream.is_open()){
  	while(getline(stream, line)){
    	std::istringstream linestream(line);
      while(linestream >> key >> value){
        if(key == filterRunningProcesses){
        	TotalNumberRunningPro = stoi(value);
          break;
        }
      }
    }
  }
  stream.close();
  return TotalNumberRunningPro;
}

// Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) {
  string CommandLine;
  std::ifstream stream(kProcDirectory + to_string(pid) + kCmdlineFilename);
  if (stream.is_open()){
    getline(stream,CommandLine);
  }
  stream.close();
  return CommandLine;
}

// Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid){
  string line, key, value;
  int ram;
  std::ifstream stream(kProcDirectory + to_string(pid) + kStatusFilename);
  
  if(stream.is_open()){
  	while(getline(stream, line)){
    	std::istringstream linestream(line);
      	while(linestream >> key >> value){
        	if(key == filterProcMem){
            	ram = (stoi(value)/1000);
            }
        }
    }
  }
  stream.close();
  return to_string(ram); 
} 


// Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) {
  string line, key, value;
  string Uid;
  std::ifstream stream(kProcDirectory + to_string(pid) + kStatusFilename);
  
  if(stream.is_open()){
  	while(getline(stream, line)){
      	std::istringstream linestream(line);
        while(linestream >> key >> value){
        	if(key == filterUID){
            	Uid = value;
            }
        }
    }
  }
  stream.close();
  return Uid;
 }

// Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) { 
  string user, x, pid_, line;
  std::ifstream stream(kPasswordPath);
  if (stream.is_open()){
    while (std::getline(stream, line)){
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      linestream >> user >> x >> pid_;
      if (pid_ == LinuxParser::Uid(pid))
        break;
    }
  }
  return user; }

// bool Is_number(const string &s)
// {
//   for (uint i = 0; i < s.length(); i++) // for each char in string,
//     if (!((s[i] >= '0' && s[i] <= '9') || (s[i] == ' ')))
//       return false;
//   return true;
// }

// Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) {
  string line, uptime_str;
  long uptime;
  std::ifstream stream(kProcDirectory + to_string(pid) + kStatFilename);
  
  if(stream.is_open()){
    getline(stream, line);
    std::istringstream linestream(line);
    for (int i = 0; i <22 ; i ++){
      linestream >> uptime_str;
    }
    // uptime = stol(uptime_str)/sysconf(_SC_CLK_TCK);
    if (uptime_str == ""){
      uptime_str = "0";
    }
    for(uint i = 0; i < uptime_str.length();i++){
      if (((uptime_str[i] >= '0' && uptime_str[i] <= '9'))){
        uptime = stol(uptime_str)/sysconf(_SC_CLK_TCK);
      } 
    }
  }
  stream.close();
  return uptime;
}


