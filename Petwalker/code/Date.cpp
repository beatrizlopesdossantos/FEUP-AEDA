#include "Date.h"
#include "Exceptions.h"
#include <ctime>


Date::Date() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    _year = 1900 + ltm->tm_year;
    _month = 1+ltm->tm_mon;
    _day = ltm->tm_mday;
    _hour = ltm->tm_sec;
    _minute = ltm->tm_min;
    if (_year% 4==0) {
        if (_year % 100 == 0) {
            if (_year % 400 == 0)
                _bisext = true;
        } else {
            _bisext = true;
        }
    }
}

Date::Date(int day, int month, int year, int hours, int minutes) {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    int actualYear = 1900 + ltm->tm_year;
    int actualMonth = 1+ltm->tm_mon;
    int actualDay = ltm->tm_mday;
    int actualHour = ltm->tm_sec;
    int actualMinute = ltm->tm_min;
    if (minutes > 59 || minutes < 0){
        throw DateNotValid();
    }
    if (hours > 23 || hours < 0){
        throw DateNotValid();
    }
    if (month <= 0 || month > 12){
        throw DateNotValid();
    }
    if (day < 0)
        throw DateNotValid();
    if ((month ==1 || month == 3 || month ==5 || month == 7 || month == 8 || month == 10 || month == 12) && (day > 31)){
        throw DateNotValid();
    }
    if ((month == 4 || month ==6 || month == 9 || month == 11) && (day >30)){
        throw DateNotValid();
    }
    if (year% 4==0) {
        if (year % 100 == 0) {
            if (year % 400 == 0)
                _bisext = true;
        } else {
            _bisext = true;
        }
    }
    if ((month == 2 && _bisext) && day >29){
        throw DateNotValid();
    }
    if ((month == 2 && _bisext == false) && day >28){
        throw DateNotValid();
    }
    _day = day;
    _month = month;
    _year = year;
    _hour = hours;
    _minute = minutes;
}

int Date::getYear() const{
    return _year;
}

int Date::getMinutes() const{
    return _minute;
}

int Date::getDay() const{
    return _day;
}

int Date::getHours() const{
    return _hour;
}

int Date::getMonth() const{
    return _month;
}

void Date::addTime(int minutes) {
    if (_minute + minutes > 59) {
        int mtemp = _minute;
        _minute = (_minute + minutes) % 60;
        if((_hour+((mtemp+minutes)/60))>23){
            _hour = ((_hour + (mtemp + minutes)/60))%24;
            switch(_month) {
                case 1:
                    if (_day == 31){
                        _day = 1;
                        _month++;
                    }
                    else
                        _day++;
                    break;
                case 2:
                    if (_day == 28){
                        if (_bisext){
                            _day++;
                        }
                        else{
                            _day = 1;
                            _month++;
                        }
                    }
                    else if (_day == 29){
                        _day = 1;
                        _month++;
                    }
                    else{
                        _day++;
                    }
                    break;
                case 3:
                    if (_day == 31){
                        _day = 1;
                        _month++;
                    }
                    else
                        _day++;
                    break;
                case 4:
                    if (_day == 30){
                        _day = 1;
                        _month++;
                    }
                    else
                        _day++;
                    break;
                case 5:
                    if (_day == 31){
                        _day = 1;
                        _month++;
                    }
                    else
                        _day++;
                    break;
                case 6:
                    if (_day == 30){
                        _day = 1;
                        _month++;
                    }
                    else
                        _day++;
                    break;
                case 7:
                    if (_day == 31){
                        _day = 1;
                        _month++;
                    }
                    else
                        _day++;
                    break;
                case 8:
                    if (_day == 31){
                        _day = 1;
                        _month++;
                    }
                    else
                        _day++;
                    break;
                case 9:
                    if (_day == 30){
                        _day = 1;
                        _month++;
                    }
                    else
                        _day++;
                    break;
                case 10:
                    if (_day == 31){
                        _day = 1;
                        _month++;
                    }
                    else
                        _day++;
                    break;
                case 11:
                    if (_day == 30){
                        _day = 1;
                        _month++;
                    }
                    else
                        _day++;
                    break;
                case 12:
                    if (_day == 31){
                        _day = 1;
                        _month = 1;
                        _year++;
                        if (_bisext)
                            _bisext = false;
                        else{
                            if (_year% 4==0) {
                                if (_year % 100 == 0) {
                                    if (_year % 400 == 0)
                                        _bisext = true;
                                } else {
                                    _bisext = true;
                                }
                            }
                        }
                    }
                    else
                        _day++;
                    break;
            }
        }
        else{
            _hour = (mtemp + minutes)/60 + _hour;
        }
    }
    else{
        _minute = _minute + minutes;
    }
}

