#pragma once

#include <string>
#include <vector>

using namespace std;

class CreditCard
{
public:
	CreditCard(void);
	CreditCard(int);
	double getCreditLimit();
	double getBalanceDue();
	double getAvailCredit();
	int getAccountNum();
	bool increaseCreditLimit(double);
	bool processTransaction(double);
	bool processTransaction(string,double);
	vector<string> readLog();
	~CreditCard(void);

private:
	int accountNum;
	bool vError;
	double vBalanceDue;
	double vCreditLimit;
	double availCredit;
	string vErrorMsg;
	string CCName;
	string CCLName;

	void writeStatus();
	void writeLog(string);
};

