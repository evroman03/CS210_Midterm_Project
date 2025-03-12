#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include "BST.h"
#include "SchoolData.h"
#include "string"
#include "CSVReader.cpp"

using namespace std;

void loadCSV(BinarySearchTree<SchoolData>& schoolTree, vector<vector<string>>& schoolList, const string& filename, bool& isFileLoaded)
{
    schoolList = CSVReader::readCSV(filename);

    if (schoolList.empty()) 
    {
        cout << "Error: CSV file could not be read or is empty.\n";
        isFileLoaded = false;
        return;
    }

    for (const auto& row : schoolList) {
        if (row.size() < 5) {
            cerr << "Skipping invalid row\n";
            continue;
        }

        SchoolData temp(row[0], row[1], row[2], row[3], row[4]);
        schoolTree.bstInsert(temp);
    }

    isFileLoaded = true;
    cout << "CSV file loaded successfully!\n";
}

int main()
{
    BinarySearchTree<SchoolData> schoolTree;
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
        cout << "4. Display All Schools In Order\n";
        cout << "5. Display All Schools Pre Order\n";
        cout << "6. Display All Schools Post Order\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";

        cin >> choice;
        cin.ignore(); // Clear input buffer

        switch (choice)
        {
        case 1:
            cout << "Enter CSV filename: ";
            getline(cin, filename);
            loadCSV(schoolTree, schoolList, filename, isFileLoaded);
            break;

        case 2:
            if (!isFileLoaded)
            {
                cout << "Error: No CSV file loaded. Please load a file first.\n";
            }
            cout << "Enter school name to search: ";
            getline(cin, name);

            {
                SchoolData searchKey(name, "", "", "", "");  // Only name matters for searching
                const SchoolData* found = schoolTree.bstSearch(searchKey);

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
            }
            cout << "Enter school name to delete: ";
            getline(cin, name);

            {
                SchoolData deleteKey(name, "", "", "", "");  // Only name matters for deletion
                bool deleted = schoolTree.bstDeleteNode(deleteKey);

                if (deleted) {
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
            }
            cout << "\n===== School List =====\n";
            schoolTree.bstInorder();
            break;
        case 5:
            if (!isFileLoaded)
            {
                cout << "Error: No CSV file loaded. Please load a file first.\n";
            }
            cout << "\n===== School List =====\n";
            schoolTree.bstPreorder();
            break;
        case 6:
            if (!isFileLoaded)
            {
                cout << "Error: No CSV file loaded. Please load a file first.\n";
            }
            cout << "\n===== School List =====\n";
            schoolTree.bstPostorder();
            break;

        case 7:
            cout << "Exiting program...\n";
            return 0;

        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
