#include <iostream>
#include <vector>

// Linked list stack implementation
class LStack {
private:
	struct Node {
		int val;
		Node *next;

		Node(int aVal, Node *aNext) :
			val(aVal), next(aNext) {}
	};
	Node *head;
	int length;
	
public:
	LStack() {
		head = nullptr;
		length = 0;
	}

	void push(int pushVal) {
		Node *newHead = new Node(pushVal, head);
		head = newHead;
		
		length++;		
	}

	int pop() {
		if(length == 0) {
			std::cout << "Stack is empty, nothing to pop\n";
			return -1;
		}
		else {
			int returnVal = head->val;
			
			Node *temp = head->next;

			delete head;
			head = temp;

			length--;

			return returnVal;
		}
	}

	int top() {
		if(length == 0) {
			std::cout << "Stack is empty, nothing to return\n";
			return -1;
		}
		else {
			return head->val;
		}
	}

	int size() {
		return length;
	}
	
	bool isEmpty() {
		return (length == 0);
	}
	
};

// Vector Stack implementation
class VStack {
private:
	std::vector<int> stack;
	int length;
	int capacity;

public:
	VStack() {
		length = 0;
		capacity = 10;
	}

	void push(int val) {
		stack[length] = val;

		length++;
	}

	int pop() {
		if(length == 0) {
			std::cout << "Stack is empty, nothing to pop\n";
			return -1;
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
			std::cout << "Stack is empty, nothing to pop\n";
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


int main() {

	return 0;
}
