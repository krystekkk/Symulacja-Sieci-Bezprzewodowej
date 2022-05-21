#ifndef GENERATE_PACKET_EVENT_H_
#define GENERATE_PACKET_EVENT_H_

#include <iostream>
#include <string>
#include <cstdlib>
#include <queue>

#include "channel_status_event.h"
#include "wireless_network.h"
#include "logger.h"
#include "event.h"

class Transmitter;

class GeneratePacketEvent : public Event
{
public:
	GeneratePacketEvent(size_t time, WirelessNetwork* wireless_network, Logger* logger, EventList* event_list, int id);
	~GeneratePacketEvent();

	void Execute() override;

private:
	Logger* logger_ = nullptr;
	EventList* event_list_ = nullptr;
	int transmitter_id;
};

#endif