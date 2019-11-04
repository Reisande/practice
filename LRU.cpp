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
          
          insertNode->next = front;
          
          if(front == nullptr || back == nullptr) {
            back = insertNode;
          }
          else {
            front->prev = insertNode;
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
        
        void printQueue() {
          node *temp = front;
          for(int i = 0; i < size; i++) {
            if(temp != nullptr) {
              std::cout << temp->key << " " << temp->value << "\n";
              temp = temp->next;
            }
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
          node *deleteNode = map[key];
          
          if(deleteNode->prev != nullptr) {
            deleteNode->prev->next = deleteNode->next;
          }
          if(deleteNode->next != nullptr) {
            deleteNode->next->prev = deleteNode->prev;
          }
          if(deleteNode == q.back) {
              q.back = deleteNode->prev;
          }
          if(deleteNode == q.front) {
              q.front = deleteNode->next;
          }
          
          q.push_front(deleteNode->key, deleteNode->value);
          delete map[key];
          map[key] = q.front;
        }
        
        std::cout << "get: " << key << "\n";
        q.printQueue();
      
        return map[key]->value;
      }
      else {
        std::cout << "get: " << key << "\n";
        q.printQueue();
      
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
        std::cout << "put: " << key << " " << value << "\n";
        q.printQueue();
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
