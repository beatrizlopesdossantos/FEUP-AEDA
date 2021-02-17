#ifndef PETWALKERPROJAEDA_DOG_H
#define PETWALKERPROJAEDA_DOG_H

#include <iostream>
#include <string>
#include "Date.h"
#include "Clients.h"

using namespace std;

/** Petwalker Dog Class
 *
 * Each object of this class represents a dog of the Petwalker company.
 */
class Dog {
private:
    string name;
    string race;
    Date birth;
    Clients *owner;
    Services *lastService = nullptr;
public:
    /**
    * Constructor of the class Dog.
    *
    * @param n - **Name** of the dog.
    * @param r - **Race** of the dog.
    * @param b - **Birth** of the dog.
    */
    Dog(string n, string r, Date b);
    /**
     * This function is used to obtain a string with the name of the dog.
     * @return **Name** - Name of the said dog.
     */
    string getName() const;
    /**
     * This function is used to obtain a string with the race of the dog.
     * @return **Race** - Race of the said dog.
     */
    string getRace() const;
    /**
     * This function is used to obtain the date of birth of the dog.
     * @return **Date** - Date of birth of the said dog.
     */
    Date getBirth() const;
    /**
     * This function is used to set the owner of the dog.
     * @param **Client** - Client that will become the owner of the dog.
     */
    void setOwner(Clients *c);
    /**
     * This function is used to obtain the name of the owner.
     * @return **Name** of the owner.
     */
    string getOwnerName() const;
    /**
     * This function is used to obtain the email of the owner.
     * @return **Email** of the owner.
     */
    string getOwnerEmail() const;
    /**
     * This function is used to sort the BST.
     * @param d1 dog to be compared with this.
     */
    bool operator < (const Dog &d1) const;
    /**
     * This operator is mainly used for search algorithms.
     * It compares the *this* Dog with the d1.
     * @param d1 Dog to compare with this.
     * @return true if the name, race, birth and owner's name is the same, false if not
     */
    bool operator ==(const Dog &d1) const;
    /**
     * This function is used to obtain the last service that the dog has done.
     * @return **Service** made.
     */
    Services * getLastService() const;
    /**
     * This function is used to set the last service that the dog has done.
     * @param **Service** made.
     */
    void setLastService(Services *s1);
    /**
     * This operator is used to do the output of all the important information stored in one dog object.
     * @param o Output stream to show the data of the dog on the console.
     * @param d1 Dog to do the output of.
     * @return o - Output stream with all the data in the defined parsing.
     */
    friend ostream & operator<<(ostream & os, const Dog &d1);
};


#endif //PETWALKERPROJAEDA_DOG_H
