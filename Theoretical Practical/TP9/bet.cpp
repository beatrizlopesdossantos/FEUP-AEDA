#include "bet.h"
#include <iostream>
#include <sstream>
using namespace std;


//TODO
bool Bet::contains(unsigned num) const
{
	tabHInt::const_iterator it = numbers.find(num);
	if (it == numbers.end()) {
	    return false;
	}
	return true;
}

//TODO
void Bet::generateBet(const vector<unsigned>& values, unsigned n)
{
    numbers.clear();
    unsigned nval = 0, i = 0;
    while (nval < n) {
        pair<tabHInt::iterator, bool> res = numbers.insert(values[i]);
        if (res.second == true) {
            nval++;
        }
        i++;
    }
}

//TODO
unsigned Bet::countRights(const tabHInt& draw) const
{
	unsigned  right = 0;
	for (auto it = draw.begin(); it != draw.end(); it++) {
	    if (contains(*it)) {
	        right++;
	    }
	}
	return right;
}

unsigned Bet::size() const {
    return numbers.size();
}
