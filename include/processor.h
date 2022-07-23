#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp
  void setPrevIdle(float PrevIdle_){PrevIdle = PrevIdle_; }
  void setPrevIowait(float PrevIowait_){PrevIowait = PrevIowait_; }
  void setPrevNonIdle(float PrevNonIdle_){PrevNonIdle = PrevNonIdle_; }
  void setPrevTotal(float PrevTotal_){PrevTotal = PrevTotal_; }
  float getPrevIdle(){return PrevIdle;}
  float getPrevIowait(){return  PrevIowait;}
  float getPrevNonIdle(){return PrevNonIdle;}
  float getPrevTotal(){return PrevTotal;}  

  // TODO: Declare any necessary private members
 private:
  float PrevIdle = 0.0;
  float PrevIowait = 0.0;
  float PrevNonIdle = 0.0;
  float PrevTotal = 0.0;
};

#endif