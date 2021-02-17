/*
 * Bank.h
 */

#ifndef SRC_BANK_H_
#define SRC_BANK_H_

#include "Account.h"
#include <vector>

#include "BankOfficer.h"


class Bank {
	vector<Account *> accounts;
	vector<BankOfficer> bankOfficers;
public:
	Bank();
	void addAccount(Account *a);
	void addBankOfficer(BankOfficer b);
	vector<BankOfficer> getBankOfficers() const;
	vector<Account *> getAccounts() const;

	//-------
	double getWithdraw(string cod1) const;
	vector<Account *> removeBankOfficer(string name);
	const BankOfficer& addAccountToBankOfficer(Account *ac, string name);
	void sortAccounts();
};

class NoBankOfficerException {
    string name;
public:
    NoBankOfficerException(string name) {this->name = name;}
    string getName() {return name;}
};

template <class T>
unsigned int numberDifferent (const vector<T> & v1) {
    vector<T> aux;
    unsigned int count = 0;
    for (auto it = v1.begin(); it != v1.end(); it++) {
        if (find(aux.begin(), aux.end(), it) != aux.end()) {
            continue;
        }
        count++;
        aux.push_back(*it);
    }
    return count;
}

#endif /* SRC_BANK_H_ */
