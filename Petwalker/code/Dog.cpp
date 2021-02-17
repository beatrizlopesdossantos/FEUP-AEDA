#include "Dog.h"
#include "Services.h"

Dog::Dog(string n, string r, Date b) {
    name = n;
    race = r;
    birth = b;
}


string Dog::getName() const {
    return name;
}

string Dog::getRace() const {
    return race;
}

Date Dog::getBirth() const {
    return birth;
}

void Dog::setOwner(Clients *c) {
    owner = c;
}

string Dog::getOwnerName() const {
    return owner->getName();
}

string Dog::getOwnerEmail() const {
    return owner->getEmail();
}

bool Dog::operator < (const Dog &d1) const {
    if (race == d1.race) {
        if (name == d1.name) {
            if (birth == d1.birth) {
                return getOwnerName() < d1.getOwnerName();
            }
            return birth < d1.birth;
        }
        return name < d1.name;
    }
    return race < d1.race;
}

bool Dog::operator==(const Dog &d1) const {
    return race == d1.race && name == d1.name && birth == d1.birth && getOwnerName() == d1.getOwnerName();
}

Services* Dog::getLastService() const {
    return lastService;
}

void Dog::setLastService(Services *s1) {
    lastService = s1;
}

ostream &operator<<(ostream &os, const Dog &d1) {
    //Config: nameOwner, name, race, dateOfBirth, dateLastService
    os << "  " << d1.getOwnerName() <<  "\t  ";
    if(d1.getOwnerName().size() < 15)
        os << "        ";
    os << d1.getName() << "\t ";
    if(d1.getName().size() < 6)
        os << "\t ";
    os << d1.getRace();
    if(d1.getRace().size() >= 15)
        os << "  ";
    else
        os<< "\t  ";
    if(d1.getRace().size() < 7)
        os << "\t  ";
    os << d1.getBirth() <<  "\t  " ;
    if(d1.getLastService() != nullptr)
        os << d1.getLastService()->getInitDate() <<  "\n" ;
    else
        os << "NoService\n";

    return os;
}
