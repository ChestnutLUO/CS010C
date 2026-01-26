#ifndef LIST_DOUBLY_LINKED_H_
#define LIST_DOUBLY_LINKED_H_

#include <cassert>
#include <memory>
#include <stdexcept>
#include <utility>

/**
 * Implementation of a List ADT using a doubly linked list data structure with
 * smart pointers.
 */
template <typename T> class ListDoublyLinked {
 private:
  struct Node {
    T item;
    std::unique_ptr<Node> next;
    Node *previous;
  };

  // Q 1.2: Using smart pointers can help prevent memory leaks and
  // automatically implement destructor.

  std::unique_ptr<Node> head = nullptr;
  Node *tail = nullptr;
  unsigned int cur_size = 0;

  // Q 1.3 GetNode() returns a pointer to a node in the list at a given
  // position. Return pointer on node located as position @pos
  Node *GetNode(unsigned int pos) {
    assert(pos < cur_size);
    if (pos >= (cur_size / 2)) {
      Node *n = tail;
      pos = cur_size - pos - 1;
      while (pos--) {
        n = n->previous;
      }
      return n;
    } else {
      Node *n = head.get();
      while (pos--) {
        n = n->next.get();
      }
      return n;
    }
  }

  Node *GetNode(unsigned int pos) const {
    assert(pos < cur_size);
    if (pos >= (cur_size / 2)) {
      Node *n = tail;
      pos = cur_size - pos - 1;
      while (pos--) {
        n = n->previous;
      }
      return n;
    } else {
      Node *n = head.get();
      while (pos--) {
        n = n->next.get();
      }
      return n;
    }
  }

 public:
  // Q 2.1 Default constructor and destructor
  ListDoublyLinked() = default;

  ~ListDoublyLinked() = default;

  // Q 2.2 Size() method - Return number of items in list
  unsigned int Size() const { return cur_size; }

  // Q 2.3 Get() method - Return item at position @pos
  const T &Get(const unsigned int pos) const {
    if (pos >= cur_size) {
      throw std::out_of_range("Position out of range!");
    }
    auto n = GetNode(pos);
    return n->item;
  }

  // Q 2.4 Find() method - Return position of first occurrence of @item
  // (-1 if not found)
  int Find(const T &item) {
    Node *current = head.get();
    int pos = 0;
    for (; current; current = current->next.get(), pos++) {
      if (current->item == item) {
        return pos;
      }
    }
    return -1;
  }

  // Q 2.5 & Q 1.1: Different scenarios for item removal:
  // Scenario 1: Empty list or invalid position - no operation needed
  //   - Check if list is empty (!head) or position out of bounds
  //     (pos >= cur_size)
  //   - Return without making changes
  // Scenario 2: Remove first node (pos == 0)
  //   - Move head to next node (head = std::move(head->next))
  //   - If list becomes empty (!head), set tail to nullptr
  //   - Otherwise, set new head's previous to nullptr
  // Scenario 3: Remove last node (pos == cur_size - 1)
  //   - Navigate to the node at position pos
  //   - Update tail to point to current node's previous
  //   - Set previous node's next to nullptr (transfer ownership)
  // Scenario 4: Remove middle node
  //   - Navigate to the node at position pos
  //   - Update previous node's next pointer to skip current node
  //   - Update next node's previous pointer to point to previous node
  //   - Ownership automatically transfers through std::move
  //
  // Remove item at position @pos
  void Remove(const unsigned int pos) {
    if (pos > cur_size) {
    throw std::out_of_range("Position out of range!");
    }
    if (!head) {
      return;
    } else if (pos == 0) {
      head = std::move(head->next);
      if (!head) {
        tail = nullptr;
      } else {
        head->previous = nullptr;
      }
      cur_size--;
    } else {
      Node *current = GetNode(pos);
      if (current->next) {
        current->next->previous = current->previous;
      } else {
        tail = current->previous;
      }
      current->previous->next = std::move(current->next);
      cur_size--;
    }
  }

  // Q 2.6 Different scenarios for item insertion
  // Insert @item at position @pos
  void Insert(const T &item, const unsigned int pos) {
    if (pos > cur_size) {
      throw std::out_of_range("Position out of range!");
    }

    auto new_node = std::make_unique<Node>();
    new_node->item = item;

    if (pos == 0) {
      // Insert at head
      new_node->next = std::move(head);
      new_node->previous = nullptr;
      if (new_node->next) {
        new_node->next->previous = new_node.get();
      } else {
        tail = new_node.get();
      }
      head = std::move(new_node);
    } else if (pos == cur_size) {
      // Insert at tail
      new_node->next = nullptr;
      new_node->previous = tail;
      tail->next = std::move(new_node);
      tail = tail->next.get();
    } else {
      // Insert in middle
      Node *prev_node = GetNode(pos - 1);
      new_node->next = std::move(prev_node->next);
      new_node->previous = prev_node;
      new_node->next->previous = new_node.get();
      prev_node->next = std::move(new_node);
    }
    cur_size++;
  }
};

#endif  // LIST_DOUBLY_LINKED_H_
