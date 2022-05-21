#include "generator.h"

#include <cmath>

Generator::Generator(int kernel) : kernel_(kernel)
{
}

Generator::~Generator()
{
}

double Generator::Rand()
{
	int h = kernel_ / kQ;
	kernel_ = kA * (kernel_ - kQ * h) - kR * h;
	if (kernel_ < 0) kernel_ = kernel_ + static_cast<int>(kM);
	return kernel_ / kM;
}

double Generator::RandZeroOne(double p)
{
	double k = Rand();

	if (k < p) return 1;
	else return 0;
}

double Generator::RandMinMax(double min, double max)
{
	return Rand() * (max - min) + min;
}

double Generator::RandExp(double lambda)
{
	double k = Rand();
	return -1 * (1.0 / lambda) * log(k);
}