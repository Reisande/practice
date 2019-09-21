#include <iostream>
#include <vector>

#include "utils.h"

void _mergeSort(std::vector<int> &array) {

}

void mergeSort(std::vector<int> &array) {
	if(array.size() == 0 || array.size() == 1) {
		// singleton and empty list is trivially sorted
		
	}
	else {
		
	}
}

void _quickSort(std::vector<int> &array, const unsigned int start,
								const unsigned int end, const unsigned int size) {
	if(start + 1 >= end) {
		return;
	}
	else {
		int pivot = array[start];
		bool lowerOutOfOrder = false;
		bool upperOutOfOrder = false;
	  int lowerIndex = start + 1;
		int upperIndex = end;
		
		while(true) {			
			lowerOutOfOrder = lowerOutOfOrder && (pivot > lowerOutOfOrder);
			upperOutOfOrder = upperOutOfOrder && (pivot < upperOutOfOrder);
			
			lowerIndex = lowerOutOfOrder ? lowerIndex : lowerIndex + 1;
			upperIndex = upperOutOfOrder ? upperIndex : upperIndex - 1;
			
			if(upperIndex <= lowerIndex) {
			  int swapIndex = lowerIndex;

				while(array[swapIndex] > pivot) {
					swapIndex--;
				}

				array[start] = array[swapIndex];
				array[swapIndex] = pivot;
				break;
			}
			
			if(lowerOutOfOrder && upperOutOfOrder) {
				int temp = array[lowerIndex];
				array[lowerIndex] = array[upperIndex];
				array[upperIndex] = temp;
				
				lowerOutOfOrder = false;
				upperOutOfOrder = false;
			}			
		}
		
		_quickSort(array, start, upperIndex, size);
		_quickSort(array, upperIndex + 1, end, size);
	}
}

void quickSort(std::vector<int> &array) {
	if(array.size() == 0) {
		return;
	}
	else {
		_quickSort(array, 0, array.size(), array.size());
	}
}

int main() {
	std::vector<int> randomVector = generateRandomVector(30);

	for(int i = 0; i < 30; i++) {
		std::cout << randomVector[i] << " ";
	}

	std::cout << std::endl << std::endl;

	quickSort(randomVector);

	for(int i = 0; i < 30; i++) {
		std::cout << randomVector[i] << " ";
	}

	bool isSorted = true;

	for(int i = 0; i < 29; i++) {
		isSorted = isSorted && (randomVector[i] < randomVector[i + 1]);
	}

	std::cout << "\n\nVector sort " << isSorted << std::endl;
	
	return 0;
}
