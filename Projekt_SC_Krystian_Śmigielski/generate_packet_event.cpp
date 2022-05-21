#include "generate_packet_event.h"

GeneratePacketEvent::GeneratePacketEvent(size_t time, WirelessNetwork* wireless_network, Logger* logger, EventList* event_list, int id)
	:Event(time, wireless_network), logger_(logger), event_list_(event_list), transmitter_id(id)
{
}

GeneratePacketEvent::~GeneratePacketEvent()
{
}

void GeneratePacketEvent::Execute()
{
	//logger_->Info("Generate Packet Event");

	int generated_packet_time = get_time();
	wirless_network_->GetChannel()->SetActualPacketGenerationTime(generated_packet_time);


	wirless_network_->GetTransmitters()->at(transmitter_id)->GeneratePacket(logger_, transmitter_id);
	
	int temp_rand_time = wirless_network_->GetTransmitters()->at(transmitter_id)->GetExpGenerator()->RandExp(wirless_network_->lambda);
	int temp_rand_id = wirless_network_->GetTransmitters()->at(transmitter_id)->GetMinMaxGenerator()->RandMinMax(0, 3);
	
	event_list_->push(new GeneratePacketEvent(time_ + temp_rand_time, wirless_network_, logger_, event_list_, temp_rand_id));
	
	if (!wirless_network_->GetTransmitters()->at(transmitter_id)->GetPackages()->empty() && wirless_network_->GetTransmitters()->at(transmitter_id)->GetCheckingChannelStatus() == false)
		event_list_->push(new ChannelStatusEvent(time_, wirless_network_, logger_, event_list_, transmitter_id));
}