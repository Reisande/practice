#include <iostream>
#include <string>

// These are my attempts to solve questions out of "Cracking the Coding interview"'s
// string chapter.

// Implement an algorithm to determine if a string has all unique characters, without
// additional data structures

bool allUniqueCharacters(const std::string checkString) {
	int checkValue = 1;

	// trivial cases. The empty string has only unique characters, as does the 
	// singleton string
	if(checkString.length() == 0 || checkString.length() == 1) {
		return true;
	}

	// O(n ^ 2) runtime, O(1) memory consumption
	for(int i = 0; i < checkString.length() - 1; i++) {
	  for(int j = i + 1; j < checkString.length(); j++) {
			checkValue = checkValue && (checkString.at(i) ^ checkString.at(j));
		}
	}
		
	return (checkValue == 1);
}

int main() {

	while(true) {
		std::string checkString = "";
		std::cin >> checkString;
		
		std::cout << "It is: " << allUniqueCharacters(checkString) << " that "
							<< checkString << " is comprised of unique characters.\n";
	}
	
	return 0;
}

