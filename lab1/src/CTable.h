#pragma once
#include <iostream>

using namespace std;

class CTable
{

public:
	static const int default_size = 1;
	CTable();
	CTable(string name, int size);
	CTable(const CTable& otherCtable);
	~CTable();


	void setName(string newName);
	bool setNewSize(int newSize);
	CTable* pcClone();
	void printInfo();
	void doubleClone(CTable** clone0, CTable** clone1);
	void setValuesInArr(int* arr, int size);


private:

	string name;
	int size;
	int* arr;


};

