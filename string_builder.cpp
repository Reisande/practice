#include <string>
#include <vector>
#include <iostream>

#include "utils.h"

// simple data structure. Simply takes a series of strings, and returns a final
// concatenated string when needed. This turns concatenation n string from an
// Theta(n^2) process to theta(n)
class StringBuilder {
private:
	std::vector<std::string> strings;
	std::string recursiveStringConvert(int count, std::string accumulator);

public:
	StringBuilder();
	std::string toString();
	void append(std::string newString);
	
};

StringBuilder::StringBuilder() {
}

std::string StringBuilder::recursiveStringConvert(int count, std::string accumulator) {
	// base case of the recursive call
	if(count >= strings.size()) {
		return accumulator;
	}
	else {
		return recursiveStringConvert(count + 1, accumulator + strings[count]);
	}
}

std::string StringBuilder::toString() {
	return recursiveStringConvert(0, "");
}

void StringBuilder::append(std::string newString) {
	strings.emplace_back(newString);
}

int main() {
	srand(time(0)); 
	StringBuilder *stringBuilder = new StringBuilder();

	int numStrings;
	
	std::cout << "Type how many random strings you want to append together: ";
	std::cin >> numStrings;
	
	for(int i = 0; i < numStrings; i++) {
		std::string newRandomString = getRandomString();
		std::cout << newRandomString << " ";

		stringBuilder->append(newRandomString);
	}

	std::cout << "\n\n" << stringBuilder->toString() << "\n\n";
	
	return 0;
}
