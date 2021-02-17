#include "carPark.h"
#include "insertionSort.h"
#include "sequentialSearch.h"
#include <algorithm>
#include <vector>
using namespace std;

CarPark::CarPark(unsigned cap, unsigned nMaxCli): capacity(cap), numMaxClients(nMaxCli)
{
    freePlaces=cap;
}

vector<InfoCard> CarPark::getClients() const
{
    return clients;
}

unsigned CarPark::getNumPlaces() const
{
    return capacity;
}

unsigned CarPark::getNumOccupiedPlaces() const
{
    return capacity-freePlaces;
}

unsigned CarPark::getNumMaxClients() const
{
    return numMaxClients;
}

unsigned CarPark::getNumClients() const
{
    return clients.size();
}

bool InfoCard::operator == (const InfoCard & inf) const
{ return name == inf.name; }

int CarPark::clientPosition(const string & name) const
{
    InfoCard inf;
    inf.name = name;
    return sequentialSearch(clients, inf);
}

unsigned CarPark::getFrequency(const string &name) const
{
    int pos = clientPosition(name);
    if (pos == -1) {
        throw ClientDoesNotExist(name);
    }
    return clients[pos].frequency;
}

bool CarPark::addClient(const string & name)
{
    if (clients.size() == numMaxClients) return false;
    if (clientPosition(name) != -1) return false;
    InfoCard info;
    info.name=name;
    info.present=false;
    clients.push_back(info);
    return true;
}

bool CarPark::removeClient(const string & name)
{
    for (vector<InfoCard>::iterator it = clients.begin(); it != clients.end(); it++)
        if ( (*it).name == name ) {
            if ( (*it).present == false ) {
                clients.erase(it);
                return true;
            }
            else return false;
        }
    return false;
}

bool CarPark::enter(const string & name)
{
    if (freePlaces == 0) return false;
    int pos = clientPosition(name);
    if (pos == -1) return false;
    if (clients[pos].present == true) return false;
    clients[pos].present = true;
    freePlaces--;
    clients[pos].frequency ++;
    return true;
}

bool CarPark::leave(const string & name)
{
    int pos = clientPosition(name);
    if (pos == -1) return false;
    if (clients[pos].present == false) return false;
    clients[pos].present = false;
    freePlaces++;
    return true;
}


InfoCard CarPark::getClientAtPos(unsigned p) const
{
    InfoCard info;
    return info;
}

bool InfoCard::operator < (const InfoCard &inf) const
{   if (frequency == inf.frequency) {
        return name < inf.name;
    }
    return frequency > inf.frequency;
}

void CarPark::sortClientsByFrequency()
{
    InfoCard inf;
    insertionSort(clients);
}

bool InfoCard::operator>(const InfoCard &inf1) const {
    return name > inf1.name;
}

bool compName(const InfoCard &c1, const InfoCard &c2)
{
    return c1.name < c2.name;
}

void CarPark::sortClientsByName()
{
    sort(clients.begin(),clients.end(),compName);
}

vector<string> CarPark::clientsBetween(unsigned f1, unsigned f2)
{
    vector<string> names;
    sortClientsByFrequency();
    for (auto it = clients.begin(); it != clients.end(); it++) {
        if ((*it).frequency >= f1 && (*it).frequency <= f2) {
            names.push_back((*it).name);
        }
    }
    return names;
}


ostream & operator<<(ostream & os, const CarPark & cp)
{
    return os;
}

ClientDoesNotExist::ClientDoesNotExist(string name){
    this->name = name;
}

string ClientDoesNotExist::getName() const {
    return name;
}
