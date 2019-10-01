#include <iostream>
#include <vector>

#include "utils.h"

enum curves { up, right, down, left };

class Space {
private:
	int order;

	curve orientation;
	
	std::vector<Space *> children;

public:
	Space(); // initializes with a first order hilbert curve
	Space(const int n); // initializes with an nth order hilbert curve
	void transformCurve(); // increases the order of the curve
	void generateBitmap(std::vector<std::vector<int>> &printVector);
	
};

Space::Space() {
	order = 1;
	orientation = up;
	children = { nullptr, nullptr, nullptr, nullptr };	
}

// orientationModifier = 1: clockwise turn
// orientationModifier = -1: counterclockwise turn
// climbs the tree down and turn each child
void turnCurve(const int orientationModifier) {
	orientation = (orientation + orientationModifier) % 4;
	if(order <= 1) { // no children case
		return;
	}
	else {
		for(int i = 0; i < 4; i++) {
			children[i]->turnCurve(orientationModifier);
		}
	}
}

void Space::transformCurve() {
	std::vector<Space *> newChildren(4, this);

	order++;
  
	newChildren[0]->turnCurve(-1);
	newChildren[3]->turnCurve(1);

  children = newChildren;
}

Space::Space(const int n) {
	children = { nullptr, nullptr, nullptr, nullptr };
	
	for(int i = 0; i < n; i++) {
		this->transformCurve();
	}
}

void Space::generateBitmap(std::vector<std::vector<int>> &printVector) {
	if(order == 1) {
		
	}
	else {
		// recursive call with infill between nodes
	}
}

int main() {

	return 0;
}
