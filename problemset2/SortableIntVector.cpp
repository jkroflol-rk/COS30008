#include "SortableIntVector.h"

SortableIntVector::SortableIntVector(const int aArrayOfIntegers[], size_t aNumberOfElements) : IntVector(aArrayOfIntegers, aNumberOfElements){}

void SortableIntVector::sort(Comparable aOrderFunction)
{
	for (size_t i = 0; i < (*this).size(); i++)
	{
		for (size_t j = (*this).size() - 1; j > i; j--)
		{
			if (aOrderFunction(get(j), get(j - 1)))
			{
				(*this).swap(j, j - 1);
			}
		}
	}
}

//Lambda expression in main_ps2.cpp:
// Use a lambda expression here that orders integers in increasing order.
// The lambda expression does not capture any variables of throws any exceptions.
// It has to return a bool value.
//lVector.sort([](int aLeft, int aRight) -> bool { return aLeft <= aRight; });