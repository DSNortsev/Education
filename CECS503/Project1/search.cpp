#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Use total size of 95 that represents ASCII characters
// starting from 32 to 126, which includes special characters, uppper and lower cases letters
const int TOTAL_SIZE = 95;
// Global variable allows to specify how many suggestion options to print
int TOTAL_SUGGESTION = 3;

class TrieNode{ 
  public:
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
    if(word.size() == 0){
      if(root->completed_word == false){
        total_words += 1;
      }
      root->completed_word = true;
      return;
    }
    // Space is 32 in ASCIS which will be 0 element in array, have to deduct 32, to shift element position
    int index = word[0]- ' ';
    TrieNode* child;

    if(root->child_node[index] != NULL){
      child = root->child_node[index];
    }else{
      child = new TrieNode(word[0]);
      root->child_node[index] = child;
    }
    insert(child,word.substr(1));
  }


  int getTotalWords() {
    return total_words;
  }


  int getTotalNodes(TrieNode* root){
    // Start with 1, becasue root is empty node
    int total = 1;

    for(int i=0;i<TOTAL_SIZE;i++){
      TrieNode* child = root->child_node[i];
      if(child!=NULL){
        total += getTotalNodes(child);
        }
      }
    return total;
  }


  void insert(string word){
    insert(root,word);
  }


  void info(){
    cout << "Total nodes in the trie: " << getTotalNodes(root) << endl;
    cout << "Total inserted words: " << total_words << endl;
  }


  void printAutoSuggestion(TrieNode* root, string output, int &TOTAL_SUGGESTION){

    if(root==NULL){
      return;
    }
    // Terminate if it reached the maximum suggestions 
    if(TOTAL_SUGGESTION == 0){
      return;
    }
    
    if(root->completed_word==true){
      cout << output << endl;
      TOTAL_SUGGESTION -= 1;
    }


    for(int i=0;i<TOTAL_SIZE;i++){
      // print start with space in ASCII which is 32
      char character = i + ' ';
      TrieNode* child = root->child_node[i];
      printAutoSuggestion(child,output+character,TOTAL_SUGGESTION);
    } 
  }


  void autocomplete(string prefix){
    TrieNode* last_node = root;
    int index = 0;
    // Copy total suggestion to temp, need to restore after
    // all suggestions are printed
    int tmp = TOTAL_SUGGESTION;
  
    // For loop to find the last node that has child nodes
    for(int i=0;i<prefix.size();i++){
      TrieNode* child = last_node->child_node[prefix[i] - ' '];
      if(child==NULL){
        break;
      }
      last_node = child;
      index += 1;
    }

    // Display message based on the input, if input value is valid word or not. 
    if (index != prefix.size()){
      cout << "Do you mean:" << endl;
    }else{
      cout << "Your options are:" << endl;
    }

    printAutoSuggestion(last_node,prefix.substr(0, index),TOTAL_SUGGESTION);
    // Restore back to original count
    TOTAL_SUGGESTION = tmp;
  }
};


  void insert_from_file(Trie &tree,string file_name){
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
      // cout << line << endl;
      tree.insert(line);
    }
    // close the file stream
    inFile.close();
  }


void prompt(Trie tree){
  string prefix; 
  cout << "Please type search queries:" << endl;
  getline(cin, prefix);
  tree.autocomplete(prefix);
}

int main() {
  Trie tree;
  // int total_suggestion = TOTAL_SUGGESTION

  // Part 1:
  // Dictionary.txt is provided to you to construct the Trie. Each line contains a valid search query. Your task is to insert these queries into your Trie. Implement trie classes for part 1.
  cout << "Part1:"<< endl;
  insert_from_file(tree, "Dictionary.txt");
  tree.info();

  //   Part II:
  // Using the Trie class completed in Part I, create a C++ program that takes an user input and output auto completion options. The interface should be similar to the following:

  // $> Please type search queries:
  // $> binary sea
  // $> Your options are:
  // $> binary search
  // $> binary search tree
  // $> binary search tree java
  // string prefix;

  cout << "\nPart2:"<< endl;
  // As example, please type above
  prompt(tree);

  // Part III:
  // Implement a recommendation search. When you search a term that is not in the Trie, recommend the top 3 most similar entries in the Trie:

  // $> Please type search queries:
  // $> cakr
  // $> Do you mean:
  // $> cake
  // $> cat
  // $> crack

  cout << "\nPart3:"<< endl;
  // As example, please type zxs
  prompt(tree);
}