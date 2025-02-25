#ifndef SCHOOLREADER_H
#define SCHOOLREADER_H

#include <iostream>
#include <string>

struct SchoolNode
{
	std::string name;
	std::string address;
	std::string city;
	std::string state;
	std::string county;

	SchoolNode* next;

	SchoolNode(std::string n, std::string a, std::string c, std::string s, std::string co)
		: name(n), address(a), city(c), state(s), county(co), next(nullptr) {} //Referenced this declaration from BST.h earlier this semester
};

class SchoolList {
private:
	SchoolNode* head;

public:
	SchoolList() : head(nullptr) {} ;
	void insertFirst(std::string name, std::string address, std::string city, std::string state, std::string county);
	void insertLast(std::string name, std::string address, std::string city, std::string state, std::string county);
	void deleteByName(std::string name);
	SchoolNode* findByName(std::string name);
	void display();
};
#endif
