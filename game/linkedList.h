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

};
#endif // LinkedList_hpp