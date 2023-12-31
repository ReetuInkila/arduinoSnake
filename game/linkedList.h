#ifndef LinkedList_hpp
#define LinkedList_hpp


template <class T>
class ListNode {
  public:
    T element;
    ListNode* next;
    ListNode* prev;

    ListNode(T element, ListNode* prev, ListNode* next) : element(element)
    {
      this->next = next;
      this->prev = prev;
    };
};

template <class T>
class LinkedList  {
  private:
    int length;
    ListNode<T>* head;
    ListNode<T>* tail;
    ListNode<T>* curr;
  public:
    // Constructor
    LinkedList() : length(0), head(nullptr), tail(nullptr), curr(nullptr) {}

    // Method to insert an item at the beginning of the list
    void insert(const T& item) {
      ListNode<T>* newNode = new ListNode<T>(item, nullptr, head);

      if (head != nullptr) {
        head->prev = newNode;
      }

      head = newNode;

      if (tail == nullptr) {
        tail = newNode;
      }

      length++;
    }

    Pair<int, int> getLast(){
      if (tail != nullptr) {
        return tail->element; // Assuming tail->element is a Pair<int, int>
      } else {
        // Handle the case when the list is empty, e.g., return a default Pair
        return Pair<int, int>(); // Default-constructed Pair
      }
    }

     // Method to remove the last item from the list
    void removeLast() {
      if (tail != nullptr) {
        if (tail == head) {
          // If there's only one element in the list
          delete tail;
          tail = head = nullptr;
        } else {
          // If there are multiple elements in the list
          tail = tail->prev;
          delete tail->next;
          tail->next = nullptr;
        }
        length--;
      }
    }
    

    int getLength(){
      return length;
    }

    bool isEmpty(){
      if (length == 0){
        return true;
      }
      return false;
    }

    // Method to empty whole list
    void empty(){
      length = 0; 
      head = nullptr; 
      tail = nullptr; 
      curr = nullptr;
    }

    // Method to iterate through the list
    class Iterator {
    private:
      ListNode<T>* current;

    public:
      Iterator(ListNode<T>* startNode) : current(startNode) {}

      // Overload the * operator to access the current element
      T& operator*() {
        return current->element;
      }

      // Overload the ++ operator to move to the next element
      Iterator& operator++() {
        if (current != nullptr) {
          current = current->next;
        }
        return *this;
      }

      // Overload the != operator to check for inequality
      bool operator!=(const Iterator& other) const {
        return current != other.current;
      }
    };

    // Method to get an iterator pointing to the beginning of the list
    Iterator begin() {
        return Iterator(head);
    }

    // Method to get an iterator pointing to the end of the list
    Iterator end() {
        return Iterator(nullptr);
    }
    

};
#endif