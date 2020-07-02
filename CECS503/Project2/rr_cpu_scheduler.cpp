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
    cout << "\nProcess ID: " << P.PID << "\nArrival Time: " <<P.arrivalTime
    <<  "\nBurst Time: " << P.burstTime <<endl;

    std::cout << "Line Finished" << std::endl;
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

  cout << waitingQueue.size()<< endl;
  cout << readyQueue.size()<< endl;

  while (waitingQueue.size() > 0 || readyQueue.size() > 0){
    cout << "Runtime: "<<runningTime<< endl;
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
      
      cout << "Job " << readyQueue.front().PID << ", scheduled for " << scheduledTime <<  "ms" <<endl;

      readyQueue.front().burstTime -= scheduledTime;
      runningTime += scheduledTime;


      if (readyQueue.front().burstTime > 0){
        readyQueue.push_back(readyQueue.front());
      }
      readyQueue.erase(readyQueue.begin());

    }else{
      cout << quantumTime << ',' << "CPU is Idle" << endl;
      runningTime += quantumTime;     
    }
  }
  // cout << waitingQueue.front().burstTime<< endl;
  // cout << waitingQueue.size()<< endl;
}




  





  //       if (jobs[i].burstTime >= quantumTime && runQuantumTime == 0){
  //         scheduledTime = quantumTime;
  //       }if else(jobs[i].burstTime <= quantumTime && runQuantumTime == 0){
  //         scheduledTime = burstTime; 
  //       }else{
  //         if (jobs[i].burstTime >= runQuantumTime ){
  //           scheduledTime = runQuantumTime;
  //           runQuantumTime = 0;
  //         }else{
  //           scheduledTime = jobs[i].burstTime;
  //           runQuantumTime - = jobs[i].burstTime;
  //         }
  //       }
  // }

  // while (totalProcessedJobs != totalJobs){
  //   isIdle = true;
  //   for (int i = 0; i < totalJobs; i++){

  //     if (jobs[i].arrivalTime <= runningTime && jobs[i].burstTime > 0){

  //       if (jobs[i].burstTime >= quantumTime && runQuantumTime == 0){
  //         scheduledTime = quantumTime;
  //       }if else(jobs[i].burstTime <= quantumTime && runQuantumTime == 0){
  //         scheduledTime = burstTime; 
  //       }else{
  //         if (jobs[i].burstTime >= runQuantumTime ){
  //           scheduledTime = runQuantumTime;
  //           runQuantumTime = 0;
  //         }else{
  //           scheduledTime = jobs[i].burstTime;
  //           runQuantumTime - = jobs[i].burstTime;
  //         }
  //       }


  //       cout << "Job " << jobs[i].PID << ", scheduled for " << scheduledTime <<  "ms" <<endl;

  //       // jobs[i].burstTime = jobs[i].burstTime - quantum;
  //       // running_Time = running_Time + quantum
  //       jobs[i].burstTime -= scheduledTime;
  //       running_Time += scheduledTime;
  //       // quantum_Number++;

  //       isIdle = false;

  //       if (jobs[i].burst_Time <= 0)
  //         totalProcessedJobs++;	//Increment size by one
  //     } else {
  //       break; // All jobs are ariving later than
  //     }
  //   }

  //   if (isIdle){
  //     cout << quantum_Number << ',' << "CPU is Idle" << endl;
  //     // quantum_Number++;
  //     // running_Time = running_Time + quantum;
  //     running_Time += quantumTime;
  //   }
  // }



  // ifstream          inFile;
  // // open the file stream
  // inFile.open("jobs.txt");
  // // check if opening a file failed
  // if (inFile.fail()) {
  //   cerr << "Error opeing a file" << endl;
  //   inFile.close();
  //   exit(1);
  // }

  // string line;
  // while (getline(inFile, line)) {
  //   proccess P;
  //   stringstream   linestream(line);
  //   string         value;
  //   int count = 0; 

  //   if (line.empty()){
  //         continue;
  //   }

  //   while(getline(linestream,value,','))
  //   {   
  //       if ( count == 0 ){
  //         P.PID = atoi(value.c_str());
  //       } else if ( count == 1) {
  //         P.arrivalTime = atoi(value.c_str());
  //       } else if ( count == 2 ){
  //         P.burstTime = atoi(value.c_str());
  //       }
  //       count++;
  //       // cout << "Value(" << value << ")\n";
  //   }
  //   jobs.push_back(P);
  //   cout << jobs.size()<< endl;
  //   // cout << "\nProcess ID: " << jobs.front().PID << "\nArrival Time: " <<
  //   // jobs.front().arrivalTime
  //   // <<  "\nBurst Time: " << jobs.front().burstTime <<endl;

  //   std::cout << "Line Finished" << std::endl;
  //   // // cout << line << endl;
  //   // tree.insert(line);
  //   //  cout <<jobs.front()<< endl;

  // }
  // // close the file stream
  // inFile.close();

  // // for (auto job = begin (jobs); job != end (jobs); ++job) {
  // //   cout << "\nProcess ID: " << job.PID << "\nArrival Time: " <<
  // //   job.arrivalTime
  // //   <<  "\nBurst Time: " << job.burstTime <<endl;
//     cout << jobsQueue.back().burstTime<< endl;
//     cout << jobsQueue.size()<< endl;
//     cout << waitingQueue.back().burstTime<< endl;
//     cout << waitingQueue.size()<< endl;
//     vector <proccess> test;
//     cout << test.size()<< endl;
// }







// while(getline(file,line))
// {
//     std::stringstream   linestream(line);
//     std::string         value;

//     while(getline(linestream,value,','))
//     {
//         std::cout << "Value(" << value << ")\n";
//     }
//     std::cout << "Line Finished" << std::endl;

// }
