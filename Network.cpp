#include "Network.h"
#include "misc.h"
#include <fstream>
#include <dirent.h>
#include <limits>
#include <vector>
#include <iterator>

Network::Network()
{
    // TODO
    // What should be the initial values for head, tail, and count?
    head = NULL;
    tail = NULL;
    count = 0;
}

void Network::push_front(Person *newEntry)
{
    // TODO
    // Adds a new entry to the front of the LL (where head is pointing)
    newEntry->next = head;
    newEntry->prev = NULL;

    if (head != NULL)
        head->prev = newEntry;

    if (head == NULL && tail == NULL)
    {
        tail = newEntry;
    }

    head = newEntry;
    count++;
}

void Network::push_back(Person *newEntry)
{
    // TODO
    // Adds a new entry to the back of the LL (where tail is pointing)
    newEntry->next = NULL;
    newEntry->prev = tail;

    if (tail != NULL)
        tail->next = newEntry;

    if (head == NULL && tail == NULL)
    {
        head = newEntry;
    }

    tail = newEntry;
    count++;
}

void Network::printDB()
{
    // Already done!
    cout << "Number of items: " << count << endl;
    cout << "------------------------------" << endl;
    Person *ptr = head;
    while (ptr != NULL)
    {
        ptr->print_person();
        cout << "------------------------------" << endl;
        ptr = ptr->next;
    }
}

Network::~Network()
{
    // TODO
    // Delete all the dynamically allocated items
    delete ptr;
    delete match;
}

Person *Network::search(Person *searchEntry)
{
    // TODO
    // Searches the Network to find an entry which has similar attributes as searchEntry
    // if found, returns a pointer to it, else returns NULL
    // Hint: We already implemented the == operator for two Person objects
    // Note: searchEntry is not a Person, but a Person*
    Person *ptr = head;
    while (ptr != NULL)
    {
        if (*ptr == *searchEntry)
        {
            ptr = searchEntry;
            return ptr;
        }
        ptr = ptr->next;
    }
    return NULL;
}

Person *Network::search(string fname, string lname, string bd)
{
    // TODO
    // Search based on fname, lname, and birthdate
    // if found, returns a pointer to it, else returns NULL
    // Note: two ways to implement this:
    // 1st) making a new Person with fname, lname, bdate and and using search(Person*)
    // 2nd) using fname, lname, and bd directly
    Person *ptr = new Person(fname, lname, bd);
    search(ptr);
}

vector<Person *> Network::search(string fname, string lname)
{
    Person *ptr = head;
    vector<Person *> people;
    while (ptr != NULL)
    {
        if (ptr->f_name == fname && ptr->l_name == lname)
        {
            people.push_back(ptr);
        }
        ptr = ptr->next;
    }
    return people;
}

void Network::saveDB(string filename)
{
    // TODO
    // Saves the network in file <filename>
    // Look at studentDB.db as a template of the format of our database files
    ofstream myfile(filename);
    Person *ptr = head;
    while (ptr != NULL)
    {
        ptr->write_to_file(myfile);
        ptr = ptr->next;
    }
    myfile << "*END-DATABASE" << endl;
}

void Network::loadDB(string filename)
{
    // TODO
    // Loads the network from file <filename>
    // The format of the input file is similar to saveDB
    // Look at network studentDB.db as a template
    // When a new database is being loaded, you need to delete the previous dataset
    ifstream myfile(filename);
    string line;
    getline(myfile, line);
    while (line.find("*END-DATABASE") == string::npos)
    {
        Person *ptr = new Person(myfile);
        if (search(ptr) == NULL)
        {
            push_back(ptr);
        }
        else
        {
            cout << "Duplicate entity not added." << endl;
        }
        getline(myfile, line);
    }
}

Network::Network(string fileName)
{
    // TODO
    // Hint: just call loadDB
    loadDB(fileName);
}

bool Network::remove(string fname, string lname, string bd)
{
    // TODO
    // remove the entry with matching fname, lname, bd
    // If it exists, returns true, otherwise, returns false
    Person *ptr = head;
    Person *match = new Person(fname, lname, bd);
    while (ptr != NULL)
    {
        if (*ptr == *match)
        {
            if (head == ptr)
                head = ptr->next;
            if (tail == ptr)
                tail = ptr->prev;
            if (ptr->next != NULL)
                ptr->next->prev = ptr->prev;
            if (ptr->prev != NULL)
                ptr->prev->next = ptr->next;
            delete ptr;
            count--;
            return true;
        }
        ptr = ptr->next;
    }
    return NULL;
}

Person * Network::select_person()
{
    string fname, lname;
    cout << "Searching: \n";
    cout << "First name: ";
    getline(cin, fname);
    cout << "Last name: ";
    getline(cin, lname);
    vector<Person *> p = search(fname, lname);
    if (p.empty())
    {
        cout << "Not found!" << endl;
        return NULL;
    }

    else if (p.size() == 1)
    {
        //automatically select?
        cout << "Person found!" << endl;
        p.at(0)->print_person();
        return p.at(0);
    }

    else
    {
        for (int i = 1; i < p.size() + 1; i++)
        {
            cout << "Person found!" << endl;
            cout << "[" << i << "]" << endl;
            p.at(i - 1)->print_person();
        }

        int choice;
        while (true)
        {
            cout << "Select the person you wish to edit: ";
            cin >> choice;
            if (!(choice > 0 && choice < (p.size() + 1)))
            {
                cout << "Not a valid option!" << endl;
            }
            else {
                return p.at(choice-1);
            }
        }
    }
}

