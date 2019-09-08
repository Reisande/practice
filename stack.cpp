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
	void push(int val);
	int pop();
	int top();
	int size();
	bool isEmpty();
	
};

// Vector Stack implementation
class VStack {
private:
	std::vector<int> stack;
	int length;

public:
	void push(int val);
	int pop();
	int top();
	int size();
	bool isEmpty();
	
};


int main() {

	return 0;
}
