#ifndef GAMMA_H_INCLUDED
#define GAMMA_H_INCLUDED

#include <cmath>
#include <assert.h>
#include "xorshift64.h"
#include "rnormal.h"

//Marsalgia2000
class Gamma
{
private:
	double beta;
	double dd;
	double cc;
public:
	void initialize(double a, double b);
	double rand_gamma(xorshift64& rand);
};

#endif // RAY_H_INCLUDED
