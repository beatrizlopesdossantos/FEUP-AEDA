#include "Services.h"
#include "Clients.h"
#include "Employees.h"
#include "Petwalker.h"

Services::Services(string client_email, bool exclusive, string employee_username, Tasks task, Date startDate, string name_Dog, Petwalker* petwalker) : _task(task.getTaskName(),task.getDuration()) {
    _petwalker = petwalker;
    _client_email = client_email;
    _exclusive = exclusive;
    _employee_username = employee_username;
    _complete = false;
    _servicePrice=0;
    _dog = name_Dog;
    setDates(startDate, _task.getDuration());

}

void Services::setClientEmail(string email) {
    _client_email = email;
}

void Services::setEmployeeUsername(string username) {
    _employee_username = username;
}


void Services::setDates(Date start, int duration) {
    Date end = start;
    end.addTime(duration);
    _dates.first = start;
    _dates.second = end;
}

bool Services::isComplete() const{
    return _complete;
}

bool Services::isExclusive() const{
    return _exclusive;
}

vector<Services*> Services::setComplete(bool file) {

    vector<Services*> allSetDone;
    if(!file)
    {
        bool exists = false;
        for (auto ser : _petwalker->getScheduledServices())
        {
            if(*this == *ser)
                exists = true;
        }

        if(!exists) {throw ServiceDoesNotExist("\n The service with the type '" + this->getTask().getTaskName() + "' at date you chose does not exist!\n");}
    }
    //

    double employeeCost;
    Clients *client = _petwalker->getClient(_client_email);
    Employees *employee = _petwalker->getEmployee(_employee_username);
    if (employee->getType() == "Professional"){
        employeeCost = _petwalker->getProfessionalCost();
    }
    else{
        employeeCost = _petwalker->getPartTimeCost();
    }
    if(client->getPoints() < _petwalker->getDiscountPoints() || client->getCategory() == "None"){
        _servicePrice = (employeeCost * _task.getDuration()/60.0 + _petwalker->getTaskCost(_task)) * _petwalker->getProfit();
        if (_exclusive){_servicePrice *=_petwalker->getExclusiveCost();}
        client->addPoints((_servicePrice/_petwalker->getCostPerPoint()));
    }
    else{
        if (client->getCategory() == "Silver"){
            _servicePrice = (employeeCost * _task.getDuration()/60.0 + _petwalker->getTaskCost(_task)) *_petwalker->getProfit() * .5;
            if(_exclusive){_servicePrice *= _petwalker->getExclusiveCost();}
        }
        else if(client->getCategory() == "Gold"){
            _servicePrice = (employeeCost * _task.getDuration()/60.0 + _petwalker->getTaskCost(_task)) *_petwalker->getProfit() * .25;
            if(_exclusive){_servicePrice *= _petwalker->getExclusiveCost();}

        }
        else if(client->getCategory() == "Platinum")
            _servicePrice = 0;
        client->usePoints(_petwalker->getDiscountPoints());
    }
    employee->addMoneyEarned(_task.getDuration()/60.0 * employeeCost);

    _petwalker->addServiceDone(this);
    allSetDone.push_back(this);
    Dog * dg = client->getDog(_dog);

    _petwalker->getLastService(client, dg);

    if (!file)
    {
        _petwalker->removeScheduledService(this);
        //
        for(auto s: _petwalker->getEmployeeScheduledServices(this->getEmployeeUsername(), this->getInitDate()))
        {
            if(this->getTask().getTaskName() == s->getTask().getTaskName())
            {
                if(!this->isExclusive() && !s->isExclusive())
                {
                    Clients *c1 = _petwalker->getClient(s->getClientEmail());

                    if(c1->getPoints() < _petwalker->getDiscountPoints() || c1->getCategory() == "None"){
                        s->setServicePriceFile(0, ((employeeCost * _task.getDuration()/60.0 + _petwalker->getTaskCost(_task)) * _petwalker->getProfit()));
                        c1->addPoints((s->getServicePrice()/_petwalker->getCostPerPoint()));
                    }
                    else{
                        if (client->getCategory() == "Silver"){
                            s->setServicePriceFile(0, ((employeeCost * _task.getDuration()/60.0 + _petwalker->getTaskCost(_task)) * _petwalker->getProfit() * .5));
                        }
                        else if(client->getCategory() == "Gold"){
                            s->setServicePriceFile(0, ((employeeCost * _task.getDuration()/60.0 + _petwalker->getTaskCost(_task)) * _petwalker->getProfit() * .25));
                        }
                        else if(client->getCategory() == "Platinum")
                            s->setServicePriceFile(0, 0);
                        c1->usePoints(_petwalker->getDiscountPoints());
                    }
                    employee->addMoneyEarned(_task.getDuration()/60.0 * employeeCost);

                    _petwalker->addServiceDone(s);
                    allSetDone.push_back(s);
                    dg = c1->getDog(s->getNameDog());
                    _petwalker->getLastService(c1, dg);

                    _petwalker->removeScheduledService(s);



                    s->setSharedComplete();
                }
            }
        }
        //
    }

    _complete = true;
    return allSetDone;
}

