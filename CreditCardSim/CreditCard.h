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
	int getAccountNum();
	~CreditCard(void);

private:
	int accountNum;
	bool vError;
	string vErrorMsg;
	double vBalanceDue;
	double vCreditLimit;
	void writeStatus();
	void writeLog(string);
	string CCName;
	string CCLName;
};

