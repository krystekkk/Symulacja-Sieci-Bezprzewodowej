#include "channel.h"

Channel::Channel()
{
}

Channel::~Channel()
{
}

std::vector<Package*>* Channel::GetTransmittingPackages()
{
	return &transmitting_packages_;
}
