#include "Petwalker.h"
#include <fstream>
#include <sstream>
#include <algorithm>

Petwalker::Petwalker() :alldogs(new Dog("","",Date())){
    loadFiles();
}

Petwalker::~Petwalker(){
    for (int i= 0;i <_clients.size();i++){
        delete _clients[i];
    }
    for (int i = 0; i < _employees.size(); i++) {
        delete _employees[i];
    }
    for (int i = 0; i < _services_done.size();i++){
        delete _services_done[i];
    }
    for (int i = 0; i < _scheduled_services.size();i++){
        delete _scheduled_services[i];
    }
    _clients.resize(0);
    _employees.resize(0);
    _services_done.resize(0);
    _scheduled_services.resize(0);
}

void Petwalker::loadFiles() {
    ifstream clients, services_done, scheduled_services, employees, price_table, dogs, old_clients;
    string line;
    price_table.open("PriceTable.txt");
    if(!price_table){
        throw FileNotFound("PriceTable.txt");
    }
    while (true){
        getline(price_table,line);
        string name;
        float price;
        if(line == "End")
            break;
        istringstream prices(line);
        prices >> name >> price;
        if(name == "CostPerPoint"){_cost_per_point = price;}
        else if(name == "NotExclusiveLimit"){_notexclusivelimit = price;}
        else if(name == "ExclusiveCost"){_exclusive_cost = price;}
        else if(name == "DiscountPoints"){_discount_points = price;}
        else if(name == "Profit"){_profit = price;}
        else if(name == "ProfessionalCost"){_professional_cost = price;}
        else if(name == "PartTimeCost"){_part_time_cost = price;}
        else if(name == "VeterinaryCost"){_veterinary_cost = price;}
        else if(name == "BathCost"){_bath_cost = price;}
        else if(name == "CutFurCost"){_cut_fur_cost = price;}
        else if(name == "WalkCost"){_walk_cost = price;}
        else if(name == "ObedienceClassCost"){_obedience_class_cost = price;}
    }
    price_table.close();
    clients.open("Clients.txt");
    if (!clients) {
        throw FileNotFound("Clients.txt");
    }
    while (true) {
        getline(clients, line);
        string firstname, lastname, category, email;
        int points, numServicesDone;
        if (line == "End")
            break;
        istringstream nam(line);
        nam >> firstname >> lastname;
        getline(clients, line);
        istringstream user(line);
        user >> email;
        getline(clients,line);
        istringstream cat(line);
        cat >> category;
        getline(clients, line);
        istringstream poi(line);
        poi >> points;
        string name = firstname + " " + lastname;
        Clients *client = new Clients(name,email, category, points);
        _clients.push_back(client);
        getline(clients, line);
        string empty_line;
        istringstream empt(line);
        empt >> empty_line;
    }
    clients.close();
    old_clients.open("OldClients.txt");
    if (!old_clients) {
        throw FileNotFound("OldClients.txt");
    }
    while (true) {
        getline(old_clients,line);
        string email;
        if (line == "End")
            break;
        stringstream old(line);
        old >> email;
        Clients *client = getClient(email);
        OldClientsRecords o1(client,email);
        _old_clients.insert(o1);
    }
    employees.open("Employees.txt");
    if (!employees) {
        throw FileNotFound("Employees.txt");
    }
    while (true) {
        getline(employees, line);
        string first_name, last_name, name, username,type;
        int availability, hour, day, month, year;
        if (line == "End")
            break;
        istringstream nam(line);
        nam >> first_name >> last_name;
        name = first_name + " " + last_name;
        getline(employees, line);
        istringstream user(line);
        user >> username;
        getline(employees,line);
        istringstream typ(line);
        typ >> type;
        int type_int;
        if(type == "Professional"){type_int = 1;}
        if(type == "Free-time"){type_int = 2;}
        Employees *employee = new Employees(name,username, type_int);
        getline(employees, line);
        istringstream avail(line);
        avail >> availability;
        for (int i = 0; i < availability;i++){
            getline(employees, line);
            istringstream date(line);
            date >> hour >> day >> month >> year;
            Date d1(day,month,year,hour,0);
            employee->addNewSlot(d1,60);
            addNewAvail(employee,d1);
        }
        getline(employees, line);
        istringstream empt(line);
        string empty_line;
        empt >> empty_line;
        _employees.push_back(employee);
    }
    employees.close();
    dogs.open("Dogs.txt");
    if(!dogs) {
        throw FileNotFound("Dogs.txt");
    }
    while (true){
        getline(dogs,line);
        string name, race, email;
        int hours, day, month, year;
        if (line == "End")
            break;
        istringstream nam(line);
        nam >> name;
        getline(dogs, line);
        istringstream rac(line);
        rac >> race;
        getline(dogs, line);
        istringstream dat(line);
        dat >> day >> month >> year;
        Date d1(day,month,year,0,0);
        getline(dogs, line);
        istringstream clientem(line);
        clientem >> email;
        Clients* c1 = getClient(email);
        Dog* dog = new Dog(name,race,d1);
        dog->setOwner(c1);
        addDogToClient(c1, dog);
        getline(dogs, line);
        istringstream empt(line);
        string empty_line;
        empt >> empty_line;
    }
    dogs.close();
    services_done.open("ServicesDone.txt");
    if (!services_done) {
        throw FileNotFound("ServicesDone.txt");
    }
    bool cont_serv_done = true;
    while (cont_serv_done) {
        while (true) {

            getline(services_done, line);
            string exclusive, task_name, client_email, employee_username, name_dog;
            int day, month, year, minutes, hours;
            double price_service;
            bool exclusivity = false;
            if (line == "End") {
                cont_serv_done = false;
                break;
            }
            istringstream client_user(line);
            client_user >> client_email;
            getline(services_done, line);
            istringstream dog_name(line);
            dog_name >> name_dog;
            getline(services_done, line);
            istringstream employee_user(line);
            employee_user >> employee_username;
            getline(services_done, line);
            istringstream excl(line);
            excl >> exclusive;
            getline(services_done, line);
            istringstream task_nam(line);
            task_nam >> task_name;
            getline(services_done, line);
            istringstream price_serv(line);
            price_serv >> price_service;
            getline(services_done, line);
            istringstream time(line);
            time >> day >> month >> year >> hours >> minutes;
            Date date(day, month, year, hours, minutes);
            if (exclusive == "Exclusive")
                exclusivity = true;
            Tasks task = createTask(task_name);
            Services *service = new Services(client_email, exclusivity, employee_username, task, date, name_dog, this);
            if ((client_email == "NoMoreAClient") && (employee_username == "NoMoreAEmployee")) {
                service->setServicePriceFile(0, price_service);
                this->addServiceDone(service); //adicionar ao vetor de servicesDone do Petwalker
            }
            else if (client_email == "NoMoreAClient" && employee_username != "NoMoreAEmployee") {
                service->setServicePriceFile(1, price_service);
                this->addServiceDone(service);
            }
            else if (client_email != "NoMoreAClient" && employee_username == "NoMoreAEmployee") {
                service->setServicePriceFile(2, price_service);
                this->addServiceDone(service);
            }
            else {
                vector<Services*> servicesDone = service->setComplete(1);
                Clients* c1;
                vector<Services*> servicesDoneDog;
                for (auto sd: servicesDone) {
                    c1 = getClient(sd->getClientEmail());
                    for (auto s: getClientServicesDone(c1->getEmail())) {
                        if (s->getNameDog() == sd->getNameDog()) {
                            servicesDoneDog.push_back(s);
                        }
                    }
                    if (servicesDoneDog.size() == 1) {
                        addToBST(c1->getDog(sd->getNameDog()));
                    }
                    servicesDoneDog.clear();
                }
            }
            getline(services_done, line);
            istringstream empt(line);
            string empty_line;
            empt >> empty_line;
        }
    }
    services_done.close();
    scheduled_services.open("ScheduledServices.txt");
    if (scheduled_services.fail()) {
        throw FileNotFound("ScheduledServices.txt"); //Substitui isto: cerr << "\nMensagem de erro : File not found";
        exit(1);
    }
    bool cont_sched_serv = true;
    while (cont_sched_serv) {
        while (true) {

            getline(scheduled_services, line);
            string exclusive, task_name, client_email, employee_username, name_dog;
            int day, month, year, minutes, hours;
            bool exclusivity = false;
            if (line == "End") {
                cont_sched_serv = false;
                break;
            }
            istringstream client_user(line);
            client_user >> client_email;
            getline(scheduled_services, line);
            istringstream dog_name(line);
            dog_name >> name_dog;
            getline(scheduled_services, line);
            istringstream employee_user(line);
            employee_user >> employee_username;
            getline(scheduled_services, line);
            istringstream excl(line);
            excl >> exclusive;
            getline(scheduled_services, line);
            istringstream task_nam(line);
            task_nam >> task_name;
            getline(scheduled_services, line);
            istringstream time(line);
            time >> day >> month >> year >> hours >> minutes;
            Date date(day, month, year, hours, minutes);
            if (exclusive == "Exclusive")
                exclusivity = true;
            Tasks task = createTask(task_name);
            Services *service = new Services(client_email, exclusivity, employee_username, task, date,name_dog, this);
            _scheduled_services.push_back(service);
            getline(scheduled_services, line);
            istringstream empt(line);
            string empty_line;
            empt >> empty_line;
        }
    }
    scheduled_services.close();

}

