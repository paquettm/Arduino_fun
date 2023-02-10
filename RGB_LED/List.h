#ifndef List_class
#define List_class
//basic template list class to hold objects
template <typename T>
class List {
 private:
  struct Node {
    T data;
    Node* next;
  };

  Node* head;
  int size;

 public:
  List() : head(nullptr), size(0) {}

  ~List() {
    clear();
  }

  int getSize() const {
    return size;
  }

  bool isEmpty() const {
    return size == 0;
  }

  void clear() {
    while (head != nullptr) {
      Node* temp = head;
      head = head->next;
      delete temp;
    }
    size = 0;
  }

  void add(const T& data) {
    Node* newNode = new Node{data, head};
    head = newNode;
    ++size;
  }

  T& operator[](int index) {
    Node* current = head;
    for (int i = 0; i < index; ++i) {
      current = current->next;
    }
    return current->data;
  }

  const T& operator[](int index) const {
    Node* current = head;
    for (int i = 0; i < index; ++i) {
      current = current->next;
    }
    return current->data;
  }
};
#endif