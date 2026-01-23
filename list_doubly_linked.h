// TODO: include guard
// TODO: What else do you need to include?

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
class ListDoublyLinked {
private:
    struct Node {
        // TODO: Define the node structure
        // Hint: What data does each node need to store?
        // Hint: How should you handle forward vs backward pointers with smart pointers?
    };

    // TODO: Q 1.2 How would you slightly change this previous data structure to use smart pointers? 
    // Explain why it would be a good design in a comment.

    // TODO: Define private data members for your list

    // TODO: Implement helper method to get node at position
    // Q 1.3 Now implement private method GetNode() which returns a pointer to a node in the list at a given position.
    // Return pointer on node located as position @pos
    Node* GetNode(unsigned int pos);

public:
    // TODO: Q 2.1 Implement a default constructor and destructor.

    // TODO: Q 2.2 Implement the Size() method.
    // Return number of items in list
    unsigned int Size();

    // TODO: Q 2.3 Implement the Get() method.
    // Return item at position @pos
    const T& Get(const unsigned int pos);

    // TODO: Q 2.4 Implement the Find method.
    // Return position of first occurrence of @item (-1 if not found)
    int Find(const T &item);

    // TODO: Q 2.5 Discuss the different scenarios for item removal.
    // Using these possible combinations, implement the Remove method.
    // Remove item at position @pos
    void Remove(const unsigned int pos);

    // TODO: Q 2.6 Discuss the different scenarios for item insertion. 
    // Based on the discussion above, implement the Insert method.
    // Insert @item at position @pos
    void Insert(const T &item, const unsigned int pos);

};