void Petwalker::saveFiles() {
    ofstream clients, services_done, scheduled_services, employees, price_table, dogs, old_clients;
    price_table.open("PriceTable.txt",ios::trunc);
    if(!price_table){
        throw FileNotFound("PriceTable.txt");
    }
    price_table << "Profit " << _profit << endl;
    price_table << "ExclusiveCost " << _exclusive_cost << endl;
    price_table << "NotExclusiveLimit " << _notexclusivelimit << endl;
    price_table << "CostPerPoint " << _cost_per_point << endl;
    price_table << "DiscountPoints " << _discount_points << endl;
    price_table << "ProfessionalCost " << _professional_cost << endl;
    price_table << "PartTimeCost " << _part_time_cost << endl;
    price_table << "VeterinaryCost " << _veterinary_cost << endl;
    price_table << "BathCost " << _bath_cost << endl;
    price_table << "CutFurCost " << _cut_fur_cost << endl;
    price_table << "WalkCost " << _walk_cost << endl;
    price_table << "ObedienceClassCost " << _obedience_class_cost << endl;
    price_table << "End";
    price_table.close();
    dogs.open("Dogs.txt", ios::trunc);
    if (!dogs) {
        throw FileNotFound("Dogs.txt");
    }
    vector<Clients*> allClients = getClients();
    for (auto c: allClients) {
        for (auto d: c->getDogs()) {
            dogs << d->getName() << endl;
            dogs << d->getRace() << endl;
            dogs << d->getBirth().getDay() << " " << d->getBirth().getMonth() << " " << d->getBirth().getYear() << endl;
            dogs << d->getOwnerEmail() << endl;
            dogs << endl;
        }

    }
    dogs << "End";
    dogs.close();

    old_clients.open("OldClients.txt",ios::trunc);
    if(!old_clients) {
        throw FileNotFound("OldClient.txt");
    }
    for(auto it : _old_clients){
        old_clients << it.getEmail() << endl;
    }
    old_clients << "End";
    old_clients.close();
    employees.open("Employees.txt",ios::trunc);
    if(!employees){
        throw FileNotFound("Employees.txt");
    }
    for (int i = 0;i < _employees.size();i++){
        employees << _employees[i]->getName() << endl;
        employees << _employees[i]->getUsername() << endl;
        employees << _employees[i]->getType() << endl;
        employees << _employees[i]->getAvailableTimes().size() << endl;
        for (int j = 0; j < _employees[i]->getAvailableTimes().size();j++){
            employees << _employees[i]->getAvailableTimes()[j].getHours() << " " << _employees[i]->getAvailableTimes()[j].getDay() << " " << _employees[i]->getAvailableTimes()[j].getMonth() << " " << _employees[i]->getAvailableTimes()[j].getYear();
            employees << endl;
        }
        employees << endl;
    }
    employees << "End";
    employees.close();
    clients.open("Clients.txt",ios::trunc);
    if(!clients){
        throw FileNotFound("Clients.txt");
    }
    for (int i = 0; i < _clients.size();i++){
        clients << _clients[i]->getName() << endl;
        clients << _clients[i]->getEmail() << endl;
        clients << _clients[i]->getCategory() << endl;
        clients << _clients[i]->getPoints() << endl;
        clients << endl;
    }
    clients << "End";
    clients.close();
    services_done.open("ServicesDone.txt",ios::trunc);
    if(!services_done){
        throw FileNotFound("ServicesDone.txt");
    }
    for(int i = 0; i< _services_done.size();i++){
        services_done << _services_done[i]->getClientEmail() << endl;
        services_done << _services_done[i]->getNameDog() << endl;
        services_done << _services_done[i]->getEmployeeUsername() << endl;
        string exclusivity;
        if (_services_done[i]->isExclusive()){exclusivity = "Exclusive";}
        else{exclusivity = "Shared";}
        services_done << exclusivity << endl;
        services_done << _services_done[i]->getTask().getTaskName() << endl;
        services_done << _services_done[i]->getServicePrice()<<endl;
        services_done << _services_done[i]->getInitDate().getDay() << " " << _services_done[i]->getInitDate().getMonth()<< " " <<  _services_done[i]->getInitDate().getYear()
                      << " " << _services_done[i]->getInitDate().getHours() << " " << _services_done[i]->getInitDate().getMinutes() << endl;
        services_done << endl;
    }
    services_done << "End";
    services_done.close();
    scheduled_services.open("ScheduledServices.txt",ios::trunc);
    if(!scheduled_services){
        throw FileNotFound("ScheduledServices.txt");
    }
    for(int i = 0; i< _scheduled_services.size();i++){
        scheduled_services << _scheduled_services[i]->getClientEmail() << endl;
        scheduled_services << _scheduled_services[i]->getNameDog() << endl;
        scheduled_services << _scheduled_services[i]->getEmployeeUsername() << endl;
        string exclusivity;
        if (_scheduled_services[i]->isExclusive()){exclusivity = "Exclusive";}
        else{exclusivity = "Shared";}
        scheduled_services << exclusivity << endl;
        scheduled_services << _scheduled_services[i]->getTask().getTaskName() << endl;
        scheduled_services << _scheduled_services[i]->getInitDate().getDay() << " " << _scheduled_services[i]->getInitDate().getMonth()<< " " <<  _scheduled_services[i]->getInitDate().getYear()
                           << " " << _scheduled_services[i]->getInitDate().getHours() << " " << _scheduled_services[i]->getInitDate().getMinutes() << endl;
        scheduled_services << endl;
    }
    scheduled_services << "End";
    scheduled_services.close();
}

