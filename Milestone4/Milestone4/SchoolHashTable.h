#ifndef SCHOOLHASHTABLE_H
#define SCHOOLHASHTABLE_H

#include <iostream>
#include <vector>
#include <list>
#include "SchoolData.h"
using namespace std;

//using chaining/chained hashing bc it seems easier to just use lists than create
//a proper addressing :P 
//Plus it's not that bad
class SchoolHashTable
{
private:
    int tableSize;
    vector<list<SchoolData>> table;
    int elementsInTable;

    /// <summary>
    /// provided
    /// </summary>
    /// <param name="name"></param>
    /// <returns></returns>
    int hashFunction(const string& name) 
    {
        int hash = 0;
        for (char ch : name) {
            hash += ch;
        }
        return hash % tableSize;
    }

    void rehash()
    {
        int newTableSize = tableSize * 2;
        vector<list<SchoolData>> newTable(newTableSize);

        for (const auto& chain : table)
        {
            for (const auto& school : chain) 
            {
                //reindexing everything to the newtable by mapping with the new size
                int newIndex = hashFunction(school.name) % newTableSize;
                newTable[newIndex].push_back(school);
            }
        }

        //Move is great. this will transfer the contents of newTable to the 
        // table member variable without copying anything
        table = move(newTable);
        tableSize = newTableSize;
    }
   

public:
    //Constructor
    SchoolHashTable(int size = 10) : tableSize(size), table(size), elementsInTable(0) {}

    void insert(const SchoolData& school) 
    {
        //i think the internet collectively decided to rehash at .7 for...reasons (probably math)
        if (elementsInTable > tableSize * 0.7f)
        {
            rehash();
        }
        elementsInTable++;
        int index = hashFunction(school.name);
        table[index].push_back(school);
    }

    /// <summary>
    /// these turned out really similar to find so ill figure out something later
    /// to combine these two.
    /// </summary>
    /// <param name="name"></param>
    /// <returns></returns>
    bool deleteByName(const string& name)
    {
        int index = hashFunction(name);
        auto& schoolNodeChain = table[index];

        //go through the WHOLE list at the index recieved from the hashing 
        for (auto it = schoolNodeChain.begin(); it != schoolNodeChain.end(); ++it)
        {
            if (it->name == name)
            {
                //Erase looks to be used for vectors queues and lists. Just removing
                //at the index 'it'
                schoolNodeChain.erase(it);
                return true;
            }
        }
        return false;
    }
    SchoolData* findByName(const string& name)
    {
        int index = hashFunction(name);
        //after getting the index recieved from hashing, we can just search the list at that index
        //and return a ref to the school itself
        auto& chain = table[index];
        for (auto& school : chain) 
        {
            if (school.name == name) 
            {
                return &school;
            }
        }
        return nullptr;
    }

    void display() 
    {
        //nested for loop to cover all entries of lists of indexes
        for (int i = 0; i <= tableSize; i++)
        {
            cout << "Index " << i << ": ";
            for (const auto& school : table[i])
            {
                cout << school << " -> ";
            }
        }
    }
};

#endif
