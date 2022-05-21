#ifndef CHANNEL_H_
#define CHANNEL_H_

#include <vector>
#include "package.h"

class Channel
{
public:
	Channel();
	~Channel();

	std::vector<Package*>* GetTransmittingPackages();

	bool GetChannelStatus() { return empty_channel; }
	void SetChannelStatus(bool channel_status) { empty_channel = channel_status; }

	bool GetCollisionInfo() { return collision_info; }
	void SetCollisionInfo(bool collision_status) { collision_info = collision_status; }
	
	bool GetAckSentInfo() { return ack_sent_info; }
	void SetAckSentInfo(bool sent_info) { ack_sent_info = sent_info; }

	double GetCorrectPackages() { return correct_packages; }
	void SetCorrectPackages(int correct) { correct_packages = correct; }

	double GetRetransmittedPackages() { return retransmitted_packages; }
	void SetRetransmittedPackages(int retransmitted) { retransmitted_packages = retransmitted; }

	double GetLostPackages() { return lost_packages; }
	void SetLostPackages(int lost) { lost_packages = lost; }

	double GetAverageRetransmissionNumber() { return GetRetransmittedPackages() / GetCorrectPackages(); }

	double GetAverageBER() { return (GetLostPackages() / GetCorrectPackages()) / number_of_txs_rxs; }

	double GetMaxBER() { return GetLostPackages() / GetCorrectPackages(); }

	double GetDelayTime() { return delay_time; }
	void SetDelayTime(int delay) { delay_time = delay; }
	
	double GetAverageDelayTime() { return GetDelayTime() / GetCorrectPackages(); }
	
	double GetWaitingTime() { return waiting_time; }
	void SetWaitingTime(int wait) { waiting_time = wait; }
	
	double GetAverageWaitingTime() { return GetWaitingInBufforTime() / GetCorrectPackages(); }

	int GetActualEventTime() { return actual_event_time; }
	void SetActualEventTime(int actual) { actual_event_time = actual; }

	int GetActualPacketGenerationTime() { return actual_package_generation_time; }
	void SetActualPacketGenerationTime(int actual_generation_time) { actual_package_generation_time = actual_generation_time; }

	int GetWaitingInBufforTime() { return waiting_in_buffor_time; }
	void SetWaitingInBufforTime(int generation_to_transmission) { waiting_in_buffor_time = generation_to_transmission; }

private:
	std::vector<Package*> transmitting_packages_;  //vector of package currently transmitting
	bool empty_channel = true;                     //true -> free, false -> busy
	bool collision_info = false;                   //false -> no collision
	bool ack_sent_info = false;                    //true -> receiver got packet

	int actual_event_time = 0;                     //time of actual event - used in collision condition
	
	int number_of_txs_rxs = 4;
	
	int correct_packages = 0;
	int retransmitted_packages = 0;
	int lost_packages = 0;

	int waiting_in_buffor_time = 0;   //help variable 
	int actual_package_generation_time = 0;
	
	int delay_time = 0;
	int waiting_time = 0;
};
#endif