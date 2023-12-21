#pragma once
#include "DoublyLinkedList.h"
#include "DoublyLinkedListIterator.h"
#include <iostream>
#include <stdexcept>

template<typename T>
class List
{
private:
    // Auxiliary definition to simplify node usage
    using Node = DoublyLinkedList<T>;
    Node* fRoot; // the first element in the list
    size_t fCount; // number of elements in the list

public:
    // Auxiliary definition to simplify iterator usage
    using Iterator = DoublyLinkedListIterator<T>;

    // Default constructor
    List() : fCount(0) {
        fRoot = nullptr;
    }

    // Copy constructor
    List(const List& aOtherList) {
        (*this) = aOtherList;
    }

    // Assignment operator
    List& operator=(const List& aOtherList)  {
        this -> ~List(); // Destruct the current object
        Iterator itr = aOtherList.begin();
        do {
            (*this).push_back(*itr);
            itr++;
        } while (itr != aOtherList.end());
        return *this;
    }

    // Destructor
    ~List() {
        // Delete all nodes in the list
        if (fCount > 0) {
            const Node* curr = fRoot;
            const Node* end = &fRoot->getPrevious();
            do {
                const Node* next = &curr->getNext();
                ((Node)(*curr)).isolate();
                delete curr;
                curr = next;
            } while (curr != end);
            delete end;
            fCount = 0;
        }
        fRoot = nullptr;
    }

    // Check if the list is empty
    bool empty() const {
        return fCount == 0 && fRoot == nullptr;
    }

    // Get the size of the list
    size_t size() const{
        return fCount;
    }

    // Add an element to the front of the list
    void push_front(const T& aElement) {
        if (size() == 0) {
            fRoot = new Node(aElement);
        }
        else {
            fRoot = &(fRoot->push_front(*new Node(aElement)));
        }
        fCount++;
    }

    // Add an element to the back of the list
    void push_back(const T& aElement) {
        if (size() == 0) {
            fRoot = new Node(aElement);
        }
        else {
            fRoot->push_front(*new Node(aElement));
        }
        fCount++;
    }

    // Remove the first occurrence of a given element from the list
    void remove(const T& aElement) {
        if (fCount > 0) {
            const Node* curr = fRoot;
            do {
                if (curr->getPayload() == aElement) {
                    ((Node)(*curr)) . isolate();
                    fCount--;
                    break;
                }
                curr = &curr->getNext();
            } while (curr != &fRoot->getPrevious());
        }
    }

    // List indexer
    const T& operator[](size_t aIndex) const {
        if (aIndex < 0 || aIndex >= fCount) {
            throw std::out_of_range("Index out of bounds.");
        }
        else {
            if (aIndex > fCount / 2) {
                // Use reverse iterator if the index is closer to the end of the list
                Iterator itr = this->end();
                for (size_t i = fCount - 1; i >= aIndex; i--) {
                    itr--;
                    if (i == 0) break;
                }
                return *itr;
            }
            else {
                // Use forward iterator if the index is closer to the beginning of the list
                Iterator itr = this->begin();
                for (size_t i = 0; i < aIndex; i++) {
                    itr++;
                }
                return *itr;
            }
        }
    }

    // Return a forward iterator for the beginning of the list
    Iterator begin() const {
        return Iterator(fRoot).begin();
    }

    // Return a forward iterator for the end of the list
    Iterator end() const {
        return Iterator(fRoot).end();
    }

    // Return a reverse iterator for the beginning of the list
    Iterator rbegin() const {
        return Iterator(fRoot).rbegin();
    }

    // Return a reverse iterator for the end of the list
    Iterator rend() const {
        return Iterator(fRoot).rend();
    }

    // Move constructor
    List(List&& aOtherList) {
        (*this) = aOtherList;
        aOtherList.~List();
    }

    // Move assignment operator
    List& operator=(List&& aOtherList) {
        this -> ~List();
        List newList = std::move(aOtherList);
        aOtherList.~List();
        return (*this) = newList;
    }

    // Add an rvalue element to the front of the list
    void push_front(T&& aElement) {
        (*this).push_front(std::move(aElement));
    }

    // Add an rvalue element to the back of the list
    void push_back(T&& aElement) {
        (*this).push_back(std::move(aElement));
    }

};

