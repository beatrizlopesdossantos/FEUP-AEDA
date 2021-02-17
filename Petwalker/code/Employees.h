#ifndef PETWALKERPROJAEDA_EMPLOYEES_H
#define PETWALKERPROJAEDA_EMPLOYEES_H


#include <string>
#include <vector>
class Services;
class Clients;

//-- Parte 2
#include <queue>
#include <algorithm>
#include "Date.h"


using namespace std;

//-- Parte 2
/** Petwalker DateAvail Class
 *
 * Each object of this class represents a slot of the Employee Availabilities Priority queue.
 */
class DateAvail{

public:
    /**
     * The constructor of the class DateAvail.
     * It is the class of objects of the priority queue availability of the employee.
     * @param d - date (hour, day , month, year) of the new slot to add to the priority queue.
     */
    DateAvail(Date d);
    /**
     * This fuction is used to obtain the date defined by the objects DateAvail.
     * @return **Date**
     */
    Date getDate() const;
    /**
     * This operator is used to sort (orderly) the priority queue of Dates Available (slots of the employee).
     * Because in the priotity queue the top is the maximum, we have to define the earliest date as the "biggest value".
     * @param dA - DateAvail to compare with this.
     * @return true if the Date Available of this is later than the of dA.
     */
    bool operator<(const DateAvail &dA ) const;

private:
    Date date;
};
//--

/** Petwalker Employees Class
 *
 * Each object of this class represents a colaborator of the Petwalker company.
 */
class Employees {
public:
    /**
     * Constructor of the class Employees.
     *
     * @param name - **Name** of the employee.
     * @param username - **Username** of the employee (unique)
     * @param type - **Type** of affiliation of the employee.
     *  - when type is equal to 1 the employee is a professional colaborator.
     *  - when type is equal to 2 the employee is a free-time colaborator.
     */
    Employees(string name, string username, int type);
    /**
     * This function is used to obtain a string with the name of the employee.
     * @return **Name** - Name of the said colaborator.
     */
    string getName();
    /**
     * This function is used to obtain a string that corresponds to the type of the employee.
     * @return String corresponding to "Professional" if @ref type equals 1 and "Free-time" if it equals 2.
     *         If @ref type is eaual to other number the function returns "NotDefinedYet".
     */
    string getType();
    /**
     * This function is used to redefine the type of the employee.
     * @param i - **Number** that represents the @ref type of affiliation of the employee.
     */
    void setType(int i);
    /**
     * This function is used to obtain the double number that represents the employees' earnings.
     * @return **MoneyEarned** - The total money earned by the collaborator until the present moment.
     */
    double getEarnings();
    /**
    * This function is used is used to redefine the username of the employee.
    * @param **username** - String that is going to be the username of the employee.
    */
    void setUsername(string username);
    /**
     * This function is used to obtain a string with the username of the employee.
     * @return **Username** - Identifier of the said collaborator.
     */
    string getUsername();
    /**
     * This operator is mainly used for search algorithms.
     * It compares the *this* employee with the e2.
     * @param e2 - Employee to compare with this.
     * @return true if the username is the same; false if not.
     */
    bool operator==(const Employees &e2) const;
    /**
     * This operator is used to do the output of all the information stored in one employee object.
     * @param o - Output stream to show the data of the employee on the console.
     * @param e1 - Employee to do the output of.
     * @return o - Output stream with all the data in the defined parsing.
     */
    friend ostream & operator<<(ostream & os, const Employees &e1);
    /**
     * This function is used to obtain the total number of services completed by this employee
     * @return *NumServicesDone* - Number of services completed by employee.
     */
    int getNumServicesDone();
    /**
     * This function is used to change the number of services an employee has scheduled
     * @param num - Number of services scheduled for the employee.
     */
    void setScheduledServices(int num);
    /**
     * This function is used to obtain the total number of services scheduled for the employee
     * @return *NumScheduledServices* - Number of services scheduled for the employee.
     */
    int getScheduledServices();
    /**
     * This function adds the value passed as argument to the total of money earned by this employee in all his services completed in Petwalker.
     * Also increments the number of services completed by employee. That is obtained by @ref getNumServicesDone.
     * @param money - Value of the earnings of the service completed.
     */
    void addMoneyEarned(double money);

