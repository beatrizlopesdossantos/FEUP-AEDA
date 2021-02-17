#ifndef PLAYER_H_
#define PLAYER_H_

#include "bet.h"
#include <string>
using namespace std;

//TODO
struct betHash
{
	int operator() (const Bet& b) const
	{
        int v = 0;
        tabHInt nums = b.getNumbers();
        for ( auto i=nums.begin(); i != nums.end(); i++) {
            v = 37*v + *i;
        }
        return v;
    }
	
	bool operator() (const Bet& b1, const Bet& b2) const
	{
		if (b1.size() == b2.size()) {
            return false;
		}
		unsigned int n = b1.countRights(b2.getNumbers());
		if (n == b1.size()) {
		    return true;
		}
		return false;
	}
};


typedef unordered_set<Bet, betHash, betHash> tabHBet;

class Player
{
	tabHBet bets;
	string name;
public:
	Player(string nm="anonymous") { name=nm; }
	void addBet(const Bet & ap);
	unsigned betsInNumber(unsigned num) const;
	tabHBet drawnBets(const tabHInt& draw) const;
	unsigned getNumBets() const { return bets.size(); }
};

#endif 
