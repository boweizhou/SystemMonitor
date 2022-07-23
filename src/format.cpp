#include <string>
#include <iomanip>

#include "format.h"

using std::string;
using std::to_string;
using std::setw;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) { 
    int hours, minutes, secondsRemaining;
    hours = seconds / 3600;
    minutes = (seconds - (hours*36000)) / 60;
    secondsRemaining = seconds - (hours * 3600) - (minutes*60);

    std::ostringstream elapsedTime;

    elapsedTime << setw(2) << std::setfill('0') << hours << ":" << setw(2) << std::setfill('0') << minutes << setw(2) << std::setfill('0') << secondsRemaining; 
    
    return elapsedTime.str();


    // string time = "00:00:00";
    // if (hours < 10){
    //     time = "0" + std::to_string(hours) + ":"; 
    // }else
    // {
    //     time = std::to_string(hours) + ":";
    // }

    // if (minutes < 10){
    //     time = time + "0" + std::to_string(minutes) + ":"; 
    // }else
    // {
    //     time = time + std::to_string(minutes) + ":";
    // }

    //  if (secondsRemaining < 10){
    //     time = time + "0" + std::to_string(secondsRemaining); 
    // }else
    // {
    //     time = time + std::to_string(secondsRemaining);
    // }

    // return time;
}
