#ifndef PETWALKERPROJAEDA_TASKS_H
#define PETWALKERPROJAEDA_TASKS_H
#include "Services.h"
#include <string>

using namespace std;
class Services;

/** Petwalker Tasks Class
 *
 * Each object of this class represents a tasks done by the Petwalker company.
 * This will be a base class.
 */
class Tasks {
    string taskName;
    int duration;

public:
    /**
     * Constructor of the class Tasks.
     *
     * @param nT - **Name** of the task.
     * @param d - **Duration** corresponding to how long will the task be taking place.
     */
    Tasks(string nT, int d) {this->taskName = nT; this->duration = d;};
    /**
     * This function is used to obtain the task that is wanted.
     * @return **Name** - Name of the task.
     */
    string getTaskName() {return taskName;}
    /**
     * This function is used to obtain the duration of the task.
     * @return **Duration** - How long the task will be taking place.
     */
    int getDuration() const {return duration;}
};

/** Petwalker Veterinary Class
 *
 * Derived class of the class Tasks.
 * Is the task related to the veterinary.
 */
class Veterinary : public Tasks {
public:
    /**
     * Constructor of the class Veterinary.
     * Sets the base class Tasks constructor arguments by default.
     */
    Veterinary() : Tasks("Veterinary",120) {};
};


/** Petwalker Bath Class
 *
 * Derived class of the class Tasks.
 * Is the task related to taking a bath.
 */
class Bath : public Tasks {
public:
    /**
     * Constructor of the class Bath.
     * Sets the base class Tasks constructor arguments by default.
     */
    Bath() : Tasks("Bath",30) {};
};


/** Petwalker CutFur Class
 *
 * Derived class of the class Tasks.
 * Is the task related to cuting the fur.
 */
class CutFur : public Tasks {
public:
    /**
     * Constructor of the class CutFur.
     * Sets the base class Tasks constructor arguments by default.
     */
    CutFur(): Tasks("CutFur",60) {};
};



/** Petwalker Walk Class
 *
 *Derived class of the class Tasks.
 * Is the task related taking a walk.
 */
class Walk : public Tasks {
public:
    /**
     * Constructor of the class Walk.
     * Sets the base class Tasks constructor arguments by default.
     */
    Walk() : Tasks("Walk",45) {};
};


/** Petwalker ObedienceClass Class
 *
 * Derived class of the class Tasks.
 * Is the task related to the obedience classes.
 */
class ObedienceClass : public Tasks {
public:
    /**
     * Constructor of the class ObedienceClass.
     * Sets the base class Tasks constructor arguments by default.
     */
    ObedienceClass() : Tasks("ObedienceClass",120) {};
};

#endif //PETWALKERPROJAEDA_TASKS_H
