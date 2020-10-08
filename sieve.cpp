#include <iostream>
#include <vector>
#include <cmath>

int main(int argc, char **argv) {
	if(argc != 2) {
		std::cout << "Usage:\n./a.out <n>\nwhere n is the prime which you would like\n";
		return -1;
	}

	std::vector<int> sieve = std::vector<int>({2});
	int nthPrime = atoi(argv[1]);

	int currentNumber = 3;
	while(sieve.size() < nthPrime) {
		bool isPrime = true;
		int sqrt = (int)(std::sqrt(currentNumber)) + 1;
		for(auto i = sieve.begin(); i != sieve.end(), *i < sqrt; i++) {
			isPrime &= (currentNumber % *i) != 0;
		}

		if(isPrime) {
			sieve.push_back(currentNumber);
		}
		
		currentNumber++;
	}

	std::cout << nthPrime << " prime is: " << sieve.back() << "\n";
}
