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

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 
  float MemTotal, MemFree, value;
  string key,line;
  std::ifstream stream(kProcDirectory+ kMeminfoFilename);
  if (stream.is_open()){
    std::getline(stream, line);
    std::istringstream linestream(line);
    while (linestream >> key >> value) {
      if (key == "MemTotal:") { MemTotal = value;}
      if (key == "MemFree:") { MemFree = value;}
    }
  }
  return (MemTotal - MemFree)/MemTotal;
}


// TODO: Read and return the system uptime
long LinuxParser::UpTime() {
  string line;
  long uptime = 0;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> uptime;
  }
  return uptime;
 }

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { 
  long TimeInSeconds = UpTime();
  long TimeInJiffies = TimeInSeconds * sysconf(_SC_CLK_TCK);
  return TimeInJiffies; 
}

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid) {
  long test;
  //  string line, data;
  //  long TotalTimeInJiffies {0};
  //  int count {0};
  //  std::ifstream myActiveJiffies(kProcDirectory + to_string(pid) + kStatFilename);
  //  if(myActiveJiffies.is_open()){
  //    getline(myActiveJiffies, line);
  //    std::istringstream myStream(line);
  //    while(myStream >> data){
  //      if(count == 13 || count == 14 || count == 15 || count == 16 || count == 21){
  //        TotalTimeInJiffies += stol(data);
  //        }
  //        count++;
  //       }
    // }
  
  return test;

 }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() {
  // string line, data;
  // long TimeInJiffies, TimeInSecs;
  // int count{0};
  // std::ifstream ifs(kProcDirectory + kStatFilename);

  // if (ifs.is_open()){
  //   getline(ifs, line);
  //   std::istringstream linestream(line);

  //    while(ifs >> data){
  //      if(count == 0){
  //        continue;
  //      }else if(count == 1||count == 2||count == 3||count == 6 || count == 7 || count == 8)
  //      {
  //       TimeInJiffies += stol(data);
  //      }
  //      count ++;
  //    }
  //    TimeInSecs = TimeInJiffies / sysconf(_SC_CLK_TCK);  
  // }
  // return TimeInSecs;
  long test = 0;
  return test;
}

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() {
  // string data,line;
  // long IdleTimeInJiffies{};
  // int count{0};
  // std::ifstream ifs(kProcDirectory + kStatFilename);

  // if(ifs.is_open()){
  //   getline(ifs, line);
  //   std::istringstream linestream(line);
  //   while(linestream >> data){
  //     if (count == 4 || count == 5){
  //       IdleTimeInJiffies += stol(data);
  //     }
  //   }
  // }
  // return IdleTimeInJiffies;
  long test;
  return test;
}

// TODO: Read and return CPU utilization
vector<float> LinuxParser::CpuUtilization(int pid) {
  string line, time_str;
  vector<float> time;
  std::ifstream stream(kProcDirectory + to_string(pid) + kStatFilename);
  if (stream.is_open()){
    std::getline(stream, line);
    std::istringstream linestream(line);
    for (int i=0; i<22; i++){
      linestream >> time_str;
      if (i==13 | i==14 | i==15 | i==16 | i==21){
        time.push_back(stof(time_str));
      }
    }  
  }

  return time;
}
  


// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() {
  string line, key, value;
  int TotalNumberProcesses {0};
  std::ifstream stream(kProcDirectory + kStatFilename);
  
  if(stream.is_open()){
  	while(getline(stream, line)){
    	std::istringstream linestream(line);
      while(linestream >> key >> value){
        if(key == "processes"){
        	TotalNumberProcesses = stoi(value);
          break;
        }
      }
    }
  }
  return TotalNumberProcesses;
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() {
  string line, key, value;
  int TotalNumberRunningPro {};
  std::ifstream stream(kProcDirectory + kStatFilename);
  
  if(stream.is_open()){
  	while(getline(stream, line)){
    	std::istringstream linestream(line);
      while(linestream >> key >> value){
        if(key == "procs_running"){
        	TotalNumberRunningPro = stoi(value);
          break;
        }
      }
    }
  }
  return TotalNumberRunningPro;
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) {
  string CommandLine;
  std::ifstream stream(kProcDirectory + to_string(pid) + kCmdlineFilename);
  if (stream.is_open()){
    getline(stream,CommandLine);
  }
  return CommandLine;
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid){
  string line, key, value;
  int ram;
  std::ifstream stream(kProcDirectory + to_string(pid) + kStatusFilename);
  
  if(stream.is_open()){
  	while(getline(stream, line)){
    	std::istringstream linestream(line);
      	while(linestream >> key >> value){
        	if(key == "VmSize:"){
            	ram = (stoi(value)/1000);
            }
        }
    }
  }
  return to_string(ram); 

} 


// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) {
  string line, key, value;
  string Uid;
  std::ifstream stream(kProcDirectory + to_string(pid) + kStatusFilename);
  
  if(stream.is_open()){
  	while(getline(stream, line)){
      	std::istringstream linestream(line);
        while(linestream >> key >> value){
        	if(key == "Uid"){
            	Uid = value;
            }
        }
    }
  }
  return Uid;
 }

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) {
  string line, user, pid_, key;
  std::ifstream stream(kPasswordPath);
  
  if(stream.is_open()){
  	while(getline(stream, line)){
      std::replace(line.begin(),line.end(), ':' , ' ');
    	std::istringstream linestream(line);
      	while(linestream >> user >> key >> pid_){
        	if(pid_ == LinuxParser::Uid(pid)){
            	break;
            }
        }
    }
  }
  
  return user;
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) {
  string line, uptime_str;
  long uptime;
  std::ifstream stream(kProcDirectory + to_string(pid) + kStatFilename);
  
  if(stream.is_open()){
    getline(stream, line);
    std::istringstream linestream(line);
    for (int i; i <22 ; i ++){
      linestream >> uptime_str;
      if (uptime_str != ""){
        uptime = stol(uptime_str)/sysconf(_SC_CLK_TCK);
      }
    }
  }
  return uptime;
}

