#include "ack_decision_event.h"

AckDecisionEvent::AckDecisionEvent(size_t time, WirelessNetwork* wireless_network, Logger* logger, EventList* event_list, int id)
	:Event(time, wireless_network), logger_(logger), event_list_(event_list), transmitter_id(id)
{
}

AckDecisionEvent::~AckDecisionEvent()
{
}

void AckDecisionEvent::Execute()
{
	//logger_->Info("ACK Decision Event");

	int lr_value = wirless_network_->GetTransmitters()->at(transmitter_id)->GetPackages()->front()->GetLrNumber() + 1;
	
	int phase = wirless_network_->GetInitialPhase();
	

	if (wirless_network_->GetChannel()->GetAckSentInfo())
	{
		//logger_->Info("Ended ACK transmission of a packet: " + std::to_string(wirless_network_->GetChannel()->GetTransmittingPackages()->front()->GetPackageId()));

		//std::ofstream correct_packages_file("Correct_packages-lambda=0.0075_NO.10.txt", std::ios_base::app | std::ios_base::out);        //Save many values to the file 
		//correct_packages_file << wirless_network_->GetChannel()->GetTransmittingPackages()->front()->GetPackageId() << "\n";

		//std::ofstream average_retransmission_number("Average_retransmission_number-lambda=0.0075_NO.10.txt", std::ios_base::app | std::ios_base::out);
		//average_retransmission_number << wirless_network_->GetChannel()->GetAverageRetransmissionNumber() << "\n";
		
		if (time_ > phase)      //actual time > initial phase
		{
			int correct = wirless_network_->GetChannel()->GetCorrectPackages() + 1;    //statistic
			wirless_network_->GetChannel()->SetCorrectPackages(correct);
			
			int time_of_being_in_buffor = wirless_network_->GetChannel()->GetWaitingInBufforTime();
			int ctpk_temp = wirless_network_->GetTransmitters()->at(transmitter_id)->GetPackages()->front()->GetCtpkTime();
			
			wirless_network_->GetChannel()->SetDelayTime(time_of_being_in_buffor + ctpk_temp);    //statistic
		}
		
		wirless_network_->GetTransmitters()->at(transmitter_id)->GetPackages()->pop();
		
		if (!wirless_network_->GetChannel()->GetTransmittingPackages()->empty())
		{
			wirless_network_->GetChannel()->GetTransmittingPackages()->pop_back();
		}

		wirless_network_->GetChannel()->SetCollisionInfo(false);
		wirless_network_->GetChannel()->SetChannelStatus(true);
	}
	
	if (!wirless_network_->GetChannel()->GetAckSentInfo() && lr_value <= 3)
	{
		//logger_->Info("ACK not received. Retransmission.");
		
		wirless_network_->GetTransmitters()->at(transmitter_id)->GetPackages()->front()->SetLrNumber(lr_value);
		
		int r_value = wirless_network_->GetTransmitters()->at(transmitter_id)->GetRvalueGenerator()->RandMinMax(0, pow(2, (lr_value)) - 1);  //R value generator
		
		//logger_->Info("R: " + std::to_string(r_value));
		
		int crp = r_value * (wirless_network_->GetTransmitters()->at(transmitter_id)->GetPackages()->front()->GetCtpkTime());
		
		//logger_->Info("LR: " + std::to_string(wirless_network_->GetTransmitters()->at(transmitter_id)->GetPackages()->front()->GetLrNumber()));

		if (time_ > phase)      //actual time > initial phase
		{
			int retransmitted = wirless_network_->GetChannel()->GetRetransmittedPackages() + 1;    //statistic
			wirless_network_->GetChannel()->SetRetransmittedPackages(retransmitted);
		}
		
		event_list_->push(new ChannelStatusEvent(time_ + crp, wirless_network_, logger_, event_list_, transmitter_id));
	}

	if (!wirless_network_->GetChannel()->GetAckSentInfo() && lr_value > 3)
	{
		//logger_->Info("LR bigger than 10. Rejection of a packet.");

		if (time_ > phase)      //actual time > initial phase
		{
			int lost_packages = wirless_network_->GetChannel()->GetLostPackages() + 1;     //statistic
			wirless_network_->GetChannel()->SetLostPackages(lost_packages);
		}
		
		wirless_network_->GetTransmitters()->at(transmitter_id)->GetPackages()->pop();
	}
}