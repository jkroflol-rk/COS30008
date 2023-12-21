#include "VigenereForwardIterator.h"

#include <iostream>

VigenereForwardIterator::VigenereForwardIterator(iVigenereStream& aIStream) : fIStream(aIStream), fCurrentChar(0), fEOF(aIStream.eof())
{
    if (!fEOF) fIStream >> fCurrentChar;
}

char VigenereForwardIterator::operator*() const
{
    return fCurrentChar;
}

VigenereForwardIterator& VigenereForwardIterator::operator++()
{
    fIStream >> fCurrentChar;
    fEOF = fIStream.eof();
    return *this;
}

VigenereForwardIterator VigenereForwardIterator::operator++(int)
{
    VigenereForwardIterator t = *this;
    ++(*this);
    return t;
}

bool VigenereForwardIterator::operator==(const VigenereForwardIterator& aOther) const
{
    return (fEOF && aOther.fEOF) && (&fIStream == &aOther.fIStream);
}

bool VigenereForwardIterator::operator!=(const VigenereForwardIterator& aOther) const
{
    return !(*this == aOther);
}

VigenereForwardIterator VigenereForwardIterator::begin() const
{
    VigenereForwardIterator iter = *this;
    iter.fIStream.reset();
    iter.fEOF = iter.fIStream.eof();
    if (!iter.fEOF)
    {
        iter.fIStream >> iter.fCurrentChar;
    }
    return iter;
}

VigenereForwardIterator VigenereForwardIterator::end() const
{
    VigenereForwardIterator iter = *this;
    iter.fEOF = true;
    return iter;
}
