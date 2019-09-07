#include <string>
#include <stdlib.h>

// creates a random string of length 8(ascii 97-122). This is just for testing purposes
std::string getRandomString() {
	std::string returnString = "";
	std::string alphabet = "AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz";

	for(int i = 0; i < 8; i++) {
		returnString += alphabet.at(rand() % 52);
	}
	
	return returnString;
}
