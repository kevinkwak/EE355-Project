
#ifndef CONTACT_H
#define CONTACT_H

#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>
using namespace std;


class ContactInfo {
    protected: //TODO: should type be private or protected?	Think about it.
	string type;
public:
	virtual void print() = 0;
    virtual string get_contact(bool full) = 0;
	virtual void set_contact() = 0;
};


// Complete the Email declaraction from scratch here 
class Email : public ContactInfo {
public:
	string type;
	string email_addr;
	Email(string type, string email_addr);
	Email();
	void print();
    string get_contact(bool full);
	void set_contact();
};

// Complete the phone declaration from scratch
class Phone : public ContactInfo {
public:
	string type;
	string num;
	Phone(string type, string num);
	Phone();
	void print();
    string get_contact(bool full);
	void set_contact();
};

// PA2
class SNAccount : public ContactInfo {
public:
   string type;  // Social media platform
   string value; // Handle/username
   SNAccount(string type, string value);
   SNAccount();
   void print();
   string get_contact(bool full);
   void set_contact();
};

#endif
