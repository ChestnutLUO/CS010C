#ifndef LIST_SINGLY_LINKED_H_
#define LIST_SINGLY_LINKED_H_

#include <cassert>
#include <memory>
#include <stdexcept>
#include <utility>

/*
 * Implementation of a List ADT using a singly linked list data structure
 */
template <typename T>
class ListSinglyLinked {
private:
    struct Node {
        T item;
        std::unique_ptr<Node> next;
    };
    
    std::unique_ptr<Node> head = nullptr;
    size_t cur_size = 0;
    
    Node* GetNode(size_t pos) {
        assert(pos < cur_size);
        Node* n = head.get();
        while (pos--) {
            n = n->next.get();
        }
        return n;
    }

public:
    ListSinglyLinked() = default;
    ~ListSinglyLinked() = default;
    
    // Return number of items in list
    size_t Size() {
        return cur_size;
    }
    
    // Return item at position @pos
    const T& Get(const size_t pos) {
        if (pos >= cur_size) {
            throw std::out_of_range("Position out of range!");
        }
        auto n = GetNode(pos);
        return n->item;
    }
    
    // Return position of first occurrence of @item (-1 if not found)
    int Find(const T& item) {
        int i = 0;
        for (auto n = head.get(); n; n = n->next.get(), i++) {
            if (n->item == item) {
                return i;
            }
        }
        return -1;
    }
    
    // Remove item at position @pos
    void Remove(const size_t pos) {
        if (pos >= cur_size) {
            throw std::out_of_range("Position out of range!");
        }
        if (!pos) {
            // Remove from top of list
            auto n = std::move(head);
            head = std::move(n->next);
        } else {
            // Remove after existing item(s)
            auto prev = GetNode(pos - 1);
            auto n = std::move(prev->next);
            prev->next = std::move(n->next);
        }
        cur_size--;
    }
    
    // Insert @item at position @pos
    void Insert(const T& item, const size_t pos) {
        if (pos > cur_size) {
            throw std::out_of_range("Position out of range!");
        }
        auto n = std::unique_ptr<Node>(new Node);
        n->item = item;
        if (pos == 0) {
            // Insert in front
            n->next = std::move(head);
            head = std::move(n);
        } else {
            // Insert after existing item(s)
            auto prev = GetNode(pos - 1);
            n->next = std::move(prev->next);
            prev->next = std::move(n);
        }
        cur_size++;
    }
};

#endif // LIST_SINGLY_LINKED_H_