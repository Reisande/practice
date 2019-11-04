

class Solution {
public:
  vector<int> twoSum(vector<int>& nums, int target) {
	vector<int> returnVec;
	for(int i = 0; i < nums.length() - 1; i++) {
	  for(int j = 1; j < nums.length(); j++) {
		if(nums[i] + nums[j] == target) {
		  returnVec.push_back(i);
		  returnVec.push_back(j);

		  break;
		}
	  }
	}

	return returnVec;
  }
};

void setZeroes(vector<vector<int>>& matrix) {
  std::set<int> rows, columns;
  for(int i = 0; i < matrix.size(); i++) {
    for(int j = 0; j < matrix[i].size(); i++) {
      if(matrix[i][j] == 0) {
		rows.insert(i);
		columns.insert(j);
      }
    }
  }

  for(auto i = rows.begin(); i != rows.end(); i++) {
    for(int j = 0; j < matrix[*i].size(); j++) {
      matrix[*i][j] = 0;
    }
  }

  for(auto i = columns.begin(); i != columns.end(); i++) {
    for(int j = 0; j < matrix.size(); j++) {
      matrix[j][*i] = 0;
    }
  }
}

class Solution {
public:
  int myAtoi(string str) {
    int returnValue = 0;
    bool isNeg = false;
    bool haveSeenNumber = false;
    for(int i = 0; i < str.length(); i++) {
      if(!isdigit(str[i]) && (str[i] != '-' && !isNeg) && (str[i] != ' ' && ! haveSeenNumber)) {
		return returnValue;
      }
      else {
		if(str[i] == '-') {
		  isNeg = true;
		}
		else if(str[i] == ' ' && ! haveSeenNumber) {
		  continue;
		}
		else {
		  haveSeenNumber = true;
		  returnValue *= 10;
		  returnValue += (int)(str[i] - '0');
		}
      }
    }
    return isNeg ? (-1) * returnValue : returnValue;
  }
};
class LRUCache {
private:
  struct node {
	int key, value;
	node *prev, *next;
        
	node(int aKey, int aValue, node *aPrev = nullptr, node *aNext = nullptr) :
	  key(aKey), value(aValue), prev(aPrev), next(aNext) {};  
  };
  unordered_map<int, node *> map;
  class myQueue {
        
  public:
	int size;
	node *front;
	node *back;
        
	myQueue(int aSize = 0, node *aFront = nullptr, node *aBack = nullptr) :
	  size(aSize), front(aFront), back(aBack) {};
       
	node *push_front(int key, int value) {
	  node *insertNode = new node(key, value, nullptr, nullptr);

	  if(front != nullptr) {
		front->prev = insertNode;
	  }

	  if(back == nullptr) {
		back = insertNode;
	  }

	  front = insertNode;
           
	  this->size++;
          
	  return insertNode;
	}
        
	void pop_back() {
	  if(this->size > 0) {
		if(this->size == 1) {
		  node *deleteNode = back;
		  back = nullptr;
		  front = nullptr;
		  //delete deleteNode;
		}
		else {
		  node *temp = back->prev;
		  node *deleteNode = back;
		  if(temp != nullptr) {
			temp->next = nullptr;
		  }
		  back = temp;
		  //delete deleteNode;
		}
            
		size--;
	  }
	  else {
		std::cout << "No node exists in queue\n";
	  }
	}
  };
  
  myQueue q;
  int capacity, size;
public:
  
  LRUCache(int capacity) {
	this->capacity = capacity;
	size = 0;
  }
    
  int get(int key) {
	if(map.end() != map.find(key)) {
	  node *currentNode = map[key];
	  if(map[key] != q.front) {
		if(map[key] == q.back && q.size != 1) {
		  q.back = map[key]->prev;
		}
		q.push_front(currentNode->key, currentNode->value);

		node *temp = currentNode->prev;

		temp = currentNode->next;
		if(temp != nullptr) {
		  temp->prev = currentNode->prev;
		}
		else {
		  q.pop_back();
		}
	  }
	  return map[key]->value;
	}
	else {
	  return -1;
	}
  }
    
