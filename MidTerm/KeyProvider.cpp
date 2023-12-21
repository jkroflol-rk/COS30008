#include "KeyProvider.h"
#include <algorithm>

KeyProvider::KeyProvider(const std::string& aKeyword) : fKeyword(new char[aKeyword.length()]), fSize(aKeyword.length()), fIndex(0)
{
	initialize(aKeyword);
}

KeyProvider::~KeyProvider()
{
	delete[] fKeyword;
}

void KeyProvider::initialize(const std::string& aKeyword)
{
	delete[] fKeyword;

	fSize = aKeyword.length();
	fKeyword = new char[fSize];
	fIndex = 0;

	transform(aKeyword.begin(), aKeyword.end(), fKeyword, [](char c) { return toupper(c); });
}

char KeyProvider::operator*() const
{
	return fKeyword[fIndex];
}

KeyProvider& KeyProvider::operator<<(char aKeyCharacter)
{
    if (isalpha(aKeyCharacter)) 
    {
		fKeyword[fIndex] = toupper(aKeyCharacter);
        fIndex = (fIndex + 1) % fSize;    
    }

    return *this;
}





