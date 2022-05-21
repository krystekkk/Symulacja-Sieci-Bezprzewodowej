#include "package.h"

Package::Package(int id_packet, int ctpk, int id_tx_) : package_id(id_packet), ctp_k_time(ctpk), tx_id(id_tx_), lr_counter(0)
{
}

Package::~Package()
{
}