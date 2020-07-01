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
	vector <proccess> jobs;
  read_pids_from_file(jobs, "job.txt");

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
    cout <<jobs.front().burstTime<< endl;
    cout << jobs.size()<< endl;
}







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