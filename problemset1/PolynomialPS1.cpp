#include <cmath>
#include "Polynomial.h"

using namespace std;

double Polynomial::operator()(double aX) const {
	double Result = 0;
	size_t temp = fDegree;
	for (size_t i = 0; i <= fDegree; ++i) {
		Result += fCoeffs[i] * pow(aX, temp);
		temp--;
	}
	return Result;
}

Polynomial Polynomial::getDerivative() const
{
	Polynomial Result;

	if (fDegree == 0) {
		return Result;
	}

	Result.fDegree = fDegree - 1;
	size_t temp = fDegree;

	for (size_t i = 0; i <= Result.fDegree; i++) {
		Result.fCoeffs[i] = fCoeffs[i] * temp;
		temp--;
	}

	return Result;
}

Polynomial Polynomial::getIndefiniteIntegral() const {
	Polynomial Result;

	Result.fDegree = fDegree + 1;
	size_t temp = Result.fDegree;

	for (size_t i = 0; i <= fDegree; i++) {
		Result.fCoeffs[i] = fCoeffs[i] / temp;
		temp--;
	}


	return Result;
}

double Polynomial::getDefiniteIntegral(double aXLow, double aXHigh) const {
	return this->getIndefiniteIntegral()(aXHigh) - this->getIndefiniteIntegral()(aXLow);
}