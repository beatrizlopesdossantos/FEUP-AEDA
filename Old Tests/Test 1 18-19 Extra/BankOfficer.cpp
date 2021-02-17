/*
 * BankOfficer.cpp
 */
#include "BankOfficer.h"

unsigned int BankOfficer::id_aux = 1;

BankOfficer::BankOfficer(): id(0) {}

void BankOfficer::setName(string nm){
	name = nm;
}

string BankOfficer::getName() const{
	return name;
}

vector<Account *> BankOfficer::getAccounts() const {
	return myAccounts;
}

void BankOfficer::addAccount(Account *a) {
	myAccounts.push_back(a);
}

unsigned int BankOfficer::getID() const{
	return id;
}


// ----------------------------------------------------------------------------------------------

// a alterar
BankOfficer::BankOfficer(string name) {
    this->name = name;
    id ++;//= id_aux;
    //id_aux++;
}

bool BankOfficer::operator>(const BankOfficer &b1) {
    if (myAccounts.size() == b1.myAccounts.size()) {
        return name > b1.getName();
    }
    if (myAccounts.size() > b1.myAccounts.size()) {
        return true;
    }
    return false;
}




