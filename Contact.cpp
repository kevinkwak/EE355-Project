
#include "Contact.h"
#include <algorithm>


Email::Email(string type, string email_addr){
    // Already done
    this->type = type;
    this->email_addr = email_addr;
}


void Email::set_contact(){
    // Already done! 
    // We don't need to validate the entered email address.  
	cout << "Enter the type of email address: ";
	cin >> type;
    cout << "Enter email address: ";
    cin >> email_addr;
}


string Email::get_contact(bool full){
    // TODO
    // return example: "(Personal) username@gmail.com" 
    ostringstream ss;
    if (full) {
        ss << "Email: (" << type << ") " << email_addr;
    }
    else {
        ss << "(" << type << ") " << email_addr;
    }
    string str = ss.str();
    return str;
}


void Email::print(){
    // TODO
    // Hint: use get_contact
    cout << get_contact(0) << endl;
}


Phone::Phone(string type, string num){
    // TODO
    // It is possible that the phone number is given with (292-431-9876) or without (2924319876) dashes. 
    // We are sure that all phone numbers have 10 digits. 
    this->type = type;
    this->num = num;
}


void Phone::set_contact(){
    // TODO
   
	cout <<"Enter the type of phone number: ";
    cin >> type;
	cout << "Enter the phone number: ";
    cin >> num;
}


string Phone::get_contact(bool full){
    // TODO
    // return example "(Cell) 213-876-0023"
    ostringstream ss;
    if (full) {
        ss << "Phone: (" << type << ") " << num;
    }
    else {
        ss << "(" << type << ") " << num;
    }
    string str = ss.str();
    return str;
}


void Phone::print(){
    // TODO 
    // Hint: use get_contact
    cout << get_contact(0) << endl;
}

SNAccount::SNAccount(string type, string value){
    this->type = type;
    this->value = value;
}


void SNAccount::set_contact(){
	cout <<"Enter the type of social media platform: ";
    cin >> type;
	cout << "Enter the account handle: ";
    cin >> value;
}


string SNAccount::get_contact(bool full){
    ostringstream ss;
    if (full) {
        ss << "SocialNetwork: (" << type << ") " << value;
    }
    else {
        ss << "(" << type << ") " << value;
    }
    string str = ss.str();
    return str;
}


void SNAccount::print(){
    cout << get_contact(0) << endl;
}

//default constructors
Email::Email(){
    Email:set_contact();
}

Phone::Phone(){
    Phone:set_contact();
}

SNAccount::SNAccount(){
    SNAccount:set_contact();
}

