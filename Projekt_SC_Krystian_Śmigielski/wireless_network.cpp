#include "wireless_network.h"

WirelessNetwork::WirelessNetwork()
{
	auto channel = new Channel();
	Generator* generator_seeds = new Generator(59);

	for (int i = 0; i < main_seed * 100000; ++i)            // generating kernel
	{
		generator_seeds->Rand();
		if(i % 100000 == 0)
		{
			auto seed_seed = generator_seeds->GetKernel();
			seeds.push_back(seed_seed);
		}
	}
	
	//std::ofstream output_file("./seed.txt");
	//std::ostream_iterator<double> output_iterator(output_file, "\n");
	//std::copy(seeds.begin(), seeds.end(), output_iterator);

	auto ter_error = seeds.back();
	seeds.pop_back();
	ter_gener = new Generator(ter_error);
	
	for (int i = 0; i < number_of_stations; ++i)         // add seeds to every generators
	{
		auto uniform= seeds.back();
		seeds.pop_back();
		auto exp = seeds.back();
		seeds.pop_back();
		auto pt_prob = seeds.back();
		seeds.pop_back();
		auto r_value = seeds.back();
		seeds.pop_back();
		auto transsmiter = new Transmitter(i, uniform, exp, pt_prob, r_value);
		transmitters_.push_back((transsmiter));
		auto receiver = new Receiver(i);
		receivers_.push_back(receiver);
	}
}

WirelessNetwork::~WirelessNetwork()
{
}