int Petwalker::getNotExclusiveLimit() {
    return _notexclusivelimit;
}

int Petwalker::getDiscountPoints() const{
    return _discount_points;
}

double Petwalker::getExclusiveCost() {
    return _exclusive_cost;
}

double Petwalker::getProfit() const {
    return _profit;
}

double Petwalker::getProfessionalCost() const {
    return _professional_cost;
}

double Petwalker::getPartTimeCost() const {
    return _part_time_cost;
}

double Petwalker::getVeterinaryCost() const {
    return _veterinary_cost;
}

double Petwalker::getBathCost() const {
    return _bath_cost;
}

double Petwalker::getCutFurCost() const {
    return _cut_fur_cost;
}

double Petwalker::getWalkCost() const {
    return _walk_cost;
}

double Petwalker::getObedienceClassCost() const {
    return _obedience_class_cost;
}

int Petwalker::getCostPerPoint() const {
    return _cost_per_point;
}

void Petwalker::setNotExclusiveLimit(const int cost) {
    _notexclusivelimit = cost;
}

void Petwalker::setExclusiveCost(const double cost) {
    _exclusive_cost = cost;
}

void Petwalker::setCostPerPoint(const int cost){
    _cost_per_point = cost;
}

void Petwalker::setProfit(const double cost) {
    _profit = cost;
}

void Petwalker::setDiscountPoints(const int points) {
    _discount_points = points;
}

void Petwalker::setProfessionalCost(const double cost) {
    _professional_cost = cost;
}

void Petwalker::setPartTimeCost(const double cost) {
    _part_time_cost = cost;
}

void Petwalker::setVeterinaryCost(const double cost) {
    _veterinary_cost = cost;
}

void Petwalker::setBathCost(const double cost) {
    _bath_cost = cost;
}

void Petwalker::setCutFurCost(const double cost) {
    _cut_fur_cost = cost;
}

void Petwalker::setWalkCost(const double cost) {
    _walk_cost = cost;
}

void Petwalker::setObedienceClassCost(const double cost) {
    _obedience_class_cost = cost;
}

Tasks Petwalker::createTask(string task_name) {
    if(task_name == "Veterinary"){
        Veterinary task;
        return task;
    }
    if(task_name == "Bath"){
        Bath task;
        return task;
    }
    if(task_name == "CutFur"){
        CutFur task;
        return task;
    }
    if(task_name == "Walk"){
        Walk task;
        return task;}
    else{
        ObedienceClass task;
        return task;}
}

double Petwalker::getTaskCost(Tasks task) {
    if (task.getTaskName() =="Veterinary"){return _veterinary_cost;}
    if (task.getTaskName() =="Bath"){return _bath_cost;}
    if (task.getTaskName() =="CutFur"){return _cut_fur_cost;}
    if (task.getTaskName() =="Walk"){return _walk_cost;}
    if (task.getTaskName() =="ObedienceClass"){return _obedience_class_cost;}

    return 0.0;
}

Clients* Petwalker::getClient(string email){
    for (int i = 0;i < _clients.size();i++){if (_clients[i]->getEmail()==email){return _clients[i];}}
    string msg;
    if (email == "NoMoreAClient"){msg = "";}
    else{msg = email;}
    throw ClientDoesNotExist(msg);
}

Employees* Petwalker::getEmployee(string username){
    for (int i = 0;i<_employees.size();i++){if (_employees[i]->getUsername() == username){return _employees[i];}}
    string msg;
    if( username == "NoMoreAEmployee"){msg = "";}
    else{ msg = username;}
    throw EmployeeDoesNotExist(msg);
}

vector<Employees*> Petwalker::getEmployees() const {
    return _employees;
}

vector<Clients*> Petwalker::getClients() const {
    return _clients;
}

