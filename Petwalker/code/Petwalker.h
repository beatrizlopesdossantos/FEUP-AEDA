#ifndef PETWALKERPROJAEDA_PETWALKER_H
#define PETWALKERPROJAEDA_PETWALKER_H

#include <vector>
#include <unordered_set>
#include "Services.h"
#include "Clients.h"
#include "Employees.h"
#include "Exceptions.h"
#include "Date.h"
#include "Dog.h"
#include "BST.h"


//-- Parte 2
#include <queue>

using namespace std;

/**
 * OldClientsRecordsHash
 * Operators for the OldClientsHashTable
 */
struct OldClientsRecordsHash {

    /**
     * Operator to atribute the place on the Hash Table
     */
    int operator()(const OldClientsRecords& ar) const {
        int v = 0;
        for (unsigned int i = 0; i < ar.getEmail().size();i++)
            v = 37*v+ar.getEmail()[i];
        return v;
    }

    /**
     * Equality Operator
     */
    bool operator()(const OldClientsRecords& ar1, const OldClientsRecords& ar2) const {
        return ar1.getEmail() == ar2.getEmail();
    }
};

/**
 * Define The Type HashTableOldClients from the unorderedSet with our operators
 */
typedef unordered_set<OldClientsRecords, OldClientsRecordsHash, OldClientsRecordsHash> HashTableOldClients;

/** Petwalker Class
 *
 * Each object of this class represents one company.
 */
