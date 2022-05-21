#ifndef CHANNEL_STATUS_EVENT_H_
#define CHANNEL_STATUS_EVENT_H_

#include "end_transmission_event.h"
#include "wireless_network.h"
#include "logger.h"
#include "event.h"

class Transmitter;

class ChannelStatusEvent : public Event
{
public:
	ChannelStatusEvent(size_t time, WirelessNetwork* wireless_network, Logger* logger, EventList* event_list, int id);
	~ChannelStatusEvent();

	void Execute() override;

private:
	Logger* logger_ = nullptr;
	EventList* event_list_ = nullptr;
	int transmitter_id;
};

#endif