vector<Services*> Petwalker::getScheduledServices() const {
    return _scheduled_services;
}

vector<Services*> Petwalker::getServicesDone() const {
    return _services_done;
}

vector<Services*> Petwalker::getClientScheduledServices(string email){
    vector<Services*> client_scheduled;
    Clients* client = getClient(email);
    for (int i = 0; i < _scheduled_services.size();i++){
        if (_scheduled_services.at(i)->getClientEmail()==email){
            client_scheduled.push_back(_scheduled_services.at(i));
        }
    }
    return client_scheduled;
}

vector<Services*> Petwalker::getEmployeeScheduledServices(string username) {
    vector<Services*> employee_scheduled;
    Employees* employee = getEmployee(username);
    for (int i = 0;i<_scheduled_services.size();i++){
        if (_scheduled_services.at(i)->getEmployeeUsername() == username){
            employee_scheduled.push_back(_scheduled_services.at(i));
        }
    }
    employee->setScheduledServices(employee_scheduled.size());
    return employee_scheduled;
}

vector<Services*> Petwalker::getDateScheduledServices(int day, int month, int year) {
    vector<Services*> date_scheduled;
    for (int i= 0;i< _scheduled_services.size();i++){
        if(_scheduled_services[i]->getInitDate().getDay()==day && _scheduled_services[i]->getInitDate().getMonth()==month && _scheduled_services[i]->getInitDate().getYear()==year){
            date_scheduled.push_back(_scheduled_services.at(i));
        }
    }
    return date_scheduled;
}

vector<Services*> Petwalker::getClientServicesDone(string email) {
    vector<Services*> client_done;
    Clients* client = getClient(email);
    for (int i = 0; i < _services_done.size();i++){
        if (_services_done.at(i)->getClientEmail()==email){
            client_done.push_back(_services_done.at(i));
        }
    }
    return client_done;
}

vector<Services*> Petwalker::getEmployeeServicesDone(string username) {
    vector<Services*> employee_done;
    Employees* employee = getEmployee(username);
    for (int i = 0; i < _services_done.size();i++){
        if (_services_done.at(i)->getEmployeeUsername()==username){
            employee_done.push_back(_services_done.at(i));
        }
    }
    return employee_done;
}

vector<Services*> Petwalker::getDateServicesDone(int day, int month, int year) {
    vector<Services*> date_done;
    for (int i= 0;i< _services_done.size();i++){
        if(_services_done[i]->getInitDate().getDay()==day && _services_done[i]->getInitDate().getMonth()==month && _services_done[i]->getInitDate().getYear()==year){
            date_done.push_back(_services_done.at(i));
        }
    }
    return date_done;
}

void Petwalker::addScheduledService(Services *service) {
    for (auto s : _scheduled_services)
    {
        if(*s == *service)
            throw ServiceAlreadyExists();
    }
    _scheduled_services.push_back(service);
}

void Petwalker::addServiceDone(Services *service) {
    _services_done.push_back(service);
}

void Petwalker::removeScheduledService(Services *service) {
    bool erased = false;
    for(int i = 0;i<_scheduled_services.size();i++){
        if (*(_scheduled_services.at(i)) == *service){
            _scheduled_services.erase(_scheduled_services.begin()+i);
            erased = true;
        }
    }
    if(!erased)
        throw ServiceDoesNotExist("No such scheduled service exists! Please try again.");
}

void Petwalker::removeClient(string email) {
    try{
        Clients* client = getClient(email);
        for(int i = 0; i < _clients.size();i++) {
            if (client == _clients[i]){
                _clients.erase(_clients.begin()+i);
            }
        }
        delete client;
        for(int i = 0;i<_services_done.size();i++){
            if (_services_done[i]->getClientEmail()==email){
                _services_done[i]->setClientEmail("NoMoreAClient");
            }
        }
        for(int i = 0; i < _scheduled_services.size();i++){
            if(_scheduled_services[i]->getClientEmail() == email){
                _scheduled_services.erase(_services_done.begin()+i);
            }
        }
    }
    catch (ClientDoesNotExist &e)
    {
        cout << "\n\t" << e.getInfo() << endl;
    }
}

void Petwalker::removeEmployee(string username) {
    try{
        Employees* employee = getEmployee(username);
        for (int i = 0;i < _employees.size();i++){
            if(employee == _employees[i]){
                _employees.erase(_employees.begin()+i);
            }
        }
        delete employee;
        for(int i = 0;i<_services_done.size();i++){
            if (_services_done[i]->getEmployeeUsername()==username){
                _services_done[i]->setEmployeeUsername("NoMoreAEmployee");
            }
        }
        for(int i = 0; i < _scheduled_services.size(); i++){
            if (_scheduled_services[i]->getEmployeeUsername()==username){
                _scheduled_services[i]->setEmployeeUsername("NoMoreAEmployee");
            }
        }
        for(int i = 0; i < _scheduled_services.size();i++){
            if(_scheduled_services[i]->getEmployeeUsername() == "NoMoreAEmployee"){
                string date = to_string(_scheduled_services[i]->getInitDate().getDay()) + "/" + to_string(_scheduled_services[i]->getInitDate().getMonth()) + "/" + to_string(_scheduled_services[i]->getInitDate().getYear()) + "  " + to_string(_scheduled_services[i]->getInitDate().getHours()) + ":" + to_string(_scheduled_services[i]->getInitDate().getMinutes());
                try{
                    string substitute = checkDate(_scheduled_services[i]->getInitDate(), _scheduled_services[i]->isExclusive(), _scheduled_services[i]->getTask(), false);
                    _scheduled_services[i]->setEmployeeUsername(substitute);
                    cout << "\n  The service '" + _scheduled_services[i]->getTask().getTaskName() + "' at date '" + date +"' changed employee to '" + substitute + "'!";
                }
                catch (DateNotValid)
                {
                    cout << "\n  The service '" + _scheduled_services[i]->getTask().getTaskName() + "' at date '" + date +"' was deleted!\n No available employees to substitute the deleted!\n";
                    _scheduled_services.erase(_services_done.begin()+i);
                    continue;
                }
                catch (EmployeeDoesNotExist &e)
                {
                    cout << "\n\t" << e.getInfo() << endl;
                }
            }
        }
    }
    catch (EmployeeDoesNotExist &e)
    {
        cout << "\n\t" << e.getInfo() << endl;
    }
}