class Petwalker {
public:
    /**
     * Constructor of class Petwalker
     */
    Petwalker();
    /**
     * Destructor of class Petwalker
     * Calls the function @ref loadFiles to iniciate the program.
     */
    ~Petwalker();
    /**
     * This function is used to obtain an integer with the points necessary to have discount.
     * @return **DiscountPoints** Points to have discount.
     */
    int getDiscountPoints() const;
    /**
     * This function is used to redefine the number of points necessary to have discount.
     * @param points integer that is going to be the number of points necessary to have discount.
     */
    void setDiscountPoints(const int points);
    /**
     * This function is used to obtain an integer with the number that the price of the service will be multiplied if exclusive.
     * @return **ExclusiveCost** Exclusive cost.
     */
    double getExclusiveCost();
    /**
     * This function is used to redefine the cost change if exclusive.
     * @param cost integer that is going to be the new exclusive cost.
     */
    void setExclusiveCost(const double cost);
    /**
     * This function is used to obtain the number of the limit of non-exclusive services of the same task a employee can do simultaneously.
     * @return **NotExclusiveLimit** Limit of simultaneous non-exclusive identical services.
     */
    int getNotExclusiveLimit();
    /**
     *This function is used to redefine the limit of simultaneous non-exclusive services a employee can do.
     * @param cost integer of the limit
     */
    void setNotExclusiveLimit(const int cost);
    /**
     * This function is used to obtain the profit(%) per service.
     * @return **Profit** Profit(%) per service.
     */
    double getProfit() const;
    /**
     * This function is used to redefine the Profit(1 + profit(%)) per service.
     * @param cost double of the profit to set.
     */
    void setProfit(const double cost);
    /**
     * This function is used to obtain the cost per hour of a Professional employee.
     * @return **ProfessionalCost** Professional cost per hour
     */
    double getProfessionalCost() const;
    /**
     * This function is used to redefine the cost per hour of a Professional employee.
     * @param cost double that is going to be the cost per hour of a Professional employee.
     */
    void setProfessionalCost(const double cost);
    /**
     * This function is used to obtain the cost per hour of a part-time employee.
     * @return **PartTimeCost** Part-time cost per hour
     */
    double getPartTimeCost() const;
    /**
     * This function is used to redefine the cost per hour of a part-time employee.
     * @param cost double that is going to be the cost per hour of a part-time employee.
     */
    void setPartTimeCost(const double cost);
    /**
     * This function is used to obtain the cost of the task Veterinary.
     * @return **VeterinaryCost** Cost of the task Veterinary.
     */
    double getVeterinaryCost() const;
    /**
     * This function is used to redefine the cost of the task Veterinary.
     * @param cost double that is going to be the cost of the task Veterinary.
     */
    void setVeterinaryCost(const double cost);
    /**
     * This function is used to obtain the cost of the task Bath.
     * @return **BathCost** Cost of the task Bath.
     */
    double getBathCost() const;
    /**
     * This function is used to redefine the cost of the task Bath.
     * @param cost double that is going to be the cost of the task Bath.
     */
    void setBathCost(const double cost);
    /**
     * This function is used to obtain the cost of the task Cut Fur.
     * @return **CutFurCost** Cost of the task Cut Fur.
     */
    double getCutFurCost() const;
    /**
     * This function is used to redefine the cost of the task Cut Fur.
     * @param cost double that is going to be the cost of the task Cut Fur.
     */
    void setCutFurCost(const double cost);
    /**
     * This function is used to obtain the cost of the task Walk.
     * @return **WalkCost** Cost of the task Walk.
     */
    double getWalkCost() const;
    /**
     * This function is used to redefine the cost of the task Walk.
     * @param cost double that is going to be the cost of the task Walk.
     */
    void setWalkCost(const double cost);
    /**
     * This function is used to obtain the cost of the task Obedience Class.
     * @return **ObedienceClassCost** Cost of the task Obedience Class.
     */
    double getObedienceClassCost() const;
    /**
     * This function is used to redefine the cost of the task Obedience Class.
     * @param cost double that is going to be the cost of the task Obedience Class.
     */
    void setObedienceClassCost(const double cost);
    /**
     * This function is used to obtain the cost per point.
     * @return **CostPerPoint** Cost of the points.
     */
    int getCostPerPoint() const;
    /**
     * This function is used to redefine the cost per point.
     * @param cost double that is going to be the cost of the points.
     */
    void setCostPerPoint(const int cost);
    /**
     * This function is used to load the files with the company's information.
     */
    void loadFiles();
    /**
     * This function is used to save the files with the recently changed company's information.
     */
    void saveFiles();
    /**
     * This function is used to create a task.
     * @param task_name - Task wanting to be created.
     */
    Tasks createTask(string task_name);
    /**
     * This function is used to get the cost of the task wanted.
     * @param task - Task that the function will depend on.
     * @return **TaskCost** Cost of the said task.
     */
    double getTaskCost(Tasks task);
    /**
     * This function is used to obtain the client depending on the email. If there is no client with that email, throws an exception.
     * @param email - Clients's email.
     * @return **Client** that has the same email.
     */
    Clients* getClient(string email);
    /**
     * This function is used to obtain the employee depending on the username. If there is no employee with that username, throws an exception.
     * @param username - Employee's username.
     * @return **Employee** that has the same username.
     */
    Employees* getEmployee(string username);
    /**
     * This function is used to obtain the vector of employees of the company.
     * @return **Employees** that the company has.
     */
    vector<Employees*> getEmployees() const;
    /**
     * This function is used to obtain the vector of all the services done of the company.
     * @return **Services Done** that the company has.
     */
    vector<Services*> getServicesDone() const;
    /**
     * This function is used to obtain the vector of all the services done of the company that involved
     * the client identified by username.
     * @param username - Identifier of the client.
     * @return **Services Done for Client with 'username'** that the company has.
     */
    vector<Services*> getClientServicesDone(string email);
    /**
      * This function is used to obtain the vector of all the services done by
      * the employee identified by username on the company.
      * @param username - Identifier of the employee.
      * @return **Services Done by Employee with 'username'** that the company has.
      */
    vector<Services*> getEmployeeServicesDone(string username);
    /**
     * This function is used to obtain the vector of all the services done on a certain day.
     * All Parameters work to define the day in which we search the services.
     * @param day
     * @param month
     * @param year
     * @return **Services Done on the date chosen** that the company has.
     */
    vector<Services*> getDateServicesDone(int day, int month, int year);
    /**
    * This function is used to obtain the vector of all the services scheduled of the company.
    * @return **Services Scheduled** that the company has.
    */
    vector<Services*> getScheduledServices() const;
    /**
     * This function is used to obtain the vector of all the services scheduled for
     * the client identified by email on the company.
     * @param email - Identifier of the client.
     * @return **Services Scheduled for Client with 'email'** that the company has.
     */
    vector<Services*> getClientScheduledServices(string email);
    /**
      * This function is used to obtain the vector of all the services scheduled
      * to be done by the employee identified by username on the company.
      * @param username - Identifier of the employee.
      * @return **Services Scheduled for the Employee with 'username'** that the company has.
      */
    vector<Services*> getEmployeeScheduledServices(string username);
    /**
      * This function is used to obtain the vector of all the services scheduled
      * to be done by the employee identified by username on the company on a certain date.
      * It is mainly used for the control of the 'choice' of the employee on a new service.
      * @param username - Identifier of the employee.
      * @param date - Date in which to search the scheduled services.
      * @return **Services Scheduled for the Employee with 'username' on 'date'** that the company has.
      */
    vector<Services*> getEmployeeScheduledServices(string username,Date date);
    /**
     * This function is used to obtain the vector of all the services scheduled for a certain day.
     * All Parameters work to define the day in which we search the services.
     * @param day
     * @param month
     * @param year
     * @return **Services Scheduled for the date chosen** that the company has.
     */
    vector<Services*> getDateScheduledServices(int day, int month, int year);
    /**
     * This function is used to obtain the vector of clients of the company.
     * @return **Clients** that the company has.
     */
    vector<Clients*> getClients() const;
    /**
     * This function is used to add a new Client to the company.
     * It checks if a client with the same email already exists.
     *   - If that happens it throws the Exception @ref ClientAlreadyExists.
     *   - Else it allows the addition of that client to the
     *    vector of clients that the company has.
     * @param c1 - **New Client** to add
     * @param d1 - **New Dog** to add to the client
     */
    void addClient(Clients *c1);
    /**
     * This function is used to remove a Client of the company.
     * It checks if a client with the same email exists.
     *   - If that happens that client is erased from the vector, all the
     *   scheduled services that he had are also erased and in the services that were
     *   already done for that client we substitute it's email for "NoMoreAClient".
     *   - Else it throws the exception @ref ClientDoesNotExist and catches
     *   it displaying the exception message.
     * @param email - **email** of the client to remove.
     */
    void removeClient(string email);
    /**
     * This function is mainly used after @ref CreateService and it adds
     * the new service to the scheduled services vector.
     * @param service - **New Service** to add to the scheduled services that the company has.
     */
    void addScheduledService(Services* service);
    /**
     * This function is mainly used in @ref Services::setComplete().
     * It removes the service identified by the parameter of the vector of Scheduled Services.
     * If it does not exist in the vector it throws the exception @ref ServiceDoesNotExist.
     * @param service
     */
    void removeScheduledService(Services* service);
    /**
     * This function is mainly used in @ref Services::setComplete().
     * It adds the service identified by the parameter to the vector of Services Done-
     * @param service
     */
    void addServiceDone(Services* service);
    /**
     * This function is used to add a new Employee to the company.
     * It checks if a employee with the same username already exists.
     *   - If that happens it throws the Exception @ref EmployeeAlreadyExists.
     *   - Else it allows the addition of that employee to the
     *    vector of employees that the company has.
     * @param e1 - **New Employee** to add
     */
    void addEmployee(Employees *e1);
    /**
     * This function is used to remove a Employee of the company.
     * It checks if a employee with the same username exists.
     *   - If that happens that employee is erased from the vector, all the
     *   scheduled services that he had are also erased (?) and in the services that were
     *   already done by that employee we substitute it's username for "NoMoreAEmployee".
     *   - Else it throws the exception @ref EmployeeDoesNotExist and catches
     *   it displaying the exception message.
     * @param username - **Username** of the employee to remove.
     */
    void removeEmployee(string username);
    /**
     * This function is used for 3 different things identified by parameter **id**:
     *    0 - Create a new Scheduled Service;
     *    1 - Choose a Scheduled Service to delete;
     *    2 (or any other int) - Choose a Scheduled Service to update to done;
     * Inside it we ask for all the parameters needed to create said service:
     * Client email, Employee Username (?), type of Task, Date and Exclusivity.
     * @param id - identifier of the **Create a service mode**
     * @return **Pointer** for the **new Service**
     */
    Services* createService(int id);
    /**
     * This function is used to create a new Employee.
     * Inside it we ask for all the parameters needed to create said employee:
     * Employee Name (only two), Employee Username and Type of Employee (1 - Professional, 2 - Free-time).
     * @return **Pointer** for the **new Employee**
     */
    Employees* createEmployee();
    /**
     * This function is used to create a new Client.
     * Inside it we ask for all the parameters needed to create said client:
     * Client Name (only two) and Client email.
     * @return **Pointer** for the **new Client**
     */
    Clients* createClient();
    /**
     * This function is used to check if we are able to create a new service of the same task
     * and exclusivity (preferably shared) on the date identified by the parameter date.
     * @param date
     * @param exclusive - Value true or false: True = the service is exclusive; False = the service is shared;
     * @param task - type of task of the service;
     * @param pq - bool that informs if it is a search to create with the priority queue also (Part 2)
     * @return **Username** of the approved **employee** for the service.
     */
    string checkDate(Date date, bool exclusive, Tasks task, bool pq);
    /**
     * This function is used to obtain the vector of all the services done of a certain type of Task.
     * @param task_name - Type of task of the services done we want to search.
     * @return
     */
    vector<Services*> getTaskServicesDone(string task_name);
    /**
     * This function is used to obtain the vector of all the services scheduled of a certain type of Task.
     * @param task_name - Type of task of the scheduled services we want to search.
     * @return
     */
    vector<Services*> getTaskScheduledServices(string task_name);

