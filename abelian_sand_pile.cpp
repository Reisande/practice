#include <iostream>
#include <vector>

class Pile {
private:
	std::vector<int> board;
	int length, width;
	
public:
	Pile();
	Pile(int length, int width);
	
	void printBoard();
	void placeSand(const int x, const int y, const int grains);
	
};

Pile::Pile() {
	length = 10;
	width = 10;
	board = new std::vector<int>(0, 100);
}

void Pile::printBoard() {
	for(int i = 0; i < length; i++) {
		for(int j = 0; j < width; j++) {
			std::cout << board[(i * width) + j] << " ";
		}
		std::cout << "\n";
	}
}

void Pile::placeSand(const int x, const int y, const int grains) {
	if(x >= width || y >= length) {
		return;
	}
	else {
		const int boardIndex = (y * width) + x;

		board[boardIndex] += grains;
	
		if(board[boardIndex] >= 4) {
			while(board[boardIndex] >= 4) {
				board[boardIndex] -= 4;
				
				placeSand(x - 1, y, 1);
				placeSand(x + 1, y, 1);
				placeSand(x, y - 1, 1);
				placeSand(x, y + 1, 1);
			}
		}
	}
}

int main() {
	Pile *pile = new Pile();
	
	while(true) {
		std::cout << "Enter a location where you would like to place sand, with the "
							<< "amount of sand you would like to place.\n Press -1 to quit.\n";
		
		int x, y, grains;
		std::cin >> x >> y >> grains;

		if(x == -1) {
			break;
		}
		else {
			pile->placeSand(x, y, grains);

			pile->printBoard();
		}
	}

	return 0;
}