void Date::addMonth(){
    switch(_month) {
        case 1:
            if (_day == 31){
                _day = 1;
                _month++;
            }
            else
                _day++;
            break;
        case 2:
            if (_day == 28){
                if (_bisext){
                    _day++;
                }
                else{
                    _day = 1;
                    _month++;
                }
            }
            else if (_day == 29){
                _day = 1;
                _month++;
            }
            else{
                _day++;
            }
            break;
        case 3:
            if (_day == 31){
                _day = 1;
                _month++;
            }
            else
                _day++;
            break;
        case 4:
            if (_day == 30){
                _day = 1;
                _month++;
            }
            else
                _day++;
            break;
        case 5:
            if (_day == 31){
                _day = 1;
                _month++;
            }
            else
                _day++;
            break;
        case 6:
            if (_day == 30){
                _day = 1;
                _month++;
            }
            else
                _day++;
            break;
        case 7:
            if (_day == 31){
                _day = 1;
                _month++;
            }
            else
                _day++;
            break;
        case 8:
            if (_day == 31){
                _day = 1;
                _month++;
            }
            else
                _day++;
            break;
        case 9:
            if (_day == 30){
                _day = 1;
                _month++;
            }
            else
                _day++;
            break;
        case 10:
            if (_day == 31){
                _day = 1;
                _month++;
            }
            else
                _day++;
            break;
        case 11:
            if (_day == 30){
                _day = 1;
                _month++;
            }
            else
                _day++;
            break;
        case 12:
            if (_day == 31){
                _day = 1;
                _month = 1;
                _year++;
                if (_bisext)
                    _bisext = false;
                else{
                    if (_year% 4==0) {
                        if (_year % 100 == 0) {
                            if (_year % 400 == 0)
                                _bisext = true;
                        } else {
                            _bisext = true;
                        }
                    }
                }
            }
            else
                _day++;
            break;
    }
}

bool Date::operator==(const Date &d1) const {

    if(this->_day != d1.getDay())
        return false;
    if(this->_month != d1.getMonth())
        return false;
    if(this->_year != d1.getYear())
        return false;
    if(this->_hour != d1.getHours())
        return false;
    if(this->_minute != d1.getMinutes())
        return false;

    return true;
}

bool Date::operator<(const Date &d1) const {
    if(_year == d1.getYear())
    {
        if(_month == d1.getMonth())
        {
            if (_day == d1.getDay())
            {
                if (_hour == d1.getHours())
                {
                    return _minute < d1.getMinutes();
                }
                else
                    return _hour < d1.getHours();
            }
            else
                return _day < d1.getDay();
        }
        else
            return _month < d1.getMonth();
    }
    else
        return _year < d1.getYear();


}

ostream &operator<<(ostream &o, const Date &d) {
    //os if's são para formatar corretamente -> dd/mm/yyyy  HH:MM
    if(d.getDay() < 10) o << "0";
    o << d.getDay() << "/";
    if(d.getMonth()< 10) o << "0";
    o << d.getMonth() << "/" << d.getYear() << "  ";
    if(d.getHours() < 10) o << "0";
    o << d.getHours() << ":";
    if(d.getMinutes() < 10) o << "0";
    o << d.getMinutes();
    return o;
}
