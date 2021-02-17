#ifndef PETWALKERPROJAEDA_EXCEPTIONS_H
#define PETWALKERPROJAEDA_EXCEPTIONS_H


#include <string>

using namespace std;

/** InvalidInput Exception Class
 *
 *  Class to define the exception InvalidInput so that it can be treated later.
 */
class InvalidInput{
private:
    string info = "\n\tInvalid Input - Please try again!\n";
public:
    InvalidInput(){};
    InvalidInput(string msg):info(msg){};
    string getInfo() {return info;};
};

/** ClientDoesNotExist Exception Class
 *
 *  Class to define the exception ClientDoesNotExist so that it can be treated later.
 */
class ClientDoesNotExist{
private:
    string email = "";
    string info = "\n Client " + email + " does not exist!\n";
public:
    ClientDoesNotExist(){};
    ClientDoesNotExist(string email):email(email){};
    string getInfo() {return info;};
};

/** EmployeeDoesNotExist Exception Class
 *
 *  Class to define the exception EmployeeDoesNotExist so that it can be treated later.
 */
class EmployeeDoesNotExist{
private:
    string username = "";
    string info = "\n Employee " + username + " does not exist!\n";
public:
    EmployeeDoesNotExist(){};
    EmployeeDoesNotExist(string username):username(username){};
    string getInfo() {return info;};
};

/** ClientAlreadyExist Exception Class
 *
 *  Class to define the exception ClientAlreadyExist so that it can be treated later.
 */
class ClientAlreadyExist{
private:
    string email = "";
    string info = "\n Client " + email + " already exists! - Use a different email.\n";
public:
    ClientAlreadyExist(){};
    ClientAlreadyExist(string email):email(email){};
    string getInfo() {return info;};
};

/** EmployeeAlreadyExist Exception Class
 *
 *  Class to define the exception EmployeeAlreadyExist so that it can be treated later.
 */
class EmployeeAlreadyExist{
private:
    string username = "";
    string info = "\n Employee " + username + " already exists! - Use a different username.\n";
public:
    EmployeeAlreadyExist(){};
    EmployeeAlreadyExist(string username):username(username){};
    string getInfo() {return info;};
};

/** NoAvailableEmployee Exception Class
 *
 *  Class to define the exception NoAvailableEmployee so that it can be treated later.
 */
class NoAvailableEmployee{
private:
    string info = "\n No available Employee for requested service!\n";

public:
    NoAvailableEmployee(){};
    NoAvailableEmployee(string msg):info(msg){};
    string getInfo() {return info;};
};

/** DateNotValid Exception Class
 *
 *  Class to define the exception DateNotValid so that it can be treated later.
 */
class DateNotValid{
private:
    string info = "\n\tNot a valid date!\n";

public:
    DateNotValid(){};
    DateNotValid(string msg):info(msg){};
    string getInfo() {return info;};
};

/** InvalidServiceType Exception Class
 *
 *  Class to define the exception InvalidServiceType so that it can be treated later.
 */
class InvalidServiceType{
private:
    string info = "\n The Service Type '" + task_n + "' you chose does not exist!\n";
    string task_n = "";
public:
    InvalidServiceType(){};
    InvalidServiceType(string n_task){ task_n = n_task;};
    string getInfo() {return info;};
};

/** ServiceDoesNotExist Exception Class
 *
 *  Class to define the exception ServiceDoesNotExist so that it can be treated later.
 */
class ServiceDoesNotExist{
private:
    string info = "\n The service with the type '" + nametype + "' at date '" + date +"' you chose does not exist!\n";
    string nametype = "";
    string date = ""; //output da classe date
public:
    ServiceDoesNotExist(){};
    ServiceDoesNotExist(string nametype, string date):nametype(nametype), date(date){};
    ServiceDoesNotExist(string msg):info(msg){};
    string getInfo() {return info;};
};

/** ServiceAlreadyExists Exception Class
 *
 *  Class to define the exception ServiceAlreadyExists so that it can be treated later.
 */
class ServiceAlreadyExists{
private:
    string info = "\n\tThat service already exists!\n";
public:
    ServiceAlreadyExists(){};
    ServiceAlreadyExists(string msg):info(msg){};
    string getInfo() {return info;};
};

/** FileNotFound Exception Class
 *
 *  Class to define the exception FileNotFound so that it can be treated later.
 */
class FileNotFound{
private:
    string info = "\n\tFile " + namefile + " not found!\n";
    string namefile = "object.txt";
public:
    FileNotFound(){};
    FileNotFound(string namefile):namefile(namefile){};
    string getInfo() {return info;};
};

/** Empty Vector Exception Class
 *
 *  Class to define the exception EmptyVector so that it can be treated later.
 */
class EmptyVector{
private:
    string info = "\n\tVector is Empty!\n";
    int typeElemVector;
public:
    EmptyVector(){};
    EmptyVector(string inf) : info(inf){};
    EmptyVector(int type_elem) : typeElemVector(type_elem){
        switch (typeElemVector){
            case 0: //Elems of vector are services
                info = "\n\tVector of Services is empty!\n";
                break;
            case 1: //Elems of vector are employees
                info = "\n\tVector of Employees is empty!\n";
                break;
            case 2: //Elems of vector are clients
                info = "\n\tVector of Clients is empty!\n";
                break;
            case 3: //Elems of vector are Availabilities
                info = "\n\tNo Availabilities to show!\n";
                break;
            case 4: //Elems of vector are dogs
                info = "\n\tNo Dogs to show!\n";
                break;
            default:
                info = "\n\tEmpty Vector.\n";
        }
    }
    string getInfo() {return info;};
};

/** AvailAlreadyExists Exception Class
 *
 *  Class to define the exception AvailAlreadyExists so that it can be treated later.
 */
class AvailAlreadyExists{
private:
    string info = "\n\tEmployee " + employee + " is already available at " + hours + " in " + day + "/" + month + "/" + year + "!\n";
    string employee = "user";
    string hours = to_string(0);
    string day = to_string(1);
    string month = to_string(1);
    string year = to_string(2001);
public:
    AvailAlreadyExists(){};
    AvailAlreadyExists(string inf):info(inf){};
    AvailAlreadyExists(string user, int h, int d, int m, int y):employee(user), hours(to_string(h)), day(to_string(d)), month(to_string(m)), year(to_string(y)) {};
    string getInfo() {return info;};
};

/** AvailDoesNotExist Exception Class
 *
 *  Class to define the exception AvailDoesNotExist so that it can be treated later.
 */
class AvailDoesNotExist{
private:
    string info = "\n\tEmployee " + employee + " is not available at " + hours + " in " + day + "/" + month + "/" + year + "!\n";
    string employee = "user";
    string hours = to_string(0);
    string day = to_string(1);
    string month = to_string(1);
    string year = to_string(2001);
public:
    AvailDoesNotExist(){};
    AvailDoesNotExist(string inf):info(inf){};
    AvailDoesNotExist(string user, int h, int d, int m, int y):employee(user), hours(to_string(h)), day(to_string(d)), month(to_string(m)), year(to_string(y)) {};
    string getInfo() {return info;};
};

/** DogAlreadyExist Exception Class
 *
 *  Class to define the exception DogAlreadyExist so that it can be treated later.
 */
class DogAlreadyExist{
private:
    string name = "";
    string clientmail = "";
    string info = "\n Dog " + name + " of client " + clientmail + " already exists!\n";
public:
    DogAlreadyExist(){};
    DogAlreadyExist(string nameD, string email):name(nameD), clientmail(email){};
    string getInfo() {return info;};
};


#endif //PETWALKERPROJAEDA_EXCEPTIONS_H