Services *Petwalker::createService(int id) {
    //Criar task e serviço só depois do input do utilizador
    string userClient, userEmployee, task_name, nameDog;
    Date dataInicial;
    Clients* client;

    while(1) {
        if (id == 0) { cout << "\n---------------------------- Create a Service ----------------------------"; }
        else if (id == 1){ cout << "\n---------------------------- Choose a Service to delete ----------------------------"; }
        else{cout << "\n---------------------------- Choose the Service to update ----------------------------";}

        cout << "\n  Insert the email of the client that wants the service: ";


        try {
            getline(cin, userClient);

            client = getClient(userClient);

            for(int i = 0; i < userClient.size(); i++)
            {
                if(userClient[i] == ' ') {
                    throw InvalidInput("\n\tInvalid email input! Please try again.\n");
                }
            }
            if(userClient.empty())
                throw InvalidInput("\n\tInvalid input! Please try again.\n");

            break;
        }
        catch (ClientDoesNotExist &e) {
            cout << e.getInfo();
            continue;
        }
        catch (InvalidInput &e) {
            cout << e.getInfo();
            continue;
        }
        catch (...) {
            cout << "\n\tInvalid Input - Please try again!\n";
            continue;
        }
    }
        OldClientsRecords tmp(client,client->getEmail());
        if(_old_clients.find(tmp)!= _old_clients.end()){_old_clients.erase(tmp);}
        if(client->getDogs().size() == 1)
        {
            nameDog = client->getDogs().at(0)->getName();
        }
        else
        {
            bool found = false;
           while(1){
               cout << "\n  Insert the name of dog that enjoys the service: ";


               try {
                   getline(cin, nameDog);

                   if(nameDog.empty())
                       throw InvalidInput("\n\tInvalid input! Please try again.\n");

                   for(auto dg: client->getDogs())
                   {
                       if(nameDog == dg->getName())
                       {
                           found = true;
                           break;
                       }
                   }

                   if(!found)
                       throw InvalidInput("\n\tDog with name " + nameDog + " does not exist!\n");

                   break;
               }
               catch (InvalidInput &e) {
                   cout << e.getInfo();
                   continue;
               }
               catch (...) {
                   cout << "\n\tInvalid Input - Please try again!\n";
                   continue;
               }
           }
        }


    if (id != 0) {
        while (1) {
            cout << "\n  Insert the username of the employee that does the service: ";


            try {
                getline(cin, userEmployee);
                Employees* employee = getEmployee(userEmployee);
                for (int i = 0; i < userEmployee.size(); i++) {
                    if (userEmployee[i] == ' ')
                        throw InvalidInput("Invalid username input! Please try again.");
                }
                if(userEmployee.empty())
                    throw InvalidInput("\n\tInvalid input! Please try again.\n");

                break;
            }
            catch (EmployeeDoesNotExist &e)
            {
                cout << e.getInfo();
            }
            catch (InvalidInput &e) {
                cout << e.getInfo()<< endl;
                continue;
            }
            catch (...) {
                cout << "\n\tInvalid Input - Please try again!\n";
                continue;
            }
        }
    }
    while(1) {
        cout << "\n  Insert the name of the task (Veterinary, Bath, CutFur, Walk, ObedienceClass): ";


        try {
            getline(cin, task_name);

            if(task_name.empty())
                throw InvalidInput("\n\tInvalid input! Please try again.\n");

            //loop para fazer tudo letras minusculas
            for (size_t i = 0; i < task_name.size(); i++) {
                task_name[i] = tolower(task_name[i]);
            }

            if(task_name == "veterinary")
            {
                task_name = "Veterinary";
            }
            else if (task_name == "bath")
            {
                task_name = "Bath";
            }
            else if (task_name == "cutfur")
            {
                task_name = "CutFur";
            }
            else if (task_name == "walk")
            {
                task_name = "Walk";
            }
            else if (task_name == "obedienceclass")
            {
                task_name = "ObedienceClass";

            }
            else
                throw InvalidServiceType(task_name); //Está funcionar de maneira estranha mas funciona!

            break;
        }
        catch (InvalidServiceType &t) {
            cout << t.getInfo();
            continue;
        }
        catch (...) {
            cout << "\n\tInvalid Input - Please try again!\n";
            continue;
        }
    }
    Tasks task = createTask(task_name);

    string exclusive;

    while(true)
    {
        cout << "\n  Is this service exclusive?";
        cout << "\n   1 - Yes" << "\t0 - No";
        cout << "\n  Insert the number corresponding to your choice:";
        try {
            getline(cin, exclusive);
            if (exclusive.size() > 1 || exclusive.empty())
                throw InvalidInput("\n\tInvalid Input - Please input a number next time!\n");
            else if ( ((stoi(exclusive)) < 0) || (stoi(exclusive)) >= 2)
                throw InvalidInput();
            else
                break;
        }
        catch (InvalidInput &e)
        {
            cout << e.getInfo();
            continue;
        }
    }

    while(1) {
        string input;
        stringstream dateinput;
        int hours, minutes = 0, day, month, year;

        cout << "\n  Insert the data in format DD MM YYYY hh: "; //Aqui tirar os minutes? YES

        try {
            getline(cin, input);
            dateinput << input;
            dateinput >> day >> month  >> year >> hours >> minutes;

            dataInicial =  Date(day, month, year, hours, minutes);
            if(id==0){
                Date dt(1, 1, 2021, 10, 00);
                Employees *e = new Employees("","",0);
                e->addNewSlot(dt, 60);

                EmplAvailable eA(e, dt);

                    if(!(stoi(exclusive))) //se não for exclusivo procura um no qual possa adicionar
                    {
                        userEmployee = checkDate(dataInicial, stoi(exclusive), task, true);

                        //check if it is added to one of the collective ones if not throw NoAvailableEmployee
                        bool found = false;

                        if(userEmployee == "NoOne") {
                            eA = getEmplMostAvail(dataInicial, task);
                        }
                        else {
                            for (auto &s: getEmployeeScheduledServices(userEmployee)) {
                                if (!s->isExclusive()) {
                                    if (s->getInitDate() == dataInicial) {
                                        found = true;
                                        break;
                                    }
                                }
                            }
                            if (!found)
                                throw NoAvailableEmployee();
                        }
                    }
                    else
                        eA = getEmplMostAvail(dataInicial, task);

                if(eA.getEmployee()->getUsername() != "")
                {
                    userEmployee = eA.getEmployee()->getUsername();

                    eA.getEmployee()->setScheduledServices(eA.getEmployee()->getScheduledServices()+1); //add to Scheduled Services of Employee
                }

            }
            break;
        }
        catch (DateNotValid &e) {
            cout << e.getInfo();
            continue;
        }
        catch (NoAvailableEmployee &e) {
            cout << e.getInfo();
            continue;
        }
        catch (...) {
            cout << "\n\tInvalid Input - Please try again!\n";
            continue;
        }
    }



    Services *result = new Services(userClient, stoi(exclusive), userEmployee, task, dataInicial, nameDog, this);

    return result;
}

