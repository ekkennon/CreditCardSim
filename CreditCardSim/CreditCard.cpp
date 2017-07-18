#include "stdafx.h"
#include "CreditCard.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <sstream>
#include <cstring>
#include <vector>

using namespace std;
using namespace System;

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
	availCredit = 1000;

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
		fin >> availCredit;
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

double CreditCard::getAvailCredit()
{
	return availCredit;
}

int CreditCard::getAccountNum()
{
	return accountNum;
}

bool CreditCard::increaseCreditLimit(double amt)
{
	srand((unsigned)time(0));
	if (rand() % 2 == 1) {
		vCreditLimit += ((int)(amt / 100) * 100);//get a whole number for the increase amount in case they enter a number such as 250
		availCredit = vCreditLimit - vBalanceDue;
		writeStatus();
		writeLog("Limit Increase: " + to_string(amt) + ", approved.");
		return true;
	}

	writeStatus();
	writeLog("Limit Increase: " + to_string(amt) + ", declined.");
	return false;
}

bool CreditCard::processTransaction(double amt)
{
	if (vBalanceDue - amt < 0) {
		writeStatus();
		writeLog("Payment declined. Must be less than " + to_string(vBalanceDue) + ". " + to_string(amt) + " not accepted.");
		return false;
	}
	
	availCredit += amt;
	vBalanceDue = vCreditLimit - availCredit;
	writeStatus();
	writeLog("Payment: " + to_string(amt));
	return true;
}

bool CreditCard::processTransaction(string desc, double amt)
{
	if (amt + vBalanceDue > vCreditLimit) {
		writeStatus();
		writeLog("Charge: " + to_string(amt) + " declined. Must be less than " + to_string(availCredit) + ".");
		return false;
	}
	
	availCredit -= amt;
	vBalanceDue = vCreditLimit - availCredit;
	writeStatus();
	writeLog("Charge: " + to_string(amt) + ", " + desc);
	return true;
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
		fout << availCredit << endl;
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
		fout << message << " Occurred " << ctime(&rawtime);
		fout.close();
	}
	else {
		vError = true;
		vErrorMsg = "Unable to write log entry: " + message;
	}
}

vector<string> CreditCard::readLog()
{
	ifstream fin;
	vector<string> lines;

	fin.open(CCLName.c_str());
	if (fin.is_open()) {
		string row;
		while (getline(fin, row)) {
			lines.push_back(row);
		}
		fin.close();
	}
	else {
		vError = true;
		vErrorMsg = "Unable to read log.";
	}

	return lines;
}

CreditCard::~CreditCard()
{
}
