#include <iostream>
#include "CTable.h"

using namespace std;

const int default_value = 34;

void print_arr(int* arr, int size);
void create_filled_array(int size);
bool alloc_2d_table(int*** arr, int sizeX, int sizeY);
bool alloc_2d_table_contiguous(int*** arr, int sizeX, int sizeY);
bool dealloc_2d_table(int*** arr, int sizeX, int sizeY);
bool dealloc_2d_table_contiguous(int*** arr);
void mod_tab(CTable* pcTab, int newSize);
void mod_tab(CTable pcTab, int newSize);


int main()
{
	// automatyczne sprawdzanie wycieków po zakoñczeniu programu
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	create_filled_array(10);
	int*** arrPointer;
	int** arr;
	arrPointer = &arr;
	alloc_2d_table(&arr, 5, 10);
	dealloc_2d_table(arrPointer, 5, 10);

	alloc_2d_table_contiguous(&arr, 5, 10);
	dealloc_2d_table_contiguous(arrPointer);

	CTable* one = new CTable();
	CTable* two = new CTable("testowy", 5);
	CTable* three = new CTable(*two);
	delete one;
	delete two;
	delete three;

	CTable* test = new CTable("test", 5);
	mod_tab(test, 3);
	test->printInfo();

	mod_tab(*test, 4);
	test->printInfo();

	delete test;


	cout << "Modyfikacja\n" << "---------------------------------\n\n\n";


	CTable org = CTable("Org", 4);
	CTable* clone0, * clone1;
	int* arr2 = new int[4];
	for (int i = 0; i < 4; i++)
		arr2[i] = i + 1;
	org.setValuesInArr(arr2, 4);
	org.printInfo();


	org.doubleClone(&clone0, &clone1);

	org.printInfo();
	clone0->printInfo();
	clone1->printInfo();

	delete clone0;
	delete clone1;
	delete[] arr2;





	return 0;


}

//Zabezpiecz funkcjê przed nieprawid³ow¹ wartoœci¹ paramteru iSize. Czy ta funkcja
//bêdzie u¿yteczna i wygodna jeœli bêdzie wypisywaæ wartoœci na ekran w przypadku
//b³êdu?
// 
// nie
// 
//Czy wartoœæ 34 powinna wystêpowaæ bezpoœrednio w kodzie
//v_alloc_table_fill_34? 
//
// nie



void create_filled_array(int size)
{
	if (size <= 0)
	{
		return;
	}
	int* arr;
	arr = new int[size];
	for (int i = 0; i < size; i++)
		arr[i] = default_value;
	delete[] arr;

}


void print_arr(int* arr, int size)
{
	for (int i = 0; i < size; i++)
		cout << i + 1 << ". " << arr[i] << endl;
}


bool alloc_2d_table(int*** arr, int sizeX, int sizeY)
{
	if (sizeX < 1 || sizeY < 1)
		return false;


	*arr = new int* [sizeX];
	for (int i = 0; i < sizeX; i++)
	{
		(*arr)[i] = new int[sizeY];

	}
	return true;


}

bool alloc_2d_table_contiguous(int*** arr, int sizeX, int sizeY)
{
	if (sizeX < 1 || sizeY < 1)
		return false;


	int* data = new int[sizeX * sizeY]; //tworzymy jeden ciagly blok w pamieci zamiast kilku oddzielnych
	/*int t[x][y];
	* int t[x] przesuwa o x wierszy, czyli tak naprawde jest to wskazanie na tablice int'ow, zatem t[] to tablica wskaznikow na tablice int'ow,
	* lecz formalnie nie jest to zwykly wskaznik (cpp doslownie uznaje go za tablice, nie za wskaznik.
	*
	* ZAPYTAC O WYTLUMACZENIE!!!
	*
	* t[i][j] = *(*(t+i)+j) dziala dopoki 0<=i<x i 0<=j<y
	* ale jest to ciagly blok w pamieci, wiec do komorki t[i][j] mozemy sie dostac uzywajac t[0][i*y+j] lub *(*t+(i*y+j))
	*/
	*arr = new int* [sizeX];
	for (int i = 0; i < sizeX; i++)
	{
		(*arr)[i] = &data[sizeY * i];
	}
	return true;

}


bool dealloc_2d_table(int*** arr, int sizeX, int sizeY)// size y niepotrzebne
{
	if (sizeX < 1 || sizeY < 1)
		return false;

	for (int i = 0; i < sizeX; i++)
		delete[](*arr)[i];
	delete[] * arr;
	return true;
}

bool dealloc_2d_table_contiguous(int*** arr)
{
	delete[](*arr)[0];
	delete[] * arr;

	return true;

}



void mod_tab(CTable* pcTab, int newSize)
{
	pcTab->printInfo();
	pcTab->setNewSize(newSize);

}

void mod_tab(CTable pcTab, int newSize) //pracuje na kopii
{
	pcTab.printInfo();
	pcTab.setNewSize(newSize);


}