Employees *Petwalker::createEmployee() {
    string name, firstname, secondname, userEmployee, type, third; //adicionei o third para controlo de input
    stringstream input;
    while(1) {
        cout << "\n------------------------ Create a Employee ------------------------";
        cout << "\n  Insert the name of the employee (two names only): ";

        try {
            getline(cin, name);
            input << name;
            input >> firstname >> secondname >> third;

            //invalidInput?

            if(!third.empty())
            {
                third = "";
                throw InvalidInput("\n\tInsert only two names please!\n");
            }
            break;
        }
        catch (InvalidInput &e) {
            cout << e.getInfo();
            continue;
        }
        catch (...) {
            cout << "\n\tInvalid Input - Please try again!\n";
            continue;
        }
    }
    while(1) {
        cout << "\n  Insert the username of the employee: ";

        try {
            getline(cin, userEmployee);

            for(int i = 0; i < userEmployee.size(); i++)
            {
                if(userEmployee[i] == ' ')
                    throw InvalidInput("\n\tInvalid username input! Please try again.");
            }

            if(userEmployee.empty())
                throw InvalidInput("\n\tInvalid input! Please try again.\n");

            break;
        }
        catch (InvalidInput &e) {
            cout << e.getInfo();
            continue;
        }
        catch (...) {
            cout << "\n\tInvalid Input - Please try again!\n";
            continue;
        }
    }

    while(1) {
        cout << "\n  Choose the type of the Employee (number: 1 - Professional, 2 - Free-time)\n";
        cout << "  Insert the number corresponding to your choice:";
        try {
            getline(cin, type);
            if (type.size() > 1 || type.empty())
                throw InvalidInput("\n\tInvalid Input - Please input a number next time!\n");
            else if (((stoi(type)) < 0) || (stoi(type)) >= 3)
                throw InvalidInput();
            else
                break;
        }
        catch (InvalidInput &e) {
            cout << e.getInfo();
            continue;
        }
    }

    Employees *result = new Employees(name, userEmployee, stoi(type));

    return result;
}

Clients *Petwalker::createClient() {
    string name, firstname, secondname, userClient, third; //adicionei o third para controlo de input
    stringstream input;
    while(1) {
        cout << "\n------------------------ Create a Client ------------------------";
        cout << "\n  Insert the name of the client (two names only): ";

        try {
            getline(cin, name);
            input << name;
            input >> firstname >> secondname >> third;

            //invalidInput?

            if(!third.empty())
            {
                third = "";
                throw InvalidInput("\n\tInsert only two names please!\n");
            }
            break;
        }
        catch (InvalidInput &e) {
            cout << e.getInfo();
            continue;
        }
        catch (...) {
            cout << "\n\tInvalid Input - Please try again!\n";
            continue;
        }
    }
    while(1) {
        cout << "\n  Insert the email of the client: ";

        try {
            getline(cin, userClient);

            for(int i = 0; i < userClient.size(); i++)
            {
                if(userClient[i] == ' ')
                    throw InvalidInput("Invalid email input! Please try again.");
            }

            if(userClient.empty())
                throw InvalidInput("\n\tInvalid input! Please try again.\n");

            break;
        }
        catch (InvalidInput &e) {
            cout << e.getInfo();
            continue;
        }
        catch (...) {
            cout << "\n\tInvalid Input - Please try again!\n";
            continue;
        }
    }


    Clients *result = new Clients(name, userClient, "None", 0);

    return result;
}

void Petwalker::addEmployee(Employees *e1) {
    for (auto e : _employees)
    {
        if(e1->getUsername() == e->getUsername())
            throw EmployeeAlreadyExist(e1->getUsername());
    }
    _employees.push_back(e1);
}

void Petwalker::addClient(Clients *c1) {
    for (auto c : _clients)
    {
        if(c1->getEmail() == c->getEmail())
            throw ClientAlreadyExist(c1->getEmail());
    }
    _clients.push_back(c1);
}

vector<Services *> Petwalker::getTaskServicesDone(string task_name) {
    vector<Services*> task_done;
    for (int i= 0;i< _services_done.size();i++){
        if(_services_done[i]->getTask().getTaskName() == task_name){
            task_done.push_back(_services_done.at(i));
        }
    }
    return task_done;
}

vector<Services *> Petwalker::getTaskScheduledServices(string task_name) {
    vector<Services*> task_scheduled;
    for (int i= 0;i< _scheduled_services.size();i++){
        if(_scheduled_services[i]->getTask().getTaskName() == task_name){
            task_scheduled.push_back(_scheduled_services.at(i));
        }
    }
    return task_scheduled;
}


