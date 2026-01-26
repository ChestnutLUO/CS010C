#ifndef LIST_DOUBLY_LINKED_H_
#define LIST_DOUBLY_LINKED_H_
// DONE: include guard

#include <cassert>
#include <memory>
#include <stdexcept>
#include <utility>
// DONE: What else do you need to include?

/**
 * Implementation of a List ADT using a doubly linked list data structure with smart pointers.
 *
 * TODO: Study the singly linked list implementation (list_singly_linked.h) for reference.
 * TODO: Design your Node structure to support bidirectional navigation.
 * TODO: Consider using smart pointers for ownership (which direction should own memory?).
 * TODO: Implement all required methods.
 */

// TODO: Q 1.1 Create a templated class ListDoublyLinked
// based on the ListSinglyLinked class studied in class.
// What extra data members do you need for this implementation?
template <typename T>
class ListDoublyLinked {
    private:
        struct Node {
            T item;
            std::unique_ptr<Node> next;
            Node* previous;
            // DONE: Define the node structure
            // Hint: What data does each node need to store?
            // Hint: How should you handle forward vs backward pointers with smart pointers?
        };

        // DONE: Q 1.2 How would you slightly change this previous data structure to use smart pointers?
        // Explain why it would be a good design in a comment.
        // A 1.2: Using smart pointrt can help you prevent from memory leak and auomaticaly
        // implement destructor.
        
        std::unique_ptr<Node> head = nullptr;
        Node* tail = nullptr;
        size_t cur_size = 0;
        // DONE: Define private data members for your list

        // TODO: Implement helper method to get node at position
        // Q 1.3 Now implement private method GetNode() which returns a pointer to a node in the list at a given position.
        // Return pointer on node located as position @pos
        Node* GetNode(size_t pos) {
            assert(pos < cur_size);
            if (pos >= (cur_size/2)) {
                Node* n = tail;
                pos = cur_size - pos - 1;
                while (pos--) {
                    n = n->previous;
                }
                return n;
            } else {
                Node* n = head.get();
                while (pos--) {
                    n = n->next.get();
                }
                return n;
            }
        }

        Node* GetNode(size_t pos) const{
            assert(pos < cur_size);
            if (pos >= (cur_size/2)) {
                Node* n = tail;
                pos = cur_size - pos - 1;
                while (pos--) {
                    n = n->previous;
                }
                return n;
            } else {
                Node* n = head.get();
                while (pos--) {
                    n = n->next.get();
                }
                return n;
            }
        }

    public:
    // TODO: Q 2.1 Implement a default constructor and destructor.

    ListDoublyLinked() = default;

    ~ListDoublyLinked() = default;
    // TODO: Q 2.2 Implement the Size() method.
    // Return number of items in list
    size_t Size() const {
        return cur_size;
    }

    // TODO: Q 2.3 Implement the Get() method.
    // Return item at position @pos
    const T& Get(const size_t pos) const {
         if (pos >= cur_size) {
            throw std::out_of_range("Position out of range!");
        }
        auto n = GetNode(pos);
        return n->item;
    }

    // TODO: Q 2.4 Implement the Find method.
    // Return position of first occurrence of @item (-1 if not found)
    int Find(const T &item) {
        Node* current = head.get();
        int pos = 0;
        for (; current; current = current->next.get(), pos++) {
            if (current->item == item) {
                return pos;
            }
        }
        return -1;
    }

    // TODO: Q 2.5 Discuss the different scenarios for item removal.
    // Using these possible combinations, implement the Remove method.
    // Remove item at position @pos
    void Remove(const unsigned int pos) {
        if (!head || pos >= cur_size) {
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
            Node* current = GetNode(pos);
            if (current->next) {
                current->next->previous = current->previous;
            } else {
                tail = current->previous;
            }
            current->previous->next = std::move(current->next);
            cur_size--;
        }
    }

    // TODO: Q 2.6 Discuss the different scenarios for item insertion.
    // Based on the discussion above, implement the Insert method.
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
            Node* prev_node = GetNode(pos - 1);
            new_node->next = std::move(prev_node->next);
            new_node->previous = prev_node;
            new_node->next->previous = new_node.get();
            prev_node->next = std::move(new_node);
        }
        cur_size++;
    }

};

#endif // !LIST_DOUBLY_LINKED_H_
