#include <ctime>
#include <iostream>
#include <cassert>
#include "date.h"

/******************************************************************************************
 *
 *  Default Constructor Date
 *_________________________________________________________________________________________
 *  Creates a "null" Date, set _date, _month, _year to 0
 *  - returns void
 *_________________________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    _date, _month, and _year are set to 0
 ******************************************************************************************/
Date::Date() {
    setNull();
}

/******************************************************************************************
 *
 *  Constructor Date
 *_________________________________________________________________________________________
 *  Initialize member variables with the given parameters
 *  - returns void
 *_________________________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    _date, _month, and _year are initialized with the given parameter
 ******************************************************************************************/
Date::Date(int date, int month, int year) : _date(date), _month(month), _year(year){
}

/******************************************************************************************
 *
 *  Compy Constructor Date
 *_________________________________________________________________________________________
 *  Set the current Date equal to the given parameter Date
 *  - returns void
 *_________________________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    _date, _month, and _year are initialized with the given parameter Date
 ******************************************************************************************/
Date::Date(const Date& d) {
    _date = d._date;
    _month = d._month;
    _year = d._year;
}

/******************************************************************************************
 *
 *  Static Method getCurrentDate: Class Date
 *_________________________________________________________________________________________
 *  Return a Date with current system dates
 *  - returns Date
 *_________________________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    A Date with current system date is returned
 ******************************************************************************************/
Date Date::getCurrentDate() {
    Date current;
    std::time_t time = std::time(0);
    struct tm *now = localtime(&time);
    current._date = now->tm_mday;
    current._month = now->tm_mon + 1;
    current._year = now->tm_year + 1900;

    return current;
}

/******************************************************************************************
 *
 *  Mutator setDate: Class Date
 *_________________________________________________________________________________________
 *  This method will update the _date, _month, and _year attributes to the
 *      parameter Date values
 *  - returns void
 *_________________________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    _date, _month, and _year are changed to the given parameter Date
 ******************************************************************************************/
void Date::setDate(const Date& d) {
    _date = d._date;
    _month = d._month;
    _year = d._year;
}

/******************************************************************************************
 *
 *  Accessor getDate: Class Date
 *_________________________________________________________________________________________
 *  This method will return _date
 *  - returns int
 *_________________________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    _date is returned
 ******************************************************************************************/
int Date::getDate() const{
    return _date;
}

/******************************************************************************************
 *
 *  Accessor getMonth: Class Date
 *_________________________________________________________________________________________
 *  This method will return _month
 *  - returns int
 *_________________________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    _month is returned
 ******************************************************************************************/
int Date::getMonth() const {
    return _month;
}

/******************************************************************************************
 *
 *  Accessor getYear: Class Date
 *_________________________________________________________________________________________
 *  This method will return _year
 *  - returns int
 *_________________________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    _year is returned
 ******************************************************************************************/
int Date::getYear() const {
    return _year;
}

/******************************************************************************************
 *
 *  Overload operator ++: Class Date
 *_________________________________________________________________________________________
 *  Set the current Date to the next Date
 *  - returns Date&
 *_________________________________________________________________________________________
 *  PRE-CONDITIONS
 *    verifyDate() == true
 *
 *  POST-CONDITIONS
 *    _date is incremented by one. _date, _month, and _year are adjusted if needed
 ******************************************************************************************/
Date& Date::operator ++(int) {
    assert(verifyDate());
    _date++;
    if(_date > 31 || (_date > 30 && (_month == 4 || _month == 6 || _month == 9 || _month == 11))) {
        _date = 1;
        _month++;
    }
    if(_month == 2) {
        if(_date > 29 || (_date > 28 && !isLeapYear())) {
            _date = 1;
            _month++;
        }
    }
    if(_month > 12) {
        _month = 1;
        _year++;
    }

    return *this;
}

/******************************************************************************************
 *
 *  Method setNull: Class Date
 *_________________________________________________________________________________________
 *  Set the current Date to "null", _date, month, _year to 0;
 *  - returns void
 *_________________________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    _date, _month, _year = 0
 ******************************************************************************************/
void Date::setNull() {
    _date = 0;
    _month = 0;
    _year = 0;
}

/******************************************************************************************
 *
 *  Overload operator =: Class Date
 *_________________________________________________________________________________________
 *  Set the current Date to the given parameter Date
 *  - returns void
 *_________________________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    _date, _month, and _year are changed to be the same as given Date
 ******************************************************************************************/
void Date::operator =(const Date& d) {
    setDate(d);
}

/******************************************************************************************
 *
 *  Method verifyDate(): Class Date
 *_________________________________________________________________________________________
 *  Verify the Date and return true/false
 *      Year is from 1980 ~ 2080
 *      Month is from 1 ~ 12
 *      Date is from 1 ~ (28, 29, 30, 31) based on the month and leap year
 *  - returns bool
 *_________________________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    Returned true if conditions above are met, false otherwise
 ******************************************************************************************/
