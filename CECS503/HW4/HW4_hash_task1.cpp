#include <iostream>
#include <vector>
#include <string>
#include <list>
using namespace std;

int nextPrime(int n);
bool isPrime(int n);


class HashEntry{
  public:
    int key;
    int value;

    HashEntry(int key, int value){
      this->key = key;
      this->value = value;
      }

    int getKey(void)
    { return key; }
    int getValue(void)
    { return value; }
};
 
class HashMap {
private:
      HashEntry **table;
      int table_size = 17;
      int current_size = 0;
public:
      HashMap() {
            table = new HashEntry*[table_size];
            for (int i = 0; i < table_size; i++)
                  table[i] = NULL;
      }
 
      void setTableSize(int n){
        table_size = n;
      }
      int getTableSize(void){
        return table_size;
      }
      
      int get(int value) {
            int hash = (value % table_size);
            while (table[hash] != NULL && table[hash]->getValue() != value)
                  hash = (hash + 1) % table_size;
            if (table[hash] == NULL)
                  return -1;
            else
              return table[hash]->getValue();
      }

      int get_key(int value) {
            int hash = (value % table_size);
            while (table[hash] != NULL && table[hash]->getValue() != value)
                  hash = (hash + 1) % table_size;
            if (table[hash] == NULL)
                  return -1;
            else
              return table[hash]->getKey();
      }

    int length(){
      return current_size;
    }

		void printHash()
		{  
      for (int i = 0; i < table_size; i++){
         if (table[i] != NULL)
          cout<< table[i]->getKey() << " - " << table[i]->getValue() <<endl;
      }
		}
      
      void insert(int value) {
            /* your code here*/
            int hash = (value % table_size);
            while (table[hash] != NULL && table[hash]->getValue() != value){
                cout << "Collision: " << hash << " " << value << endl;	
                hash = (hash + 1) % table_size;
              }

            if (table[hash] != NULL){
                cout << "PERFORMING DELETE!!!!!!!" << endl;
                current_size -= 1;
                delete table[hash];
              }

            table[hash] = new HashEntry(hash, value);
            current_size += 1;

            // if (current_size > table_size/2) {
				    //   rehash();
			      // }
      }     

      ~HashMap() {
            for (int i = 0; i < table_size; i++)
                  if (table[i] != NULL)
                        delete table[i];
            delete[] table;
      }


		void rehash()
    {
      cout << "Performing rehashing" << endl;
      int old_table_size = table_size;
      table_size = nextPrime(2 * table_size);
      HashEntry **tmp_table = table;
      table = new HashEntry*[table_size];

      current_size = 0;

      for (int i = 0; i < old_table_size; i++){
        if (tmp_table[i] != NULL){
          insert(tmp_table[i]->getValue());
        }
      } 
    }
};

int nextPrime(int n)
{
	if (n % 2 == 0)
		n++;

	for (; !isPrime(n); n += 2)
		;

	return n;
}

bool isPrime(int n)
{
	if (n == 2 || n == 3)
		return true;

	if (n == 1 || n % 2 == 0)
		return false;

	for (int i = 3; i * i <= n; i += 2)
		if (n % i == 0)
			return false;

	return true;
}

int main(int argc, const char * argv[]){
  HashMap hash;
  int key;
  int itemsCount = 12;
  int data[12] = { 121, 81, 16, 100, 25, 0, 1, 9, 4, 36, 64, 49}; 

  for (int i = 0; i < itemsCount; ++i){
    cout << i << " " << data[i] << endl;
    hash.insert(data[i]);

	}

  // Test all values in array 
  cout << "\nCheck each variable in array: " <<endl; 
  for (int i = 0; i < itemsCount; ++i){
      cout << hash.get(data[i]) << ",";

	}
  cout << "\n\nTotal size of Hash table: " <<hash.getTableSize() << endl;
  cout << "Total elements in Hash table: " << hash.length() <<endl;

    // cout << hash.get(121) << endl;
    // cout << hash.get_key(121) << endl;
    // cout << hash.getTableSize() << endl;

  cout << "\nKey - Value" << endl;
  hash.printHash();
}