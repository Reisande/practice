#include <iostream>
#include <vector>

#include "utils.h"

class Pile {
private:
	std::vector<int> board;
	int length, width;
	
public:
	Pile();
	Pile(const int width, const int length);
	
	void printBoard();
	void placeSand(const int x, const int y, const int grains);

	std::vector<int> returnBoard();
	int returnWidth();
	int returnLength();
	
};

Pile::Pile() {
	length = 11;
	width = 11;
	board.assign(length * width, 0);
}

Pile::Pile(const int width, const int length) {
	this->length = length;
	this->width = width;
	board.assign(length * width, 0);
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
	if(x >= width || y >= length || x < 0 || y < 0) {
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

std::vector<int> Pile::returnBoard() {
	return this->board;
}

int Pile::returnWidth() {
	return this->width;
}

int Pile::returnLength() {
	return this->length;
}

int main() {
	Pile *pile = new Pile();
	
	std::cout << "Enter a location where you would like to place sand, with the "
						<< "amount of sand you would like to place.\n"
						<< "Press -1 to quit.\n"
						<< "Enter -2 <width> <length> to create a new board\n";
	
	while(true) {	
		int x, y, grains;
		std::cin >> x >> y >> grains;

		if(x == -1) {
			break;
		}
		if(x == -2) {
			pile = new Pile(y, grains);
		}
		else {
			pile->placeSand(x, y, grains);

			//pile->printBoard();
		}
	}
	
	std::cout << createBitMap("./board", pile->returnBoard(), pile->returnWidth(), pile->returnLength())
						<< " file created\n";

	return 0;
}
