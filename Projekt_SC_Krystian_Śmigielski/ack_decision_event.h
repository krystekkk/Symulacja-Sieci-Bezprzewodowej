#ifndef ACK_DECISION_EVENT_H_
#define ACK_DECISION_EVENT_H_

#include "event.h"
#include "logger.h"
#include "channel_status_event.h"
#include "wireless_network.h"
#include "transmitter.h"

class Transmitter;

class AckDecisionEvent : public Event
{
public:
	AckDecisionEvent(size_t time, WirelessNetwork* wireless_network, Logger* logger, EventList* event_list, int id);
	~AckDecisionEvent();

	void Execute() override;

	
private:
	Logger* logger_ = nullptr;
	EventList* event_list_ = nullptr;
	int transmitter_id;
	//std::vector<double> vector_of_correct_packages;
};

#endif


