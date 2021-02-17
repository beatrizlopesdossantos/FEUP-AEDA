#include "Employees.h"
#include "Clients.h"
#include "Services.h"

#include "Exceptions.h"
#include "Date.h"

Employees::Employees(string name, string username, int type) {
    this->name = name;
    this->username = username;
    this->type = type;
    this->numServicesDone = 0;
    this->moneyEarned = 0;
    this->numScheduledServices = 0;
}

string Employees::getName() {
    return name;
}

string Employees::getType() {
    if (type == 1){
        return "Professional";
    }
    else if (type == 2){
        return "Free-time";
    }
    else
        return "NotDefinedYet";
}

void Employees::setType(int i)
{
    if (i == 1){
        this->type = 1;
    }
    else if (i == 2){
        this->type = 1;
    }
    else
        this->type = 0;;
}

string Employees::getUsername() {
    return username;
}

double Employees::getEarnings() {
    return moneyEarned;
}

int Employees::getNumServicesDone() {
    return numServicesDone;
}

void Employees::setUsername(string username) {
    this->username = username; //talvez esta função seja necessária para os finds
}

bool Employees::operator==(const Employees &e2) const {
    return (this->username == e2.username);
}


ostream &operator<<(ostream &os, const Employees &e1) {
    //Config: username, name, type, numServicesDone (size vector), moneyEarned
    os << "  " << e1.username <<  " - \t" << e1.name;
    if(e1.name.size() < 15)
    {
        cout <<" \t\t ";
    }
    else
        cout << " \t ";

    if (e1.type == 1){
        os << "Professional";
    }
    else if (e1.type == 2){
        os <<  "Free-time ";
    }
    else
        os << "NotDefinedYet";

    os << " \t\t" << e1.numServicesDone << " \t\t" << e1.moneyEarned << "\n" ;

    return os;
}

void Employees::addMoneyEarned(double money) {
    //Função chamada quando se põe um serviço como completo
    numServicesDone++; //incrementa o número de Serviços completos
    moneyEarned += money;
}

void Employees::setScheduledServices(int num) {
    numScheduledServices = num;
}

int Employees::getScheduledServices() {
    return numScheduledServices;
}

//-- Parte 2

vector<Date> Employees::getAvailableTimes() {
    vector<Date> availableTimes;
    priority_queue<DateAvail> aux = availability;

    while (!aux.empty())
    {
        availableTimes.push_back((aux.top()).getDate());
        aux.pop();
    }

    return availableTimes;
}

void Employees::addNewSlot(Date Initial, int duration) {

    Date in = Initial;
    bool found = false;

    int numSlots = (int) (duration/60);


    for(int i = 0; i < numSlots; i++)
    {
        if(slotExists(in))
        {
            found = true;
            break;
        }

        in.addTime(60); //+ 60 minutes == 1 hour per slot
    }

    in = Initial;

    if(!found)
    {

        for(int c = 0; c < numSlots; c++)
        {
            DateAvail toAdd(in);
            availability.push(toAdd);

            in.addTime(60); //+ 60 minutes == 1 hour per slot
        }
    }
    else
        throw AvailAlreadyExists(this->username, Initial.getHours(), Initial.getDay(), Initial.getMonth(), Initial.getYear());

}

bool Employees::remSlot(Date Initial, int duration) {
    vector<Date> avail = getAvailableTimes(); //para facilitar as pesquisas
    Date aux = Initial;
    bool found = false;
    int numSlots = duration/60;
    priority_queue<DateAvail> pq_Aux;

    for(int i = 0; i < numSlots; i++)
    {
        found = false;
        for (auto d : avail)
        {
            if(aux == d)
            {
                found = true;
                break;
            }
        }
        aux.addTime(60); //para o prox. slot se o numSlots for maior que 1
    }

    //só elimina se encontrar todos os slots que são implicados pela duração definida

    if(found)
    {
        for(int c = 0; c < numSlots; c++)
        {
            while(!availability.empty())
            {
                if(availability.top().getDate() == Initial)
                {
                    availability.pop(); //não guarda e retira
                }
                else
                {
                    pq_Aux.push(availability.top()); //guarda e retira
                    availability.pop();
                }
            }

            availability = pq_Aux; //availability sem o slot já

            while(!pq_Aux.empty()){ pq_Aux.pop();}

            Initial.addTime(60); //para o prox. slot se o numSlots for maior que 1
        }
    }

    return found;
}

bool Employees::slotExists(Date Initial) {
    bool exists = false;
    priority_queue<DateAvail> pq_Aux = availability;

    while (!pq_Aux.empty())
    {
        if (pq_Aux.top().getDate() == Initial) {
            exists = true;
            break;
        }
        pq_Aux.pop();
    }
    return exists;
}

Date Employees::getTopAvailable() {
    //get top without removing
    return availability.top().getDate();
}

// Empl Available Class definitions
EmplAvailable::EmplAvailable(Employees *employee) {
    e1 = employee;
    Available = employee->getTopAvailable();
}

EmplAvailable::EmplAvailable(Employees *employee, Date Initial) {
    e1 = employee;
    if(e1->slotExists(Initial))
        Available = Initial;
    else
    {
        throw AvailDoesNotExist(employee->getUsername(), Initial.getHours(), Initial.getDay(), Initial.getMonth(), Initial.getYear());
    }
}

Employees *EmplAvailable::getEmployee() const {
    return e1;
}

Date EmplAvailable::getSlot() const {
    return Available;
}

bool EmplAvailable::operator<(const EmplAvailable &eA) const {
    if(Available == eA.getSlot())
        return (e1->getUsername() > eA.getEmployee()->getUsername());
    else
    {
        DateAvail th(Available); DateAvail dA(eA.getSlot());

        return th < dA;
    }
}

bool EmplAvailable::operator==(const EmplAvailable &eA) const {
    return ((e1->getUsername() == eA.getEmployee()->getUsername())&&(Available == eA.Available));
}

ostream &operator<<(ostream &os, const EmplAvailable &eA) {
    //Config: date, username
    os << "  " << eA.getSlot() <<  "   \t" << eA.getEmployee()->getUsername();

    return os;
}

//Date Avail Class Definitions
DateAvail::DateAvail(Date d) {
    date = d;
}

Date DateAvail::getDate() const {
    return date;
}

bool DateAvail::operator<(const DateAvail &dA ) const {
    if(date.getYear() == dA.getDate().getYear())
    {
        if(date.getMonth() == dA.getDate().getMonth())
        {
            if (date.getDay() == dA.getDate().getDay())
            {
                if (date.getHours() == dA.getDate().getHours())
                {
                    return date.getMinutes() > dA.getDate().getMinutes();
                }
                else
                    return date.getHours() > dA.getDate().getHours();
            }
            else
                return date.getDay() > dA.getDate().getDay();
        }
        else
            return date.getMonth() > dA.getDate().getMonth();
    }
    else
        return date.getYear() > dA.getDate().getYear();
}
