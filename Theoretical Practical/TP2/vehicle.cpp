#include "vehicle.h"
#include <iostream>

using namespace std;

Vehicle::Vehicle(string b, int m, int y) {
    brand = b;
    month = m;
    year = y;
}

string Vehicle::getBrand() const {
    return brand;
}

int Vehicle::getYear() const {
    return year;
}

int Vehicle::info(ostream &o) const {
    cout << "Brand: " << brand << endl;
    cout << "Date: " << year << "/" << month << endl;
    return 3;
}

int Vehicle::info() const {
    return Vehicle::info(cout);
}

bool Vehicle::operator<(const Vehicle &v) const {
    if (year < v.year) {
        return true;
    }
    if (year == v.year && month < v.month) {
        return true;
    }
    return false;
}

MotorVehicle::MotorVehicle(string b, int m, int y, string f, int cyl) : Vehicle(b, m, y) {
    fuel = f;
    cylinder = cyl;
}

string MotorVehicle::getFuel() const {
    return fuel;
}

int MotorVehicle::info(ostream &o) const {
    int infoV = Vehicle::info();
    cout << "Fuel: " << fuel;
    cout << "Cylinder: " << cylinder;
    return infoV + 2;
}

int MotorVehicle::info() const {
    return MotorVehicle::info(cout);
}

float MotorVehicle::calculateTax() const {
    if (fuel == "gas") {
        if (cylinder <= 1000) {
            if (year > 1995) {
                return 14.56;
            }
            else {
                return 8.10;
            }
        }
        if (cylinder > 1000 && cylinder <= 1300) {
            if (year > 1995) {
                return 29.06;
            }
            else {
                return 14.56;
            }
        }
        if (cylinder > 1300 && cylinder <= 1700) {
            if (year > 1995) {
                return 45.15;
            }
            else {
                return 22.65;
            }
        }
        if (cylinder > 1750 && cylinder <= 2600) {
            if (year > 1995) {
                return 113.98;
            }
            else {
                return 54.89;
            }
        }
        if (cylinder > 2600 && cylinder <= 3500) {
            if (year > 1995) {
                return 181.17;
            }
            else {
                return 87.13;
            }
        }
        if (cylinder > 3500) {
            if (year > 1995) {
                return 320.89;
            }
            else {
                return 148.37;
            }
        }
    }
    else {
        if (cylinder <= 1500) {
            if (year > 1995) {
                return 14.56;
            }
            else {
                return 8.10;
            }
        }
        if (cylinder > 1500 && cylinder <= 2000) {
            if (year > 1995) {
                return 29.06;
            }
            else {
                return 14.56;
            }
        }
        if (cylinder > 2000 && cylinder <= 3000) {
            if (year > 1995) {
                return 45.15;
            }
            else {
                return 22.65;
            }
        }
        if (cylinder > 3000) {
            if (year > 1995) {
                return 113.98;
            }
            else {
                return 54.89;
            }
        }
    }
}

Car::Car(string b, int m, int y, string f, int cyl) : MotorVehicle(b, m, y, f, cyl) {}

int Car::info(ostream &o) const {
    cout << "Car" << endl;
    int infoC = MotorVehicle::info();
    cout << endl;
    return infoC;
}

int Car::info() const {
    return Car::info(cout);
}

Truck::Truck(string b, int m, int y, string f, int cyl, int ml) : MotorVehicle(b, m, y, f, cyl) {
    maximumLoad = ml;
}

int Truck::info(ostream &o) const {
    cout << "Truck" << endl;
    int infoT = MotorVehicle::info();
    cout << endl << "Maximum load: " << maximumLoad << endl << endl;
    return infoT + 1;
}

int Truck::info() const {
    return Truck::info(cout);
}

Bicycle::Bicycle(string b, int m, int y, string t) : Vehicle(b, m, y) {
    type = t;
}

int Bicycle::info(ostream&o) const {
    cout << "Bicycle" << endl;
    int infoB = Vehicle::info();
    cout << "Type: " << type << endl << endl;
    return infoB + 1;
}

int Bicycle::info() const {
    return Bicycle::info(cout);
}

float Bicycle::calculateTax() const {
    return 0;
}