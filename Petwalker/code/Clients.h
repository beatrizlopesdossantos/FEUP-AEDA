#ifndef PETWALKERPROJAEDA_CLIENTS_H
#define PETWALKERPROJAEDA_CLIENTS_H

#include <iostream>
#include <string>
#include <vector>
class Services;
class Employees;
class Tasks;
class Dog;

using namespace std;


/** Petwalker Clients Class
 *
 * Each object of this class represents a client of the Petwalker company.
 */
class Clients {
private:
    string name;
    int points;
    string category;
    int numServices;
    string email;
    vector<Dog*> dogs;


public:
    /**
     * Constructor of the class Clients.
     *
     * @param n - **Name** of the clients.
     * @param user - **Email** of the clients.
     * @param c - **Category** type of discount that the client can have (silver, gold, platinum).
     * @param p - **Points** points attributed to each client.
     * - the category will depend on the points
     */
    Clients(string n, string e, string c, int p);
    /**
     * This function is used to obtain a string with the name of the client.
     * @return **Name** - Name of the said client.
     */
    string getName();
    /**
     * This function is used to obtain an integer with the number of points corresponding to the client.
     * @return **Points** - Points of the said client.
     */
    int getPoints();
    /**
     * This function is used to redefine the category of the client.
     * - Silver if number of services is equal or higher than 5 and lower than 10;
     * - Gold if points are equal or higher than 10 and lower than 15;
     * - Platinum if points are equal or higher that 15;
     */
    void setCategory();
    /**
     * This function is adds points to the client depending on the services he wanted.
     * By adding this points, the number of services increases.
     * @param pointsAdd - points to add to @ref points.
     */
    void addPoints(int pointsAdd);
    /**
    * This function is used to obtain an integer with the number of services corresponding to the client.
    * @return **Number of services** - Services that the client has done.
    */
    int getNumberServices() const;
    /**
     * this function is used to remove from the @ref points the points that the client used to have a discount.
     * @param points - Points to subtract.
     */
    void usePoints(int pointsDisc);
    /**
     * This function is used to obtain a string with the category of the client.
     * @return **Category** - Category of the said client.
     */
    string getCategory();
    /**
     * This function is used to obtain the email.
     * @return **Email** created for the client.
     */
    string getEmail() const;
    /**
     * This function is used to redefine the email of the client.
     * @param **email** - String that is going to be the email of the client.
     */
    void setEmail(string email);
    /**
     * This operator is mainly used for search algorithms.
     * It compares the *this* Client with the c2.
     * @param c2 Clients to compare with this.
     * @return true if the email are the same; false if not.
     */
    bool operator==(const Clients &c2) const;
    /**
     * This operator is used to do the output of all the information stored in one client object.
     * @param o Output stream to show the data of the client on the console.
     * @param c1 Client to do the output of.
     * @return o - Output stream with all the data in the defined parsing.
     */
    friend ostream & operator<<(ostream & os, const Clients &c1);
    /**
     * This function increments the number of services scheduled by this client that were updated to complete.
     */
    void incrementNumServices();
    /**
     * This function is used to obtain all the dogs that a client has.
     * @return **Dogs** - Vector of the dogs owned by the client.
     */
    vector<Dog*> getDogs();
    /**
     * This function adds a dog to the vector dogs associated with the client.
     */
    void addDog(Dog *d);
    /**
     * This function is used to return the Dog named **name** from the
     * vector of dogs of this client.
     * If the dog is not found, this function throws an exception.
     * (Dog with name **name** was not found!)
     * @param name - **name of the dog**
     * @return Dog* - pointer para o Dog correspondente
     */
    Dog * getDog(string name);

};

/** Petwalker OldClientsRecords Class
 *
 * Each object of this class represents an old client of the Petwalker company.
 */
class OldClientsRecords {

public:
    /**
     * Constructor of class OldClientsRecords
     * This object is used on our HashTable.
     * @param client - Pointer to a client.
     * @param email - email of said client.
     */
    OldClientsRecords(Clients* client, string email);
    /**
     * This function is used to obtain the email of the client that
     * the record represents.
     */
    string getEmail() const;
    /**
     * This function is used to obtain the adress of the client that
     * the record represents.
     */
    Clients *getClient() const;
    /**
     * This function is used to change the email of the client in the Records.
     * @param email - **new client email**
     */
    void setEmail(string email);
    /**
     * This function is used to set the adress of the client in the Records.
     * @param client - **pointer to client**
     */
    void setClient(Clients* client);

private:
    string _email;
    Clients* _client;
};


#endif //PETWALKERPROJAEDA_CLIENTS_H
