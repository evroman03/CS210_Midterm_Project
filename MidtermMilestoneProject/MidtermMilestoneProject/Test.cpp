#include "SchoolReader.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

void loadCSV(SchoolList& schoolList, const string& filename) 
{
    ifstream file(filename);
    cout << filename;
    if (!file) 
    {
        cout << "There was an error: Could not find or open file: " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) 
    {
        stringstream ss(line);
        string name, address, city, state, county;

        getline(ss, name, ',');
        getline(ss, address, ',');
        getline(ss, city, ',');
        getline(ss, state, ',');
        getline(ss, county, ',');

        //Creating a school node to insert
        SchoolNode newSchool(name, address, city, state, county);
        schoolList.insertFirst(newSchool);
    }

    file.close();
    cout << "CSV file loaded successfully!\n";
}
int main()
{
    SchoolList schoolList;
    int choice;

    string name, address, city, state, county, filename;

    while (true) 
    {
        //The "display" menu
        cout << "\nSchool Management Menu\n";
        cout << "1. Load a CSV File\n";
        cout << "2. Search for a School\n";
        cout << "3. Delete a School\n";
        cout << "4. Display All Schools\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";


        cin >> choice;
        cin.ignore(); // Clear input buffer

        switch (choice) {
        case 1:
            cout << "Enter CSV filename: ";
            getline(cin, filename);
            loadCSV(schoolList, filename);
            break;
        case 2:
            cout << "Enter school name to search: ";
            getline(cin, name);
            if (SchoolNode* found = schoolList.findByName(name)) 
            {
                cout << "\nSchool Found:\n";
                cout << "Name: " << found->name << "\nAddress: " << found->address
                    << "\nCity: " << found->city << "\nState: " << found->state
                    << "\nCounty: " << found->county << endl;
            }
            else {
                cout << "School not found.\n";
            }
            break;
        case 3:
        {
            cout << "Enter a school name to delete: ";
            getline(cin, name);
            bool temp = schoolList.deleteByName(name);
            if (temp)
            {
                cout << "School " << name << " was deleted! \n";
            }
            else
            {
                cout << "School " << name << " does not exist!\n";
            }
            break;
        }
        case 4:
            cout << "\n===== School List =====\n";
            schoolList.display();
            break;
        case 5:
            cout << "Exiting program...\n";
            return 0;
        default:
            cout << "Invalid choice. Please try again with a correct input number.\n";
        }
    }

    return 0;
}