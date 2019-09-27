#include <string>
#include <stdlib.h>
#include <fstream>

// creates a random string of length 8(ascii 97-122). This is just for testing purposes
std::string getRandomString() {
	std::string returnString = "";
	std::string alphabet = "AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz";

	for(int i = 0; i < 8; i++) {
		returnString += alphabet.at(rand() % 52);
	}
	
	return returnString;
}

unsigned long int hashString(const std::string key) {
	long unsigned int hashValue = 0;

	for(int i = 0; i < key.length(); i++) {
		hashValue += (int)(key.at(i));
	}

	return hashValue;
}


// simple robin-karp substring check

// uses the idea that if two strings are equal, then they must have the same hash.
// If we pregenerate the hashes for the larger string, then we can efficiently
// check if one string is a substring of the other

// if two strings have the same hash, then we can make the check if one string
// is actually equal to the other

// this assumes that s2 is the string which is the substring
bool isSubstring(const std::string s1, const std::string s2) {
	// the pair is for hash and position within s1
	std::vector<std::pair<long unsigned int, unsigned int>> hashes;

	if(s2.length() > s1.length()) {
		return false;
	}
	else {
		for(int i = 0; i < (s1.length() / s2.length()) + 1; i++) {
			std::pair<long unsigned int, unsigned int> pushPair
				(hashString(s1.substr(i, s2.length())), i);

			hashes.emplace_back(pushPair);
		}

		const unsigned long int checkHash = hashString(s2);

		bool areEqual = false;
		
		for(int i = 0; i < hashes.size(); i++) {
			if(checkHash == hashes[i].first) {
				areEqual = areEqual || (s1.substr(i, s2.length()) == s2);
			}
		}

		return areEqual;
	}
}

std::vector<int> generateRandomVector(const unsigned int size) {
	std::vector<int> returnVector;

	for(int i = 0; i < size; i++) {
		// allows for duplicates in the array
		returnVector.emplace_back(rand() % size);
	}

	return returnVector;
}

// creates bitmap and returns the name of the local file
std::string createBitMap(const std::string filename,
												 const std::vector<int> data,
												 const int width, const int length) {
	std::ofstream ofs;
	ofs.open(filename + ".bmp");

	ofs << "P6\n " << width << " " << length << " 255\n";
	
	for(int i = 0; i < data.size(); i++) {
		if(data[i] == 0) {
			ofs << "0 0 0 ";
		}
		else if(data[i] == 1) {
			ofs << "255 0 0 ";
		}
		else if(data[i] == 2) {
			ofs << "0 255 0 ";
		}
		else if(data[i] == 3) {
			ofs << "0 0 255 ";
		}
	}

	return (filename + ".bmp");
}