  void put(int key, int value) {
	if(map.end() == map.find(key)) {
	  if(size == capacity) {
		// resize map
		node *removeNode = q.back;
		q.pop_back();
		map.erase(removeNode->key);
		q.size--;
		size--;
	  }

	  map[key] = q.push_front(key, value);
	  size++;  
	}
	else {
	  this->get(key);
	  map[key]->value = value;
	}
  }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

vector<int> spiralOrder(vector<vector<int>>& matrix) {
        
}

// Trie implementation

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
/*class Solution {
  ListNode *findMinNode(vector<ListNode*>& lists, int &position) {
    if(! lists.empty()) {
      auto minNode = lists.begin();
      for(auto i = minNode + 1; i != lists.end(); i++) {
        if(*minNode != nullptr && *i != nullptr) {
          minNode = (*minNode)->val < (*i)->val ? minNode : i;
        }
        else if(*minNode == nullptr) {
          minNode = i;
        }
      }
      position = minNode - lists.begin();
      return *minNode;
    }
    else {
      return nullptr;
    }
  }
  
public:
  ListNode* mergeKLists(vector<ListNode*>& lists) {
	// this is probably simplest to solve by just dividing and
	// conquering the lists, and just merging n/2 lists at a time
	auto position = 0;
	auto firstNode = findMinNode(lists, position);
	auto mostRecentNode = firstNode;
	auto currentNode = firstNode;
	while(mostRecentNode != nullptr && currentNode != nullptr) {
	  currentNode = findMinNode(lists, position);
	  lists[position] = currentNode != nullptr ? currentNode->next : nullptr;
	  if(mostRecentNode != nullptr) {
		mostRecentNode->next = currentNode;
		mostRecentNode = currentNode;
	  }
	}

	return firstNode;
  }
};

*/

Node *mergeTwoLists(Node *a, Node *b) {
  if(a != nullptr && b != nullptr) {
	Node *tempA = a, *tempB = b, *currentNode = tempA =, *nextNode = nullptr;
	if(tempA->val > tempB->val) {
	  currentNode = tempB;
	  tempB = tempB->next;
	}
	else {
	  tempA = tempA->next;
	}
		  
	while(tempA != nullptr || tempB != nullptr) {
	  if(tempA->val < tempB->val) {
		nextNode->next = tempA;
		tempA = tempA->next;
	  }
	  else {
		nextNode->next = tempB;
		tempB = tempB->next;
	  }  
	  nextNode = nextNode->next;
	}
	return currentNode;
  }
  else {
	return a != nullptr ? a : b;
  }	 
}

Node *_mergeKLists(std::vector<ListNode*>& lists, const int lower, const int upper) {
  if(lower > upper) {
	return nullptr;
  }
  if(lower == upper) {
	return lists[lower];
  }
  else if(upper - lower == 1) {
	return mergeKLists(lists[lower], lists[upper]);
  }
  else {
	return mergeTwoLists(_mergeKLists(lists, lower, ((lower + upper) / 2) - 1),
						 _mergeKLists(lists, (lower + upper) / 2, upper));
  }
}

Node *mergeKLists(std::vector<ListNode*>& lists) {
  // this is probably simplest to solve by just dividing and
  // conquering the lists, and just merging n/2 lists at a time
  if(lists.size() == 0) {
	return nullptr;
  }
  else if(lists.size() == 1) {
	return lists[0];
  }
  else {
	auto returnNode = _mergeKLists(lists, 0, lists.size() - 1);
	return currentNode;
  }
}


/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
  ListNode* reverseList(ListNode* head) {
    if(head == nullptr) {
	  return nullptr;
	}
	if(head->next == nullptr) {
	  return head;
	}
	else {
	  ListNode *temp = reverseList(head->next);
      
      if(head->next != nullptr) {
		head->next->next = head;
	  }
	  head->next = nullptr;

	  return temp;
	}
  }
};

/*
  {{1, 2, 3},
   {4, 5, 6},
   {7, 8, 9}}

   returns {1, 2, 3, 6, 9, 8, 7, 4, 5}

   {1, 2, 3}
   {6, 9}
   {8, 7}
   {4}
   {5}

 */

std::vector<int> spiralmatrix(std::vector<std::vector<int>> matrix) {
  unsigned int lowerRow = 0, lowerColumn = 0;
  unsigned int upperRow = matrix.size(), upperColumn = matrix[i].size();
  std::vector<int> returnVector = {};

  
}


/*
  diagonal matrix:
  {{1, 2, 3},
   {4, 5, 6},
   {7, 8, 9}}

   returns {1, 2, 4, 3, 5, 7, 6, 8, 9 }

 */


// n is the size, array is the memory block
long unsigned int countBits(const unsigned char array[], const unsigned int n) {  
  int bitarray[256];

  for(int i = 0; i < 256; i++) {
	bitarray[i] = 0;
    for(int j = 0; j < 8; j++) {
	  bitarray[i] += (i >> j) & 1;
	} 
  }

  long unsigned int returnCounter = 0;
  for(unsigned int i = 0; i < n; i++) {
	returnCounter += bitarray[array[i]];
  }

  return returnCounter;
}
