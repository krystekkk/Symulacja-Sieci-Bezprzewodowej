#ifndef PACKAGE_H_
#define PACKAGE_H_

class Package
{
public:
	Package(int id_package, int ctpk, int id_tx_);
	~Package();

	size_t GetPackageId() const { return package_id; }

	int GetCtpkTime() { return ctp_k_time; }

	int GetTxRxId() { return tx_id; }

	int GetLrNumber() { return lr_counter; }
	void SetLrNumber(int lr_numb) { lr_counter = lr_numb; }
	
private:
	int package_id;
	int ctp_k_time = 0;
	int tx_id;
	int lr_counter;
};
#endif