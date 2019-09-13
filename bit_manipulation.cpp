#include <iostream>
#include <climits>
#include <cmath>
#include <bitset>

unsigned int insertion(unsigned int n, unsigned int m, unsigned int i,
											 unsigned int j) {
	// the following section of code generates a number that would be the zero
	// in all the bits from i to j
	int zeros = pow(2, j - i) - 1;
	zeros <<= i;
	zeros ^= INT_MAX;

	n &= zeros;

	n |= m << j;

	return n;
}

int main() {

	unsigned int n, m, i, j;
	
	std::cin >> n >> m >> i >> j;

	std::cout << std::bitset<16>(n).to_string() << " " << std::bitset<16>(m).to_string()
						<< " " << std::bitset<16>(insertion(n, m, i, j)).to_string() << std::endl;
	
	return 0;
}
