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
	if(start >= end) {
		return;
	}
	else {
		int pivot = array[start];
		bool lowerOutOfOrder = false;
		bool upperOutOfOrder = false;
	  bool lowerIndex = start + 1;
		bool upperIndex = end;
		for(int i = start + 1; i < (end - start) / 2; i++) {
			if(array[i] > pivot) {
				// lower end is out of order
				lowerIndex = i;
				lowerOutOfOrder = true;
			}
			if(array[end - i - 1] < pivot) {
				// upper end is out of order
				upperIndex = end - i - 1;
				upperOutOfOrder = true;
			}
			if(upperOutOfOrder && lowerOutOfOrder) {
				int temp = array[lowerIndex];
				array[lowerIndex] = array[upperIndex];
				array[upperIndex] = temp;
				
				lowerOutOfOrder = false;
				upperOutOfOrder = false;
			}
		}

		if(upperOutOfOrder) {
			array[start] = array[upperIndex];
			array[upperIndex] = pivot;
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


	return 0;
}
