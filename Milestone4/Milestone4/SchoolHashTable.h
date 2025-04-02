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

    int hashFunction(const string& name) 
    {
        int hash = 0;
        for (char ch : name) {
            hash += ch;
        }
        return hash % tableSize;
    }

   

public:
    SchoolHashTable(int size = 10) : tableSize(size), table(size) {}

    void insert(const SchoolData& school) 
    {
        int index = hashFunction(school.name);
        table[index].push_back(school);
    }
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
};

#endif
