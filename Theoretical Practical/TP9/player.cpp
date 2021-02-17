#include "player.h"

//TODO
void Player::addBet(const Bet& b)
{
    bets.insert(b);
}

//TODO
unsigned Player::betsInNumber(unsigned num) const
{
    unsigned count = 0;
	for (auto it = bets.begin(); it != bets.end(); it++) {
	    if (it->contains(num)) {
	        count++;
	    }
	}
	return count;
}

//TODO
tabHBet Player::drawnBets(const tabHInt& draw) const
{
	tabHBet res;
	res.clear();
	for (auto it = bets.begin(); it != bets.end(); it++) {
	    if (it->countRights(draw) > 3) {
	        res.insert(*it);
	    }
	}
	return res;
}
