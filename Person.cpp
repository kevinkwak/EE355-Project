#include "Person.h"

Person::Person()
{
    // Already Done! :)
    set_person();
}

Person::Person(string fname, string lname, string bdate)
{
    // TODO
    this->f_name = fname;
    this->l_name = lname;
    this->birthdate = new Date(bdate);
}

Person::~Person()
{
    // TODO
    delete birthdate;
    for (ContactInfo* contact : contacts) {
        delete contact;
    }
    contacts.clear();
}

void Person::set_person()
{
    //TODO
    // prompts for the information of the user
    // first/last name can have spaces!
    // date format must be "M/D/YYYY", but user can make mistakes
    // OOP:://github.com/EE355/project_phase_2-kwakkevi-santosba-pa2.gitthe one who wrote the Date class did take care of handling mistakes

    cout << "First Name: ";
    // TODO: read the first name
    cin >> this->f_name;
    cout << "Last Name: ";
    // TODO: read the last name
    cin >> this->l_name;
    cout << "Birthdate (M/D/YYYY): ";
    // TODO: get birthdate from user as a string and use it to create a new Date (dynamic allocation)
    string bday;
    cin >> bday;
    this->birthdate = new Date(bday);

    this->add_contact();
}

bool Person::operator==(const Person &rhs)
{
    // TODO
    // Hint: Look at how we overloaded == in Date
    // Two persons are equal only if they have the same first name, last name and date of birth!
    return ((f_name == rhs.f_name) && (l_name == rhs.l_name) && (birthdate->get_date() == rhs.birthdate->get_date()));
}

bool Person::operator!=(const Person &rhs)
{
    // TODO
    // Hint: two things are either equal or not equal
    return !((f_name == rhs.f_name) && (l_name == rhs.l_name) && (birthdate->get_date() == rhs.birthdate->get_date()));
}

void Person::print_person()
{
    // Already done!
    cout << l_name << ", " << f_name << endl;
    birthdate->print_date("Month D, YYYY");
    for (int i = 0; i < this->contacts.size(); i++) {
        contacts.at(i)->print();
    }
}

// PA 2
void Person::add_contact()
{
    string choice;
    string select;
    cout << "Do you want to add contact information? (Y/N): ";
    cin >> choice;

    while (choice == "Y")
    {
        cout << "Select: Email/Phone/SocialNetwork: ";
        cin >> select;

        if (select == "Email")
        {
            Email * email = new Email();
            this->contacts.push_back(email);
        }

        else if (select == "Phone")
        {
            Phone * phone = new Phone();
            this->contacts.push_back(phone);
        }

        else if (select == "SocialNetwork")
        {
            SNAccount * account = new SNAccount();
            this->contacts.push_back(account);
        }

        else
        {
            cout << "Not a valid option.";
        }
        cout << "Do you want to add more contact information? (Y/N): ";
        cin >> choice;
    }
}

void Person::remove_contact() {
    char cinput[5];
    string input2;
    
    while(1) {
      cout << "Remove menu: " << endl;
      for (int i = 1; i < this->contacts.size() + 1; i++) {
         cout << "[" << i << "]";
         contacts.at(i-1)->print();
      }

      if (contacts.size() == 0){
         cout << "This person has no contact info to remove." << endl;
         return;
      }

      cout << "Choose the contact that you wish to remove or quit: ";

      cin.ignore();
      cin.getline(cinput, 5);

      for(int j = 0; cinput[j]; j++){
         cinput[j] = tolower(cinput[j]);
      }
      
      string input(cinput);

      if (input != "quit" && input != "q" && input != "0") {
         cout << "Are you sure you want to delete this contact info? (Y/N): ";
         cin >> input2;
         
         if (input2 == "Y") {
            contacts.erase(contacts.begin() + stoi(input) - 1);
         }
            
         else {
            continue;
         }
      }
         
      else if (input == "quit" || input == "q" || input == "0") {
         return;
      }
   }  
}

void Person::write_to_file(ofstream& outfile) {
    outfile << "*START-PERSON" << endl;
    outfile << this->l_name <<", " << this->f_name << endl;
	outfile << this->birthdate->get_date() << endl;
    for (int i = 0; i < this->contacts.size(); i++) {
        outfile << this->contacts.at(i)->get_contact(true) << endl;
    }
    outfile << "*END-PERSON" << endl;
}

Person::Person(ifstream& infile) {
    // assign values for f_name, l_name, *birthdate, vector<ContactInfo*> contacts;
    string line;
    string type, value;
    int ln = 0;
    size_t comma;
    size_t fparen, bparen; //front parenthesis, back parenthesis
    while (getline(infile,line)) {
        if (line.find("*END-PERSON") != string::npos) {
            break;
        }
        else if (ln == 0) {
            comma = line.find(",");
            this->l_name = line.substr(0,comma);
            this->f_name = line.substr(comma + 2);
        }
        else if (ln == 1) {
            this->birthdate = new Date(line);
        }
        else if (line.find("Email: ") != string::npos) {
            fparen = line.find("(");
            bparen = line.find(")");
            type = line.substr(fparen+1, bparen-1-fparen);
            value = line.substr(bparen+2, line.size() - (bparen + 1));
            Email * email = new Email(type, value);
            this->contacts.push_back(email);
        }
        else if (line.find("Phone: ") != string::npos) {
            fparen = line.find("(");
            bparen = line.find(")");
            type = line.substr(fparen+1, bparen-1-fparen);
            value = line.substr(bparen+2, line.size() - (bparen + 1));
            Phone * phone = new Phone(type, value);
            this->contacts.push_back(phone);
        }
        else if (line.find("SocialNetwork: ") != string::npos) {
            fparen = line.find("(");
            bparen = line.find(")");
            type = line.substr(fparen+1, bparen-1-fparen);
            value = line.substr(bparen+2, line.size() - (bparen + 1));
            SNAccount * account = new SNAccount(type, value);
            this->contacts.push_back(account);
        }
        ln++;
    }
}

void Person::modify() {
    cout << "[1] Edit first name" << endl;
    cout << "[2] Edit last name" << endl;
    cout << "[3] Edit birthdate" << endl;
    cout << "[4] Remove contact information" << endl;
    cout << "[5] Add contact information" << endl;
    cout << "Select an option: ";

    int option;
    cin >> option;
    
    if (option == 1) {
        cout << "Enter new first name: ";
        cin >> this->f_name;
    }

    else if (option == 2) {
        cout << "Enter new last name: ";
        cin >> this->l_name;
    }

    else if (option == 3) {
        cout << "Enter new birthdate (M/D/YYYY): ";
        string bday;
        cin >> bday;
        this->birthdate->set_date(bday);
    }

    else if (option == 4) {
        remove_contact();
    }

    else if (option == 5) {
        add_contact();
    }

    this->print_person();
}
