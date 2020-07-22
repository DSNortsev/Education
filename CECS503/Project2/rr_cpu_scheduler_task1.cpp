#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <bits/stdc++.h> 

using namespace std;

const int TIMEQUANTUM = 5;

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
        // cout << "Value(" << value << ")\n";
    }
    jobs.push_back(P);
    // cout << "\nProcess ID: " << P.PID << "\nArrival Time: " <<P.arrivalTime
    // <<  "\nBurst Time: " << P.burstTime <<endl;

    // std::cout << "Line Finished" << std::endl;
    // // cout << line << endl;
    // tree.insert(line);
    //  cout <<jobs.front()<< endl;

  }
  // close the file stream
  inFile.close();
  // cout <<jobs.front().burstTime<< endl;

}

int main(int argc, const char * argv[]){
	
  //Creating a vector of proccesses
	// vector <proccess> jobsQueue;
  vector <proccess> waitingQueue;
  vector <proccess> readyQueue;

  int quantumTime = 5;
  int runQuantumTime = 0;
  int totalProcessedJobs = 0; 
  int runningTime = 0;
  int jobCounts = 1;
  // bool isIdle = true;	
  int scheduledTime; 

  read_pids_from_file(waitingQueue, "job.txt");
  // int totalJobs = jobsQueue.size();
  // vector <proccess> waitingQueue = jobsQueue;

  // cout << waitingQueue.size()<< endl;
  // cout << readyQueue.size()<< endl;

  while (waitingQueue.size() > 0 || readyQueue.size() > 0){
    // cout << "Runtime: "<<runningTime<< endl;
    if (waitingQueue.size() > 0 && waitingQueue.front().arrivalTime <= runningTime){
    
      if (waitingQueue.front().burstTime <= 0){
        waitingQueue.erase(waitingQueue.begin());
        continue;
      }
      readyQueue.push_back(waitingQueue.front());
      waitingQueue.erase(waitingQueue.begin());
    }

    if (readyQueue.size() > 0){
      if (readyQueue.front().burstTime >= quantumTime && runQuantumTime == 0){
        scheduledTime = quantumTime;
      }else if (readyQueue.front().burstTime < quantumTime && runQuantumTime == 0){
        scheduledTime = readyQueue.front().burstTime;
        runQuantumTime =  quantumTime -  scheduledTime;
      }else{
        if (readyQueue.front().burstTime >= runQuantumTime ){
          scheduledTime = runQuantumTime;
          runQuantumTime = 0;
        }else{
          scheduledTime = readyQueue.front().burstTime;
          runQuantumTime -= readyQueue.front().burstTime;
        }
      }

      readyQueue.front().burstTime -= scheduledTime;
      runningTime += scheduledTime;

      if (readyQueue.front().burstTime > 0){ 
        cout << "Job " << readyQueue.front().PID << ", scheduled for " << scheduledTime <<  "ms" <<endl;
      }else{
        cout << "Job " << readyQueue.front().PID << ", scheduled for " << scheduledTime <<  "ms" << ", completed"<<endl;
      }

      if (readyQueue.front().burstTime > 0){
        readyQueue.push_back(readyQueue.front());
      }
      readyQueue.erase(readyQueue.begin());

    }else{
      cout << quantumTime << ',' << "CPU is Idle" << endl;
      runningTime += quantumTime;     
    }
  }
}
