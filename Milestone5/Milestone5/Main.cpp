#include <fstream>
#include <iostream>
#include <random>
#include <algorithm>
#include "Timer.h"
#include "CSVReader.cpp"
#include "SchoolData.h"
#include "SchoolReader.h"
#include "SchoolHashTable.h"
#include "BST.h"

using namespace std;

int main() {
    const string filename = "Illinois_Peoria_Schools.csv";
    vector<vector<string>> csvData = CSVReader::readCSV(filename);
    vector<SchoolData> allSchools;

    // Populate vector of SchoolData
    for (const auto& row : csvData) {
        if (row.size() >= 5) {
            allSchools.emplace_back(row[0], row[1], row[2], row[3], row[4]);
        }
    }

    const size_t testInterval = 5; // Change this to control testing frequency

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(allSchools.begin(), allSchools.end(), g);

    SchoolList schoolList;
    BinarySearchTree<SchoolData> schoolBST;
    SchoolHashTable schoolHash(10007);

    ofstream output("IPSTimings1.csv");
    output << "Structure,Operation,Index,TimeMicroseconds\n";

    std::uniform_int_distribution<size_t> dist(0, allSchools.size() - 1);

    for (size_t i = 0; i < allSchools.size(); ++i) {
        SchoolData& school = allSchools[i];
        std::cout << i << endl;
        // Always insert, but only time every testInterval
        if (i % testInterval == 0) {
            double timeLL = Timer::time_function([&]() {
                schoolList.insertLast(SchoolNode(school.name, school.address, school.city, school.state, school.county));
                });
            output << "LinkedList,Insert," << i << "," << timeLL << "\n";

            double timeBST = Timer::time_function([&]() {
                schoolBST.bstInsert(school);
                });
            output << "BST,Insert," << i << "," << timeBST << "\n";

            double timeHash = Timer::time_function([&]() {
                schoolHash.insert(school);
                });
            output << "HashMap,Insert," << i << "," << timeHash << "\n";
        }
        else {
            schoolList.insertLast(SchoolNode(school.name, school.address, school.city, school.state, school.county));
            schoolBST.bstInsert(school);
            schoolHash.insert(school);
        }

        // Only test search/delete every testInterval
        if (i % testInterval == 0) 
        {
            const SchoolData& randomSchool = allSchools[dist(g)];
            const string& randomName = randomSchool.name;

            // Search timings
            double timeLLSearch = Timer::time_function([&]() {
                schoolList.findByName(randomName);
                });
            output << "LinkedList,Search," << i << "," << timeLLSearch << "\n";

            double timeBSTSearch = Timer::time_function([&]() {
                schoolBST.bstSearch(randomSchool);
                });
            output << "BST,Search," << i << "," << timeBSTSearch << "\n";

            double timeHashSearch = Timer::time_function([&]() {
                schoolHash.findByName(randomName);
                });
            output << "HashMap,Search," << i << "," << timeHashSearch << "\n";

            // Delete timings on fresh copies
            SchoolList tempList;
            BinarySearchTree<SchoolData> tempBST;
            SchoolHashTable tempHash(10007);

            for (size_t j = 0; j <= i; ++j) {
                const SchoolData& s = allSchools[j];
                tempList.insertLast(SchoolNode(s.name, s.address, s.city, s.state, s.county));
                tempBST.bstInsert(s);
                tempHash.insert(s);
            }

            double timeLLDelete = Timer::time_function([&]() {
                tempList.deleteByName(randomName);
                });
            output << "LinkedList,Delete," << i << "," << timeLLDelete << "\n";

            double timeBSTDelete = Timer::time_function([&]() {
                tempBST.bstDeleteNode(randomSchool);
                });
            output << "BST,Delete," << i << "," << timeBSTDelete << "\n";

            double timeHashDelete = Timer::time_function([&]() {
                tempHash.deleteByName(randomName);
                });
            output << "HashMap,Delete," << i << "," << timeHashDelete << "\n";
        }
    }

    output.close();
    std::cout << "Timing complete! Results written to timings.csv\n";
    return 0;
}

