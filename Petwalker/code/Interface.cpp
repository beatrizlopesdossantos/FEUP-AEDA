#include "Interface.h"


#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

//para usar os pointers
class Services;
class Employees;
class Clients;
class Dog;

extern Petwalker PW;
using namespace std;

bool beginning(){
    string num, msg;
    bool power_off = false;

    while(true)
    {
        cout << "\n\t\t  PetWalker System Interface";
        cout << "\n------------------------------------------------------------------";
        cout << "\n  What would you like to do?";
        cout << "\n   1 - Create a new object";
        cout << "\n   2 - Read a collection of existing objects";
        cout << "\n   3 - Update an object";
        cout << "\n   4 - Search for services";
        cout << "\n   5 - Delete an object";
        cout << "\n   6 - Save all current objects to files";
        cout << "\n   0 - Exit System Interface";
        cout << "\n  Insert the number corresponding to your choice: ";


        try {
            getline(cin, num);
            if (num.size() > 1)
                throw InvalidInput("\n Invalid Input - Please input a number next time!\n");
            else if ( ((stoi(num)) < 0) || (stoi(num)) >= 7)
                throw InvalidInput();
            else
                break;
        }
        catch (InvalidInput &e)
        {
            cout << e.getInfo();
            continue;
        }
        catch (...)
        {
            cout << "\n Invalid Input - Please try again!\n";
            continue;
        }
    }

    switch(stoi(num)){
        case 1:
            power_off = create();
            break;
        case 2:
            power_off = read();
            break;
        case 3:
            power_off = update();
            break;
        case 4:
            power_off = search();
            break;
        case 5:
            power_off = obj_delete();
            break;
        case 6:
            power_off = saveFile();
            break;
        case 0:
            power_off = exit(true);
            break;
        default:
            cout << "\nNo harm done - Nothing done actually!\n";
            break;
    }

    return power_off;

}