string Petwalker::checkDate(Date date, bool exclusive, Tasks task, bool pq) {

    if(!exclusive) {
        for (int i = 0; i < _scheduled_services.size(); i++) {
            if (task.getTaskName() == _scheduled_services[i]->getTask().getTaskName())
            {
                if (date == _scheduled_services[i]->getInitDate() &&  _scheduled_services[i]->isExclusive()==exclusive && _scheduled_services[i]->getEmployeeUsername() != "NoMoreAEmployee") {
                    if (getEmployeeScheduledServices(_scheduled_services[i]->getEmployeeUsername(), date).size() <
                        _notexclusivelimit) {
                        return _scheduled_services[i]->getEmployeeUsername();
                    }
                }
            }
        }

        if(pq)
            return "NoOne";
    }

    for (int i = 0; i < _employees.size(); i++) {
        _employees[i]->setScheduledServices(getEmployeeScheduledServices(_employees[i]->getUsername()).size());
    }

    sort(_employees.begin(), _employees.end(),[](Employees *e1, Employees *e2){
        if(e1->getScheduledServices() == e2->getScheduledServices())
        {
            return (e1->getUsername() < e2->getUsername());
        }
        else return (e1->getScheduledServices() < e2->getScheduledServices());
    });

    Date end_date = date;
    end_date.addTime(task.getDuration());
    for (int i = 0; i < _employees.size();i++){
        bool aprooved;
        if (getEmployeeScheduledServices(_employees[i]->getUsername()).size() == 0){aprooved = true;}
        else{
            for (int j = 0; j < getEmployeeScheduledServices(_employees[i]->getUsername()).size(); j++) {
                aprooved = true;
                if (date < getEmployeeScheduledServices(_employees[i]->getUsername())[j]->getInitDate() &&
                    getEmployeeScheduledServices(_employees[i]->getUsername())[j]->getInitDate() < end_date) {
                    aprooved = false;
                } else if (date < getEmployeeScheduledServices(_employees[i]->getUsername())[j]->getEndDate() &&
                           getEmployeeScheduledServices(_employees[i]->getUsername())[j]->getEndDate() < end_date) {
                    aprooved = false;
                } else if (end_date < getEmployeeScheduledServices(_employees[i]->getUsername())[j]->getEndDate() &&
                           getEmployeeScheduledServices(_employees[i]->getUsername())[j]->getInitDate() < date) {
                    aprooved = false;
                } else if (end_date == getEmployeeScheduledServices(_employees[i]->getUsername())[j]->getEndDate() &&
                           getEmployeeScheduledServices(_employees[i]->getUsername())[j]->getInitDate() == date) {
                    aprooved = false;
                }else if (date ==getEmployeeScheduledServices(_employees[i]->getUsername())[j]->getInitDate()){
                    aprooved = false;
                } else {break; }
            }
        }
        if (aprooved == true){
            return _employees[i]->getUsername();
        }
    }
    throw DateNotValid("\nThere are no employees available, please choose another date.");
}

vector<Services *> Petwalker::getEmployeeScheduledServices(string username,Date date) {
    vector<Services*> employee_scheduled;
    Employees* employee = getEmployee(username);
    for (int i = 0;i<_scheduled_services.size();i++){
        if (_scheduled_services.at(i)->getEmployeeUsername() == username && _scheduled_services.at(i)->getInitDate() == date){
            employee_scheduled.push_back(_scheduled_services.at(i));
        }
    }
    return employee_scheduled;
}

//-- Parte 2

vector<EmplAvailable > Petwalker::getEmplAvail() {
    vector<EmplAvailable > res;
    priority_queue<EmplAvailable> aux = EmplAvail;

    while (!aux.empty())
    {
        res.push_back(aux.top());
        aux.pop();
    }

    return res;
}

void Petwalker::addNewAvail(Employees *e1, Date Initial) {

    EmplAvailable eA(e1, Initial);

    vector<EmplAvailable> avail = getEmplAvail(); //para facilitar as pesquisas
    bool found = false;

    for (auto e : avail) {
        if (e == eA) {
            found = true;
            break;
        }
    }

    if(!found)
        EmplAvail.push(eA);
    else
        throw AvailAlreadyExists(e1->getUsername(), Initial.getHours(), Initial.getDay(), Initial.getMonth(), Initial.getYear());
}

bool Petwalker::remAvail(Employees *e1, Date Initial) {
    vector<EmplAvailable> avail = getEmplAvail(); //para facilitar as pesquisas
    bool found = false;
    priority_queue<EmplAvailable> pq_Aux;

    for (auto e : avail) {
        if ((e1->getUsername() == e.getEmployee()->getUsername())&&(Initial == e.getSlot())) {
            found = true;
            break;
        }
    }

    if (found) {
        while (!EmplAvail.empty()) {
            if ((e1->getUsername() == EmplAvail.top().getEmployee()->getUsername())&&(Initial == EmplAvail.top().getSlot())) {
                EmplAvail.pop(); //não guarda e retira
            } else {
                pq_Aux.push(EmplAvail.top()); //guarda e retira
                EmplAvail.pop();
            }
        }

        EmplAvail = pq_Aux; //EmplAvail sem o eA já
    }

    return found;
}

EmplAvailable Petwalker::getEmployeeMostAvail() {
    EmplAvailable eA = EmplAvail.top();
    EmplAvail.pop();
    return eA;
}

EmplAvailable Petwalker::getEmplMostAvail(Date hours, Tasks task) {
    priority_queue<EmplAvailable> Aux;
    Date dt(1, 1, 2021, 10, 00);
    Employees *e = new Employees("","",0);
    e->addNewSlot(dt, 60);

    EmplAvailable eA(e, dt);

    bool found = false;
    bool twoSlots = false;
    int duration = 60; //duration of the slots needed for the service
    Date h = hours;

    while(!EmplAvail.empty())
    {
        //Check if it is the day & hours we are looking for
        if(EmplAvail.top().getSlot() == hours)
        {
            eA = EmplAvail.top();
            EmplAvail.pop(); //tirar e não adicionar a Aux
            found = true;
            break; //break para ser apenas o primeiro nesse dia
        }
        else
        {
            Aux.push(EmplAvail.top());
            EmplAvail.pop();
        }
    }

    //Repor a priority queue sem o eliminado
    while(!Aux.empty())
    {
        EmplAvail.push(Aux.top());
        Aux.pop();
    }

    //Se for Veterinary/ObedienceClass - ir procurar no do employees e depois alterar na do petwalker
    if(task.getDuration() > 60) //Quando é mais do que um slot (2 - 120 min)
    {
        found = false;
        h.addTime(60); //Para ser o proximo slot
        if(eA.getEmployee()->slotExists(h))
        {
            twoSlots = true;
            //Se existir eliminar também da pq de Petwalker
            while(!EmplAvail.empty())
            {
                //Check if it is the day & hours we are looking for
                if((EmplAvail.top().getSlot() == h) && (EmplAvail.top().getEmployee()->getUsername() == eA.getEmployee()->getUsername()))
                {
//                    eA = EmplAvail.top();
                    EmplAvail.pop(); //tirar e não adicionar a Aux
                    found = true;
                    break; //break para ser apenas o primeiro nesse dia
                }
                else
                {
                    Aux.push(EmplAvail.top());
                    EmplAvail.pop();
                }
            }

            //Repor a priority queue sem o "novo" eliminado
            while(!Aux.empty())
            {
                EmplAvail.push(Aux.top());
                Aux.pop();
            }

        }
        else
        {
            EmplAvail.push(eA);
            eA = EmplAvailable(e, dt); //se não existir voltar a adicionar o eA inicial à PQ de Petwalker
        }
    }

    if(twoSlots)
        duration = 120;

    if(found)
    {
        //eliminar das disponibilidades do employee
        if(!eA.getEmployee()->remSlot(eA.getSlot(), duration)) //duration depende do tipo de service (120 se Vet. ou Obedience - 60 se outro)
            throw NoAvailableEmployee();

    }
    else
        throw NoAvailableEmployee();

    return eA;
}

