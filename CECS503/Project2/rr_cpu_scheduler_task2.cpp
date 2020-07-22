#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <bits/stdc++.h> 

using namespace std;

const int TIMEQUANTUM = 5;
const int TOTAL_CPUS = 4;

struct proccess {
  int PID;
  int arrivalTime;
  int burstTime;

  proccess(){
    PID = 0;
    arrivalTime = 0;
    // All jobs  with burstTime 0 teated as Completed 
    burstTime = 0;
  }
};

struct cpu_struct {
  int runQuantumTime;
  vector <proccess> readyQueue;

  cpu_struct(){
    runQuantumTime = 0;
  }
};


void read_pids_from_file(vector <proccess> &jobs, string file_name){
  ifstream inFile;
  // open the file stream
  inFile.open(file_name);
  // check if opening a file failed
  if (inFile.fail()) {
    cerr << "Error opeing a file" << endl;
    inFile.close();
    exit(1);
  }

  string line;
  while (getline(inFile, line)) {
    proccess P;
    stringstream   linestream(line);
    string         value;
    int count = 0; 

    while(getline(linestream,value,','))
    {
        if ( count == 0 ){
          P.PID = atoi(value.c_str());
        } else if ( count == 1) {
          P.arrivalTime = atoi(value.c_str());
        } else if ( count == 2 ){
          P.burstTime = atoi(value.c_str());
        }
        count++;
    }
    // Append processes to wait queue 
    jobs.push_back(P);
    // cout << "\nProcess ID: " << P.PID << "\nArrival Time: " <<P.arrivalTime
    // <<  "\nBurst Time: " << P.burstTime <<endl;

    // std::cout << "Line Finished" << std::endl;
  }
  // close the file stream
  inFile.close();
}

int main(int argc, const char * argv[]){
  
  //Creating a vector of proccesses
  // vector <proccess> jobsQueue;
  vector <proccess> waitingQueue;
  vector <proccess> readyQueue;
  cpu_struct cpuProcesses[TOTAL_CPUS];
  

  for ( int i = 0; i < TOTAL_CPUS; i++ ) {
    // cout << i << endl;
    cpu_struct C;
    cpuProcesses[i]=C;
   }

  // for ( int i = 0; i < TOTAL_CPUS; i++ ) {
  //   cout << "i = " << i << cpuProcesses[i].readyQueue.size() << endl;
  //  }
  // cout << "ARRAY SIZE: " << sizeof(cpuProcesses)/sizeof(cpuProcesses[0]) << endl;
   
   

  int quantumTime = 5;
  // Need to keep track of how many 
  int runQuantumTime = 0;
  int totalProcessedJobs = 0; 
  int runningTime = 0;
  // int jobCounts = 1;
  // bool isIdle = true;  
  int scheduledTime; 
  int array_size;

  read_pids_from_file(waitingQueue, "job.txt");
  // int totalJobs = jobsQueue.size();
  // vector <proccess> waitingQueue = jobsQueue;

  // cout << waitingQueue.size()<< endl;
  // cout << readyQueue_new.size()<< endl;

  //  while (waitingQueue.size() > 0 || sizeof(cpuProcesses)/sizeof(cpuProcesses[0]) > 0){

  while (waitingQueue.size() > 0 || cpuProcesses[0].readyQueue.size() > 0 || 
  cpuProcesses[1].readyQueue.size() > 0|| cpuProcesses[2].readyQueue.size() > 0 || cpuProcesses[3].readyQueue.size() > 0){
    
    array_size = sizeof(cpuProcesses)/sizeof(cpuProcesses[0]);

    for ( int i = 0; i < array_size; i++ ){
      // cout << "Runtime: "<<runningTime<< endl;
      if (waitingQueue.size() > 0 && waitingQueue.front().arrivalTime <= runningTime){
      
        if (waitingQueue.front().burstTime <= 0){
          waitingQueue.erase(waitingQueue.begin());
          continue;
        }
        cpuProcesses[i].readyQueue.push_back(waitingQueue.front());
        waitingQueue.erase(waitingQueue.begin());
      }

      if (cpuProcesses[i].readyQueue.size() > 0){
        if (cpuProcesses[i].readyQueue.front().burstTime >= quantumTime && cpuProcesses[i].runQuantumTime == 0){
          scheduledTime = quantumTime;
        }else if (cpuProcesses[i].readyQueue.front().burstTime < quantumTime && cpuProcesses[i].runQuantumTime == 0){
          scheduledTime = cpuProcesses[i].readyQueue.front().burstTime;
          cpuProcesses[i].runQuantumTime =  quantumTime -  scheduledTime;
        }else{
          if (cpuProcesses[i].readyQueue.front().burstTime >= cpuProcesses[i].runQuantumTime ){
            scheduledTime = cpuProcesses[i].runQuantumTime;
            cpuProcesses[i].runQuantumTime = 0;
          }else{
            scheduledTime = cpuProcesses[i].readyQueue.front().burstTime;
            cpuProcesses[i].runQuantumTime -= cpuProcesses[i].readyQueue.front().burstTime;
          }
        }

        cpuProcesses[i].readyQueue.front().burstTime -= scheduledTime;
        runningTime += scheduledTime;

        if (cpuProcesses[i].readyQueue.front().burstTime > 0){ 
          cout << "Process #: " << i + 1 << " Job " << cpuProcesses[i].readyQueue.front().PID << ", scheduled for " << scheduledTime <<  "ms" <<endl;
        }else{
          cout << "Process #: " << i + 1 << " Job " << cpuProcesses[i].readyQueue.front().PID << ", scheduled for " << scheduledTime <<  "ms, completed" <<endl;
        }

        if (cpuProcesses[i].readyQueue.front().burstTime > 0){
          cpuProcesses[i].readyQueue.push_back(cpuProcesses[i].readyQueue.front());
        }
        cpuProcesses[i].readyQueue.erase(cpuProcesses[i].readyQueue.begin());

      }else{
        cout << "Process #: " << i + 1  << ", " << quantumTime << ',' << " CPU is Idle" << endl;
        runningTime += quantumTime;     
      }
    }
  }
}


