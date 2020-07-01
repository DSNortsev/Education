#include<iostream>
#include <fstream>
#include<stdlib.h>
#include <sys/wait.h>
#include <unistd.h> 
#include <time.h>

using namespace std;
int SIZE = 1000;

void pprint(int array[]){
    cout<<'[';
    for(int i=0;i<SIZE-1;i++)
      cout << array[i] <<','; 
    cout<< array[SIZE-1]<<']'<< endl;
}


void search_and_fork_from_file(string file_name, int array[]){
  ifstream inFile;
  string line;
  int number;
  pid_t  pid;

  inFile.open(file_name);
  
  // check if opening a file failed
  if (inFile.fail()) {
    cerr << "Error opeing a file" << endl;
    inFile.close();
    exit(1);
  }

  while (getline(inFile, line)) {
    // Convert to integer
    number = atoi(line.c_str());
    // Create child process
    pid = fork();
    
    // Run in child process
    if ( pid == 0 ){
      int count = 0, index = 0;
      while( index<SIZE ){
        if( array[index] == number )
          count++;
          index++;
      }
      cout<<"query: "<<number<<"\tcount: "<<count<<"\tpid: "<<getpid()<<endl;
      exit(1);
    } else {
      wait(NULL);
    }  
  }
  // close the file stream
  inFile.close();
}

int main() {
    //Declare the array variable with size "1000"
    int array[SIZE];
    //generating numbers
    srand(time(0)); //seed to random number generator

    //Create a for loop to iterate 1000 times
    for(int i=1;i<=SIZE;i++) {
        /*Generate a random number between "1" and "1000" using rand() function*/
        // tmp = (rand() % 100) + 1; 
        array[i] = (rand() % 100) + 1; 
    }

    cout<< "Random array: " <<endl;
    pprint(array);
    cout<< "\n " <<endl;

    // Read from file and fork while searching
    search_and_fork_from_file("input.txt", array);
}