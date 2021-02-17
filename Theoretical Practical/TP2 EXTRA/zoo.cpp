#include "zoo.h"
#include <iostream>
#include <sstream>
#include <stdlib.h>
using namespace std;

unsigned Zoo::numAnimals() const {
    return animals.size();
}

unsigned Zoo::numVeterinarians() const {
    return veterinarians.size();
}

bool Zoo::isYoung(string nameA) {
    for (auto it = animals.begin(); it != animals.end(); it++) {
        if ((*it)->getName() == nameA) {
            return (*it)->isYoung();
        }
    }
    return false;
}

void Zoo::addAnimal(Animal *a1) {
    animals.push_back(a1);
}

string Zoo::getInfo() const {
    stringstream ss;
    for (auto it = animals.begin(); it != animals.end(); it++) {
        ss << (*it)->getInfo() << "\n";
    }
    return ss.str();
}

void Zoo::allocateVeterinarians(istream &isV) {
    string name, cod;
    while (!isV.eof()) {
        getline(isV, name);
        getline(isV, cod);
        long num = atoi(cod.c_str());
        Veterinary *v1 = new Veterinary(name, num);
        veterinarians.push_back(v1);
    }
    for(unsigned int i = 0; i < animals.size(); i++)
        animals[i]->setVeterinary( veterinarians[i%veterinarians.size()] );
}

bool Zoo::removeVeterinary(string nameV) {
    for(unsigned int i = 0; i < veterinarians.size(); i++) {
        if (veterinarians[i]->getName() == nameV) {
            for(unsigned int j = 0; j < animals.size(); j++) {
                if( animals[j]->getVeterinary() == veterinarians[i] ) {
                    animals[j]->setVeterinary(veterinarians[(i + 1) % veterinarians.size()]);
                }
            }
            veterinarians.erase(veterinarians.begin() + i);
            return true;
        }
    }
    return false;
}

bool Zoo::operator < (Zoo& zoo2) const {
    int sum = 0, sum2 = 0;
    for (auto it = animals.begin(); it != animals.end(); it++) {
        sum += (*it)->getAge();
    }
    for (auto it = zoo2.animals.begin(); it != zoo2.animals.end(); it++) {
        sum2 += (*it)->getAge();
    }
    if (sum < sum2) {
        return sum < sum2;
    }
    else {
        return sum > sum2;
    }
}