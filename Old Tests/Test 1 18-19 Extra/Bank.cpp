/*
 * Bank.cpp
 */

#include "Bank.h"
#include <algorithm>
#include <string>

Bank::Bank() {}

void Bank::addAccount(Account *a) {
	accounts.push_back(a);
}

void Bank::addBankOfficer(BankOfficer b){
	bankOfficers.push_back(b);
}

vector<BankOfficer> Bank::getBankOfficers() const {
	return bankOfficers;
}

vector<Account *> Bank::getAccounts() const {
	return accounts;
}


// ----------------------------------------------------------------------------------------------

// a alterar
double Bank::getWithdraw(string cod1) const{
    double result = 0;
    for (auto &it: accounts) {
        if (cod1 == it->getCodH()) {
            result += it->getWithdraw();
        }
    }
    return result;
}


// a alterar
vector<Account *> Bank::removeBankOfficer(string name){
	vector<Account *> res;
	for (auto x = bankOfficers.begin(); x != bankOfficers.end(); x++) {
	    if ((*x).getName() == name) {
            res = (*x).getAccounts();
	        bankOfficers.erase(x);
            break;
	    }
	}
	return res;
}


// a alterar
const BankOfficer & Bank::addAccountToBankOfficer(Account *ac, string name) {
    for (auto x = bankOfficers.begin(); x != bankOfficers.end(); x++) {
        if ((*x).getName() == name) {
            (*x).addAccount(ac);
            return *x;
        }
    }
    throw NoBankOfficerException(name);
}

bool compareAccounts(Account *ac1, Account *ac2) {
    if (ac1->getBalance() == ac2->getBalance()) {
        return ac1->getCodIBAN() < ac2->getCodIBAN();
    }
    return ac1->getBalance() < ac2->getBalance();
}

// a alterar
void Bank::sortAccounts() {
    sort(accounts.begin(), accounts.end(), compareAccounts);
}
