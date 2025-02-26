#include <iostream>
#include "SchoolReader.h"

using namespace std;

//Defining constructors of schoolnode and school list
SchoolNode::SchoolNode(string n, string a, string c, string s, string co) 
{
    name = n;
    address = a;
    city = c;
    state = s;
    county = co;
    next = nullptr;
}

SchoolList::SchoolList()
{
    head = nullptr;
};
