#include <string>
#include <vector>

// simple data structure. Simply takes a series of strings, and returns a final
// concatenated string when needed. This turns concatenation n string from an
// Theta(n^2) process to theta(n)
class StringBuilder {
private:
	std::vector<std::string> strings;
	std::string recursiveStringConvert(int count);

public:
	StringBuilder(std::string initString);
	std::string toString();
	void append(std::string newString);
	
};

StringBuilder::StringBuilder(std::string initString) {
	strings[0] = initString;
}

std::string StringBuilder::recursiveStringConvert(int count) {
	// bsae case of the recursive call
	if(count >= strings.size()) {
		return "";
	}
	else {
		return strings[count] + recursiveStringConvert(count + 1);
	}
}

std::string StringBuilder::toString() {
	return recursiveStringConvert(0);
}

void StringBuilder::append(std::string newString) {
	strings.emplace_back(newString);
}

int main() {
	return 0;
}
