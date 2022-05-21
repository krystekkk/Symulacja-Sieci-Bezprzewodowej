#ifndef RECEIVER_H_
#define RECEIVER_H_

#include "channel.h"

class Channel;

class Receiver : public Channel
{
public:
	Receiver(int id);
	~Receiver();

	bool GetTerStatus() { return ter_status; }
	void SetTerStatus(int ter) { ter_status = ter; }
	
private:
	int receiver_id;             //ID of a single receiver
	bool ter_status = false;     //true -> TER detected
};
#endif