vector<Dog*> Petwalker::findSameBirthDogs(Date d) {
    BSTItrIn<Dog*> it(alldogs);
    vector<Dog*> sameBirth;
    while (!it.isAtEnd()) {
        if (it.retrieve()->getBirth().getMonth() == d.getMonth()) {
            sameBirth.push_back(it.retrieve());
        }
        it.advance();
    }
    return sameBirth;
}

vector<Dog*> Petwalker::findSameRaceDogs(string r) {
    BSTItrLevel<Dog*> it(alldogs);
    vector<Dog*> sameRace;
    while (!it.isAtEnd()) {
        if (it.retrieve()->getRace() == r) {
            sameRace.push_back(it.retrieve());
        }
        it.advance();
    }
    return sameRace;
}

Dog* Petwalker::createDog(Clients *c) {
    string name, race;
    string firstname, secondname, third;
    stringstream input;
    Date birth;
    while(1) {
        cout << "\n------------------------ Create a Dog ------------------------";
        cout << "\n  Insert the name of the dog (two names only): ";

        try {
            getline(cin, name);
            input << name;
            input >> firstname >> secondname >> third;

            //invalidInput?

            if(!third.empty())
            {
                third = "";
                throw InvalidInput("\n\tInsert only two names please!\n");
            }
            break;
        }
        catch (InvalidInput &e) {
            cout << e.getInfo();
            continue;
        }
        catch (...) {
            cout << "\n\tInvalid Input - Please try again!\n";
            continue;
        }
    }
    while(1) {
        cout << "\n  Insert the race of the dog: ";

        try {
            getline(cin, race);

            for(int i = 0; i < race.size(); i++)
            {
                if(race[i] == ' ')
                    throw InvalidInput("Invalid race input! Please try again.");
            }

            if(race.empty())
                throw InvalidInput("\n\tInvalid input! Please try again.\n");

            break;
        }
        catch (InvalidInput &e) {
            cout << e.getInfo();
            continue;
        }
        catch (...) {
            cout << "\n\tInvalid Input - Please try again!\n";
            continue;
        }
    }
    while(1) {
        string input;
        stringstream dateinput;
        int hours, minutes = 0, day, month, year;

        cout << "\n  Insert the data of birth in format DD MM YYYY: "; //Aqui tirar os minutes? YES

        try {
            getline(cin, input);
            dateinput << input;
            dateinput >> day >> month  >> year >> hours >> minutes;

            birth =  Date(day, month, year, hours, minutes);

            break;
        }
        catch (DateNotValid &e) {
            cout << e.getInfo();
            continue;
        }
        catch (...) {
            cout << "\n\tInvalid Input - Please try again!\n";
            continue;
        }
    }



    Dog *result = new Dog(name, race, birth);
    result->setOwner(c);

    return result;
}

void Petwalker::addDogToClient(Clients *c1, Dog *d) {
    for (auto c : _clients)
    {
        if(c1->getEmail() == c->getEmail())
        {
            for(auto dog : c->getDogs())
            {
                if(dog == d)
                {
                    throw DogAlreadyExist(d->getName(), c->getName());
                }
            }

            c->addDog(d);
            break;
        }
    }
}

vector<Dog *> Petwalker::getDogs() {
    BSTItrLevel<Dog*> it(alldogs);
    vector<Dog *> res;
    while (!it.isAtEnd()) {
        res.push_back(it.retrieve());
        it.advance();
    }
    return res;
}

void Petwalker::getLastService(Clients *c1, Dog* d) {
    /*if (file) {
        getClientServicesDone()
    }*/
    vector<Services*> clientsServices;
    for (auto c : _clients)
    {
        if(c1->getEmail() == c->getEmail())
        {
            clientsServices = getClientServicesDone(c->getEmail());
            break;
        }
     }
    sort(clientsServices.begin(), clientsServices.end(), [](Services *s1, Services *s2){
        return (s2->getInitDate() < s1->getInitDate());
    });

        for (auto cS : clientsServices)
        {
            if(cS->getNameDog() == d->getName())
            {
                d->setLastService(cS);
                break;
            }
        }

}


void Petwalker::changeEmail(string old_email, string new_email) {
    Clients *client = getClient(old_email);
    OldClientsRecords tmp(client,old_email);
    if(_old_clients.find(tmp) != _old_clients.end()){
        _old_clients.erase(tmp);
        tmp.setEmail(new_email);
        _old_clients.insert(tmp);
    }
    for(int i = 0;i < _services_done.size();i++){
        if(_services_done.at(i)->getClientEmail() == old_email)
            _services_done.at(i)->setClientEmail(new_email);
    }
    for(int i = 0;i < _scheduled_services.size();i++){
        if(_scheduled_services.at(i)->getClientEmail() == old_email)
            _scheduled_services.at(i)->setClientEmail(new_email);
    }
    client->setEmail(new_email);
}

vector<Clients*> Petwalker::getOldClients() {
    vector<Clients*> tmp;
    for (auto it : _old_clients){
        tmp.push_back(it.getClient());
    }
    return tmp;
}

void Petwalker::addToBST(Dog* d) {

    alldogs.insert(d);
}

void Petwalker::addToOld(OldClientsRecords OldClient) {
    _old_clients.insert(OldClient);
}