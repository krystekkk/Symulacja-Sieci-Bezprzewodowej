#ifndef GENERATOR_H_
#define GENERATOR_H_

class Generator
{
public:
	Generator(int kernel);
	~Generator();

	double Rand();
	double RandZeroOne(double p);
	double RandMinMax(double min, double max);
	double RandExp(double lambda);
	int GetKernel() { return kernel_; }

private:
	int kernel_;
	const double kM = 2147483647.0;
	static const int kA = 16807;
	static const int kQ = 127773;
	static const int kR = 2836;
};

#endif