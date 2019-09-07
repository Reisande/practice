#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <stdlib.h>

class HashTable {
private:
	int maxSize;
	std::string *table;
	int numStrings;
	
public:
	unsigned long int insertString(const std::string key);
	int getSize();
	void setSize(const int size); // really just a resize function
	std::string getString(const unsigned long int hash);
	HashTable();
	HashTable(const int size);
};

HashTable::HashTable() {
	numStrings = 0;
	maxSize = 83; // this is just a generic prime
	table = new std::string[maxSize];
	for(int i = 0; i < maxSize; i++) {
		table[i] = "";
	}
}

HashTable::HashTable(const int size) {
	numStrings = 0;
	maxSize = size;
	table = new std::string[maxSize];
	for(int i = 0; i < maxSize; i++) {
		table[i] = "";
	}
}

int HashTable::getSize() {
	return maxSize;
	// TODO: build rebuild table function
}

void HashTable::setSize(const int newSize) {
	std::cout << "Resizing hashtable from " << maxSize << " to " << newSize << "\n";
	HashTable *newTable = new HashTable(newSize);
	// TODO: create a copy constructor and just call that
  for(int i = 0; i < maxSize; i++) {
		newTable->insertString(table[i]);
	}
	delete []table;
	maxSize = newSize;
	table = newTable->table;
}

// size corresponds to the length of the strings which occupy the
// hash table
unsigned long int HashTable::insertString(const std::string key) {
	unsigned long int hashValue = 0;
	if(numStrings >= maxSize / 2) {
		// Since this is a simple linear replacement hashtable,
		// The amortized runtime when lambda >= size / 2 greatly
		// increases, so then the correct option is to resize the
		// table with a (likely) coprime value

		this->setSize((maxSize * 2) + 2);
	}
	numStrings++;
	for(int i = 0; i < key.length(); i++) {
		hashValue += (int)(key.at(i)) * std::pow(37, i);
	}
	hashValue %= maxSize;
	
	while(table[hashValue] != "") {
		hashValue++;
		hashValue %= maxSize;
	}

	table[hashValue] = key;
	
	return hashValue;
}

std::string HashTable::getString(const unsigned long int hash) {
	return table[hash];
}

// creates a random string of length 8(ascii 97-122). This is just for testing purposes
std::string randomString() {
	std::string returnString = "";
	std::string alphabet = "AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz";
	for(int i = 0; i < 8; i++) {
		returnString += alphabet.at(rand() % 52);
	}
	return returnString;
}

int main() {
	// used for random string generation
	srand(time(0)); 

	HashTable *hashTable = new HashTable();

	std::string insertString = "hello";
	
	unsigned long int hashKey = hashTable->insertString(insertString);

	std::cout << "Inserted String: " << insertString << " at position "
						<< hashKey << "\n";

	std::cout << "Searched value at position: " << hashKey << " "
						<< hashTable->getString(hashKey) << "\n";

	std::vector<long unsigned int> hashKeys;
	// build a bunch of random strings and inserts them into the hashtable
	for(int i = 0; i < 42; i++) {
		std::string insertString = randomString();
		long unsigned int randomPosition = (hashTable->insertString(insertString));
		std::cout << "inserting: " << insertString << " at " << randomPosition << "\n";
	  hashKeys.emplace_back(randomPosition);
	}

	std::cout << "Hash table in order of hash key:\n\n";
	for(int i = 0; i < hashTable->getSize(); i++) {
		// prints out hash keys in chronological order of insertion
		std::cout << "Hash key: " << i << " String: " << hashTable->getString(i) << "\n";
	}

	std::cout << "\n\nHash table in order of hash keys in hashKeys vector:\n";
	for(int i = 0; i < hashKeys.size(); i++) {
	  std::cout << "Hash key: " << hashKeys[i] << " String: " << hashTable->getString(hashKeys[i]) << "\n";
	}
	std::cout << "\n";
	
	return 0;
}