bool create()
{
    string num, msg;
    int type_data;

    while(1) {
        cout << "\n---------------------------- Create Mode ----------------------------";
        cout << "\n  What type of data would you like to create?";
        cout << "\n   1 - A Service";
        cout << "\n   2 - A Employee";
        cout << "\n   3 - A Client";
        cout << "\n   4 - A Dog";
        cout << "\n  Insert the number corresponding to your choice:";

        try {
            getline(cin, num);
            if (num.size() > 1)
                throw InvalidInput("\n Invalid Input - Please input a number next time!\n");
            else if (((stoi(num)) <= 0) || (stoi(num)) >= 5)
                throw InvalidInput();
            else
                break;
        }
        catch (InvalidInput &e) {
            cout << e.getInfo();
            continue;
        }
        catch (...) {
            cout << "\n Invalid Input - Please try again!\n";
            continue;
        }
    }

    type_data = stoi(num);
    string userClient;
    Clients *c;
    switch(type_data)
    {
        case 1:
            while(1)
            {
                try{
                    Services *s1 = PW.createService(0);
                    PW.addScheduledService(s1);

                    cout << "\n\tCreated the service successfully!\n";
                    break;
                }
                catch(ServiceAlreadyExists &e){
                    cout << "\n\t" << e.getInfo() << endl;

                    while(true)
                    {
                        cout << "\n  Do you want to try again?";
                        cout << "\n   1 - Yes" << "\t2 - No";
                        cout << "\n  Insert the number corresponding to your choice:";
                        try {
                            getline(cin, num);
                            if (num.size() > 1 || num.empty())
                                throw InvalidInput("\n Invalid Input - Please input a number next time!\n");
                            else if ( ((stoi(num)) <= 0) || (stoi(num)) >= 3)
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
                    if(stoi(num) == 2)
                        break;
                }
            }
            break;
        case 2:
            while(1)
            {
                try{
                    Employees *e1 = PW.createEmployee();
                    PW.addEmployee(e1);
                    cout << "\n\tCreated the employee successfully!\n";
                    break;
                }
                catch(EmployeeAlreadyExist &e){
                    cout << "\n\t" << e.getInfo() << endl;

                    while(true)
                    {
                        cout << "\n  Do you want to try again?";
                        cout << "\n   1 - Yes" << "\t2 - No";
                        cout << "\n  Insert the number corresponding to your choice:";
                        try {
                            getline(cin, num);
                            if (num.size() > 1 || num.empty())
                                throw InvalidInput("\n Invalid Input - Please input a number next time!\n");
                            else if ( ((stoi(num)) <= 0) || (stoi(num)) >= 3)
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
                    if(stoi(num) == 2)
                        break;
                }
            }
            break;
        case 3:
            while(1)
            {
                try{
                    Clients *c1 = PW.createClient();
                    Dog *d1 = PW.createDog(c1);
                    PW.addClient(c1);
                    PW.addDogToClient(c1, d1);
                    cout << "\n\tCreated the client successfully!\n";
                    break;
                }
                catch(ClientAlreadyExist &e){
                    cout << "\n\t" << e.getInfo() << endl;

                    while(true)
                    {
                        cout << "\n  Do you want to try again?";
                        cout << "\n   1 - Yes" << "\t2 - No";
                        cout << "\n  Insert the number corresponding to your choice:";
                        try {
                            getline(cin, num);
                            if (num.size() > 1 || num.empty())
                                throw InvalidInput("\n Invalid Input - Please input a number next time!\n");
                            else if ( ((stoi(num)) <= 0) || (stoi(num)) >= 3)
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
                    if(stoi(num) == 2)
                        break;
                }
            }
            break;
        case 4:

            while (1) {
                try {
                    while (1) {
                        cout << "\n  Insert the email of the Client to add a dog: ";

                        try {
                            getline(cin, userClient);

                            for (int i = 0; i < userClient.size(); i++) {
                                if (userClient[i] == ' ')
                                    throw InvalidInput("Invalid email input! Please try again.");
                            }

                            break;
                        }
                        catch (InvalidInput &e) {
                            cout << e.getInfo();
                            continue;
                        }
                        catch (...) {
                            cout << "\n Invalid Input - Please try again!\n";
                            continue;
                        }

                    }
                    c = PW.getClient(userClient);
                    break;
                }
                catch (ClientDoesNotExist &e) {
                    cout << "\n\t" << e.getInfo() << endl;
                    while (true) {
                        cout << "\n  Do you want to try again?";
                        cout << "\n   1 - Yes" << "\t2 - No";
                        cout << "\n  Insert the number corresponding to your choice:";
                        try {
                            getline(cin, num);
                            if (num.size() > 1 || num.empty())
                                throw InvalidInput("\n Invalid Input - Please input a number next time!\n");
                            else if (((stoi(num)) <= 0) || (stoi(num)) >= 3)
                                throw InvalidInput();
                            else
                                break;
                        }
                        catch (InvalidInput &e) {
                            cout << e.getInfo();
                            continue;
                        }
                    }
                    if (stoi(num) == 2)
                        break;
                }
            }
            while(1) {
                try {
                    Dog *d1 = PW.createDog(c);
                    PW.addDogToClient(c, d1);
                    cout << "\n\tCreated the dog successfully!\n";
                    break;
                }
                catch (DogAlreadyExist &e) {
                    cout << "\n\t" << e.getInfo() << endl;

                while(true)
                {
                    cout << "\n  Do you want to try again?";
                    cout << "\n   1 - Yes" << "\t2 - No";
                    cout << "\n  Insert the number corresponding to your choice:";
                    try {
                        getline(cin, num);
                        if (num.size() > 1 || num.empty())
                            throw InvalidInput("\n Invalid Input - Please input a number next time!\n");
                        else if ( ((stoi(num)) <= 0) || (stoi(num)) >= 3)
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
                if(stoi(num) == 2)
                    break;
        }
            }
            break;
        default:
            break;
    }

    if (!exit(false))
    {

        cout << "\n\t Returning to menu...\n";
        _sleep(1000);
        return false;
    }
    else
        return true;
}

bool read()
{
    string num, msg;
    int type_data;

    while(1) {
        cout << "\n---------------------------- Read Mode ----------------------------";
        cout << "\n  What would you like to do?";
        cout << "\n   1 - View Completed Services";
        cout << "\n   2 - View Scheduled Services";
        cout << "\n   3 - View all Employees";
        cout << "\n   4 - View all Clients";
        cout << "\n                      -- PART 2 OF PROJECT --";
        cout << "\n   5 - View Employee Availability"; //read the priority queue availability of an Employee
        cout << "\n   6 - View all the Availabilities"; //read the priority queue EmplAvail
        cout << "\n   7 - View Dogs"; //read the BST
        cout << "\n   8 - View Old Clients"; //read the Hash Table
        cout << "\n  Insert the number corresponding to your choice:";


        try {
            getline(cin, num);
            if (num.size() > 1)
                throw InvalidInput("\n Invalid Input - Please input a number next time!\n");
            else if (((stoi(num)) <= 0) || (stoi(num)) >= 9)
                throw InvalidInput();
            else
                break;
        }
        catch (InvalidInput &e) {
            cout << e.getInfo();
            continue;
        }
        catch (...) {
            cout << "\n Invalid Input - Please try again!\n";
            continue;
        }
    }

    type_data = stoi(num);
    int type_sort;

    if(type_data == 1)
    {
        while(1)
        {
            cout << "\n---------------------------- Completed Services ----------------------------";
            cout << "\n  How would you like to sort the vector?";
            cout << "\n   1 - Sort by Date";
            cout << "\n   2 - Sort by price (if == by date)";
            cout << "\n   3 - Sort by task (if == by date)";
            cout << "\n  Insert the number corresponding to your choice:";
            try {
                getline(cin, num);
                if (num.size() > 1)
                    throw InvalidInput("\n Invalid Input - Please input a number next time!\n");
                else if (((stoi(num)) <= 0) || (stoi(num)) >= 4)
                    throw InvalidInput();
                else
                    break;
            }
            catch (InvalidInput &e) {
                cout << e.getInfo();
                continue;
            }
            catch (...) {
                cout << "\n Invalid Input - Please try again!\n";
                continue;
            }
        }
        type_sort = stoi(num);

        vector<Services*>output = PW.getServicesDone();

        //switch para os sorts com lambdas
        switch(type_sort)
        {
            case 1:
                sort(output.begin(), output.end(), [](Services *s1, Services *s2){
                    return (s1->getInitDate() < s2->getInitDate());
                });
                break;
            case 2:
                sort(output.begin(), output.end(), [](Services *s1, Services *s2){
                    if(s1->getServicePrice() == s2->getServicePrice())
                        return (s1->getInitDate() < s2->getInitDate());
                    else
                        return (s1->getServicePrice() < s2->getServicePrice());
                });
                break;
            case 3:
                sort(output.begin(), output.end(), [](Services *s1, Services *s2) {
                    if (s1->getTask().getTaskName() == s2->getTask().getTaskName())
                        return (s1->getInitDate() < s2->getInitDate());
                    else
                        return (s1->getTask().getTaskName() < s2->getTask().getTaskName());
                });
                break;
            default:
                break;
        }
        //Output do vetor em tabela

        try{
            if(output.empty()) throw EmptyVector(0);
            else
            {
                cout << "\n\t\t\t\t\tPetWalker Completed Services\n";

                cout << "------------------------------------------------------------------------------------------------------------------------";
                cout << "        Date              Task         Exclusive?    Client Email     NameDog      Employee Username      Service Price\n";
                cout << "------------------------------------------------------------------------------------------------------------------------";                for (int i = 0; i < output.size(); i++)
                {
                    cout << *(output.at(i));
                }
                cout << "------------------------------------------------------------------------------------------------------------------------\n";                cout << "\t\t Total number of completed services of PetWalker = " << output.size() << endl;
            }
        }
        catch (EmptyVector &e)
        {
            cout << "\n   " << e.getInfo() << endl;
        }
    }
    else if(type_data == 2)
    {
        while(1)
        {
            cout << "\n---------------------------- Scheduled Services ----------------------------";
            cout << "\n  How would you like to sort the vector?";
            cout << "\n   1 - Sort by Date";
            cout << "\n   2 - Sort by task (if == by date)";
            cout << "\n  Insert the number corresponding to your choice:";
            try {
                getline(cin, num);
                if (num.size() > 1)
                    throw InvalidInput("\n Invalid Input - Please input a number next time!\n");
                else if (((stoi(num)) <= 0) || (stoi(num)) >= 3)
                    throw InvalidInput();
                else
                    break;
            }
            catch (InvalidInput &e) {
                cout << e.getInfo();
                continue;
            }
            catch (...) {
                cout << "\n Invalid Input - Please try again!\n";
                continue;
            }
        }
        type_sort = stoi(num);

        vector<Services*>output = PW.getScheduledServices();

        //switch para os sorts com lambdas
        switch(type_sort)
        {
            case 1:
                sort(output.begin(), output.end(), [](Services *s1, Services *s2){
                    return (s1->getInitDate() < s2->getInitDate());
                });
                break;
            case 2:
                sort(output.begin(), output.end(), [](Services *s1, Services *s2) {
                    if (s1->getTask().getTaskName() == s2->getTask().getTaskName())
                        return (s1->getInitDate() < s2->getInitDate());
                    else
                        return (s1->getTask().getTaskName() < s2->getTask().getTaskName());
                });
                break;
            default:
                break;
        }

        //Output do vetor em tabela

        try{
            if(output.empty()) throw EmptyVector(0);
            else
            {
                cout << "\n\t\t\t\t\tPetWalker Scheduled Services\n";

                cout << "------------------------------------------------------------------------------------------------------------------------";
                cout << "        Date              Task         Exclusive?    Client Email     NameDog      Employee Username      Service Price\n";
                cout << "------------------------------------------------------------------------------------------------------------------------";
                for (int i = 0; i < output.size(); i++)
                {
                    cout << *(output.at(i));
                }
                cout << "------------------------------------------------------------------------------------------------------------------------\n";
                cout << "\t\t Total number of scheduled services of PetWalker = " << output.size() << endl;
            }
        }
        catch (EmptyVector &e)
        {
            cout << "\n   " << e.getInfo() << endl;
        }
    }
    else if(type_data == 3)
    {
        while(1)
        {
            cout << "\n---------------------------- Employees ----------------------------";
            cout << "\n  How would you like to sort the vector?";
            cout << "\n   1 - Sort by username";
            cout << "\n   2 - Sort by name (if == by username)";
            cout << "\n   3 - Sort by moneyEarned (if == by username)";
            cout << "\n   4 - Sort by number of Services Done (if == by username)";
            cout << "\n  Insert the number corresponding to your choice:";
            try {
                getline(cin, num);
                if (num.size() > 1)
                    throw InvalidInput("\n Invalid Input - Please input a number next time!\n");
                else if (((stoi(num)) <= 0) || (stoi(num)) >= 5)
                    throw InvalidInput();
                else
                    break;
            }
            catch (InvalidInput &e) {
                cout << e.getInfo();
                continue;
            }
            catch (...) {
                cout << "\n Invalid Input - Please try again!\n";
                continue;
            }
        }
        type_sort = stoi(num);

        vector<Employees*>output = PW.getEmployees();

        //switch para os sorts com lambdas
        switch(type_sort)
        {
            case 1:
                sort(output.begin(), output.end(), [](Employees *e1, Employees *e2){
                    return (e1->getUsername() < e2->getUsername());
                });
                break;
            case 2:
                sort(output.begin(), output.end(), [](Employees *e1, Employees *e2){
                    if(e1->getName() == e2->getName())
                        return (e1->getUsername() < e2->getUsername());
                    else
                        return (e1->getName() < e2->getName());
                });
                break;
            case 3:
                sort(output.begin(), output.end(), [](Employees *e1, Employees *e2){
                    if(e1->getEarnings() == e2->getEarnings())
                        return (e1->getUsername() < e2->getUsername());
                    else
                        return (e1->getEarnings() < e2->getEarnings());
                });
                break;
            case 4:
                sort(output.begin(), output.end(),[](Employees *e1, Employees *e2){
                    if(e1->getNumServicesDone() == e2->getNumServicesDone())
                    {
                        return (e1->getUsername() < e2->getUsername());
                    }
                    else return (e1->getNumServicesDone() < e2->getNumServicesDone());
                });
                break;
            default:
                break;
        }
        //Output do vetor em tabela

        try{
            if(output.empty()) throw EmptyVector(1);
            else
            {
                cout << "\n\t\t\t    PetWalker Employees\n";

                cout << "-----------------------------------------------------------------------------------------";
                cout << "\n Username           Name                    Type           ServicesDone    moneyEarned\n";
                cout << "-----------------------------------------------------------------------------------------\n";
                for (int i = 0; i < output.size(); i++)
                {
                    cout << *(output.at(i));
                }
                cout << "-----------------------------------------------------------------------------------------\n";
                cout << "\t Total number of employees of PetWalker = " << output.size() << endl;
            }
        }
        catch (EmptyVector &e)
        {
            cout << "\n   " << e.getInfo() << endl;
        }
    }
    else if (type_data == 4)
    {
        while(1)
        {
            cout << "\n---------------------------- Clients ----------------------------";
            cout << "\n  How would you like to sort the vector?";
            cout << "\n   1 - Sort by email";
            cout << "\n   2 - Sort by name (if == by email)";
            cout << "\n   3 - Sort by points (if == by email)";
            cout << "\n   4 - Sort by number of Services Requested (if == by email)";
            cout << "\n  Insert the number corresponding to your choice:";
            try {
                getline(cin, num);
                if (num.size() > 1)
                    throw InvalidInput("\n Invalid Input - Please input a number next time!\n");
                else if (((stoi(num)) <= 0) || (stoi(num)) >= 5)
                    throw InvalidInput();
                else
                    break;
            }
            catch (InvalidInput &e) {
                cout << e.getInfo();
                continue;
            }
            catch (...) {
                cout << "\n Invalid Input - Please try again!\n";
                continue;
            }
        }
        type_sort = stoi(num);

        vector<Clients*>output = PW.getClients();

        //switch para os sorts com lambdas
        switch(type_sort)
        {
            case 1:
                sort(output.begin(), output.end(), [](Clients *c1, Clients *c2) {
                    return (c1->getEmail() < c2->getEmail());
                });
                break;
            case 2:
                sort(output.begin(), output.end(), [](Clients *c1, Clients *c2){
                    if(c1->getName() == c2->getName())
                        return (c1->getEmail() < c2->getEmail());
                    else
                        return (c1->getName() < c2->getName());
                });
                break;
            case 3:
                sort(output.begin(), output.end(),[](Clients *c1, Clients *c2){
                    if(c1->getPoints() == c2->getPoints())
                        return (c1->getEmail() < c2->getEmail());
                    else
                        return (c1->getPoints() < c2->getPoints());
                });
                break;
            case 4:
                sort(output.begin(), output.end(), [](Clients *c1, Clients *c2){
                    if(c1->getNumberServices() == c2->getNumberServices())
                        return (c1->getEmail() < c2->getEmail());
                    else
                        return (c1->getNumberServices() < c2->getNumberServices());
                });
                break;
            default:
                break;
        }
        //Output do vetor em tabela

        try{
            if(output.empty()) throw EmptyVector(2);
            else
            {
                cout << "\n\t\t\tPetWalker Clients\n";

                cout << "------------------------------------------------------------------------------------------";
                cout << "\n  Email                    Name                Category        Points     ServicesDone\n";
                cout << "------------------------------------------------------------------------------------------\n";
                for (int i = 0; i < output.size(); i++)
                {
                    cout << *(output.at(i));
                }
                cout << "------------------------------------------------------------------------------------------\n";
                cout << "\t Total number of clients of PetWalker = " << output.size() << endl;
            }
        }
        catch (EmptyVector &e)
        {
            cout << "\n   " << e.getInfo() << endl;
        }
    }
    else if (type_data == 5)
    {
        //read the vector of availabilities of a employee

        string userEmployee;
        Employees* e = nullptr;
        //ask for user name & read the vector from the stack
        while(1) {
            try {
                while (1) {
                    cout << "\n\t         Employee Availability \n";
                    cout << "--------------------------------------------------------------";
                    cout << "\n  Insert the username of the Employee to search: ";

                    try {
                        getline(cin, userEmployee);

                        for (int i = 0; i < userEmployee.size(); i++) {
                            if (userEmployee[i] == ' ')
                                throw InvalidInput("Invalid username input! Please try again.");
                        }

                        break;
                    }
                    catch (InvalidInput &e) {
                        cout << e.getInfo();
                        continue;
                    }
                    catch (...) {
                        cout << "\n Invalid Input - Please try again!\n";
                        continue;
                    }
                }

                e = PW.getEmployee(userEmployee);
                break;
            }
            catch (EmployeeDoesNotExist &e) {
                cout << "\n\t" << e.getInfo() << endl;
                while (true) {
                    cout << "\n  Do you want to try again?";
                    cout << "\n   1 - Yes" << "\t2 - No";
                    cout << "\n  Insert the number corresponding to your choice:";
                    try {
                        getline(cin, num);
                        if (num.size() > 1 || num.empty())
                            throw InvalidInput("\n Invalid Input - Please input a number next time!\n");
                        else if (((stoi(num)) <= 0) || (stoi(num)) >= 3)
                            throw InvalidInput();
                        else
                            break;
                    }
                    catch (InvalidInput &e) {
                        cout << e.getInfo();
                        continue;
                    }
                }
                if (stoi(num) == 2)
                    break;
            }
        }

        vector<Date> output = e->getAvailableTimes();

        try{
            if(output.empty()) throw EmptyVector(3);
            else
            {
                cout << "\n\t" << userEmployee << " Availability \n";
                cout << "------------------------------------------";
                cout << "\n   Num                  Date\n";
                cout << "------------------------------------------\n";
                for (int i = 0; i < output.size(); i++)
                {
                    cout << "    " << (i+1) << "            ";
                    if(i+1 < 10)
                        cout << " ";
                    cout << output.at(i) << endl;
                }
                cout << "------------------------------------------\n";
                cout << " Total of slots available of " << userEmployee << " = " << output.size() << endl;

            }
        }
        catch (EmptyVector &e)
        {
            cout << "\n   " << e.getInfo() << endl;
        }
    }
    else if (type_data == 6)
    {
        //read the vector that is equal to the priority queue (EmplAvail)

        cout << "\n\t              All Availabilities \n";
        cout << "--------------------------------------------------------------";
        cout << "\n  The order in which the values appear is the order in";
        cout << "\n which they appear on the priority queue.\n";
        cout << "--------------------------------------------------------------\n";

        _sleep(1000);

        vector<EmplAvailable> output = PW.getEmplAvail();

        try{
            if(output.empty()) throw EmptyVector(3);
            else
            {
                cout << "\n\t              All Availabilities \n";
                cout << "--------------------------------------------------------------";
                cout << "\n   Num               Date                 Employee Username\n";
                cout << "--------------------------------------------------------------\n";
                for (int i = 0; i < output.size(); i++)
                {
                    cout << "    " << (i+1) << "            ";
                    if(i+1 < 10)
                        cout << " ";
                    cout << output.at(i) << endl;
                }
                cout << "--------------------------------------------------------------\n";
                cout << "\t Total number of slots available = " << output.size() << endl;

            }
        }
        catch (EmptyVector &e)
        {
            cout << "\n   " << e.getInfo() << endl;
        }
    }
    else if (type_data == 7) //view dogs
    {
        while(1)
        {
            cout << "\n---------------------------- Dogs ----------------------------";
            cout << "\n  What would you like to see?";
            cout << "\n   1 - View Dogs that have completed at least one service";
            cout << "\n   2 - View dogs by client";
            cout << "\n   3 - View dogs by race that have completed at least one service";
            cout << "\n   4 - View dogs by month of birth that have completed at least one service";
            cout << "\n  Insert the number corresponding to your choice:";
            try {
                getline(cin, num);
                if (num.size() > 1)
                    throw InvalidInput("\n Invalid Input - Please input a number next time!\n");
                else if (((stoi(num)) <= 0) || (stoi(num)) >= 5)
                    throw InvalidInput();
                else
                    break;
            }
            catch (InvalidInput &e) {
                cout << e.getInfo();
                continue;
            }
            catch (...) {
                cout << "\n Invalid Input - Please try again!\n";
                continue;
            }
        }
        type_sort = stoi(num);

        vector<Dog*> output;

        string search;
        Date toSearch;

        switch (type_sort) {
            case 1:
                output = PW.getDogs();
                break;
            case 2:
                //ask client
                Clients *c;
                while (1) {
                    try {
                        while (1) {
                            cout << "\n  Insert the email of the Client to read the dogs: ";

                            try {
                                getline(cin, search);

                                for (int i = 0; i < search.size(); i++) {
                                    if (search[i] == ' ')
                                        throw InvalidInput("Invalid email input! Please try again.");
                                }

                                break;
                            }
                            catch (InvalidInput &e) {
                                cout << e.getInfo();
                                continue;
                            }
                            catch (...) {
                                cout << "\n Invalid Input - Please try again!\n";
                                continue;
                            }

                        }
                        c = PW.getClient(search);
                        break;
                    }
                    catch (ClientDoesNotExist &e) {
                        cout << "\n\t" << e.getInfo() << endl;
                        while (true) {
                            cout << "\n  Do you want to try again?";
                            cout << "\n   1 - Yes" << "\t2 - No";
                            cout << "\n  Insert the number corresponding to your choice:";
                            try {
                                getline(cin, num);
                                if (num.size() > 1 || num.empty())
                                    throw InvalidInput("\n Invalid Input - Please input a number next time!\n");
                                else if (((stoi(num)) <= 0) || (stoi(num)) >= 3)
                                    throw InvalidInput();
                                else
                                    break;
                            }
                            catch (InvalidInput &e) {
                                cout << e.getInfo();
                                continue;
                            }
                        }
                        if (stoi(num) == 2)
                            break;
                    }
                }
                output = c->getDogs();

                break;
            case 3:
                //ask race
                while (1) {
                    cout << "\n  Insert the race of dogs to read: ";

                    try {
                        getline(cin, search);

                        for (int i = 0; i < search.size(); i++) {
                            if (search[i] == ' ')
                                throw InvalidInput("Invalid email input! Please try again.");
                        }

                        break;
                    }
                    catch (InvalidInput &e) {
                        cout << e.getInfo();
                        continue;
                    }
                    catch (...) {
                        cout << "\n Invalid Input - Please try again!\n";
                        continue;
                    }
                }
                output = PW.findSameRaceDogs(search);
                break;
            case 4:
                //ask birth
                while (1) {
                    string input;
                    stringstream dateinput;
                    int month;

                    cout << "\n  Insert the month of birth of dogs to search in format MM: ";

                    try {
                        getline(cin, input);
                        dateinput << input;
                        dateinput >> month;

                        toSearch =  Date(1, month, 2001, 00, 00);
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
                output = PW.findSameBirthDogs(toSearch);
                break;
            default:
                break;
        }


        //Output do vetor em tabela

        try{
            if(output.empty()) throw EmptyVector(4);
            else
            {
                cout << "\n\t\t\t\t  Petwalker Dogs\n";
                cout << "------------------------------------------------------------------------------------------------------";
                cout << "\n  OwnerName                Name          Breed              DateOfBirth            DateLastService\n";
                cout << "------------------------------------------------------------------------------------------------------\n";
                for (int i = 0; i < output.size(); i++)
                {
                    cout << *(output.at(i));
                }
                cout << "------------------------------------------------------------------------------------------------------\n";
                cout << "\t\t Total number of Dogs listed = " << output.size() << endl;
            }
        }
        catch (EmptyVector &e)
        {
            cout << "\n   " << e.getInfo() << endl;
        }
    }
    else if (type_data == 8)
    {
        while(1)
        {
            cout << "\n---------------------------- Old Clients ----------------------------";
            cout << "\n  What would you like to see?";
            cout << "\n   1 - Sort Old Clients by email";
            cout << "\n   2 - Sort Old Clients by name (if == by email)";
            cout << "\n   3 - View Old Clients by points (if == by email)";
            cout << "\n   4 - View Old Clients by last service(if == by email)";
            cout << "\n  Insert the number corresponding to your choice:";
            try {
                getline(cin, num);
                if (num.size() > 1)
                    throw InvalidInput("\n Invalid Input - Please input a number next time!\n");
                else if (((stoi(num)) <= 0) || (stoi(num)) >= 5)
                    throw InvalidInput();
                else
                    break;
            }
            catch (InvalidInput &e) {
                cout << e.getInfo();
                continue;
            }
            catch (...) {
                cout << "\n Invalid Input - Please try again!\n";
                continue;
            }
        }
        //read OldClients
        type_sort = stoi(num);

        vector<Clients*>output = PW.getOldClients();

        //switch para os sorts com lambdas
        switch(type_sort)
        {
            case 1:
                sort(output.begin(), output.end(), [](Clients *c1, Clients *c2) {
                    return (c1->getEmail() < c2->getEmail());
                });
                break;
            case 2:
                sort(output.begin(), output.end(), [](Clients *c1, Clients *c2){
                    if(c1->getName() == c2->getName())
                        return (c1->getEmail() < c2->getEmail());
                    else
                        return (c1->getName() < c2->getName());
                });
                break;
            case 3:
                sort(output.begin(), output.end(),[](Clients *c1, Clients *c2){
                    if(c1->getPoints() == c2->getPoints())
                        return (c1->getEmail() < c2->getEmail());
                    else
                        return (c1->getPoints() < c2->getPoints());
                });
                break;
            case 4:
                sort(output.begin(), output.end(), [](Clients *c1, Clients *c2){
                    if(PW.getClientServicesDone(c1->getEmail()).at(PW.getClientServicesDone(c1->getEmail()).size()-1)->getInitDate() == PW.getClientServicesDone(c1->getEmail()).at(PW.getClientServicesDone(c1->getEmail()).size()-1)->getInitDate())
                        return (c1->getEmail() < c2->getEmail());
                    else
                        return (PW.getClientServicesDone(c1->getEmail()).at(PW.getClientServicesDone(c1->getEmail()).size()-1)->getInitDate() < PW.getClientServicesDone(c1->getEmail()).at(PW.getClientServicesDone(c1->getEmail()).size()-1)->getInitDate());
                });
                break;
            default:
                break;
        }


        try{
            if(output.empty()) throw EmptyVector(2);
            else
            {
                cout << "\n\t\t\tPetWalker Clients\n";

                cout << "-------------------------------------------------------------------------------------";
                cout << "\n  Email              Name             Category        Points     ServicesDone\n";
                cout << "-------------------------------------------------------------------------------------\n";
                for (int i = 0; i < output.size(); i++)
                {
                    cout << *(output.at(i));
                }
                cout << "-------------------------------------------------------------------------------------\n";
                cout << "\t Total number of clients of PetWalker = " << output.size() << endl;
            }
        }
        catch (EmptyVector &e)
        {
            cout << "\n   " << e.getInfo() << endl;
        }

    }

    if (!exit(false))
    {

        cout << "\n\t Returning to menu...\n";
        _sleep(1000);
        return false;
    }
    else
        return true;
}

bool update()
{
    string num, msg, sprice;
    int type_data;
    double price;

    while(1) {
        cout << "\n---------------------------- Update Mode ----------------------------";
        cout << "\n  What would you like to do?";
        cout << "\n   1 - Set a Service to Complete";
        cout << "\n   2 - Update values of the price table";
        cout << "\n                      -- PART 2 OF PROJECT --";
        cout << "\n   3 - Add new availability for an Employee";
        cout << "\n   4 - Remove availability for an Employee";
        cout << "\n   5 - Update Client email";
        cout << "\n   6 - Set Client to Old Client";
        cout << "\n  Insert the number corresponding to your choice:";

        try {
            getline(cin, num);
            if (num.size() > 1)
                throw InvalidInput("\n Invalid Input - Please input a number next time!\n");
            else if (((stoi(num)) <= 0) || (stoi(num)) >= 7)
                throw InvalidInput();
            else
                break;
        }
        catch (InvalidInput &e) {
            cout << e.getInfo();
            continue;
        }
        catch (...) {
            cout << "\n Invalid Input - Please try again!\n";
            continue;
        }
    }

    type_data = stoi(num);
    Clients* c1;
    string emailClient, oldemail, newemail;
    vector<Services*> servicesDoneDog;
    vector<Services*> servicesDone;
    switch(type_data) {
        case 1:
            while(1)
            {
                try{
                    Services *s1 = PW.createService(2);
                    servicesDone = s1->setComplete(0);
                    for (auto sd: servicesDone) {
                        c1 = PW.getClient(sd->getClientEmail());
                        for (auto s: PW.getClientServicesDone(c1->getEmail())) {
                            if (s->getNameDog() == sd->getNameDog()) {
                                servicesDoneDog.push_back(s);
                            }
                        }
                        if (servicesDoneDog.size() == 1) {
                            PW.addToBST(c1->getDog(sd->getNameDog()));
                        }
                        servicesDoneDog.clear();
                    }
                    cout << "\n\tUpdated the service to done successfully!\n";
                    break;
                }
                catch(ServiceDoesNotExist &e){
                    cout << "\n\t" << e.getInfo() << endl;

                    while(true)
                    {
                        cout << "\n  Do you want to try again?";
                        cout << "\n   1 - Yes" << "\t2 - No";
                        cout << "\n  Insert the number corresponding to your choice:";
                        try {
                            getline(cin, num);
                            if (num.size() > 1 || num.empty())
                                throw InvalidInput("\n Invalid Input - Please input a number next time!\n");
                            else if ( ((stoi(num)) <= 0) || (stoi(num)) >= 3)
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
                    if(stoi(num) == 2)
                        break;
                }
            }
            break;
        case 2:
            while(1) {
                cout << "\n---------------------------- Update Values ----------------------------";
                cout << "\n  What would you like to do?";
                cout << "\n   0  - Update Petwalkers' Profit per service (%)";
                cout << "\n   1  - Update Cost per point";
                cout << "\n   2  - Update Points necessary to have discount";
                cout << "\n   3  - Update Professional employee cost";
                cout << "\n   4  - Update Part-time employee cost";
                cout << "\n   5  - Update Veterinary Price";
                cout << "\n   6  - Update Bath Price";
                cout << "\n   7  - Update Cut Fur Price";
                cout << "\n   8  - Update Walk Price";
                cout << "\n   9  - Update Obedience Class Price";
                cout << "\n   10 - Update Exclusives' increment of price";
                cout << "\n   11 - Update Not Exclusive limit os simultaneous services";

                cout << "\n  Insert the number corresponding to your choice:";

                try {
                    getline(cin, num);
                    if (num.size() > 2)
                        throw InvalidInput("\n Invalid Input - Please input a number next time!\n");
                    else if (((stoi(num)) < 0) || (stoi(num)) > 11)
                        throw InvalidInput();
                    else
                        break;
                }
                catch (InvalidInput &e) {
                    cout << e.getInfo();
                    continue;
                }
                catch (...) {
                    cout << "\n Invalid Input - Please try again!\n";
                    continue;
                }
            }
            type_data = stoi(num);

            while(1) {
                cout << "\n  Insert the new value:";

                try {
                    getline(cin, sprice);
                    if(sprice.empty())
                        throw InvalidInput("\n Invalid Input - Please input a number next time!\n");
                    cout << "\n\t New value updated successfully!\n";
                    break;
                }
                catch (InvalidInput &e) {
                    cout << e.getInfo();
                    continue;
                }
                catch (...) {
                    cout << "\n Invalid Input - Please try again!\n";
                    continue;
                }
            }
            price = stod(sprice);

            switch(type_data) {
                case 0:
                    PW.setProfit(price);
                    break;
                case 1:
                    PW.setCostPerPoint(price);
                    break;
                case 2:
                    PW.setDiscountPoints(price);
                    break;
                case 3:
                    PW.setProfessionalCost(price);
                    break;
                case 4:
                    PW.setPartTimeCost(price);
                    break;
                case 5:
                    PW.setVeterinaryCost(price);
                    break;
                case 6:
                    PW.setBathCost(price);
                    break;
                case 7:
                    PW.setCutFurCost(price);
                    break;
                case 8:
                    PW.setWalkCost(price);
                    break;
                case 9:
                    PW.setObedienceClassCost(price);
                    break;
                case 10:
                    PW.setExclusiveCost(price);
                case 11:
                    PW.setNotExclusiveLimit(price);
                default:
                    break;
            }
            break;
        case 3:
            while (1) {

                //add new availability
                string userEmployee;
                Employees *em;
                Date Initial;
                int duration = 60;

                cout << "\n\t              Add Availabilities to employee \n";
                cout << "-----------------------------------------------------------------------------------------\n";

                while (1) {
                    cout << "\n  Insert the username of the employee that will have new available hours: ";


                    try {
                        getline(cin, userEmployee);
                        em = PW.getEmployee(userEmployee);
                        for (int i = 0; i < userEmployee.size(); i++) {
                            if (userEmployee[i] == ' ')
                                throw InvalidInput("Invalid username input! Please try again.");
                        }
                        if (userEmployee.empty())
                            throw InvalidInput("\n\tInvalid input! Please try again.\n");

                        break;
                    }
                    catch (EmployeeDoesNotExist &e) {
                        cout << e.getInfo();
                        continue;
                    }
                    catch (InvalidInput &e) {
                        cout << e.getInfo() << endl;
                        continue;
                    }
                    catch (...) {
                        cout << "\n\tInvalid Input - Please try again!\n";
                        continue;
                    }
                }
                while (1) {
                    string input;
                    stringstream dateinput;
                    int hours, day, month, year, minutes = 0;

                    cout << "\n  Insert the data in format DD MM YYYY hh: ";

                    try {
                        getline(cin, input);
                        dateinput << input;
                        dateinput >> day >> month >> year >> hours >> minutes;

                        Initial = Date(day, month, year, hours, minutes);

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
                while (1) {
                    string input;
                    stringstream Dur_input;

                    cout << "\n  Insert the duration of the availability (>= 60 minutes): ";

                    try {
                        getline(cin, input);
                        Dur_input << input;
                        Dur_input >> duration;

                        if (duration < 60)
                            throw InvalidInput();
                        break;
                    }
                    catch (...) {
                        cout << "\n\tInvalid Input - Please try again!\n";
                        continue;
                    }
                }

                try {
                    em->addNewSlot(Initial, duration);

                    for (int i = 0; i < (duration / 60); i++) {
                        PW.addNewAvail(em, Initial);
                        Initial.addTime(60);
                    }

                    cout << "\n\tNew availability created successfully!\n";

                    break;
                }
                catch (AvailAlreadyExists &e) {
                    cout << e.getInfo();
                }
                catch (...){
                    cout << "\n\tCould not create Availability!\n";
                }

                while (true) {
                    cout << "\n  Do you want to try again?";
                    cout << "\n   1 - Yes" << "\t2 - No";
                    cout << "\n  Insert the number corresponding to your choice:";
                    try {
                        getline(cin, num);
                        if (num.size() > 1 || num.empty())
                            throw InvalidInput("\n Invalid Input - Please input a number next time!\n");
                        else if (((stoi(num)) <= 0) || (stoi(num)) >= 3)
                            throw InvalidInput();
                        else
                            break;
                    }
                    catch (InvalidInput &e) {
                        cout << e.getInfo();
                        continue;
                    }
                }
                if (stoi(num) == 2)
                    break;
            }
            break;
        case 4:
        while(1){
            //remove availability
            string userEmployee;
            Employees *em;
            Date Initial;
            int duration = 60;

            cout << "\n\t              Remove Availabilities from employee \n";
            cout << "-----------------------------------------------------------------------------------------\n";

            while (1) {
                cout << "\n  Insert the username of the employee that wants to remove available hours: ";


                try {
                    getline(cin, userEmployee);
                    em = PW.getEmployee(userEmployee);
                    for (int i = 0; i < userEmployee.size(); i++) {
                        if (userEmployee[i] == ' ')
                            throw InvalidInput("Invalid username input! Please try again.");
                    }
                    if (userEmployee.empty())
                        throw InvalidInput("\n\tInvalid input! Please try again.\n");

                    break;
                }
                catch (EmployeeDoesNotExist &e) {
                    cout << e.getInfo();
                    continue;
                }
                catch (InvalidInput &e) {
                    cout << e.getInfo() << endl;
                    continue;
                }
                catch (...) {
                    cout << "\n\tInvalid Input - Please try again!\n";
                    continue;
                }
            }
            while (1) {
                string input;
                stringstream dateinput;
                int hours, day, month, year, minutes = 0;

                cout << "\n  Insert the data of the slot in format DD MM YYYY hh: ";

                try {
                    getline(cin, input);
                    dateinput << input;
                    dateinput >> day >> month >> year >> hours >> minutes;

                    Initial = Date(day, month, year, hours, minutes);

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

            try {

                if(em->remSlot(Initial, 60)) {
                    if(PW.remAvail(em, Initial))
                    {
                        cout << "\n\tAvailability removed successfully!\n";
                        break;
                    }
                    else
                    {
                        em->addNewSlot(Initial, 60);
                    }
                }
                cout << "\n\tCould not remove Availability!\n";

            }
            catch (AvailAlreadyExists &e) {
                cout << "\n\tCould not remove Availability!\n";
            }
            catch (...){
                cout << "\n\tCould not remove Availability!\n";
            }

            while (true) {
                cout << "\n  Do you want to try again?";
                cout << "\n   1 - Yes" << "\t2 - No";
                cout << "\n  Insert the number corresponding to your choice:";
                try {
                    getline(cin, num);
                    if (num.size() > 1 || num.empty())
                        throw InvalidInput("\n Invalid Input - Please input a number next time!\n");
                    else if (((stoi(num)) <= 0) || (stoi(num)) >= 3)
                        throw InvalidInput();
                    else
                        break;
                }
                catch (InvalidInput &e) {
                    cout << e.getInfo();
                    continue;
                }
            }
            if (stoi(num) == 2)
                break;
        }
        break;
        case 5:
            cout << "\n\t                      Change Client's Email \n";
            cout << "-----------------------------------------------------------------------------------------\n";
            //função para alterar o email do cliente
            while (1) {
                cout << "\n  Insert the email of the client that wants to change email: ";


                try {
                    getline(cin, emailClient);
                    c1 = PW.getClient(emailClient);
                    for (int i = 0; i < emailClient.size(); i++) {
                        if (emailClient[i] == ' ')
                            throw InvalidInput("Invalid username input! Please try again.");
                    }
                    if (emailClient.empty())
                        throw InvalidInput("\n\tInvalid input! Please try again.\n");
                    oldemail = emailClient;
                    break;
                }
                catch (ClientDoesNotExist &e) {
                    cout << e.getInfo();
                    continue;
                }
                catch (InvalidInput &e) {
                    cout << e.getInfo() << endl;
                    continue;
                }
                catch (...) {
                    cout << "\n\tInvalid Input - Please try again!\n";
                    continue;
                }
            }
            while (1) {
                cout << "\n  Insert the new email to be set on the client: ";

                try {
                    getline(cin, emailClient);
                    PW.getClient(emailClient);
                    for (int i = 0; i < emailClient.size(); i++) {
                        if (emailClient[i] == ' ')
                            throw InvalidInput("Invalid username input! Please try again.");
                    }
                    if (emailClient.empty())
                        throw InvalidInput("\n\tInvalid input! Please try again.\n");
                    cout << "\n\tClient already exists\n";
                    while (true) {
                        cout << "\n  Do you want to try again?";
                        cout << "\n   1 - Yes" << "\t2 - No";
                        cout << "\n  Insert the number corresponding to your choice:";
                        try {
                            getline(cin, num);
                            if (num.size() > 1 || num.empty())
                                throw InvalidInput("\n Invalid Input - Please input a number next time!\n");
                            else if (((stoi(num)) <= 0) || (stoi(num)) >= 3)
                                throw InvalidInput();
                            else
                                break;
                        }
                        catch (InvalidInput &e) {
                            cout << e.getInfo();
                            continue;
                        }
                        if (stoi(num) == 2)
                            break;
                    }
                }
                catch (ClientDoesNotExist &e) {
                    newemail = emailClient;
                    PW.changeEmail(oldemail,newemail);
                    cout << "\n\tEmail updated successfully!\n";
                    break;
                }
                catch (InvalidInput &e) {
                    cout << e.getInfo() << endl;
                    continue;
                }
                catch (...) {
                    cout << "\n\tInvalid Input - Please try again!\n";
                    continue;
                }
            }
            break;
        case 6:
            while(1) {
                cout << "\n\t                         Set Client to Old  \n";
                cout << "-----------------------------------------------------------------------------------------\n";
                //função para alterar o email do cliente
                string emailClient;
                Clients *cl;
                while (1) {
                    cout << "\n  Insert the email of the client that wants to set to old: ";
                    try {
                        getline(cin, emailClient);
                        cl = PW.getClient(emailClient);
                        for (int i = 0; i < emailClient.size(); i++) {
                            if (emailClient[i] == ' ')
                                throw InvalidInput("Invalid username input! Please try again.");
                        }
                        if (emailClient.empty())
                            throw InvalidInput("\n\tInvalid input! Please try again.\n");
                        break;
                    }
                    catch (ClientDoesNotExist &e) {
                        cout << e.getInfo();
                        continue;
                    }
                    catch (InvalidInput &e) {
                        cout << e.getInfo() << endl;
                        continue;
                    }
                    catch (...) {
                        cout << "\n\tInvalid Input - Please try again!\n";
                        continue;
                    }
                }
                if(PW.getClientScheduledServices(cl->getEmail()).size() != 0 || (PW.getClientScheduledServices(cl->getEmail()).size() == 0 && PW.getClientServicesDone(cl->getEmail()).size() == 0)){
                    cout << "\n\t\tClient can´t be set to Old\n";
                }
                else if(find(PW.getOldClients().begin(),PW.getOldClients().end(),cl) != PW.getOldClients().end()){
                    cout << "\n\t\tClient is already Old\n";
                }
                else{
                    Date tmp = PW.getClientServicesDone(cl->getEmail()).at(PW.getClientServicesDone(cl->getEmail()).size()-1)->getInitDate();
                    tmp.addMonth();
                    Date now;
                    if (now < tmp){
                        cout << "\n\t\tClient can´t be set to Old\n";
                    }
                    else {
                        OldClientsRecords temp(cl,cl->getEmail());
                        PW.addToOld(temp);
                        cout << "\n\tClient updated successfully!\n";
                        break;
                    }
                }
                while (true) {
                    cout << "\n  Do you want to try again?";
                    cout << "\n   1 - Yes" << "\t2 - No";
                    cout << "\n  Insert the number corresponding to your choice:";
                    try {
                        getline(cin, num);
                        if (num.size() > 1 || num.empty())
                            throw InvalidInput("\n Invalid Input - Please input a number next time!\n");
                        else if (((stoi(num)) <= 0) || (stoi(num)) >= 3)
                            throw InvalidInput();
                        else
                            break;
                    }
                    catch (InvalidInput &e) {
                        cout << e.getInfo();
                        continue;
                    }
                }
                if (stoi(num) == 2)
                    break;
            }
            break;
        default:
            break;
    }

    if (!exit(false))
    {

        cout << "\n\t Returning to menu...\n";
        _sleep(1000);
        return false;
    }
    else
        return true;
}

bool search() {
    string num, msg;
    int type_data;

    while (1) {
        cout << "\n---------------------------- Search Mode ----------------------------";
        cout << "\n  What would you like to do?";
        cout << "\n   1 - Search for the services in a certain day";
        cout << "\n   2 - Search for the services of a certain task";
        cout << "\n   3 - Search for the services of an Employee";
        cout << "\n   4 - Search for the services of a Client";
        cout << "\n  Insert the number corresponding to your choice:";

        try {
            getline(cin, num);
            if (num.size() > 1)
                throw InvalidInput("\n Invalid Input - Please input a number next time!\n");
            else if (((stoi(num)) <= 0) || (stoi(num)) >= 5)
                throw InvalidInput();
            else
                break;
        }
        catch (InvalidInput &e) {
            cout << e.getInfo();
            continue;
        }
        catch (...) {
            cout << "\n Invalid Input - Please try again!\n";
            continue;
        }
    }

    type_data = stoi(num);
    int type_search;
    string task_name;
    string userEmployee;
    string userClient;
    vector<Services *> outputC;
    vector<Services *> outputD;
    vector<Services *> outputE;
    switch (type_data) {
        case 1:
            int day, month, year;
            while (1) {
                string input;
                stringstream dateinput;

                cout << "\n  Insert the data in format DD MM YYYY: ";

                try {
                    getline(cin, input);
                    dateinput << input;
                    dateinput >> day >> month >> year;
                    break;
                }
                catch (DateNotValid &e) {
                    cout << e.getInfo();
                    continue;
                }
                catch (...) {
                    cout << "\n Invalid Input - Please try again!\n";
                    continue;
                }
            }
            cout << "\n---------------------------- Search by Date ----------------------------";
            cout << "\n  Which type of service would you like to see?";
            cout << "\n   1 - Scheduled Services";
            cout << "\n   2 - Completed Services";
            cout << "\n  Insert the number corresponding to your choice:";
            while (1) {
                try {
                    getline(cin, num);
                    if (num.size() > 1)
                        throw InvalidInput("\n Invalid Input - Please input a number next time!\n");
                    else if (((stoi(num)) <= 0) || (stoi(num)) >= 3)
                        throw InvalidInput();
                    else
                        break;
                }
                catch (InvalidInput &e) {
                    cout << e.getInfo();
                    continue;
                }
                catch (...) {
                    cout << "\n Invalid Input - Please try again!\n";
                    continue;
                }
            }

            type_search = stoi(num);
            switch (type_search) {
                case 1:
                    outputD = PW.getDateScheduledServices(day, month, year);
                    break;
                case 2:
                    outputD = PW.getDateServicesDone(day, month, year);
                    break;
                default:
                    break;
            }
            //Output do vetor em tabela
            try {
                if (outputD.empty()) throw EmptyVector(0);
                else {
                    cout << "\n\t\t\t\t\tPetWalker Services on " << day << "/" << month << "/" << year << "\n";

                    cout << "------------------------------------------------------------------------------------------------------------------------";
                    cout << "        Date              Task         Exclusive?    Client Email     NameDog      Employee Username      Service Price\n";
                    cout << "------------------------------------------------------------------------------------------------------------------------";
                    for (int i = 0; i < outputD.size(); i++) {
                        cout << *(outputD.at(i));
                    }
                    cout << "------------------------------------------------------------------------------------------------------------------------\n";
                    cout << "\t\t Total number of services on " << day << "/" << month << "/" << year << " = " << outputD.size() << endl;
                }
            }
            catch (EmptyVector &e) {
                cout << "\n   " << e.getInfo() << endl;
            }

            break;
        case 2:
            while (1) {
                cout << "\n  Insert the name of the task (Veterinary, Bath, CutFur, Walk, ObedienceClass): ";

                try {
                    getline(cin, task_name);

                    //loop para fazer tudo letras minusculas
                    for (size_t i = 0; i < task_name.size(); i++) {
                        task_name[i] = tolower(task_name[i]);
                    }

                    if (task_name == "veterinary") {
                        task_name = "Veterinary";
                    } else if (task_name == "bath") {
                        task_name = "Bath";
                    } else if (task_name == "cutfur") {
                        task_name = "CutFur";
                    } else if (task_name == "walk") {
                        task_name = "Walk";
                    } else if (task_name == "obedienceclass") {
                        task_name = "ObedienceClass";
                    } else {
                        throw InvalidInput("\n\tInvalid Task Name input! Please try again.\n");
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

            cout << "\n---------------------------- Search by Task Name ----------------------------";
            cout << "\n  Which type of service would you like to see?";
            cout << "\n   1 - Scheduled Services";
            cout << "\n   2 - Completed Services";
            cout << "\n  Insert the number corresponding to your choice:";
            while (1) {
                try {
                    getline(cin, num);
                    if (num.size() > 1)
                        throw InvalidInput("\n Invalid Input - Please input a number next time!\n");
                    else if (((stoi(num)) <= 0) || (stoi(num)) >= 3)
                        throw InvalidInput();
                    else
                        break;
                }
                catch (InvalidInput &e) {
                    cout << e.getInfo();
                    continue;
                }
                catch (...) {
                    cout << "\n Invalid Input - Please try again!\n";
                    continue;
                }
            }

            type_search = stoi(num);
            switch (type_search) {
                case 1:
                    outputD = PW.getTaskScheduledServices(task_name);
                    break;
                case 2:
                    outputD = PW.getTaskServicesDone(task_name);
                    break;
                default:
                    break;
            }
            //Output do vetor em tabela
            try {
                if (outputD.empty()) throw EmptyVector(0);
                else {
                    cout << "\n\t\t\t\t\tPetWalker " << task_name << "Services\n";

                    cout << "-----------------------------------------------------------------------------------------------------------------------";
                    cout << "          Date              Task         Exclusive?        Client Email           Employee Username      Service Price\n";
                    cout << "-----------------------------------------------------------------------------------------------------------------------";
                    for (int i = 0; i < outputD.size(); i++) {
                        cout << *(outputD.at(i));
                    }
                    cout << "-----------------------------------------------------------------------------------------------------------------------\n";
                    cout << "\t\t Total number of " << task_name << " services = " << outputD.size() << endl;
                }
            }
            catch (EmptyVector &e) {
                cout << "\n   " << e.getInfo() << endl;
            }

            break;
        case 3:
            try {
                while (1) {
                    cout << "\n  Insert the username of the Employee to search: ";

                    try {
                        getline(cin, userEmployee);

                        for (int i = 0; i < userEmployee.size(); i++) {
                            if (userEmployee[i] == ' ')
                                throw InvalidInput("Invalid username input! Please try again.");
                        }

                        break;
                    }
                    catch (InvalidInput &e) {
                        cout << e.getInfo();
                        continue;
                    }
                    catch (...) {
                        cout << "\n Invalid Input - Please try again!\n";
                        continue;
                    }
                }
            }
            catch (EmployeeDoesNotExist &e) {
                cout << "\n\t" << e.getInfo() << endl;
                while (true) {
                    cout << "\n  Do you want to try again?";
                    cout << "\n   1 - Yes" << "\t2 - No";
                    cout << "\n  Insert the number corresponding to your choice:";
                    try {
                        getline(cin, num);
                        if (num.size() > 1 || num.empty())
                            throw InvalidInput("\n Invalid Input - Please input a number next time!\n");
                        else if (((stoi(num)) <= 0) || (stoi(num)) >= 3)
                            throw InvalidInput();
                        else
                            break;
                    }
                    catch (InvalidInput &e) {
                        cout << e.getInfo();
                        continue;
                    }
                }
                if (stoi(num) == 2)
                    break;
            }
            cout << "\n---------------------------- " << userEmployee << " Services ----------------------------";
            cout << "\n  Which type of service would you like to see?";
            cout << "\n   1 - Scheduled Services";
            cout << "\n   2 - Completed Services";
            cout << "\n  Insert the number corresponding to your choice:";
            while (1) {
                try {
                    getline(cin, num);
                    if (num.size() > 1)
                        throw InvalidInput("\n Invalid Input - Please input a number next time!\n");
                    else if (((stoi(num)) <= 0) || (stoi(num)) >= 3)
                        throw InvalidInput();
                    else
                        break;
                }
                catch (InvalidInput &e) {
                    cout << e.getInfo();
                    continue;
                }
                catch (...) {
                    cout << "\n Invalid Input - Please try again!\n";
                    continue;
                }
            }

            type_search = stoi(num);
            switch (type_search) {
                case 1:
                    outputE = PW.getEmployeeScheduledServices(userEmployee);
                    break;
                case 2:
                    outputE = PW.getEmployeeServicesDone(userEmployee);
                    break;
                default:
                    break;
            }
            //Output do vetor em tabela
            try {
                if (outputE.empty()) throw EmptyVector(1);
                else {
                    cout << "\n\t\t\t\t\tPetWalker "<< userEmployee << " Services\n";

                    cout << "-----------------------------------------------------------------------------------------------------------------------";
                    cout << "          Date              Task         Exclusive?        Client Email           Employee Username      Service Price\n";
                    cout << "-----------------------------------------------------------------------------------------------------------------------";
                    for (int i = 0; i < outputE.size(); i++) {
                        cout << *(outputE.at(i));
                    }
                    cout << "-----------------------------------------------------------------------------------------------------------------------\n";
                    cout << "\t\t Total number of services of " << userEmployee << " = " << outputE.size() << endl;
                }
            }
            catch (EmptyVector &e) {
                cout << "\n   " << e.getInfo() << endl;
            }
            break;

        case 4:
            while (1) {
                try {
                    while (1) {
                        cout << "\n  Insert the email of the Client to search: ";

                        try {
                            getline(cin, userClient);

                            for (int i = 0; i < userClient.size(); i++) {
                                if (userClient[i] == ' ')
                                    throw InvalidInput("Invalid email input! Please try again.");
                            }

                            break;
                        }
                        catch (InvalidInput &e) {
                            cout << e.getInfo();
                            continue;
                        }
                        catch (...) {
                            cout << "\n Invalid Input - Please try again!\n";
                            continue;
                        }

                    }
                    PW.getClient(userClient);
                    break;
                }
                catch (ClientDoesNotExist &e) {
                    cout << "\n\t" << e.getInfo() << endl;
                    while (true) {
                        cout << "\n  Do you want to try again?";
                        cout << "\n   1 - Yes" << "\t2 - No";
                        cout << "\n  Insert the number corresponding to your choice:";
                        try {
                            getline(cin, num);
                            if (num.size() > 1 || num.empty())
                                throw InvalidInput("\n Invalid Input - Please input a number next time!\n");
                            else if (((stoi(num)) <= 0) || (stoi(num)) >= 3)
                                throw InvalidInput();
                            else
                                break;
                        }
                        catch (InvalidInput &e) {
                            cout << e.getInfo();
                            continue;
                        }
                    }
                    if (stoi(num) == 2)
                        break;
                }
            }

            cout << "\n---------------------------- " << userClient << " Services ----------------------------";
            cout << "\n  Which type of service would you like to see?";
            cout << "\n   1 - Scheduled Services";
            cout << "\n   2 - Completed Services";
            cout << "\n  Insert the number corresponding to your choice:";
            while (1) {
                try {
                    getline(cin, num);
                    if (num.size() > 1)
                        throw InvalidInput("\n Invalid Input - Please input a number next time!\n");
                    else if (((stoi(num)) <= 0) || (stoi(num)) >= 3)
                        throw InvalidInput();
                    else
                        break;
                }
                catch (InvalidInput &e) {
                    cout << e.getInfo();
                    continue;
                }
                catch (...) {
                    cout << "\n Invalid Input - Please try again!\n";
                    continue;
                }
            }

            type_search = stoi(num);
            switch (type_search) {
                case 1:
                    outputC = PW.getClientScheduledServices(userClient);
                    break;
                case 2:
                    outputC = PW.getClientServicesDone(userClient);
                    break;
                default:
                    break;
            }
            //Output do vetor em tabela
            try {
                if (outputC.empty()) throw EmptyVector(2);
                else {
                    cout << "\n\t\t\t\t\tPetWalker "<< userClient << " Services\n";

                    cout << "-----------------------------------------------------------------------------------------------------------------------";
                    cout << "          Date              Task         Exclusive?        Client Email           Employee Username      Service Price\n";
                    cout << "-----------------------------------------------------------------------------------------------------------------------";
                    for (int i = 0; i < outputC.size(); i++) {
                        cout << *(outputC.at(i));
                    }
                    cout << "-----------------------------------------------------------------------------------------------------------------------\n";
                    cout << "\t\t Total number of services of " << userClient << " = " << outputC.size() << endl;
                }
            }
            catch (EmptyVector &e) {
                cout << "\n   " << e.getInfo() << endl;
            }

            break;

        default:
            break;
    }


    if (!exit(false)) {

        cout << "\n\t Returning to menu...\n";
        _sleep(1000);
        return false;
    } else
        return true;
}

bool obj_delete()
{
    string num, msg;
    int type_data;

    while(1) {
        cout << "\n---------------------------- Delete Mode ----------------------------";
        cout << "\n  What would you like to do?";
        cout << "\n   1 - Delete a Scheduled Service";
        cout << "\n   2 - Delete an Employee";
        cout << "\n   3 - Delete a Client";
        cout << "\n  Insert the number corresponding to your choice:";


        try {
            getline(cin, num);
            if (num.size() > 1)
                throw InvalidInput("\n Invalid Input - Please input a number next time!\n");
            else if (((stoi(num)) <= 0) || (stoi(num)) >= 5)
                throw InvalidInput();
            else
                break;
        }
        catch (InvalidInput &e) {
            cout << e.getInfo();
            continue;
        }
        catch (...) {
            cout << "\n Invalid Input - Please try again!\n";
            continue;
        }
    }

    type_data = stoi(num);

    switch(type_data)
    {
        case 1:
            while(1)
            {
                try{
                    Services *s1 = PW.createService(1);
                    PW.removeScheduledService(s1);

                    cout << "\n\n\tRemoved the Scheduled Service successfully!\n";
                    break;
                }
                catch(ServiceDoesNotExist &e){
                    cout << "\n\t" << e.getInfo() << endl;

                    while(true)
                    {
                        cout << "\n  Do you want to try again?";
                        cout << "\n   1 - Yes" << "\t2 - No";
                        cout << "\n  Insert the number corresponding to your choice:";
                        try {
                            getline(cin, num);
                            if (num.size() > 1 || num.empty())
                                throw InvalidInput("\n Invalid Input - Please input a number next time!\n");
                            else if ( ((stoi(num)) <= 0) || (stoi(num)) >= 3)
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
                    if(stoi(num) == 2)
                        break;
                }
            }
            break;
        case 2:
            while(1)
            {
                try{
                    string userEmployee;
                    while(1) {
                        cout << "\n  Insert the username of the Employee to delete: ";

                        try {
                            getline(cin, userEmployee);

                            for(int i = 0; i < userEmployee.size(); i++)
                            {
                                if(userEmployee[i] == ' ')
                                    throw InvalidInput("Invalid username input! Please try again.");
                            }

                            break;
                        }
                        catch (InvalidInput &e) {
                            cout << e.getInfo();
                            continue;
                        }
                        catch (...) {
                            cout << "\n Invalid Input - Please try again!\n";
                            continue;
                        }
                    }
                    PW.removeEmployee(userEmployee);
                    cout << "\n\n\tRemoved the Employee "<< userEmployee << " successfully!\n";
                    break;
                }
                catch(EmployeeDoesNotExist &e){
                    cout << "\n\t" << e.getInfo() << endl;
                    while(true)
                    {
                        cout << "\n  Do you want to try again?";
                        cout << "\n   1 - Yes" << "\t2 - No";
                        cout << "\n  Insert the number corresponding to your choice:";
                        try {
                            getline(cin, num);
                            if (num.size() > 1 || num.empty())
                                throw InvalidInput("\n Invalid Input - Please input a number next time!\n");
                            else if ( ((stoi(num)) <= 0) || (stoi(num)) >= 3)
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
                    if(stoi(num) == 2)
                        break;
                }
            }
            break;
        case 3:
            while(1)
            {
                try{
                    string userClient;
                    while(1) {
                        cout << "\n  Insert the email of the Client to delete: ";


                        try {
                            getline(cin, userClient);

                            for (int i = 0; i < userClient.size(); i++) {
                                if (userClient[i] == ' ')
                                    throw InvalidInput("Invalid email input! Please try again.");
                            }
                            break;
                        }
                        catch (InvalidInput &e) {
                            cout << e.getInfo();
                            continue;
                        }
                        catch (...) {
                            cout << "\n Invalid Input - Please try again!\n";
                            continue;
                        }
                    }
                    PW.removeClient(userClient);
                    cout << "\n\n\tRemoved the Client " << userClient << " successfully!\n";
                    break;
                }
                catch(ClientDoesNotExist &e){
                    cout << "\n\t" << e.getInfo() << endl;
                    while(true)
                    {
                        cout << "\n  Do you want to try again?";
                        cout << "\n   1 - Yes" << "\t2 - No";
                        cout << "\n  Insert the number corresponding to your choice:";
                        try {
                            getline(cin, num);
                            if (num.size() > 1 || num.empty())
                                throw InvalidInput("\n Invalid Input - Please input a number next time!\n");
                            else if ( ((stoi(num)) <= 0) || (stoi(num)) >= 3)
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
                    if(stoi(num) == 2)
                        break;
                }
            }

            break;
        default:
            break;
    }

    if (!exit(false))
    {

        cout << "\n\t Returning to menu...\n";
        _sleep(1000);
        return false;
    }
    else
        return true;
}

bool saveFile()
{
    string num, msg;
    int type_data;
    bool exception;

    cout << "\n---------------------------- Save File ----------------------------";
    cout << "\n\n\t\t\tSaving all files...\n";
    try{
        PW.saveFiles();
        cout << "\n\t\t   All files saved successfully!\n";
    }
    catch (FileNotFound &e)
    {
        cout << e.getInfo();
    }
    cout << "\n-------------------------------------------------------------------\n";


    if (!exit(false))
    {

        cout << "\n\t Returning to menu...\n";
        _sleep(1000);
        return false;
    }
    else
        return true;
}

bool exit(bool full_exit)
{
    string num, msg;
    bool exit = false;
    while(true)
    {
        if(!full_exit) {
            cout << "\n  Do you want to do anything else?";
            cout << "\n   1 - Yes" << "\t2 - No";
            cout << "\n  Insert the number corresponding to your choice:";
            try {
                getline(cin, num);
                if (num.size() > 1 || num.empty())
                    throw InvalidInput("\n Invalid Input - Please input a number next time!\n");
                else if (((stoi(num)) <= 0) || (stoi(num)) >= 3)
                    throw InvalidInput();
                else
                {
                    if (stoi(num) == 2)
                        exit = true;
                    else
                        exit = false;

                    break;
                }
            }
            catch (InvalidInput &e) {
                cout << e.getInfo();
                continue;
            }
        }
        else
        {
            cout << "\n\n  Do you really want to leave?";
            cout << "\n   1 - Yes" << "\t2 - No";
            cout << "\n  Insert the number corresponding to your choice:";
            try {
                getline(cin, num);
                if (num.size() > 1 || num.empty())
                    throw InvalidInput("\n Invalid Input - Please input a number next time!\n");
                else if ( ((stoi(num)) <= 0) || (stoi(num)) >= 3)
                    throw InvalidInput();
                else
                {
                    if (stoi(num) == 1)
                        exit = true;
                    else
                        exit = false;

                    break;
                }
            }
            catch (InvalidInput &e)
            {
                cout << e.getInfo();
                continue;
            }
        }

    }

    if (full_exit && !exit)
    {
        cout << "\n\t Returning to menu...\n";
        _sleep(1000);
    }

    return exit;
}
