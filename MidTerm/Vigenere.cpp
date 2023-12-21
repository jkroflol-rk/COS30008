#include "Vigenere.h"

void Vigenere::initializeTable()
{
	for (char row = 0; row < CHARACTERS; row++)
	{
		char lChar = 'B' + row;
		for (char column = 0; column < CHARACTERS; column++)
		{
			if (lChar > 'Z')
				lChar = 'A';
			fMappingTable[row][column] = lChar++;
		}
	}
}

Vigenere::Vigenere(const std::string& aKeyword) : fKeyword(aKeyword), fKeywordProvider(KeyProvider(aKeyword))
{
	initializeTable();
}

std::string Vigenere::getCurrentKeyword()
{
	std::string current_keyword;

	for (size_t i = 0; i < fKeyword.length(); i++)
	{
		current_keyword += *fKeywordProvider;
		fKeywordProvider << *fKeywordProvider;
	}
	return current_keyword;
}

void Vigenere::reset()
{
	fKeywordProvider.initialize(fKeyword);
}

char Vigenere::encode(char aCharacter)
{
	if (isalpha(aCharacter))
	{
		char encoded_char = fMappingTable[*fKeywordProvider - 'A'][toupper(aCharacter) - 'A'];

		fKeywordProvider << aCharacter;
		if (islower(aCharacter))
		{
			return tolower(encoded_char);
		}
		return encoded_char;
	}
	return aCharacter;
}

char Vigenere::decode(char aCharacter)
{
	if (isalpha((aCharacter)))
	{
		char encoded_char = toupper(aCharacter);
		char decoded_char = 0;

		for (char column = 0; column < CHARACTERS; column++)
		{
			if (fMappingTable[*fKeywordProvider - 'A'][column] == encoded_char)
			{
				decoded_char = column + 'A';
				break;
			}
		}

		fKeywordProvider << decoded_char;
		if (islower(aCharacter))
		{
			return tolower(decoded_char);
		}
		return decoded_char;
	}
	return aCharacter;
}





