#include <ctime>
#include <iostream>
#include <queue>
#include <iterator>
#include <fstream>

#include "generate_packet_event.h"
#include "ack_decision_event.h"
#include "channel_status_event.h"
#include "end_transmission_event.h"
#include "wireless_network.h"
#include "transmitter.h"
#include "receiver.h"
#include "channel.h"
#include "package.h"
#include "logger.h"
#include "simulation.h"
#include "generator.h"


int main()
{
	std::srand((int)time(NULL));
	
	std::cout << "Simulation of the wireless network. Method: M2 | Algorithm: A5c\n\n";
	
	
	int number_of_rands = 100000;
	int header_seed = 50;
	auto uniform_generator = Generator(header_seed);
	
	std::vector<double> numbersRandZeroOne;
	std::vector<double> numbersRandMinMax;
	std::vector<double> numbersRandExp;

	for (int i = 0; i < number_of_rands; ++i)
	{
		numbersRandZeroOne.push_back(uniform_generator.RandZeroOne(0.2));
		numbersRandMinMax.push_back(uniform_generator.RandMinMax(1, 100));
		numbersRandExp.push_back(uniform_generator.RandExp(0.025));
	}

	//std::ofstream output_fileRandZeroOne("./generatorRandZeroOne.txt");
	//std::ostream_iterator<double> output_iteratorRandZeroOne(output_fileRandZeroOne, "\n");
	//std::copy(numbersRandZeroOne.begin(), numbersRandZeroOne.end(), output_iteratorRandZeroOne);

	//std::ofstream output_fileRandMinMax("./generatorRandMinMax.txt");
	//std::ostream_iterator<double> output_iteratorRandMinMax(output_fileRandMinMax, "\n");
	//std::copy(numbersRandMinMax.begin(), numbersRandMinMax.end(), output_iteratorRandMinMax);

	//std::ofstream output_fileRandExp("./generatorRandExp.txt");
	//std::ostream_iterator<double> output_iteratorRandExp(output_fileRandExp, "\n");
	//std::copy(numbersRandExp.begin(), numbersRandExp.end(), output_iteratorRandExp);
	
	
	auto wirelessnet = new WirelessNetwork();
	Simulation simulation = Simulation(wirelessnet);
	
	int time;
	std::cout << "Enter the simulation time (in miliseconds): ";    // To get some results put a huge number - for example 100 000)
	std::cin >> time;
	std::cout << "\n";

	int simulation_time = time * 10;

	simulation.M2(simulation_time);

	return 0;
}
