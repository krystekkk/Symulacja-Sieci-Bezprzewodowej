#ifndef END_TRANSMISSION_EVENT_H_
#define END_TRANSMISSION_EVENT_H_

#include "wireless_network.h"
#include "logger.h"
#include "event.h"
#include "package.h"
#include "ack_decision_event.h"

class EndTransmissionEvent : public Event
{
public:
	EndTransmissionEvent(size_t time, WirelessNetwork* wireless_network, Logger* logger, EventList* event_list, int id);
	~EndTransmissionEvent();

	void Execute() override;

private:
	Logger* logger_ = nullptr;
	EventList* event_list_ = nullptr;
	int transmitter_id;
	Package* package_ = nullptr;
};

#endif