bool Date::verifyDate() const {
    if(_year < 1980 || _year > 2080) {
        return false;
    }
    if(_month < 1 || _month > 12) {
        return false;
    }

    if(_date < 1 || _date > 31 || ((_month == 4 || _month == 6 || _month == 9 || _month == 11) && _date > 30))
        return false;

    if(_month == 2 && (_date > 29 || (!isLeapYear() && _date > 28)))
        return false;

    return true;
}

/******************************************************************************************
 *
 *  Method dayOfWeek: Class Date
 *_________________________________________________________________________________________
 *  Return the day of the week based on the current Date.
 *  - returns std:;string
 *_________________________________________________________________________________________
 *  PRE-CONDITIONS
 *    verifDate() == true
 *
 *  POST-CONDITIONS
 *    return the day of the week. (Monday ~ Sunday)
 ******************************************************************************************/
std::string Date::dayOfWeek() const {
    assert(verifyDate());
    int sum = _date + getMonthValue() + getCenturyValue() + getYearValue();
    int day = sum % 7;

    switch(day)
    {
        case 1:
            return "Monday";
        case 2:
            return "Tuesday";
        case 3:
            return "Wednesday";
        case 4:
            return "Thursday";
        case 5:
            return "Friday";
        case 6:
            return "Saturday";
        default:
            return "Sunday";
    }
}

/******************************************************************************************
 *
 *  Overload operator ==: Class Date
 *_________________________________________________________________________________________
 *  Return true if the current Date matches the given parameter Date, false otherwise
 *  - returns bool
 *_________________________________________________________________________________________
 *  PRE-CONDITIONS
 *    verifyDate() == true && d.verifyDate() == true
 *
 *  POST-CONDITIONS
 *    Return true if the current Date matches the given parameter Date, false otherwise
 ******************************************************************************************/
bool Date::operator ==(const Date& d) const {
    assert(verifyDate() && d.verifyDate());
    return (d._date == _date && d._month == _month && d._year == _year);
}

/******************************************************************************************
 *
 *  Overload operator !=: Class Date
 *_________________________________________________________________________________________
 *  Return true if the current Date does not matches the given parameter Date, false otherwise
 *  - returns bool
 *_________________________________________________________________________________________
 *  PRE-CONDITIONS
 *    verifyDate() == true && d.verifyDate() == true
 *
 *  POST-CONDITIONS
 *    Return true if the current Date does not matches the given parameter Date, false otherwise
 ******************************************************************************************/
bool Date::operator !=(const Date& d) const {
    assert(verifyDate() && d.verifyDate());
    return (d._date != _date || d._month != _month || d._year != _year);
}

/******************************************************************************************
 *
 *  Overload operator >: Class Date
 *_________________________________________________________________________________________
 *  Return true if the current Date comes after the given parameter Date, false otherwise
 *  - returns bool
 *_________________________________________________________________________________________
 *  PRE-CONDITIONS
 *    verifyDate() == true && d.verifyDate() == true
 *
 *  POST-CONDITIONS
 *    Return true if the current Date comes after the given parameter Date, false otherwise
 ******************************************************************************************/
bool Date::operator >(const Date& d) const {
    assert(verifyDate() && d.verifyDate());
    if(_year != d._year) {
        return _year > d._year;
    }
    if(_month != d._month) {
        return _month > d._month;
    }
    if(_date != d._date) {
        return _date > d._date;
    }

    return false;
}

/******************************************************************************************
 *
 *  Overload operator <: Class Date
 *_________________________________________________________________________________________
 *  Return true if the current Date comes before the given parameter Date, false otherwise
 *  - returns bool
 *_________________________________________________________________________________________
 *  PRE-CONDITIONS
 *    verifyDate() == true && d.verifyDate() == true
 *
 *  POST-CONDITIONS
 *    Return true if the current Date comes before the given parameter Date, false otherwise
 ******************************************************************************************/
bool Date::operator <(const Date& d) const {
    assert(verifyDate() && d.verifyDate());
    if(_year != d._year) {
        return _year < d._year;
    }
    if(_month != d._month) {
        return _month < d._month;
    }
    if(_date != d._date) {
        return _date < d._date;
    }

    return false;
}

/******************************************************************************************
 *
 *  Overload operator >=: Class Date
 *_________________________________________________________________________________________
 *  Return true if the current Date matches or comes after the given parameter Date,
 *      false otherwise
 *  - returns bool
 *_________________________________________________________________________________________
 *  PRE-CONDITIONS
 *    verifyDate() == true && d.verifyDate() == true
 *
 *  POST-CONDITIONS
 *    Return true if the current Date matches or comes after the given parameter Date,
 *      false otherwise
 ******************************************************************************************/
bool Date::operator >=(const Date& d) const {
    assert(verifyDate() && d.verifyDate());
    return *this == d || *this > d;
}

/******************************************************************************************
 *
 *  Overload operator <=: Class Date
 *_________________________________________________________________________________________
 *  Return true if the current Date matches or comes before the given parameter Date,
 *      false otherwise
 *  - returns bool
 *_________________________________________________________________________________________
 *  PRE-CONDITIONS
 *    verifyDate() == true && d.verifyDate() == true
 *
 *  POST-CONDITIONS
 *    Return true if the current Date matches or comes before the given parameter Date,
 *      false otherwise
 ******************************************************************************************/
