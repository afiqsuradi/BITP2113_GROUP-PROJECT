#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <iostream>
#include <stdexcept>
#include "node.h" // Include the new Node header

template<typename T>
class LinkedList {
protected:
    Node<T> *head;
    Node<T> *tail;
    size_t size;

public:
    LinkedList() : head(nullptr), tail(nullptr), size(0) {
    }

    ~LinkedList() {
        clear();
    }

    LinkedList(const LinkedList &other) : head(nullptr), tail(nullptr), size(0) {
        Node<T> *current = other.head;
        while (current != nullptr) {
            pushBack(current->data);
            current = current->next;
        }
    }

    LinkedList &operator=(const LinkedList &other) {
        if (this != &other) {
            LinkedList temp(other);
            std::swap(head, temp.head);
            std::swap(tail, temp.tail);
            std::swap(size, temp.size);
        }
        return *this;
    }

    void pushFront(const T &value);

    void pushBack(const T &value);

    void popFront();

    void popBack();

    bool isEmpty() const;

    size_t getSize() const;

    void clear();

    void print() const;

    Node<T> *getHead() const;

    Node<T> *getTail() const;

    void setHead(Node<T> *newHead);

    void setTail(Node<T> *newTail);

    void fixTail();
};

template<typename T>
void LinkedList<T>::fixTail() {
    Node<T> *current = head;
    while (current->next != nullptr) {
        current = current->next;
    }
    tail = current;
}

template<typename T>
void LinkedList<T>::setHead(Node<T> *newHead) {
    head = newHead;
}

template<typename T>
void LinkedList<T>::setTail(Node<T> *newTail) {
    tail = newTail;
}

template<typename T>
Node<T> *LinkedList<T>::getHead() const {
    return head;
}

template<typename T>
Node<T> *LinkedList<T>::getTail() const {
    return tail;
}

template<typename T>
void LinkedList<T>::pushFront(const T &value) {
    Node<T> *newNode = new Node<T>(value);
    newNode->next = head;
    head = newNode;
    if (tail == nullptr)
        tail = head; // Fix to update tail when list is empty
    size++;
}

template<typename T>
void LinkedList<T>::pushBack(const T &value) {
    Node<T> *newNode = new Node<T>(value);

    if (head == nullptr) {
        head = newNode;
        tail = newNode; // Ensure tail is set correctly for the first node
    } else {
        tail->next = newNode;
        tail = newNode;
    }
    size++;
}

template<typename T>
void LinkedList<T>::popFront() {
    if (isEmpty()) {
        throw std::runtime_error("List is empty");
    }

    Node<T> *temp = head;
    head = head->next;
    if (head == nullptr)
        tail = nullptr; // Update tail if the list becomes empty
    delete temp;
    size--;
}

template<typename T>
void LinkedList<T>::popBack() {
    if (isEmpty()) {
        throw std::runtime_error("List is empty");
    }

    if (head->next == nullptr) {
        delete head;
        head = nullptr;
        tail = nullptr; // Ensure tail is reset
    } else {
        Node<T> *current = head;
        while (current->next->next != nullptr) {
            current = current->next;
        }
        tail = current;
        delete current->next;
        current->next = nullptr;
    }
    size--;
}

template<typename T>
bool LinkedList<T>::isEmpty() const {
    return head == nullptr;
}

template<typename T>
size_t LinkedList<T>::getSize() const {
    return size;
}

template<typename T>
void LinkedList<T>::clear() {
    while (!isEmpty()) {
        popFront();
    }
}

template<typename T>
void LinkedList<T>::print() const {
    Node<T> *current = head;
    while (current != nullptr) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

#endif
