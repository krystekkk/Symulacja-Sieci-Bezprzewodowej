#ifndef SIMULATION_H_
#define SIMULATION_H_

#include <iostream>
#include "wireless_network.h"
#include "generate_packet_event.h"
#include "channel_status_event.h"
#include "ack_decision_event.h"
#include "end_transmission_event.h"
#include "transmitter.h"
#include "channel.h"
#include "generator.h"

class Simulation
{
public:
	explicit  Simulation(WirelessNetwork* wireless_network);
	~Simulation();

	bool ChooseMode(int option);
	void StepMode();
	void M2(int time);
	
private:
	WirelessNetwork* wireless_network_ = nullptr;
	size_t clock_;
	int transmitter_id;
};
#endif