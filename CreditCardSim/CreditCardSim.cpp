// CreditCardSim.cpp : main project file.  Erin K Kennon

#include "stdafx.h"
#include "CreditCard.h"
#include <iostream>

using namespace std;
using namespace System;

char choose(string);
int getValue(string);
void requestIncrease(bool);
void transact(bool);
string getDescription(string);

int main()
{
	CreditCard *cc;
	char accntType;
	int accntNum;

	cout << "Welcome to the credit card simulator" << endl;
	accntType = choose("Will this be a new or existing account? (n/e): ");

	if (accntType == 'e' || accntType == 'E') {
		cc = new CreditCard(getValue("Enter account number: "));
	}
	
	if (cc == NULL || cc->getAccountNum() == 0) {
		cout << "Opening new account..." << endl;
		cc = new CreditCard();
	}

	cout << "Your account number: " << cc->getAccountNum() << endl;
	cout << "Your credit limit: " << cc->getCreditLimit() << endl;

	int transType;
	do {
		cout << "Transaction Options:" << endl << "0. Quit" << endl << "1. New Charge" << endl << "2. Payment" << endl << "3. Credit Increase Request" << endl << "4. Card History" << endl;
		transType = getValue("Choice: ");
		switch (transType) {
		case 1:
			transact(cc->processTransaction(getValue("Charge Amount: "), getDescription("Charge Description: ")));
			break;
		case 2:
			transact(cc->processTransaction(getValue("Payment Amount: ")));
			break;
		case 3:
			requestIncrease(cc->increaseCreditLimit(getValue("Requested Increase: ")));
			break;
		case 4:
			break;
		default:

		}

		cout << "Account Balance: " << endl << "Outstanding Balance: " << endl << "Your credit limit: " << cc->getCreditLimit() << endl << "Availale Credit" << endl;

	} while (transType > 0 && transType < 5);

	system("Pause");
    return 0;
}

char choose(string message) {
	char choice;
	cout << message;
	cin >> choice;

	if (!cin.good()) {
		cin.clear();
		cin.ignore(1000, '\n');
		choice = 'n';
	}

	return choice;
}

int getValue(string message) {
	int value;
	cin.ignore(1000, '\n');
	cout << message;
	cin >> value;

	if (!cin.good()) {
		cin.clear();
		cin.ignore(1000, '\n');
		value = 0;
	}

	return value;
}

string getDescription(string message) {
	string desc;
	cout << message;
	cin.ignore(1000, '\n');
	getline(cin, desc);
	return desc;
}

void requestIncrease(bool granted) {
	if (granted) {
		cout << "The request was granted.";
	}
	else {
		cout << "The request was denied. Please try again another time." << endl;
	}
}

void transact(bool approved) {
	if (approved) {
		cout << "Your transaction was approved.";
	}
	else {
		cout << "The transaction was denied. Please check the amount and try again.";
	}
}
