#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int TOTAL_SIZE = 26;

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
    root = new TrieNode('\0');
    total_words = 0;
  }

void insert(TrieNode* root, string word){
  if(word.size()==0){
    if(root->completed_word == false){
      total_words += 1;
      }

    root->completed_word = true;
    return;
  }

  int index = word[0]-'a';
  // cout << word << index << endl;
  // cout << (int)word[0] << endl;
  cout << word.substr(1) << endl;
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

  if(word.size()==0){
    return root->completed_word;
}
  int index = word[0]-'a';
  TrieNode* child = root->child_node[index];

  if(child!=NULL){
    return lookup(child,word.substr(1));
  }

  return false;
}

  

void remove(TrieNode* root, string word){

  if(word.size()==0){
    if(root->completed_word == true){
    total_words -= 1;
    }

  root->completed_word = false;
  return;
  }

  int index = word[0]-'a';

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
  if(root->completed_word){
    cout << word << endl;
    }
    
  for(int i=0;i<TOTAL_SIZE;i++){
    TrieNode* child = root->child_node[i];
    char character = i + 'a';
    if(child!=NULL){
      alphabetical(child,word+character);
      }
    }
  }

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

  

void print(TrieNode* root, string output, int k){
  if(root==NULL){
    return;
    }

  if(root->completed_word==true){
    cout << output << " ";
    }
  
  if(k==0){
    return;
    }

  for(int i=0;i<TOTAL_SIZE;i++){
    // print start with a
    char ch = i+97;
    TrieNode* child = root->child_node[i];
    
    print(child,output+ch,k-1);
    }
}

void autocomplete(string prefix, int k){
  TrieNode* current = root;
  
  for(int i=0;i<prefix.size();i++){
    TrieNode* child = current->child_node[prefix[i]-'a'];
    if(child==NULL){
      return;
    }
    current = child;
  }
  print(current,prefix,k);
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
  inFile.open("Dict.txt");
// check if opening a file failed
  if (inFile.fail()) {
    cerr << "Error opeing a file" << endl;
    inFile.close();
    exit(1);
  }

  string line;
  while (getline(inFile, line)) {
    if (char_check(line)){
      // cout << line << endl;
      t.insert(line);
    }
    // cout << line << endl;
    // // char_check(line);
    //  t.insert(line);
  }
  // close the file stream
  inFile.close();
  // t.alphabetical();
  t.autocomplete("a",2);


  // read_file("Dictionary.txt");
  // t.insert(word);
}