#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Use total size of 94 that represents ASCII characters
// starting from 32 to 126
const int TOTAL_SIZE = 95;

class TrieNode{ public:
    char data;
    TrieNode** child_node;
    bool completed_word;

TrieNode(char data){
  this->data = data;
  completed_word = false;
  child_node = new TrieNode*[TOTAL_SIZE];

  for(int i=0;i<TOTAL_SIZE;i++){
    child_node[i] = NULL;
    }
  }
};

class Trie{
  TrieNode* root;
  int total_words;
public:
  Trie(){
    // Creare object with NULL. ASCII \0 means NULL
    root = new TrieNode('\0');
    total_words = 0;
  }

void insert(TrieNode* root, string word){
  // Base case when word size reaches 0
  if(word.size()==0){
    if(root->completed_word == false){
      total_words += 1;
      }

    root->completed_word = true;
    return;
  }

  int index = word[0]- ' ';
  // int index = word[0];
  // cout << word[0] << " " << index << endl;
  // cout << (int)word[0] << endl;
  // cout << word.substr(1) << endl;
  TrieNode* child;

  if(root->child_node[index] != NULL){
    child = root->child_node[index];
  }else{
    child = new TrieNode(word[0]);
    root->child_node[index] = child;
  }
  insert(child,word.substr(1));
}

bool lookup(TrieNode* root, string word){
  // Base case when reaches 0 size
  if(word.size()==0){
    return root->completed_word;
}
  int index = word[0] - ' ';
  // int index = word[0];
  TrieNode* child = root->child_node[index];

  if(child!=NULL){
    return lookup(child,word.substr(1));
  }
  return false;
}


int getTotalWords() {
  return total_words;
}


void remove(TrieNode* root, string word){
  // Base case 
  if(word.size()==0){
    if(root->completed_word == true){
      total_words -= 1;
    }
    root->completed_word = false;
    return;
  }

  int index = word[0]- ' ';
  // int index = word[0];
  TrieNode* child = root->child_node[index];

  if(child != NULL){
    remove(child, word.substr(1));
    if(child->completed_word == false){
      for(int i=0;i<TOTAL_SIZE;i++){
        if(child->child_node[i]!=NULL){
          return;
          }
      }
      delete child;
      root->child_node[index] = NULL;
    }
  }
}

  
int numberOfNodes(TrieNode* root){
  int sum = 1;

  for(int i=0;i<TOTAL_SIZE;i++){
    TrieNode* child = root->child_node[i];
    if(child!=NULL){
      sum += numberOfNodes(child);
      }
    }
  return sum;
}

void alphabetical(TrieNode* root, string word){
  // Base case when completed_word is set to True
  if(root->completed_word){
    cout << word << endl;
    }
    
  for(int i=0;i<TOTAL_SIZE;i++){
    TrieNode* child = root->child_node[i];
    char character = i + ' ';
    // char character = i;
    if(child!=NULL){
      alphabetical(child,word+character);
    }
  }
}

// void alphabetical(TrieNode* root, string word, bool initial = false){
//   // Base case when completed_word is set to True
//   if(root->completed_word){
//     cout << word << endl;
//   }

//   if(initial){
//     int index = word[0] - ' ';
//     TrieNode* child = root->child_node[index];
//     // char character = i;
//     if(child!=NULL){
//       alphabetical(child,word);
//       }
//   }else{ 
//   for(int i=0;i<TOTAL_SIZE;i++){
//     TrieNode* child = root->child_node[i];
//     char character = i + ' ';
//     // char character = i;
//     if(child!=NULL){
//       alphabetical(child,word+character);
//       }
//     }
//   }
// }

void insert(string word){
  insert(root,word);
}

void remove(string word){
  remove(root,word);
}

bool lookup(string word){
  return lookup(root,word);
}

void info(){
  cout << numberOfNodes(root) << " " << total_words << endl;
}

void alphabetical(){
  alphabetical(root,"");
}

void print(TrieNode* root, string output, int depth){
  if(root==NULL){
    return;
    }

  if(root->completed_word==true){
    cout << output << endl;
    }
  // Terminate if it reached the maximum depth
  if(depth==0){
    return;
    }

  for(int i=0;i<TOTAL_SIZE;i++){
    // print start with a
    // char ch = i+97;
     char ch = i + ' ';
    TrieNode* child = root->child_node[i];
    
    print(child,output+ch,depth-1);
    }
}

void autocomplete(string prefix, int depth){
  TrieNode* last_node = root;
  int index = 0;
  
  for(int i=0;i<prefix.size();i++){
    TrieNode* child = last_node->child_node[prefix[i] - ' '];
    // TrieNode* child = current->child_node[prefix[i]];
    if(child==NULL){
      break;
    }
    last_node = child;
    index += 1;
  }
  cout << prefix.substr(0, index) << endl;
  print(last_node,prefix.substr(0, index),depth);
  cout << endl;
}
};

