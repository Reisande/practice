#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <vector>

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
				for(int j = argString.length(); j > i + 2; j--) {
					argString.at(j) = argString.at(j - 2);					
				}
				
				argString.at(i) = '%';
				argString.at(i) = '2';
				argString.at(i) = '0';
			}
		}
	}
	
	return argString;
}

int main() {

	while(true) {
		std::string checkString1 = "", checkString2 = "";
		int spaceCount = -1;
		for(int i = 0; i < 3; i++){
			std::cin >> checkString2;
			checkString1 += checkString2 + " ";
		}
		for(int i = 0; i < spaceCount; i++) {
			checkString1 += "   ";
		}
		
		//std::cout << checkString1 << " " << checkString2 << ": "
		//					<< checkPermutations(checkString1, checkString2) << "\n";
		std::cout << checkString1 << " " << urlify(checkString1);
	}
	
	return 0;
}

