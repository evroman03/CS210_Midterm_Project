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
}
/// <summary>
/// Without 'new' the object would be created on the stack and disappear when the function ends. So
/// instead of taking the school.next and pointing it to head, we have to make a new one.
/// </summary>
/// <param name="school"></param>
void SchoolList::insertFirst(SchoolNode school)
{
    SchoolNode* newSchool = 
        new SchoolNode(school.name, school.address, school.city, school.state, school.county);

    //make the new node's next the current head
    newSchool->next = head;
    //turn the current head into the newSchool to complete the insert
    head = newSchool;
}

/// <summary>
/// This function checks the head and then makes a temporary node that copies/follows the node list
/// When the temporary node's next is null, it sets itself to newSchool to add at the end
/// </summary>
/// <param name="school"></param>
void SchoolList::insertLast(SchoolNode school)
{
    SchoolNode* newSchool = 
        new SchoolNode(school.name, school.address, school.city, school.state, school.county);

    //Checking head
    if (head == nullptr)
    {
        head = newSchool;
        return;
    }


    SchoolNode* temp = head; // temp is a pointer to the actual node
    while (temp->next != nullptr) 
    {
        temp = temp->next;
    }
    temp->next = newSchool;
}

/// <summary>
/// Similar to insertLast, this makes a temporary node to follow along until its name matches the
/// target name, in which case it returns a pointer to that node. We can take that node and affect
/// the real list
/// </summary>
/// <param name="name"></param>
/// <returns></returns>
SchoolNode* SchoolList::findByName(string name) 
{
    SchoolNode* temp = head; // reminder, temp is a pointer to the actual node
    while (temp != nullptr) 
    {
        if (temp->name == name) 
        {
            return temp;
        }
        temp = temp->next;
    }
    return nullptr;
}

bool SchoolList::deleteByName(string name)
{
    SchoolNode* temp = head; // reminder, temp is a pointer to the actual node
    if (head == nullptr) //nothing in the list
    {
        return false;
    }
    if (head->name == name) //if the head is the very thing we want, delete it and move its next
    {
        SchoolNode* temp2 = head;
        head = head->next;
        delete temp2;
        return true;
    }
   
    while (temp->next != nullptr && temp->next->name != name)
    {
        temp = temp->next;
    }

    if (temp->next != nullptr) //we looped and found the node and double checked its not null
    {
        SchoolNode* toDelete = temp->next;
        temp->next = temp->next->next;
        delete toDelete;
        return true;
    }
    return false;
}

void SchoolList::display()
{
    SchoolNode* temp = head; // reminder, temp is a pointer to the actual node

    while (temp != nullptr) 
    {
        cout << "Name: " << temp->name << ", Address: " << temp->address
            << ", City: " << temp->city << ", State: " << temp->state
            << ", County: " << temp->county << endl;

        temp = temp->next;
    }
}


