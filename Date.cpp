#include "Date.h"
#include <iterator>
#include <string>

Date::Date(){
    // Already done! 
    // cout << "Default constructor called! " << endl;
    day = 1;
    month = 1;
    year = 1970;
}


Date::Date(int day, int month, int year){
    // Already done! 
    // cout << "Constructor with integer arguments is called!" << endl;
    set_date(day, month, year);
}


Date::Date(string str){
    // Already done! 
    // input format is M/D/YYYY
    // cout << "Constructor wtih string argument is called" << endl;
    set_date(str); 
}


bool Date::operator==(const Date& rhs){
    // TODO
    return ((day == rhs.day) && (month == rhs.month) && (year == rhs.year));
}


bool Date::operator!=(const Date& rhs){
    // TODO
    return !((day == rhs.day) && (month == rhs.month) && (year == rhs.year));
}

bool Date::operator < (const Date& rhs){ 
    // TODO
    if (year > rhs.year) {
        return false;
    }
    else if (year < rhs.year) {
        return true;
    }
    else {
        if (month < rhs.month) {
            return true;
        }
        else if (month > rhs.month) {
            return false;
        }
        else {
            if (day < rhs.day) {
                return true;
            }
            else {
                return false;
            }
        }
    }
}

bool Date::operator > (const Date& rhs){
    // TODO
    if (year > rhs.year) {
        return true;
    }
    else if (year < rhs.year) {
        return false;
    }
    else {
        if (month < rhs.month) {
            return false;
        }
        else if (month > rhs.month) {
            return true;
        }
        else {
            if (day < rhs.day) {
                return false;
            }
            else {
                return true;
            }
        }
    }
}

bool Date::check_date(int day, int month, int year){
    // TODO -- you did this in Lab3
    // Leap years are those years divisible by 4, except for century years which are not divisible by 400.
    if (year <= 0 || year > 9999)
        return false;
    
    if (day < 1 || day > 31)
	    return false;
	
	if (month < 1 || month > 12)
	    return false;
	   
	/* if (month == 2)
	   if (year % 4 == 0)
	      if (year % 100 == 0)
	         if (day > 28)
	            return false;
    */

    if (month == 2) {
	    if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0)) {
		    if (day > 29)
			    return false;
	    }
	    else {
		    if (day > 28)
			    return false;
    	}
    }

    if (month == 4 || month == 6 || month == 9 || month == 11) {
        if (day > 30)
            return false;
    }

    return true;
}

bool Date::set_date(string str){
    // TODO
    // input format should be M/D/YYYY

    // You may use these prompts
    // cout << "Error! Invalid date!" << endl;
    // cout << "Date set to default!" << endl;
    string month;
    string day;
    string year;

    size_t firstslash = str.find('/');
    size_t lastslash = str.rfind('/');

    month = str.substr(0,firstslash);

    day = str.substr(firstslash+1,lastslash - (firstslash + 1));
    
    year = str.substr(lastslash+1);

    return set_date(stoi(day), stoi(month), stoi(year));
}


bool Date::set_date(int day, int month, int year){
    // Already done!
    // returns a true if operation successful, or false if unsuccessful
    // understand why we used "this" statement in this method
    if (check_date(day, month, year)){
        this->day = day;
        this->month = month;
        this->year = year;
        return true;
    }
    else {
        cout << "Error! Invalid date!" << endl;
        cout << "Date set to default!" << endl;
        this->day = 1;
        this->month = 1;
        this->year = 1970;
        return false;
    }
}


void Date::print_date(string type){
    // TODO
    // Different types for print, are: 
    // "M/D/YYYY"
    // "Month D, YYYY"
    // "D-Month-YYYY"
    // otherwise, cout << "Wrong print type!" << endl;

    if (type == "M/D/YYYY") {
        cout << month << "/" << day << "/" << year << endl;
    }
    
    else if (type == "Month D, YYYY"){
        string m;
	    switch (month) {
		    case 1:
			    m = "Jan";
			    break;
		    case 2:
			    m = "Feb";
			    break;
		    case 3:
			    m = "Mar";
			    break;
		    case 4:
			    m = "Apr";
			    break;
		    case 5:
		    	m = "May";
			    break;
		    case 6:
	    		m = "Jun";
	    		break;
	    	case 7:
	    		m = "Jul";
	    		break;
	    	case 8:
	    		m = "Aug";
	    		break;
	    	case 9:
	    		m = "Sep";
	    		break;
	    	case 10:
	    		m = "Oct";
	    		break;
	    	case 11:
	    		m = "Nov";
	    		break;
	    	case 12:
	    		m = "Dec";
	    		break;
	    }
	    cout << m << " " << day << ", " << year << endl;
    }

    else if (type == "D-Month-YYYY"){
        cout << day << "-" << month << "-" << year << endl;
    }

    else {
        cout << "Wrong print type!" << endl;
    }
}

string Date::get_date(){
    // Already done!
    ostringstream ss;
    ss << month << "/" << day << "/" << year; 
    string str = ss.str();
    return str;
}