void Network::showMenu()
{
    int opt;
    while (1)
    {
        cout << "\033[2J\033[1;1H";
        printMe("banner");
        cout << "Select from below: \n";
        cout << "1. Save network database \n";
        cout << "2. Load network database \n";
        cout << "3. Add a new person \n";
        cout << "4. Remove a person \n";
        cout << "5. Search & Edit \n";
        cout << "6. Print database \n";
        cout << "7. Send Email \n";
        cout << "0. Quit \n";
        cout << "\nSelect an option ... ";

        if (cin >> opt)
        {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else
        {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Wrong option! Quitting ... " << endl;
            return;
        }

        string fname, lname, fileName, bdate;
        cout << "\033[2J\033[1;1H";

        if (opt == 1)
        {
            // Already done!
            cout << "Saving network database \n";
            cout << "Enter the name of the save file: ";
            cin >> fileName;
            this->saveDB(fileName);
            cout << "Network saved in " << fileName << endl;
        }
        else if (opt == 2)
        {
            // Already done!
            cout << "Loading network database \n";
            // Note: we added a nice feature to show the files in current directory
            DIR *dir;
            struct dirent *ent;
            if ((dir = opendir("./")) != NULL)
            {
                string str;
                while ((ent = readdir(dir)) != NULL)
                {
                    str = ent->d_name;
                    if (str.size() > 3)
                    {
                        if (str.substr(str.size() - 3) == ".db")
                            cout << str << endl;
                    }
                }
                closedir(dir);
            }
            cout << "Enter the name of the load file: ";
            cin >> fileName;
            ifstream check(fileName.c_str());
            if (!bool(check))
                cout << "Warning! File does not exist! \n";
            else
            {
                loadDB(fileName);
                cout << "Network loaded from " << fileName << " with " << count << " items \n";
            }
        }
        else if (opt == 3)
        {
            // TODO
            // Prompt and get the information of a new Person
            // You need to make sure this item does not already exists!
            // If it does not exist, push it to the front of the LL
            cout << "Adding a new item (push front)\n";

            Person *ptr = new Person();
            if (search(ptr) == NULL)
            {
                push_front(ptr);
                cout << "Entity added" << endl;
            }
            else
            {
                cout << "Entity already exists" << endl;
            }

            // If it already exists:
            // cout << "Entity already exists\n"; -- not required in 2021
        }
        else if (opt == 4)
        {
            // TODO
            cout << "Removing an item \n";
            cout << "First name: ";
            getline(cin, fname);
            cout << "Last name: ";
            getline(cin, lname);
            cout << "Birthdate: ";
            cin >> bdate;

            if (search(fname, lname, bdate) != NULL)
            {
                remove(fname, lname, bdate);
                cout << "Remove Successful! \n";
            }
            else
            {
                cout << "Person not found!" << endl;
            }
            // If found and removed successfully: cout << "Remove Successful! \n";
            // else: cout << "Person not found! \n";
        }
        else if (opt == 5)
        {
            Person * c = select_person();
            if (c != NULL) {
                c->modify();
            }
        }

        else if (opt == 6)
        {
            // TODO
            cout << "Network Database: \n";
            // this should be simple ...
            printDB();
        }

        else if (opt == 7)
        {
            cout << "Send Email: \n";
            Person * c = select_person();
            bool found = false;
            int num;
            size_t bparenth;
            string fullemail, address, subject, content, attachment;
            vector<ContactInfo*> emails;
            if (c != NULL) {
                for (int i = 1; i < c->contacts.size()+1; i++) {
                    if (c->contacts.at(i-1)->get_contact(1).find("Email") != string::npos) {
                        cout << "[" << i << "]" << endl;
                        cout << c->contacts.at(i-1)->get_contact(0) << endl;
                        emails.push_back(c->contacts.at(i-1));
                        found = true;
                    }
                    if (!found) {
                        cout << "No email found for this user." << endl;
                        return;
                    }
                }
                cout << "Select an email address: ";
                cin >> num;
		        fullemail = emails.at(num-1)->get_contact(0);
		        bparenth = fullemail.find(")");
		        address = fullemail.substr(bparenth+1);
                cout << "Email subject: ";
                cin.ignore();
                getline(cin, subject);
                cout << "Email content: ";
                getline(cin, content);
		        attachment = "";

                sendEmail(address, subject, content);

            }
        }

        else if (opt == 0)
            // QUIT!
            return;

        else
            cout << "Nothing matched!\n";

        // Don't touch the lines below! :)
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cin.clear();
        cout << "\n\nPress Enter key to go back to main menu ... ";
        string temp;
        std::getline(std::cin, temp);
        cout << "\033[2J\033[1;1H";
    }
}

void Network::sendEmail(string addr, string subject, string content, string attachment){
    // Sending a command looks like:
    // echo "content" | mailx -s "subject" -a "attachment" addr;
    // TODO: Search how you can run a unix command in C++
    // TODO: You need to add double quotation character (") to both sides of strings for this command. Adding other characters (like ? in code below) should be easy, but double quotation says: I'm a character but not a typical character! 
    // string new_str = '?' + old_str + '?'
    // TODO: Complete this method

    addr = "\"" + addr + "\"";
    content = "\"" + content + "\"";
    subject = "\"" + subject + "\"";
    string cmd;
    cmd = "echo " + content + " | mailx -s " + subject + " ";
    if (attachment == "")
        cmd += addr;
    else {
        attachment = "\"" + attachment + "\"";
        cmd += "-a "  + attachment + " " + addr;
    }
    cout << "|" << cmd << "|" << endl;
    system(cmd.c_str());
}
