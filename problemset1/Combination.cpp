#include "Combination.h"

Combination::Combination(size_t aN, size_t aK) {
	fN = aN;
	fK = aK;
}

size_t Combination::getN() const {
	return fN;
}

size_t Combination::getK() const{
	return fK;
}

unsigned long long Combination::operator()() const{
	unsigned long long combination = 1;

	for (size_t i = 0; i < fK; ++i) {
		combination *= (fN - i);
		combination /= (i + 1);
	}

	return combination;
}
