#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <cmath>

// These are my attempts to solve questions out of "Cracking the Coding interview"'s
// string chapter.

// Implement an algorithm to determine if a string has all unique characters, without
// additional data structures

bool allUniqueCharacters(const std::string checkString) {
	// trivial cases. The empty string has only unique characters, as does the 
	// singleton string
	if(checkString.length() == 0 || checkString.length() == 1) {
		return true;
	}
	else {
		int checkValue = 1;
		// O(n ^ 2) runtime, O(1) memory consumption
		for(int i = 0; i < checkString.length() - 1; i++) {
			for(int j = i + 1; j < checkString.length(); j++) { 
				checkValue = (checkString.at(i) ^ checkString.at(j)) & checkValue;
			}
		}
		
		return (checkValue == 1);
	}
}

// given two strings, check to see if they are permutations of one another
bool checkPermutations(std::string string1, std::string string2) {
	// this solution assumes that there is no difference between upper and lower cases
	// letters. This also assumes there are no numbers or special characters. This
	// solution can be trivially extended to include numbers and special characters, but
	// is unnecessary for the sake of the exxercise

	// This solution just parses through the two strings, one letter at a time, and
	// increments two vectors in the corresponding position to a letter (a in string 1
	// means that the 0th index of vector 1 is incremented, b increments 2, etc).
	// This only occurs after checking that the two strings have the same length. The
	// runtime of this is O(n) when n is the length of the strings, and O(1) memory
	if(string1.length() == string2.length()) {
		std::vector<int> vector1(26, 0);
		std::vector<int> vector2(26, 0);

		for(int i = 0; i < string1.length(); i++) {
			(vector1[(int)(tolower(string1.at(i))) - (int)('a')])++;
		}

		for(int i = 0; i < string2.length(); i++) {
			(vector2[(int)(tolower(string2.at(i))) - (int)('a')])++;
		}

		for(int i = 0; i < 26; i++) {
			if(vector1[i] != vector2[i]) {
				return false;
			}
		}

		return true;
	}
	else {										
		return false;
	}
}

std::string urlify(std::string argString) {
	bool haveSeenCharacters = false;
  for(int i = argString.length() - 1; i > 0; i--) {
		if(isalpha(argString.at(i))) {
			haveSeenCharacters = true;
		}

		if(haveSeenCharacters) {
			if(argString.at(i) == ' ') {
				// move back all characters after i 2 spaces, and then replace the space
				// with '%20'
				// this has O(n^2) runtime
				for(int j = argString.length() - 1; j > i + 2; j--) {
					argString.at(j) = argString.at(j - 2);					
				}
				
				argString.at(i) = '%';
				argString.at(i + 1) = '2';
				argString.at(i + 2) = '0';
			}
		}
	}
	
	return argString;
}


// The first, most simple solution I can think of is generate the
// array of all permutations, and check if its a palindrome
// Another solution is to check to see if every character has
// a corresponding pair, or every character except one(which would
// be the middle one)
bool palindromePermuation(std::string argString) {
	std::vector<bool> checkBools(true);

	for(int i = 0; i < argString.length(); i++) {
		// The isalpha() is to allow for convenient testing  with std::cin
		if(isalpha(argString.at(i))) {
			int currentPosition = tolower(argString.at(i)) - (int)('a');
			checkBools[currentPosition] = ! checkBools[currentPosition];
		}
	}

	int numFalses = 0;

	for(int i = 0; i < checkBools.size(); i++) {
		if(! checkBools[i]) {
			numFalses++;
		}
	}
	
	return (numFalses <= 1);
}

// given two strings, check to see whether one can form another after: replacing
// a character, removing a character, or adding a character
bool oneAway(std::string origin, std::string target) {
	bool remove = true;
	bool insert = true;
	bool replace = true;

  if(abs(origin.length() - target.length()) > 1) {
		return false;
	}
	else {
		for(int i = 0; i < std::max(origin.length(), target.length()) - 1; i++) {
			int j = i + (int)(!remove);
			if(origin.at(j) == target.at(i)) {
				continue;
			}
			else if(origin.at(j + 1) == target.at(i)) {
				if(remove) {
					remove = false;
				}
				else {
					return false;
				}
			}
			else if(origin.at(j) == target.at(i + 1)) {
				if (insert) {
					insert = false;
				}
				else {
					return false;
				}
			}
			else if(replace) {
			  replace = false;
			}
			else {
				return false;
			}														 
		}		
	}
	
	return true;
}

std::string compressString(std::string argString) {
	if(argString == "") {
		return "";
	}
	else {
		std::string returnString = "";
		char mostRecentChar = argString.at(0);
		int mostRecentCharCount = 1;
		
		for(int i = 1; i < argString.length(); i++) {
			if(mostRecentChar == argString.at(i)) {
				mostRecentCharCount++;
			}
			else {
				// characters don't match
				returnString += mostRecentChar + std::to_string(mostRecentCharCount);
				mostRecentChar = argString.at(i);
				mostRecentCharCount = 1;
			}
		}

		mostRecentCharCount++;
		returnString += (mostRecentChar) + std::to_string(mostRecentCharCount);	  
	  
		if(returnString.length() <= argString.length()) {
			return returnString;
		}
		else {
			return argString;
		}
	}
}

// given a 2d, n by m  matrix, if an index is 0, set the entire column and
// row of the index to be 0
std::vector<std::vector<int>> zeroMatrix(const std::vector<std::vector<int>> originMatrix) {
	std::vector<std::vector<int>> returnVector = originMatrix;
	std::vector<int> zeroColumns, zeroRows;

	// x is the number of columns, y is the number of rows
	const int x = originMatrix.size();
	const int y = originMatrix[0].size();
	
	for(int i = 0; i < x; i++) {
		for(int j = 0; i < y; i++) {
			if(originMatrix[i][j] == 0) {
				zeroColumns.push_back(i);
				zeroRows.push_back(j);
			}
		}
	}

	// replaces every value in the return matrix column with 0
	for(int i = 0; i < zeroColumns.size(); i++) {
		for(int j = 0; j < y; j++) {
		  returnVector[i][j] = 0;
		}
	}

	// replaces every value in the return matrix row with 0
	for(int i = 0; i < zeroRows.size(); i++) {
		for(int j = 0; j < x; j++) {
		  returnVector[j][i] = 0;
		}
	}

  return returnVector;
}

int main() {
	
	std::string checkString1 = "", checkString2 = "";

	while(true) {
		std::cin >> checkString1;
		//std::cout << checkString1 << " " << checkString2 << ": "
		//					<< checkPermutations(checkString1, checkString2) << "\n";

		std::cout << checkString1 << " "  << compressString(checkString1) << "\n";
	}
	
	return 0;
}

