#define default_name  "Ctable"


#include "CTable.h"


CTable::CTable() :name(default_name), size(default_size), arr(new int[default_size])
{

	cout << "bezp: " << name << endl << endl;


}

CTable::CTable(string name, int size) :name(name)
{
	if (size < 1)
		this->size = default_size;
	else
		this->size = size;

	arr = new int[this->size];

	cout << "parametr: " << this->name << endl << endl;


}

CTable::CTable(const CTable& otherCtable) :name(otherCtable.name + "_copy"), size(otherCtable.size), arr(new int[otherCtable.size])
{
	for (int i = 0; i < size; i++)
		arr[i] = otherCtable.arr[i];
	cout << "kopiuj: " << name << endl << endl;

}

CTable::~CTable()
{
	cout << "usuwam: " << name << endl << endl;

	delete[] arr;
}

void CTable::setName(string newName)
{
	name = newName;
}

bool CTable::setNewSize(int newSize)
{
	if (newSize < 1)
		return false;

	int* tempArr = new int[newSize];
	for (int i = 0; i < newSize && i < size; i++)
		tempArr[i] = arr[i];
	size = newSize;
	delete[] arr;
	arr = tempArr;
	return true;
}

CTable* CTable::pcClone()
{
	return new CTable(*this);
}

void CTable::printInfo()
{
	cout << "Name: " << name << endl;
	cout << "Size: " << size << endl;
	cout << "Array: " << endl;
	for (int i = 0; i < size; i++)
		cout << i << ". " << arr[i] << endl;
	cout << endl;
}

void CTable::setValuesInArr(int* arr, int size)
{
	for (int i = 0; i < size && i < this->size; i++)
	{
		this->arr[i] = (*arr + i);
	}
}

void CTable::doubleClone(CTable** clone0, CTable** clone1)
{
	*clone0 = new CTable(*this);
	*clone1 = new CTable(*this);


}






