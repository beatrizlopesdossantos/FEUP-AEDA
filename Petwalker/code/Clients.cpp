#include "Clients.h"
#include "Services.h"
#include "Employees.h"
#include "Dog.h"
#include "Exceptions.h"

Clients::Clients(string n, string e, string c = "None", int p = 0) {
    name = n;
    category = c;
    points = p;
    numServices = 0;
    email = e;
}

string Clients::getName() {
    return name;
}

int Clients::getPoints() {
    return points;
}

string Clients::getCategory() {
    return category;
}

void Clients::addPoints(int pointsAdd) {
    points += pointsAdd;
    numServices++;
    setCategory();
}

void Clients::usePoints(int pointsDisc) {
    points -= pointsDisc;
}


int Clients::getNumberServices() const{
    return numServices;
}



void Clients::setCategory() {
    if (numServices>= 2 && numServices < 5) category = "Silver";
    else if (numServices >= 5 && numServices < 8) category = "Gold";
    else if (numServices >= 8) category = "Platinum";
}

string Clients::getEmail() const{
    return email;
}

void Clients::setEmail(string email) {
    this->email = email;
}

bool Clients::operator==(const Clients &c2) const {
    return ((this->email == c2.email));
}

ostream &operator<<(ostream &os, const Clients &c1) {
    //Config: email, name, category, Points
    os << "  " << c1.email <<  " - \t" << c1.name;
    if(c1.name.size() < 15)
    {
        os << " \t\t";
    }
    else
        os << "\t";

    os << c1.category << "\t";
    if (c1.category == "Gold" || c1.category == "Silver" || c1.category == "None")
        os << "\t";



    os << c1.points << "\t\t" << c1.numServices << "\n" ;

    return os;
}

void Clients::incrementNumServices() {
    numServices++;
}

void Clients::addDog(Dog *d) {
    dogs.push_back(d);
}

vector<Dog*> Clients::getDogs() {
    return dogs;
}

Dog *Clients::getDog(string name) {
    for(auto d: dogs)
    {
        if(d->getName() == name)
            return d;
    }

    throw InvalidInput("\n\tDog with name " + name + " does not exist!\n");
}

OldClientsRecords::OldClientsRecords(Clients* client, string email) {
    _client = client;
    _email = email;
}

void OldClientsRecords::setClient(Clients *client) {
    _client = client;
}

void OldClientsRecords::setEmail(string email) {
    _email = email;
}

Clients* OldClientsRecords::getClient() const {
    return _client;
}

string OldClientsRecords::getEmail() const {
    return _email;
}