bool Date::operator <=(const Date& d) const {
    assert(verifyDate() && d.verifyDate());
    return *this == d || *this < d;
}

/******************************************************************************************
 *
 *  Method printDate: Class Date
 *_________________________________________________________________________________________
 *  Return a string of the current Date in the format of:
 *      ->xx/yy/zz    dayOfWeek, (without '\n' at the end)
 *  - returns void
 *_________________________________________________________________________________________
 *  PRE-CONDITIONS
 *    verifyDate() == true
 *
 *  POST-CONDITIONS
 *    The current Date and day of the week are returned separated by 4 spaces
 ******************************************************************************************/
std::string Date::printDate() const {
    assert(verifyDate());
    std::string str = "";
    if(getDate() < 10) {
        str += '0';
    }
    str += std::to_string(getDate()) + '/';

    if(getMonth() <10) {
        str += '0';
    }
    str += std::to_string(getMonth()) + '/' + std::to_string(getYear()) + "    " + dayOfWeek();

    return str;
}

/******************************************************************************************
 *
 *  Method printMonth: Class Date
 *_________________________________________________________________________________________
 *  Return a string of the month
 *  - returns void
 *_________________________________________________________________________________________
 *  PRE-CONDITIONS
 *    verifyDate() == true
 *
 *  POST-CONDITIONS
 *    Prints "January" to "December" based on _month;
 ******************************************************************************************/
std::string Date::printMonth() const {
    assert(verifyDate());
    switch(_month) {
        case 1:
            return "January";
        case 2:
            return "February";
        case 3:
            return "March";
        case 4:
            return "April";
        case 5:
            return "Mar";
        case 6:
            return "June";
        case 7:
            return "July";
        case 8:
            return "August";
        case 9:
            return "September";
        case 10:
            return "October";
        case 11:
            return "November";
        default:
            return "December";
    }
}

/******************************************************************************************
 *
 *  Overload operator <<: Class Date
 *_________________________________________________________________________________________
 *  Prints the current Date in the format of:
 *      ->xx/yy/zz    dayOfWeek, (without '\n' at the end)
 *  - returns void
 *_________________________________________________________________________________________
 *  PRE-CONDITIONS
 *    verifyDate() == true
 *
 *  POST-CONDITIONS
 *    The current Date and day of the week are printed separated by 4 spaces
 ******************************************************************************************/
std::ostream& operator<<(std::ostream& os, const Date& d) {
    assert(d.verifyDate());
    if(d.getDate() < 10) {
        os << '0';
    }
    os << d.getDate() << '/';

    if(d.getMonth() <10) {
        os << '0';
    }
    os << d.getMonth() << '/' << d.getYear() << "    " << d.dayOfWeek();

    return os;
}

/******************************************************************************************
 *
 *  Method isLeapYear: Class Date
 *_________________________________________________________________________________________
 *  Return true if the year is a leap year, false otherwise, used to calculate dayOfWeek()
 *  - returns bool
 *_________________________________________________________________________________________
 *  PRE-CONDITIONS
 *    verifyDate() == true
 *
 *  POST-CONDITIONS
 *    Return true if the year is a leap year
 ******************************************************************************************/
bool Date::isLeapYear() const {
    assert(verifyDate());
    return _year % 400 == 0 || (_year % 4 == 0 && _year % 100 != 0);
}

/******************************************************************************************
 *
 *  Method getCentruyValue: Class Date
 *_________________________________________________________________________________________
 *  No special meaning except used to calculate dayOfWeek()
 *  - returns int
 *_________________________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    Return a value based on the century
 ******************************************************************************************/
int Date::getCenturyValue() const {
    return (3 - (_year / 100) % 4) * 2;
}

/******************************************************************************************
 *
 *  Method getYearValue: Class Date
 *_________________________________________________________________________________________
 *  No special meaning except used to calculate dayOfWeek()
 *  - returns int
 *_________________________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    Return a value based on the year
 ******************************************************************************************/
int Date::getYearValue() const {
    return _year % 100 + (_year % 100) / 4;
}

/******************************************************************************************
 *
 *  Method getMonthValue: Class Date
 *_________________________________________________________________________________________
 *  No special meaning except used to calculate dayOfWeek()
 *  - returns int
 *_________________________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    Return a value based on the month
 ******************************************************************************************/
int Date::getMonthValue() const {
    switch(_month)
    {
        case 1:
            if(isLeapYear())
                return 6;
            return 0;
        case 2:
            if(isLeapYear())
                return 2;
            return 3;
        case 3:
            return 3;
        case 4:
            return 6;
        case 5:
            return 1;
        case 6:
            return 4;
        case 7:
            return 6;
        case 8:
            return 2;
        case 9:
            return 5;
        case 10:
            return 0;
        case 11:
            return 3;
        default:
            return 5;
    }
}
