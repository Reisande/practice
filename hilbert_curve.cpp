#include <iostream>
#include <vector>

#include "utils.h"

class Space {
private:
	enum curves { up, down, left, right };

	struct Point {
		int x, y;

		Point(const int aX, const int aY) : x(aX), y(aY) {};
	};

public:
	void transformCurve(); // increases the order of the curve
};

int main() {

}