    //-- Parte 2
    /**
     * This function is used to obtain the vector of EmplAvailable that is equal to the priority queue.
     * @return *res* - Vector of EmplAvailable objects.
     */
    vector<EmplAvailable>  getEmplAvail();
    /**
     * This function is used to add new availabilities to the priority queue.
     * @param e1 - Employee with the new availability
     * @param Initial - Date of the new slot that is going to be added on the pq.
     */
    void addNewAvail(Employees *e1, Date Initial);
    /**
     * This function is used to remove an availability from the priority queue.
     * @param e1 - Employee with the availability
     * @param Initial - Date of the slot that is going removed from the pq.
     * @return *found* - boolean variable that is equal to true if the eA was found and removed; false if not.
     */
    bool remAvail(Employees *e1, Date Initial);
    /**
     * This function is used to obtain the top of the priority_queue of EmplAvail and remove it.
     * @return **Employee Available Earliest**
     */
    EmplAvailable getEmployeeMostAvail();
    /**
     * This function is used to obtain the Employee that is most available on day from the priority_queue of EmplAvail and remove it.
     * It is used also to obtain the employee and the hours to schedule a new Service.
     * @param day - Date (day, month, year) in which to search a available employee.
     * @param type_Ser - Type of task of the service being scheduled
     * @return **Employee Available Earliest on day**
     */
    EmplAvailable getEmplMostAvail(Date hours, Tasks task);
    /**
     * This function is used to obtain a vector of dogs of the same month of birth
     * from the BST.
     * @param d - Date that has the month to search.
     * @return **vector of dog* **
     */
    vector<Dog*> findSameBirthDogs(Date d);
    /**
     * This function is used to obtain a vector of dogs of the breed
     * from the BST.
     * @param r - Breed to search.
     * @return **vector of dog* **
     */
    vector<Dog*> findSameRaceDogs(string r);
    /**
     * This function is used to obtain the necessary input to create a dog
     * for the client defined by c.
     * @param c - **pointer to the client**
     * @return **Dog * ** created
     */
    Dog* createDog(Clients *c);
    /**
     * This function is used to add a dog that was previously created to the
     * client referenced by the pointer c1.
     */
    void addDogToClient(Clients *c1, Dog *d);
    /**
     * This function is used to obtain the vector of dogs (dog *) that are
     * present on the BST. (mainly for output)
     */
    vector<Dog*> getDogs();
    /**
     * This function is used to set the new date for Last Service on the dog
     * referenced by the pointer d with owner pointed by c1.
     * Because the Dog objects are pointers and the Last Service Date does not
     * influence the order of the Binary Search Tree this function alters that value
     * with no colateral issues.
     */
    void getLastService(Clients *c1, Dog *d);
    /**
     * This function is used to alter the email of the client that has the old_email.
     * If it is an Old Client, this function calls @ref OldClientsRecords::setEmail() also.
     * @param old_email - current email to allow the access to the client in question.
     * @param new_email - email to substitute the previous one
     */
    void changeEmail(string old_email, string new_email);
    /**
     * This function is used to obtain the vector of Clients (Clients *) that are
     * present on the HashTableOldClients.
     */
    vector<Clients*> getOldClients();
    /**
     * This function is used to add a dog that has one complete service to
     * the BST of dogs.
     */
    void addToBST(Dog* d);
    /**
     * This function adds a new Old Client to the hash table
     */
    void addToOld(OldClientsRecords OldClient);



private:
    int _cost_per_point;
    int _discount_points;
    int _notexclusivelimit;
    double _profit;
    double _exclusive_cost;
    double _professional_cost;
    double _part_time_cost;
    double _veterinary_cost;
    double _bath_cost;
    double _cut_fur_cost;
    double _walk_cost;
    double _obedience_class_cost;
    vector<Services*> _services_done;
    vector<Services*> _scheduled_services;
    vector<Clients*> _clients;
    vector<Employees*> _employees;

    //-- Parte 2
    priority_queue<EmplAvailable> EmplAvail;
    BST<Dog*> alldogs;
    HashTableOldClients _old_clients;

};

#endif //PETWALKERPROJAEDA_PETWALKER_H
