#include "game.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

Game::Game() {
    this->kids.clear();
}

Game::Game(list<Kid>& l2) {
    this->kids = l2;
}

unsigned int Game::numberOfWords(string phrase)
{
    if ( phrase.length() == 0 ) return 0;

    unsigned n=1;
    size_t pos = phrase.find(' ');
    while (pos != string::npos) {
        phrase = phrase.substr(pos+1);
        pos = phrase.find(' ');
        n++;
    }
    return n;
}

void Game::addKid(const Kid &k1) {
    kids.push_back(k1);
}

list<Kid> Game::getKids() const {
    return kids;
}

void Game::setKids(const list<Kid>& l1) {
    this->kids = l1;
}

string Game::write() const {
    stringstream oss;
    for (auto it = kids.begin(); it != kids.end(); it++) {
        oss << it->write() << endl;
    }
    return oss.str();
}


Kid& Game::loseGame(string phrase)
{
    int num = numberOfWords(phrase)-1;
    list<Kid>::iterator it = kids.begin();
    list<Kid>::iterator ite = kids.end();
    while (kids.size() > 1) {
        int nk = kids.size();
        int l = num%nk;
        for (int i = 1; i <= l; i++) {
            it++;
            if (it == ite) it = kids.begin();
            }
        cout << "leaves: " << it->write() << endl;
        it = kids.erase(it);
        if (it == ite) it = kids.begin();
    }
    return *it;
}

list<Kid>& Game::reverse()
{
/*    list<Kid> l1;
    for (auto it = kids.begin(); it != kids.end(); it++)
    {
        Kid *k=new Kid(*it);
        l1.push_front(*k);
        it ++;
    }*/
    //kids = l1;
    kids.reverse();
    return this->kids;
}

list<Kid> Game::removeOlder(unsigned id)
{
    list<Kid> rem;
    for (auto it = kids.begin(); it != kids.end(); it++) {
        if (it->getAge() > id) {
            rem.push_back(*it);
            kids.erase(it);
        }
    }
    return rem;
}


bool Game::operator==(Game& g2)
{
    if (kids.size() != g2.kids.size()) return false;
    list<Kid>::iterator it = kids.begin();
    list<Kid>::iterator ite = kids.end();
    list<Kid>::iterator it2 = g2.kids.begin();
    for(; it != ite; it++, it2++){
        if( !((*it) == (*it2)) ) return false;
    }
    return true;
}

list<Kid> Game::shuffle() const
{
    list<Kid> tempList = this->kids;
    list<Kid> newList;

    int rPos;
    /* initialize random seed: */
    srand(time(NULL) );

    while( !tempList.empty() ){
        /* generate a random position: */
        rPos = rand() % tempList.size();
        list<Kid>::iterator it = tempList.begin();
        for(unsigned i = 0; i < rPos; i++, it++);
        newList.push_back(*it);
        tempList.erase(it);
    }

    return newList;
}