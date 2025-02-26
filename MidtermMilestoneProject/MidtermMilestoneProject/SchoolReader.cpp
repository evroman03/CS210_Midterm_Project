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
    while (temp != nullptr)
    {
        if (temp->next->name == name)//if the next node's next matches, we found it
        {
            temp->next = temp->next->next; //set this node's next to skip the next node by going to
                                           //the next's next
            delete temp->next;  
            return true;
        }
        //if we didnt find it, move to the next node
        temp = temp->next;
    }
    //We didnt find it at all, so delete was unsuccessful
    return false;
}


