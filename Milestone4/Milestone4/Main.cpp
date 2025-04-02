#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include "SchoolHashTable.h"
#include "SchoolData.h"
#include "string"
#include "CSVReader.cpp"

using namespace std;

//void loadCSV(BinarySearchTree<SchoolData>& schoolTree, vector<vector<string>>& schoolList, const string& filename, bool& isFileLoaded)
void loadCSV(SchoolHashTable& schoolHasher, vector<vector<string>>& schoolList, const string& filename, bool& isFileLoaded)
{
    schoolList = CSVReader::readCSV(filename);

    if (schoolList.empty())
    {
        cout << "Error: CSV file could not be read or is empty. Did you forget to include the file extension?\n";
        isFileLoaded = false;
        return;
    }
    if (isFileLoaded)
    {
        //schoolTree.clear();
        cout << "\n Previous file cleared. Starting to load new file... \n";
    }
    for (const auto& row : schoolList) {
        if (row.size() < 5) {
            cerr << "Skipping invalid row\n";
            continue;
        }

        SchoolData temp(row[0], row[1], row[2], row[3], row[4]);
        schoolHasher.insert(temp);
    }

    isFileLoaded = true;
    cout << "CSV file loaded successfully!\n";
}

int main()
{
    SchoolHashTable myTable = SchoolHashTable(50);
    //BinarySearchTree<SchoolData> schoolTree;
    vector<vector<string>> schoolList;
    string name, address, city, state, county, filename;
    int choice;
    bool isFileLoaded = false;

    while (true)
    {
        // Display menu
        cout << "\nSchool Management Menu\n";
        cout << "1. Load a CSV File\n";
        cout << "2. Search for a School\n";
        cout << "3. Delete a School\n";
        cout << "4. Display All Schools\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";

        cin >> choice;
        cin.ignore(); // Clear input buffer

        switch (choice)
        {
        case 1:
            cout << "Enter CSV filename: ";
            getline(cin, filename);
            loadCSV(myTable, schoolList, filename, isFileLoaded);
            break;

        case 2:
            if (!isFileLoaded)
            {
                cout << "Error: No CSV file loaded. Please load a file first.\n";
                break;
            }
            cout << "Enter school name to search: ";
            getline(cin, name);
            {
                //SchoolData searchKey(name, "", "", "", "");  // Only name matters for searching
                const SchoolData* found = myTable.findByName(name);

                if (found != nullptr)
                {
                    cout << "\nSchool Found:\n" << *found << endl;
                }
                else
                {
                    cout << "School not found.\n";
                }
            }
            break;

        case 3:
            if (!isFileLoaded)
            {
                cout << "Error: No CSV file loaded. Please load a file first.\n";
                break;
            }
            cout << "Enter school name to delete: ";
            getline(cin, name);

            {
                //SchoolData deleteKey(name, "", "", "", "");  // Only name matters for deletion
                bool deleted = myTable.deleteByName(name);
                if (deleted) 
                {
                    cout << "School " << name << " was deleted!\n";
                }
                else {
                    cout << "School " << name << " does not exist!\n";
                }
            }
            break;

        case 4:
            if (!isFileLoaded)
            {
                cout << "Error: No CSV file loaded. Please load a file first.\n";
                break;
            }
            cout << "\n===== School List =====\n";
            myTable.display();
            break;

        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }
    return 0;
}
