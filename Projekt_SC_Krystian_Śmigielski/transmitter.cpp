#include "transmitter.h"

Transmitter::Transmitter(int id, int seed_uniform, int seed_exp, int seed_pt_prob, int seed_r_value)
{
	transmitter_id = id;

	generator_min_max = new Generator(seed_uniform);
	generator_exp = new Generator(seed_exp);
	generator_pt_prob = new Generator(seed_pt_prob);
	generator_r_value = new Generator(seed_r_value);
}

Transmitter::~Transmitter()
{
}

std::queue<Package*>* Transmitter::GetPackages()
{
	return &packages_;
}

int Transmitter::GetTransmitterId()
{
	return transmitter_id;
}

void Transmitter::SetTransmitterId(int tx_id)
{
	transmitter_id = tx_id;
}

int Transmitter::GetTimeChannel()
{
	return time_channel;
}

void Transmitter::SetTimeChannel(int checking_time)
{
	time_channel = checking_time;
}

int Transmitter::GetTimeAck()
{
	return time_ack;
}

bool Transmitter::GetCheckingChannelStatus()
{
	return checking_channel_status;
}

void Transmitter::SetCheckingChannelStatus(int checking_status)
{
	checking_channel_status = checking_status;
}

void Transmitter::GeneratePacket(Logger* logger, int tx_id)
{
	static size_t id = 0;     //ID of a new generated packet
	++id;
	
	int ctpk_time = GetMinMaxGenerator()->RandMinMax(10, 100);  //min = 10 -> 1 ms, max = 100 -> 10 ms
	
	auto package = new Package(id, ctpk_time, tx_id);
	packages_.push(package);

	//logger->Info("Transmitter ID: " + std::to_string(tx_id) + ". Generated packet ID: " + std::to_string(id) + ". Transmission time: " + std::to_string(packages_.back()->GetCtpkTime()));
}

void Transmitter::StartTransmission(Logger* logger, Package* package, WirelessNetwork* wireless_network)
{
	//logger->Info("Started transmission of a packet: " + std::to_string(packages_.front()->GetPackageId()));

	wireless_network->GetChannel()->GetTransmittingPackages()->push_back(package);      //Add last package in the end of vector
	wireless_network->GetChannel()->SetChannelStatus(false);
}