double Services::getServicePrice() const {
    return _servicePrice;
}

string Services::getClientEmail() const {
    return _client_email;
}

string Services::getEmployeeUsername() const {
    return _employee_username;
}

bool Services::operator==(const Services &s2) const {

    if(this->_client_email != s2.getClientEmail())
        return false;
    if(this->_employee_username != s2.getEmployeeUsername())
        return false;
    if(!(this->_dates.first == s2.getInitDate()))
        return false;
    if(this->_exclusive != s2.isExclusive())
        return false;
    if(this->getTask().getTaskName() != s2.getTask().getTaskName())
        return false;
    if(this->getNameDog() != s2.getNameDog())
        return false;

    return true;
}

Date Services::getInitDate() const {
    return _dates.first;
}

Date Services::getEndDate() const {
    return _dates.second;
}

Tasks Services::getTask() const {
    return _task;
}

ostream &operator<<(ostream &os, const Services &s1) {
    //Config: date, taskname, isExclusive, userClient, userEmployee, ServicePrice

    os << "  " << s1.getInitDate() <<  " - \t" << s1.getTask().getTaskName();
    if(s1.getTask().getTaskName() == "Walk" || s1.getTask().getTaskName() == "Bath" || s1.getTask().getTaskName() == "CutFur")
    { cout << "\t\t ";}
    else
        cout <<" \t ";
    if (s1.isExclusive()){
        os << "  Yes";
    }
    else{
        os <<  "  No";
    }
    os << " \t    " << s1.getClientEmail();
    if(s1.getClientEmail().size() < 7)
        cout << " \t\t";
    else
        cout << " \t";

    cout << s1.getNameDog() << "\t ";
    if(s1.getNameDog().size() < 7)
        os << "\t ";

    cout << s1.getEmployeeUsername();
    if(s1.getEmployeeUsername().size() < 8)
        cout << " \t\t\t";
    else
        cout << " \t\t";
    os <<  s1.getServicePrice() << "\n" ;

    return os;
}

void Services::setServicePriceFile(int type, double priceService) {
    this->_servicePrice = priceService;

    if(type == 1)
    {
        //Employee != NoMore...
        double employeeCost;
        Employees *employee = _petwalker->getEmployee(_employee_username);
        if (employee->getType() == "Professional"){
            employeeCost = _petwalker->getProfessionalCost();
        }
        else{
            employeeCost = _petwalker->getPartTimeCost();
        }

        employee->addMoneyEarned(_task.getDuration()/60.0 * employeeCost);
    }
    else if(type == 2)
    {
        //Client != NoMore...
        Clients *client = _petwalker->getClient(_client_email);
        client->incrementNumServices();
    }

}

void Services::setSharedComplete() {
    _complete = true;
}

string Services::getNameDog() const {
    return _dog;
}
