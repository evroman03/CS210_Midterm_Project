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

   
};

#endif
