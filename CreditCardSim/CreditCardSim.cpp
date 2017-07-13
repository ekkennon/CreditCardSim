// CreditCardSim.cpp : main project file.  Erin K Kennon

#include "stdafx.h"
#include "CreditCard.h"
#include <iostream>

using namespace std;
using namespace System;

int main()
{
	CreditCard *cc;
	char choice;
	int accntNum;

	cout << "new or existing (n or e): ";//input validation
	cin >> choice;

	if (choice == 'n') {
		cc = new CreditCard();
		cout << "account " << cc->getAccountNum() << " was opened" << endl;

	}
	else if (choice == 'e') {
		cout << "enter accnt num ";
		cin.ignore(1000, '\n');
		cin >> accntNum;
		cc = new CreditCard(accntNum);
		cout << "account " << cc->getAccountNum() << " was re-opened" << endl;
		cout << "limit = " << cc->getCreditLimit() << " and the balance due is " << cc->getBalanceDue() << endl;
	}

	system("Pause");
    return 0;
}
