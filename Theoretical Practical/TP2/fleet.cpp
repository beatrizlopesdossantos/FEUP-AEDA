#include "fleet.h"
#include <string>

using namespace std;

vector<Vehicle *> Fleet::getVehicles() const {
    return vehicles;
}

void Fleet::addVehicle(Vehicle *v1) {
    vehicles.push_back(v1);
}

int Fleet::numVehicles() const {
    return vehicles.size();
}

int Fleet::lowestYear() const {
    if (vehicles.size() == 0) {
        return 0;
    }
    vector<Vehicle *>::const_iterator i =vehicles.begin();
    int lowest = (*i)->getYear();
    for (auto it = vehicles.begin(); it != vehicles.end(); it++) {
        int year1 = (*it)->getYear();
        if (year1 < lowest) {
            lowest = year1;
        }
    }
    return lowest;
}

ostream & operator<<(ostream & o, const Fleet & f) {
    for (int i = 0; i < f.numVehicles(); i++) {
        f.vehicles[i]->info(o);
    }
    return o;
}

vector<Vehicle *> Fleet::operator () (int yearM) const {
    vector<Vehicle *> vehiclesYear;
    if (vehicles.size() == 0) {
        return vehiclesYear;
    }
    for (auto it = vehicles.begin(); it != vehicles.end(); it++) {
        if ((*it)->getYear() == yearM) {
            vehiclesYear.push_back(*it);
        }
    }
    return vehiclesYear;
}

float Fleet::totalTax() const {
    if (vehicles.size() == 0) {
        return 0;
    }
    float total = 0;
    for (auto it = vehicles.begin(); it != vehicles.end(); it++) {
        total += (*it)->calculateTax();
    }
    return total;
}

unsigned Fleet::removeOldVehicles(int y1) {
    int num = 0;
    vector<Vehicle *>::const_iterator it = vehicles.begin();
    while(it != vehicles.end()) {
        if ((*it)->getYear()<= y1) {
            it = vehicles.erase(it);
            num++;
        }
        else
            it++;
    }
    return num;
}