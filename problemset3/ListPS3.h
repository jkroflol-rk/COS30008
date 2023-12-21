#pragma once

#include "DoublyLinkedList.h"
#include "DoublyLinkedListIterator.h"
#include <stdexcept>

template<typename T>
class List
{
private:
	// auxiliary definition to simplify node usage
	using Node = DoublyLinkedList<T>;

	Node* fRoot; // the first element in the list
	size_t fCount; // number of elements in the list
public:
	// auxiliary definition to simplify iterator usage
	using Iterator = DoublyLinkedListIterator<T>;

	List() : fRoot(nullptr), fCount(0) {} // default constructor

	List(const List& aOtherList)
	{
		*this = aOtherList;
	}// copy constructor

	List& operator=(const List& aOtherList)
	{
		if (this != &aOtherList)
		{
			this->~List();
			if (aOtherList.fRoot == nullptr) 
			{
				fRoot = nullptr;
			}
			else 
			{
				fRoot = nullptr;
				fCount = 0;

				for (auto& node: aOtherList) {
					push_back(node);
				}
			}
		}
		return *this;
	} // assignment operator

	~List()
	{
		while (fRoot != nullptr)
		{
			if (fCount > 1)
			{
				Node* temp = const_cast<Node*>(&fRoot->getPrevious());
				temp->isolate();
				delete temp;
				--fCount;
			}
			else
			{
				delete fRoot;
				break;
			}
		}
	} // destructor - frees all nodes

	bool empty() const
	{
		return fRoot == nullptr;
	} // Is list empty?

	size_t size() const
	{
		return fCount;
	} // list size

	void push_front(const T& aElement)
	{
		if (empty())
		{
			fRoot = new Node(aElement);
		}
		else
		{
			Node* node = new Node(aElement);
			fRoot->push_front(*node);
			fRoot = node;
		}
		fCount++;
	} // adds aElement at front

	void push_back(const T& aElement)
	{
		if (empty())
		{
			fRoot = new Node(aElement);
		}
		else
		{
			Node* lastNode = const_cast<Node*>(&fRoot->getPrevious());
			Node* newNode = new Node(aElement);
			lastNode->push_back(*newNode);
		}
		fCount++;
	} // adds aElement at back

	void remove(const T& aElement)
	{
		Node* delNote = fRoot;

		while (delNote != nullptr)
		{
			if (**delNote == aElement)
			{
				break;
			}
			if (delNote != (&delNote->getNext()))
			{
				delNote = const_cast<Node*>(&delNote->getNext());
			}
			else
			{
				delNote = nullptr;
			}
		}

		if (delNote != nullptr)
		{
			if (fCount > 1)
			{
				if (delNote == fRoot)
				{
					fRoot = const_cast<Node*>(&delNote->getNext());
				}
			}
			else
			{
				fRoot = nullptr;
			}
			delNote->isolate();
			delete delNote;
			fCount--;
		}
	} // remove first match from list

	const T& operator[](size_t aIndex) const
	{
		if (empty())
		{
			throw std::out_of_range("Index out of bounds.");
		}
		if (aIndex < size())
		{
			Iterator iter = Iterator(fRoot).begin();
			for (size_t i = 0; i < aIndex; i++)
			{
				++iter;
			}
			return *iter;
		}
		else
		{
			throw std::out_of_range("Index out of bounds.");
		}
	} // list indexer

	Iterator begin() const
	{
		return Iterator(fRoot);
	} // return a forward iterator

	Iterator end() const
	{
		return Iterator(fRoot).end();
	} // return a forward end iterator

	Iterator rbegin() const
	{
		return Iterator(fRoot).rbegin();
	} // return a backwards iterator

	Iterator rend() const
	{
		return Iterator(fRoot).rend();
	} // return a backwards end iterator

	// move features
	List(List&& aOtherList) 
	{
		*this = std::move(aOtherList);
	} // move constructor

	List& operator=(List&& aOtherList)
	{
		if (this != &aOtherList)
		{
			this->~List();
			if (aOtherList.fRoot == nullptr)
			{
				fRoot = nullptr;
			}
			else
			{
				fRoot = aOtherList.fRoot;
				fCount = aOtherList.fCount;

				aOtherList.fRoot = nullptr;
				aOtherList.fCount = 0;
			}
		}
		return *this;
	} // move assignment operator

	void push_front(T&& aElement)
	{
		T temp = std::move(aElement);
		(*this).push_front(temp);
	} // adds aElement at front
	
	void push_back(T&& aElement)
	{
		T temp = std::move(aElement);
		(*this).push_back(temp);
	} // adds aElement at back
};