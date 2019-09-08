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

	void push(int val) {
		Node *newVal = new Node(val, head);
		head = newVal;
		length++;
	}

	int pop() {
		if(length == 0) {
			std::cout << "Empty Queue, nothing to dequeue\n";
			return -1; // generic error value, means nothing
		}
		else if(length == 1) {
			int returnVal = head->value;
			
			delete head;
			head = nullptr;

			length--;

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

			length--;

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

	int size() {
		return length;
	}

	bool isEmpty() {
		return (length == 0);
	}
	
};

// doubly linked list queue
class DLQueue {
private:
	struct Node {		
		int value;
		Node *next;
		Node *previous;

		Node(int aVal, Node *aNext, Node *aPrevious) :
			value(aVal), next(aNext), previous(aPrevious) {};
	};
	Node *sentinel;
	int length;
	
public:
	DLQueue() {
	  sentinel = new Node(-1, sentinel, sentinel);
		length = 0;
	}
	
	void push(int pushValue) {
		length++;
		Node *newNode = new Node(pushValue, sentinel->next, sentinel->previous);
		sentinel->next = newNode;
	}
	
	int pop() {
		if(length == 0) {
			std::cout << "Empty Queue, nothing to dequeue\n";
			return -1; // generic error value, means nothing
		}
		else {
			int returnValue = sentinel->previous->value;

			sentinel->previous->previous->next = sentinel;
			Node *temp = sentinel->previous->previous;
			delete sentinel->previous;

			length--;

			sentinel->previous = temp;

			return returnValue;
		}
	}

	int top() {
		if(length == 0) {
			std::cout << "Empty Queue, nothing to dequeue\n";
			return -1; // generic error value, means nothing
		}
		else {
			return sentinel->next->value;
		}
	}

	int bottom() {
		if(length == 0) {
			std::cout << "Empty Queue, nothing to dequeue\n";
			return -1; // generic error value, means nothing
		}
		else {
			return sentinel->previous->value;
		}
	}

	int size() {
		return length;
	}

	bool isEmpty() {
		return (length == 0);
	}

};

// vector based queue
class VQueue {
private:
	std::vector<int> queue;
	int length;
	int capacity;
	
public:
	VQueue() {
		length = 0;
		capacity = 10;
		queue = { };
	}

	void push(int newValue) {
		// emplace back is just in case I want to come back and make this polymorphic
		queue.emplace_back(newValue);
	}

	int pop() {
		if(length == 0) {
			std::cout << "Queue is empty, nothing to pop\n";
		}
		else {
			length--;

			int returnValue = queue[length];
			
			if(length < capacity / 2 && capacity > 10) {
				capacity /= 2;
				queue.resize(capacity);
			}

			return returnValue;
		}
	}

	int top() {
		if(length == 0) {
			std::cout << "Queue is empty\n";
			return -1;
		}
		else {
			return queue[0];
		}
	}

	int bottom() {
		if(length == 0) {
			std::cout << "Queue is empty\n";
			return -1;
		}
		else {
			return queue[length - 1];
		}
	}

	int size() {
		return length;
	}

	bool isEmpty() {
		return (length == 0);
	}
		
};

// array based queue
class AQueue {
private:


public:
	void push(int newValue) { }
	int pop() { return 0; }
	int top() { return 0; }
	int bottom() { return 0; }
	int size() { return 0; }
	bool isEmpty() { return true; }
			
};

int main() {

	return 0;
}
