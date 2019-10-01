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
bool isSubstring(const std::string &s1, const std::string &s2) {
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
	// Taken from Rosetta code's .ppm tutorial in C originally, then modified
  FILE *fp = fopen((filename + ".ppm").c_str(), "wb"); /* b - binary mode */
  (void) fprintf(fp, "P6\n%d %d\n255\n", width, length);
  
	for(int i = 0; i < width * length; i++) {
	  unsigned char color[3] = {0, 0, 0};
		if(data[i] == 0) {
			// leave array as is
		}
		else if(data[i] == 4) {
			//color = {255, 255, 255};
		}
		else {
			color[(data[i]) - 1] = 255;
		}
			
		(void) fwrite(color, 1, 3, fp);
	}
  
  (void) fclose(fp);

	return (filename + ".ppm");
}
