#include "end_transmission_event.h"

EndTransmissionEvent::EndTransmissionEvent(size_t time, WirelessNetwork* wireless_network, Logger* logger, EventList* event_list, int id)
	:Event(time, wireless_network), logger_(logger), event_list_(event_list), transmitter_id(id)
{
}

EndTransmissionEvent::~EndTransmissionEvent()
{
}

void EndTransmissionEvent::Execute()
{
	// logger_->Info("End Transmission Event");
	
	int ter = wirless_network_->get_ter_with_generator()->RandZeroOne(0.2);
	
	if (wirless_network_->GetChannel()->GetCollisionInfo() || ter == 1)     // TER value from generator
	{
		// logger_->Info("Collision / TER detected!");
		wirless_network_->GetChannel()->SetAckSentInfo(false);
		
		if (!wirless_network_->GetChannel()->GetTransmittingPackages()->empty())
		{
			wirless_network_->GetChannel()->GetTransmittingPackages()->pop_back();
		}
		
		if (wirless_network_->GetChannel()->GetTransmittingPackages()->empty())
		{
			wirless_network_->GetChannel()->SetChannelStatus(true);
			wirless_network_->GetChannel()->SetCollisionInfo(false);
		}
		
		event_list_->push(new AckDecisionEvent(time_ + 10, wirless_network_, logger_, event_list_, transmitter_id));
	}
	else
	{
		// logger_->Info("Ended transmission of a packet");

		wirless_network_->GetChannel()->SetAckSentInfo(true);
		
		event_list_->push(new AckDecisionEvent(time_ + 10, wirless_network_, logger_, event_list_, transmitter_id));
	}
}