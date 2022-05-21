#include "event.h"

Event::Event(size_t time, WirelessNetwork* wirless_network) : time_(time) , wirless_network_(wirless_network)
{
}

Event::~Event()
{
}
