#include "ShakerSortableIntVector.h"

ShakerSortableIntVector::ShakerSortableIntVector(const int aArrayOfIntegers[], size_t aNumberOfElements) : SortableIntVector(aArrayOfIntegers, aNumberOfElements){}

void ShakerSortableIntVector::sort(Comparable aOrderFunction)
{
    size_t begin = 0;
    size_t end = (*this).size() - 1;

    while (begin < end)
    {
        for (size_t i = begin; i < end; i++)
        {
            if (aOrderFunction(get(i), get(i + 1)))
            {
                (*this).swap(i + 1, i);
            }
        }

    	end -= 1;

        for (size_t i = end; i > begin; i--)
        {
			if (aOrderFunction(get(i - 1), get(i)))
            {
                (*this).swap(i, i - 1);
            }
        }

        begin += 1;
    }
}