void read_file(string file_name){
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
    cout << line << endl;
  }
  // close the file stream
  inFile.close();
}

bool char_check(string word) { 
  for(int i=0;i<word.length();i++){
    // if ((word[i]>=48 && word[i]<=57)||
    //     (word[i]>=65 && word[i]<=90)||
    //     (word[i]>=97 && word[i]<=122))
        
    if(word[i]>=97 && word[i]<=122) {
          continue;
    } else {
      return false;
    }
  }
  return true;
}

int main() {

  // int choice;

  // cin >> choice;

  Trie t;

  

//   while(choice != -1){
//     string word;
//     string prefix;
//     int k;
//   switch(choice) {

// case 1 : // insert

// cin >> word;

// t.insert(word);

// break;

// case 2 : // lookup

// cin >> word;

// cout << t.lookup(word) << endl;

// break;

// case 3 : // remove

// cin >> word;

// t.remove(word);

// break;

// case 4 : // info

// t.info();

// break;

// case 5 : // alphabetical

// t.alphabetical();

// break;

// case 6 : //autocomplete

// cin >> prefix;

// cin >> k;

// t.autocomplete(prefix,k);

// break;

// default :

// return 0;

// }

// cin >> choice;

// }

// return 1;
  // read_file("Dictionary.txt");
  ifstream inFile;
  // open the file stream
  inFile.open("Dictionary.txt");
// check if opening a file failed
  if (inFile.fail()) {
    cerr << "Error opeing a file" << endl;
    inFile.close();
    exit(1);
  }

  string line;
  while (getline(inFile, line)) {
    t.insert(line);
    // cout << line << endl;
    // if (char_check(line)){
    //   // cout << line << endl;
    //   t.insert(line);
    // }
    // cout << line << endl;
    // // char_check(line);
    //  t.insert(line);
  }
  // close the file stream
  inFile.close();
  // t.alphabetical();
  // t.autocomplete(" ",3);
  // cout << t.getTotalWords()<< endl;
  // char c = ' ';
  // cout << (int) c << endl;
// 

  // read_file("Dictionary.txt");
  // t.insert(word);

  // Part 1:
  // Dictionary.txt is provided to you to construct the Trie. Each line contains a valid search query. Your task is to insert these queries into your Trie. Implement trie classes for part 1.
  cout << "Part1:"<< endl;
  cout << "Total inserted words: " << t.getTotalWords() << endl;
  t.info();

  // cout << "Show first 10 words:" << t.getTotalWords() << endl;
  // cout << "Show first 10 words:" << t.getTotalWords() << endl;
  // t.alphabetical();


//   Part II:
// Using the Trie class completed in Part I, create a C++ program that takes an user input and output auto completion options. The interface should be similar to the following:

// $> Please type search queries:
// $> binary sea
// $> Your options are:
// $> binary search
// $> binary search tree
// $> binary search tree java
string prefix;

cout << "\nPart2:"<< endl;
cout << "Please type search queries:" << endl;
getline(cin, prefix);
cout << "Your options are:" << endl;
// getline(cin, prefix);
t.autocomplete(prefix,10);

// Part III:

// Implement a recommendation search. When you search a term that is not in the Trie, recommend the top 3 most similar entries in the Trie:

// $> Please type search queries:
// $> cakr
// $> Do you mean:
// $> cake
// $> cat
// $> crack
// cout << "\nPart3:"<< endl;
// cout << "Please type search queries:" << endl;
// getline(cin, prefix);
// cout << "Do you mean:" << endl;



}