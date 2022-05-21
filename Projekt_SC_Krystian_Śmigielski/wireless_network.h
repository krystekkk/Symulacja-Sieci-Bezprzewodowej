#ifndef WIRELESS_NETWORK_H_
#define WIRELESS_NETWORK_H_

#include <vector>
#include <fstream>
#include <iterator>

#include "channel.h"
#include "receiver.h"
#include "transmitter.h"
#include "generator.h"

class Generator;
class Transmitter;
class Receiver;
class Channel;

class WirelessNetwork : public Channel
{
public:
	WirelessNetwork();
	~WirelessNetwork();

	int GetNumberOfStations() { return number_of_stations; }

	Channel* GetChannel() { return &channel_; }
	
	std::vector<Transmitter*>* GetTransmitters() { return &transmitters_; }
	std::vector<Receiver*>* GetReceivers() { return &receivers_; }

	double GetPtProbablityValue() { return pt_probability_value; }

	double lambda = 0.0083;
	
	Generator* get_ter_with_generator() { return ter_gener; }    // returning TER error

	int GetInitialPhase() { return initial_phase; }

	int GetMainSeed() { return main_seed; }
	
private:
	Generator* ter_gener = nullptr;
	int number_of_stations = 4;
	int main_seed = 116;
	std::vector<int> seeds;
	Channel channel_;
	std::vector<Transmitter*>transmitters_;
	std::vector<Receiver*>receivers_;
	double pt_probability_value = 0.6;
	int initial_phase = 65000;
};
#endif

