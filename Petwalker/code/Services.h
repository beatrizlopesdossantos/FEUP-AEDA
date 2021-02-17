#ifndef PETWALKERPROJAEDA_SERVICES_H
#define PETWALKERPROJAEDA_SERVICES_H

#include "Tasks.h"
#include "Date.h"


class Clients;
class Employees;
class Petwalker;


using namespace std;

/** Petwalker Services Class
 *
 * Each object of this class represents a service provided by the Petwalker company.
 */
class Services {
public:

    /**
     * Constructor of class Services.
     *
     * @param client_email - **Client** paying the service.
     * @param exclusive - **Type** of service provided.
     *  - when exclusive is true, the service is exclusive.
     *  - when exclusive is false, the service is collective.
     * @param employee_username  - **Employee** providing the service.
     * @param tasks - **Tasks** to perform during the service.
     * @param startDate - **Date** the service is made.
     * @param name_dog - **Dog**
     * @param petwalker - Enterprise of the service.
     */
    Services(string client_email,bool exclusive, string employee_username, Tasks task, Date startDate, string name_dog, Petwalker* petwalker);
    /**
     * This function is used to get the state of the service, true if completed, false if not.
     * @return **Complete** - state od the service.
     */
    bool isComplete() const;
    /**
     * This function is used to redefine the email of the client.
     */
    void setClientEmail(string email);
    /**
     * This function is used to redefine the username of the employee.
     */
    void setEmployeeUsername(string username);
    /**
     * This function is used to get the type of service. True if exclusive, false if collective.
     * @return **Exclusive**
     */
    bool isExclusive() const;
    /**
     * This function is used to change the state of the service to completed
     */
    vector<Services*> setComplete(bool file);
    /**
     * This function is used to set the starting date.
     * Depending on how long the service will last, sets the ending date.
     */
    void setDates(Date start, int duration);
    /**
     * This function is used to calculate de price of the service
     * @return **Price**
     */
    double getServicePrice() const;
    /**
     * This function is used to obtain a string with the email of the client.
     * @return **Email**
     */
    string getClientEmail() const;
    /**
     * This function is used to obtain a string with the username of the employee.
     * @return **UserName**
     */
    string getEmployeeUsername() const;
    /**
     * This operator is mainly used for search algorithms.
     * It compares the *this* Service with the s2.
     * @param s2 - Services to compare with this.
     * @return true if the services have the same attributes; false if not.
     */
    bool operator==(const Services &s2) const;
    /**
     * This function is used to obtain the date the service starts.
     * @return **InicialDate**
     */
    Date getInitDate() const;
    /**
     * This function is used to obtain the date the service ends.
     * @return **ENDDATE**
     */
    Date getEndDate() const;
    /**
     * This function is used to obtain the task made in the service.
     * @return **Task**
     */
    Tasks getTask() const;
    /**
     * This operator is used to do the output of all the information stored in one client object.
     * @param os - Output stream to show the data of the service on the console.
     * @param s1 - Service to do the output of.
     * @return **o** - Output stream with all the data in the defined parsing(?).
     */
    friend ostream & operator<<(ostream & os, const Services &s1);
    /**
     * This function is used to update the services when the client or the employee is removed.
     * @param type - 1 if the employee no longer exist, 2 if the client no longer exists.
     * @param priceService Price of the service.
     */
    void setServicePriceFile(int type, double priceService);
    /**
     * This function is used to set to complete the shared services of an employee.
     */
    void setSharedComplete();
    /**
     * This function is used to obtain a string with the name of the dog.
     * @return **Dog Name**
     */
    string getNameDog() const;

private:

    bool _complete;
    bool _exclusive;
    pair<Date, Date> _dates;
    string _client_email;
    string _employee_username;
    Tasks _task;
    double _servicePrice;
    string _dog;
    Petwalker* _petwalker;

};




#endif //PETWALKERPROJAEDA_SERVICES_H
