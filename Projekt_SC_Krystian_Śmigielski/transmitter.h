#ifndef TRANSMITTER_H_
#define TRANSMITTER_H_

#include <queue>
#include <iostream>
#include <vector>

#include "channel.h"
#include "package.h"
#include "logger.h"
#include "wireless_network.h"
#include "generator.h"


class WirelessNetwork;
class Channel;

class Transmitter : public Channel
{
public:
	Transmitter(int id, int seed_uniform, int seed_exp, int seed_pt_prob, int seed_r_value);
	~Transmitter();

	void Initiation();
	
	std::queue<Package*>* GetPackages();

	int GetTransmitterId();
	void SetTransmitterId(int tx_id);
	
	int GetTimeChannel();
	void SetTimeChannel(int checking_time);

	int GetTimeAck();

	bool GetCheckingChannelStatus();
	void SetCheckingChannelStatus(int checking_status);

	bool IsBufferEmpty();
	size_t GetBufferSize();
	
	void GeneratePacket(Logger* logger, int tx_id);
	void StartTransmission(Logger* logger, Package* package, WirelessNetwork* wireless_network);

	Generator* GetUniformGenerator() { return uniform_generator; }
	Generator* GetExpGenerator() { return generator_exp; }
	Generator* GetMinMaxGenerator() { return generator_min_max; }
	Generator* GetPtProbabilityGenerator() { return generator_pt_prob; }
	Generator* GetRvalueGenerator() { return generator_r_value; }
	
private:
	std::queue<Package*> packages_;			 //queue of packages
	int transmitter_id;						 //ID of a single transmitter
	int time_ack = 100;						 //time of waiting for ACK message, 100 -> 10 ms
	int time_channel = 10;					 //time of waiting for free channel, 10 -> 1 ms
	int crp_time;                            //time of packet retransmission
	bool checking_channel_status = false;    //true -> channel is checking, false -> channel is not checking

	Generator* uniform_generator = nullptr;
	Generator* generator_exp = nullptr;
	Generator* generator_min_max = nullptr;
	Generator* generator_pt_prob = nullptr;
	Generator* generator_r_value = nullptr;
};

#endif
