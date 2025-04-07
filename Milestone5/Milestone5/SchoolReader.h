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

	//.h file declares the structure of schoolnode and class (SchoolList),
	// and can outline the available fxs.
	SchoolNode(std::string n, std::string a, std::string c, std::string s, std::string co);
	//The .cpp file implements those functions.
		//: name(n), address(a), city(c), state(s), county(co), next(nullptr) {} 
		//Referenced this declaration from BST.h earlier this semester
};

class SchoolList {
private:
	SchoolNode* head;

public:
	SchoolList();	//For future reference and my readability im moving definition to cpp
	void insertFirst(SchoolNode school);
	void insertLast(SchoolNode school);
	bool deleteByName(std::string name); 
	//Knowing if we actually found a node to delete is nice, so i like bool or to return that node
	SchoolNode* findByName(std::string name);
	void display();
};
#endif
