#include "processor.h"
#include <sstream>
#include "linux_parser.h"

using std::string;

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() {
    string line, key;
    float NonIdle, Total, totald, idled;
    float user, nice, system, idle, iowait, irq, softirq, steal, guest, guest_nice;
    float cpu_percentage = 0.0;
    std::ifstream stream(LinuxParser::kProcDirectory + LinuxParser::kStatFilename);
    if (stream.is_open()){
        while (std::getline(stream, line)) {
            std::istringstream linestream(line);
            linestream >> key >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal >> guest >> guest_nice;
            if (key == "cpu")
                break;
        }
        // Calculate CPU usage percentage
        idle = idle + iowait;
        NonIdle = user + nice + system + irq + softirq + steal;
        Total = idle + NonIdle;
        totald = Total - getPrevTotal();
        idled = idle - getPrevIdle();
        cpu_percentage = (totald - idled) / totald;
        // Update previous values
        setPrevIdle(idle);
        setPrevIowait(iowait);
        setPrevTotal(Total);
        setPrevNonIdle(NonIdle);
    }
    return cpu_percentage; 

}