    //-- Parte 2
    /**
     * This function is used to obtain the vector of availableTimes of an Employee. Can be used for output!
     * @return *availableTimes* - Vector of available times for the employee.
     */
    vector<Date> getAvailableTimes();
    /**
     * This function is used to add newSlots to the availability of an Employee.
     * @param Initial -  Initial date (hours, day, month, year) in which the Employee is going to be available for work.
     * @param duration - Amount of time (im minutes) that the employee is available. (>= 60 -> >= 1 slot)
     */
    void addNewSlot(Date Initial, int duration);
    /**
     * This function is used to remove existing slots on the availability of an Employee.
     * @param Initial -  Initial date (hours, day, month, year) in which the Employee is not going to be available for work.
     * @param duration - Amount of time (im minutes) that the employee no longer is available. (>= 60 -> >= 1 slot)
     * @return *found* - boolean variable that is equal to true if the slots were found and removed; false if not.
     */
    bool remSlot(Date Initial, int duration);
    /**
     * This function is used to check if a certain slot exists in the availability of the employee.
     * @param Initial - Initial date (hours, day, month, year) of the slot.
     * @return *exists* - boolean variable that is equal to true if the slot was found; false if not.
     */
    bool slotExists(Date Initial);
    /**
     * This function is used to obtain the top of the availability priority queue.
     * @return *Date* of the slot in first place on the priority_queue.
     */
    Date getTopAvailable();

private:
    string name, username;
    int type, numServicesDone, numScheduledServices;
    double moneyEarned;

    //-- Parte 2
    priority_queue<DateAvail> availability;

};

/** Petwalker EmplAvailable Class
 *
 * Each object of this class represents a slot of the Petwalker Availabilities Priority queue.
 */
class EmplAvailable
{
public:
    /**
     * One of the constructors of class EmplAvailable.
     * It creates a new 'slot' to add to the priority queue in which the date is
     * the top of the Employees' availability priority_queue.
     * @param employee - Pointer to the employee to add.
     */
    EmplAvailable(Employees *employee);
    /**
     * The other constructor of class EmplAvailable.
     * It creates a new 'slot' to add with the date defined by Initial.
     * (and checks if it exists in the availability p.q. of employee.
     * @param employee - Pointer to the employee to add.
     * @param Initial - Initial date (hour, day , month, year) of the new slot to add to the priority queue.
     */
    EmplAvailable(Employees * employee, Date Initial);
    /**
     * This function is used to obtain the pointer to the employee of the slot.
     * @return **Pointer to employee**
     */
    Employees * getEmployee() const;
    /**
     * This function is used to obtain the initial date of the slot.
     * @return **Initial date**
     */
    Date getSlot() const;
    /**
     * This operator is used to sort (orderly) the priority queue of Employees Available.
     * Because in the priotity queue the top is the maximum, we have to define the earliest date as the "biggest value".
     * @param eA - EmplAvailable to compare with this.
     * @return true if the Date Available of this is later than the one from eA - if it is the same we sort by username (alphabetic order); false if not.
     */
    bool operator<(const EmplAvailable& eA) const;
    /**
     * This operator is used to search a value on the priority queue of Employees Available.
     * @param eA - EmplAvailable to compare with this.
     * @return true if the Date Available and the Employee (username) are the same; false if not.
     */
    bool operator==(const EmplAvailable& eA) const;
    /**
     * This operator is used to do the output of all the information stored in one EmplAvailable object.
     * @param o - Output stream to show the data of the employee on the console.
     * @param eA - Employee Available to do the output of.
     * @return o - Output stream with all the data in the defined parsing.
     */
    friend ostream & operator<<(ostream & os, const EmplAvailable &eA);

private:
    Employees *e1;
    Date Available;

};


#endif //PETWALKERPROJAEDA_EMPLOYEES_H

