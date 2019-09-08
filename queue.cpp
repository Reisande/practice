#include <vector>
#include <iostream>

// linked list queue
class LQueue {
private:
	struct Node {
		int value;
		Node *next;

		Node(int aVal, Node *aNext) :
			value(aVal), next(aNext) {};
	};
	int length;
	Node *head;
		
public:
	LQueue() {
		length = 0;
		head = nullptr;
	}
	void enque(int val) {
		Node *newVal = new Node(val, head);
		head = newVal;
		length++;
	}
	int deque() {
		if(length == 0) {
			std::cout << "Empty Queue, nothing to dequeue\n";
			return -1; // generic error value, means nothing
		}
		else if(length == 1) {
			int returnVal = head->value;
			
			delete head;
			head = nullptr;

			return returnVal;
		}
		else {
			Node *current = head;
			Node *nextNode = head->next;
			
			for(int i = 0; i < length - 1; i++) {
				current = nextNode;
				nextNode = nextNode->next;
			}

			int returnVal = nextNode->value;
			current->next = nullptr;
			delete nextNode;

			return returnVal;
		}
	}
	// the top is the first element
	int top() {
		if(length == 0) {
			std::cout << "Queue is empty\n";
			return -1;
		}
		else {
			return head->value;
		}
	}
	// the bottom is the last element in the linked list
	int bottom() {
		if(length == 0) {
			std::cout << "Queue is empty\n";
			return -1;
		}
		else {
			Node *current = head;
			for(int i = 0; i < length; i++) {
				current = current->next;
			}
			return current->value;
		}
	}
};

// doubly linked list queue
class DLQueue {

};

// vector/dynamic array based queue
class VQueue {

};

int main() {

	return 0;
}
