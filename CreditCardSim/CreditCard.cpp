#include "stdafx.h"
#include "CreditCard.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <sstream>

using namespace std;

CreditCard::CreditCard()
{
	string filename;
	ifstream fin;
	ostringstream n;

	srand((unsigned)time(0));

	do {
		if (fin.is_open()) {
			fin.close();
		}
		
		accountNum = (rand() % 100000) + 1;
		n << accountNum << flush;
		filename = "CC" + n.str() + ".txt";
		fin.open(filename.c_str());
	} while (fin.is_open());
	fin.close();
	vCreditLimit = 1000;
	vBalanceDue = 0;
	CCName = filename;
	CCLName = "CCL" + n.str() + ".txt";
	writeStatus();
	writeLog("Account " + n.str() + " opened.");
}

CreditCard::CreditCard(int anum)
{
	
	string filename;
	ifstream fin;
	ostringstream n;
	vError = false;

	n << anum << flush;
	filename = "CC" + n.str() + ".txt";
	fin.open(filename.c_str());
	if (fin.is_open()) {
		accountNum = anum;
		fin >> vCreditLimit;
		fin >> vBalanceDue;
		fin.close();
		CCName = filename;
		CCLName = "CCL" + n.str() + ".txt";
		writeLog("Account " + n.str() + " re-opened.");
	}
	else {
		accountNum = 0;
		vCreditLimit = 0;
		vBalanceDue = 0;
		vError = true;
		vErrorMsg = "Account " + n.str() + " could not be opened.";

	}
}


double CreditCard::getCreditLimit()
{
	return vCreditLimit;
}

double CreditCard::getBalanceDue()
{
	return vBalanceDue;
}

int CreditCard::getAccountNum()
{
	return accountNum;
}

void CreditCard::writeStatus()
{
	vError = false;
	vErrorMsg = "";
	ofstream fout;

	fout.open(CCName.c_str());
	if (fout.is_open()) {
		fout << vCreditLimit << endl;
		fout << vBalanceDue << endl;
		fout.close();
	}
	else {
		vError = true;
		vErrorMsg = "Unable to write status file.";
	}
}

void CreditCard::writeLog(string message)
{
	vError = false;
	vErrorMsg = "";
	time_t rawtime;
	time(&rawtime);
	ofstream fout;
	fout.open(CCLName.c_str(),ios_base::app);
	if (fout.is_open()) {
		fout << message << " occurred at " << ctime(&rawtime) << endl;
		fout.close();
	}
	else {
		vError = true;
		vErrorMsg = "Unable to write log entry: " + message;
	}
}

CreditCard::~CreditCard()
{
}
