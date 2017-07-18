// CreditCardSim.cpp : main project file.  Erin K Kennon

#include "stdafx.h"
#include "CreditCard.h"
#include <iostream>
#include <vector>

using namespace std;
using namespace System;

char choose(string);
int getValue(string);
void requestIncrease(bool);
void transact(bool);
string getDescription(string);
void printHistory(vector<string>);

int main()
{
	CreditCard *cc;
	char accntType;

cout << "Welcome to the credit card simulator" << endl;
accntType = choose("Will this be a new or existing account? (n/e): ");

if (accntType == 'e' || accntType == 'E') {
	cc = new CreditCard(getValue("Enter account number: "));
}

if (cc == NULL || cc->getAccountNum() == 0) {
	cout << "Opening new account..." << endl;
	cc = new CreditCard();
}

cout << "\nYour account number: " << cc->getAccountNum() << endl;
cout << "Your credit limit: " << cc->getCreditLimit() << endl << endl;

int transType;
do {
	cout << "Transaction Options:" << endl << "0. Quit" << endl << "1. New Charge" << endl << "2. Payment" << endl << "3. Credit Increase Request" << endl << "4. Card History" << endl << endl;
	transType = getValue("Choice: ");
	switch (transType) {
	case 1:
		transact(cc->processTransaction(getDescription("Charge Description: "), getValue("Charge Amount: ")));
		cout << endl;
		break;
	case 2:
		transact(cc->processTransaction(getValue("Payment Amount: ")));
		cout << endl;
		break;
	case 3:
		requestIncrease(cc->increaseCreditLimit(getValue("Requested Increase: ")));
		cout << endl;
		break;
	case 4:
		printHistory(cc->readLog());
		cout << endl;
		break;
	}

	cout << "\nAccount Number: " << cc->getAccountNum() << endl << "Outstanding Balance: " << cc->getBalanceDue() << endl << "Your credit limit: " << cc->getCreditLimit() << endl << "Availale Credit: " << cc->getAvailCredit() << endl << endl;

} while (transType > 0 && transType < 5);

cout << "Thank you for using the credit card simulator!" << endl;

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
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	string desc;
	cout << message;
	getline(cin, desc);
	return desc;
}

void requestIncrease(bool granted) {
	if (granted) {
		cout << "The request was granted.";
	}
	else {
		cout << "The request was declined. Please try again another time.";
	}
}

void transact(bool approved) {
	if (approved) {
		cout << "Your transaction was approved.";
	}
	else {
		cout << "The transaction was declined. Please check the amount and try again.";
	}
}

void printHistory(vector<string> lines) {
	for (unsigned int i = 0; i < lines.size(); i++) {
		cout << "\t" << lines[i] << endl;
	}
	cout << endl;
}
