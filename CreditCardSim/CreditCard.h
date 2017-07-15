#pragma once

#include <string>

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
	bool processTransaction(double,string);
	~CreditCard(void);

private:
	int accountNum;
	bool vError;
	string vErrorMsg;
	double vBalanceDue;
	double vCreditLimit;
	double availCredit;
	void writeStatus();
	void writeLog(string);
	string CCName;
	string CCLName;
};

