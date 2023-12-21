#include "Polynomial.h"

Polynomial::Polynomial() {
	fDegree = 0;
	for (size_t i = 0; i <= MAX_DEGREE; i++) {
		fCoeffs[i] = 0.00;
	}
}

Polynomial Polynomial::operator*(const Polynomial& aRHS) const {
	Polynomial result;
	size_t newDegree = fDegree + aRHS.fDegree;

	for (size_t i = 0; i <= fDegree; i++) {
		for (size_t j = 0; j <= aRHS.fDegree; j++) {
			result.fCoeffs[i + j] += fCoeffs[i] * fCoeffs[j];
		}
	}
	
	result.fDegree = newDegree;
	return result;
}

bool Polynomial::operator==(const Polynomial& aRHS) const {
	if (fDegree != aRHS.fDegree) {
		return false;
	}

	for (size_t i = 0; i <= fDegree; i++) {
		if (fCoeffs[i] != aRHS.fCoeffs[i]) {
			return false;
		}
	}

	return true;
}

std::istream& operator>>(std::istream& aIStream, Polynomial& aObject) {
	aIStream >> aObject.fDegree;

	for (size_t i = 0; i <= aObject.fDegree; ++i) {
		aIStream >> aObject.fCoeffs[i];
	}

	return aIStream;
}

std::ostream& operator<<(std::ostream& aOStream, const Polynomial& aObject) {
	size_t temp = aObject.fDegree;

	for (size_t i = 0; i <= aObject.fDegree; ++i) {
		if (aObject.fCoeffs[i] != 0) {
			aOStream << aObject.fCoeffs[i] << "x^" << temp;
		}
		if (aObject.fCoeffs[i + 1] != 0) {
			aOStream << " + ";
		}
		temp--;
	}

	//aOStream << aObject.fCoeffs[aObject.fDegree] << "x^" << temp << "\n";

	return aOStream;
}