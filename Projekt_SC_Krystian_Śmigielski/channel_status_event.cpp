#include "channel_status_event.h"

ChannelStatusEvent::ChannelStatusEvent(size_t time, WirelessNetwork* wireless_network, Logger* logger, EventList* event_list, int id)
	:Event(time, wireless_network), logger_(logger), event_list_(event_list), transmitter_id(id)
{
}

ChannelStatusEvent::~ChannelStatusEvent()
{
}

void ChannelStatusEvent::Execute()
{
	//logger_->Info("Channel Status Event");
	
	double pt_probability = wirless_network_->GetTransmitters()->at(transmitter_id)->GetPtProbabilityGenerator()->RandMinMax(0, 1);   //PT probability generator

	int phase = wirless_network_->GetInitialPhase();   //get initial phase to start collecting statistics


	if (wirless_network_->GetChannel()->GetChannelStatus() == true)
	{
		if (pt_probability <= wirless_network_->GetPtProbablityValue())
		{
			//logger_->Info("Channel is empty. We can start transmission.");

			wirless_network_->GetTransmitters()->at(transmitter_id)->SetTimeChannel(10);

			int event_time = get_time();
			wirless_network_->GetChannel()->SetActualEventTime(event_time);
			
			auto transmission = wirless_network_->GetTransmitters()->at(transmitter_id)->GetPackages()->front()->GetCtpkTime();
			auto package_ = wirless_network_->GetTransmitters()->at(transmitter_id)->GetPackages()->front();

			if (time_ > phase)
			{
				int temp_generation_time = wirless_network_->GetChannel()->GetActualPacketGenerationTime();
				int actual_event_time = get_time();
				int temporary = actual_event_time - temp_generation_time;

				int correct_waiting_time = wirless_network_->GetChannel()->GetWaitingInBufforTime() + temporary;
				
				wirless_network_->GetChannel()->SetWaitingInBufforTime(correct_waiting_time);
			}
			
			wirless_network_->GetTransmitters()->at(transmitter_id)->StartTransmission(logger_, package_, wirless_network_);

			event_list_->push(new EndTransmissionEvent(time_ + transmission, wirless_network_, logger_, event_list_, transmitter_id));
		}
		else
		{
			//logger_->Info("Channel is empty, but PT > 0.6. Waiting to the next time slot.");

			wirless_network_->GetTransmitters()->at(transmitter_id)->SetTimeChannel(10);

			
			event_list_->push(new ChannelStatusEvent(time_ + 10, wirless_network_, logger_, event_list_, transmitter_id));
		}
	}
	
	else if (wirless_network_->GetChannel()->GetActualEventTime() == time_ && wirless_network_->GetChannel()->GetChannelStatus() == false)
	{	
		wirless_network_->GetChannel()->SetCollisionInfo(true);
	}
	
	else
	{
		//logger_->Info("Channel is busy. Checking channel again.");

		wirless_network_->GetTransmitters()->at(transmitter_id)->SetTimeChannel(5);   //5 -> 0.5 ms

		
		event_list_->push(new ChannelStatusEvent(time_ + 5, wirless_network_, logger_, event_list_, transmitter_id));
	}
}