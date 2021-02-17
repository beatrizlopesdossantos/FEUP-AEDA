#ifndef PETWALKERPROJAEDA_DATE_H
#define PETWALKERPROJAEDA_DATE_H


#include <string>
#include <vector>
#include <ostream>

using namespace std;

/** Petwalker Date Class
 *
 * Each object of this class represents a date to be set in the Petwalker company.
 */

class Date {
public:
    /**
     * Constructor of the class Date.
     *
     * Sets the current time.
     */
    Date();
    /**
     * Constructor of the class Date.
     *
     * @param day - **Day**
     * @param month - **Month**
     * @param year - **Year**
     * @param hours - **Hours**
     * @param minutes - **Minutes**
     */
    Date(int day, int month, int year, int hours, int minutes);
    /**
     * This function is used to obtain an integer with the day.
     * @return **Day**
     */
    int getDay() const;
    /**
     * This function is used to obtain an integer with the month.
     * @return **Month**
     */
    int getMonth() const;
    /**
     * This function is used to obtain an integer with the year.
     * @return **Year**
     */
    int getYear() const;
    /**
     * This function is used to obtain an integer with the hours.
     * @return **Hours**
     */
    int getHours() const;
    /**
     * This function is used to obtain an integer with the minutes.
     * @return **Minutes**
     */
    int getMinutes() const;
    /**
     * This function is used to change the date by adding minutes (duration of the task).
     * @param minutes
     */
    void addTime(int minutes);
    /**
     * This function is used to change the date by adding 1 month (limit to be set old).
     */
    void addMonth();
    /**
     * This operator is mainly used for search algorithms.
     * It compares the *this* Date with the d1.
     * @param d1 Date to compare with this.
     * @return true if the date is completely equal.
     */
    bool operator==(const Date &d1)const;
    /**
     * This operator is mainly used for search algorithms.
     * It compares the *this* Date with the d1.
     * @param d1 Date to compare with this.
     * @return true if this is lower than d1; false if not.
     */
    bool operator<(const Date &d1)const;
    /**
     * This operator is used to do the output of all the information stored in one date object.
     * @param o Output stream to show the data of the date on the console.
     * @param d Date to do the output of.
     * @return o - Output stream with all the data in the defined parsing.
     */
    friend ostream & operator<<(ostream & o, const Date & d);

private:
    int _day;
    int _month;
    int _year;
    int _hour;
    int _minute;
    bool _bisext;

};


#endif //PETWALKERPROJAEDA_DATE_H
