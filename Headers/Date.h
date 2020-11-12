#ifndef DATE_H_INCLUDED
#define DATE_H_INCLUDED

#include <iostream>
#include <string>

class Date{

    int day;
    int month;
    int year;

public:

    Date() {
            day = month = year = 0;
        }

    Date(int day, int month, int year) {
            this->day = day;
            this->month = month;
            this->year = year;

        }

    int getDay() const {return day;}
    int getMonth() const {return month;}
    int getYear() const {return year;}

    void afficher() const;

};

#endif // DATE_H_INCLUDED
