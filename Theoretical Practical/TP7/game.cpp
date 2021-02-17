#include "game.h"
#include <sstream>


//TODO
ostream &operator << (ostream &os, Circle &c1)
{
	string state;
	if (c1.getState() == true) {
	    state = "true";
	}
	else {
	    state = "false";
	}
	os << c1.getPoints() << "-" << state << "-" << c1.getNVisits() << "\n";
	return os;
}

BinaryTree<Circle> Game::initiateGame(int pos, int level, vector<int> &points, vector<bool> &states) {
    Circle c(points[pos], states[pos]);
    if (level == 0) return BinaryTree<Circle>(c);
    BinaryTree<Circle> leftChild = initiateGame(2 * pos + 1, level - 1, points, states);
    BinaryTree<Circle> rightChild = initiateGame(2 * pos + 2, level - 1, points, states);
    return BinaryTree<Circle>(c, leftChild, rightChild);
}
//TODO
Game::Game(int h, vector<int> &points, vector<bool> &states)
{
    game = initiateGame(0, h, points, states);
}


//TODO
string Game::writeGame()
{
	BTItrLevel<Circle> it(game);
	stringstream gamestr("");
	while (!it.isAtEnd()) {
	    gamestr << it.retrieve();
	    it.advance();
	}
	return gamestr.str();
}


//TODO
int Game::move()
{
    int pos = 1; int nPoints = -1;
	BTItrLevel<Circle> it(game);
	if (it.isAtEnd()) return nPoints;
	while(true) {
	    Circle &c = it.retrieve();
	    int n;
	    if (c.getState() == false) n = pos;
	    else n = pos + 1;
	    c.changeState();
	    c.incNVisits();
	    nPoints = c.getPoints();
	    int i=0;
	    while (i<n && !it.isAtEnd()) {
	        it.advance();
	        i++;
	    }
	    if (!it.isAtEnd()) pos += n;
	    else break;
	}
	return nPoints;
}


//TODO
int Game::mostVisited()
{
	BTItrLevel<Circle> it(game);
	if (it.isAtEnd()) return -1;
	int more = -1;
	it.advance();
	while(!it.isAtEnd()) {
	    Circle c = it.retrieve();
	    if (c.getNVisits() > more) {
            more = c.getNVisits();
        }
	    it.advance();
	}
	return more;
}
