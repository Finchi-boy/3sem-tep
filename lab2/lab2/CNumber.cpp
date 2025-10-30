#include "CNumber.h"

using namespace std;


CNumber::CNumber()
{
	size = 1;
	arr = new char [1];
	arr[0] = 0;
	is_positive = true;
}


CNumber::~CNumber()
{
	delete[] this->arr;
}

int CNumber::getIntLength(int value)
{
	int l = 1;


	while (value / 10 != 0)
	{
		l++;
		value /= 10;

	}
	return l;
}

void CNumber::operator=(const int value)
{
	size = getIntLength(value);
	delete[] arr;
	arr = new char[size];
	int copy_value;
	if (value < 0)
	{
		copy_value = -value;
		is_positive = false;
	}
	else
	{
		copy_value = value;
		is_positive = true;
	}

	if (copy_value == 0)
	{
		arr[0] = 0;
		return;
	}

	for (int i = 1; copy_value > 0 && i <= size; i++)
	{
		arr[size - i] = copy_value % 10;
		copy_value /= 10;
	}

}


// Blad przy delete w destruktorze,
// oba wskazniki wskazuja na ta sama tablice w pamieci!
// 
// po usunieciu destruktora nie wywala programu, ale za to mamy wyciek
// 
//void CNumber::operator=(const CNumber& pcOther)
//{
//	arr = pcOther.arr;
//	size = pcOther.size;
//}





void CNumber::operator=(const CNumber& pcOther)
{
	if (this == &pcOther)
		return;
	delete[] arr;
	size = pcOther.size;
	is_positive = pcOther.is_positive;
	arr = new char[size];
	for (int i = 0; i < size; i++)
	{
		arr[i] = pcOther.arr[i];
	}
	
}


CNumber CNumber::operator+(const CNumber& pcOther)
{
	CNumber result;
	cout << "z dodawania" << result.sToStr() << endl;

	if (is_positive == pcOther.is_positive)//ten sam znak, wiec zwykle dodawanie bez zmiany znaku
	{
		absAdd(*this, pcOther, result);
	}
	else//mamy rozne znaki liczb, wiec bedziemy odejmowac i zmieniac znak wyniku
	{

		if (isAbsGreater(*this, pcOther))
		{
			absSub(*this, pcOther, result);
		}
		else
		{

			absSub(pcOther, *this, result);
			//is_positive = !is_positive;
		}
	}
	return result;

}


CNumber CNumber::operator-(const CNumber& pcOther)
{
	CNumber result;
	if (is_positive == pcOther.is_positive)
	{
		if (isAbsGreater(*this, pcOther))
		{
			absSub(*this, pcOther, result);

			
		}
		else
		{
			absSub(pcOther, *this, result);
		}
	}
	else
	{
		absAdd(*this, pcOther, result);
	}

	return result;

}


CNumber CNumber::operator*(const CNumber& pcOther)
{
	CNumber acc;
	CNumber result;
	result = 0;

	for (int i = 0; i < pcOther.size; i++)
	{
		mulByTen(result, result);
		mulByDigit(*this, pcOther.arr[i], acc);
		absAdd(result, acc, result);

	}

	result.is_positive = (this->is_positive == pcOther.is_positive);


	return result;

}

CNumber CNumber::operator/(const CNumber& pcOther)
{
	CNumber result;
	CNumber acc;
	acc.arr[0] = arr[0];
	int counter;
	for (int i = 1; i < size; i++)
	{
		if (!(acc.size == 1 && acc.arr[0] == 0 && arr[i] == 0))
			getAnotherDigit(acc, arr[i]);
		counter = 0;
		while (isAbsGreater(acc, pcOther))
		{
			counter++;
			absSub(acc, pcOther, acc);
		}
		mulByTen(result, result);
		result.arr[result.size - 1] = counter;
		

	}



	result.is_positive = (this->is_positive == pcOther.is_positive);
	return result;

}

void CNumber::getAnotherDigit(CNumber& acc, const int val)
{
	//problem gdy acc=0000
	char* temp = acc.arr;
	int old_size = acc.size;   // tu bierzesz aktualny rozmiar acc po absSub
	acc.arr = new char[old_size + 1];
	for (int i = 0; i < old_size; i++)
		acc.arr[i] = temp[i];
	acc.arr[old_size] = val;
	acc.size = old_size + 1;
	delete[] temp;
}

void CNumber::mulByTen(const CNumber& cnumber, CNumber& result)
{
		
	if (cnumber.size == 1 && cnumber.arr[0] == 0)
	{
		result = cnumber;
		return;
	}

	char* temp_arr = new char[cnumber.size + 1];
	for (int i = 0; i < cnumber.size; i++)
	{
		temp_arr[i] = cnumber.arr[i];
	}
	delete[] result.arr;
	result.size =cnumber.size+1;
	result.arr = new char[result.size];
	for (int i = 0; i < cnumber.size; i++)
	{
		result.arr[i] = temp_arr[i];
	}
	result.arr[result.size - 1] = 0;
	delete[] temp_arr;
}


void CNumber::mulByDigit(const CNumber& cnumber, const char digit, CNumber& result)
{
	if (digit == 0)
	{
		result = CNumber();
		return;
	}
	if (digit == 1)
	{
		result = cnumber;
		return;
	}
	int temp_size = cnumber.size+1;
	char* temp_arr = new char[temp_size];
	char carry = 0;
	for (int i = 1; i < temp_size; i++)
	{
		temp_arr[temp_size - i] = cnumber.arr[cnumber.size - i] * digit+carry;
		carry = temp_arr[temp_size - i] / 10;
		temp_arr[temp_size - i] %= 10;

	}
	temp_arr[0] = carry;

	int empty_cells = 0;
	while (temp_arr[empty_cells] == 0 && empty_cells < cnumber.size - 1)
		empty_cells++;
	result.size = temp_size - empty_cells;

	delete[] result.arr;
	result.arr = new char[result.size];

	for (int i = 0; i < result.size; i++)
		result.arr[i] = temp_arr[empty_cells + i];

	delete[] temp_arr;

}




void CNumber::absAdd(const CNumber& a, const CNumber& b, CNumber& result)
{
	int temp_size = max(a.size, b.size)+1;
	char* temp_arr = new char[temp_size];
	char carry = 0;
	for (int i = 1; i <temp_size; i++)
	{
		temp_arr[temp_size - i] = ((i <= a.size) ? a.arr[a.size - i] : 0)+ carry;
		temp_arr[temp_size - i] += (i <= b.size) ? b.arr[b.size - i] : 0;

		if (temp_arr[temp_size - i] > 9)
		{
			temp_arr[temp_size - i] -= 10;
			carry = 1;
		}
		else carry = 0;
	}
	temp_arr[0] = carry;



	int empty_cells = 0;
	while (temp_arr[empty_cells] == 0 && empty_cells < temp_size-1)
		empty_cells++;


	result.is_positive = a.is_positive;
	result.size= temp_size - empty_cells;

	delete[] result.arr;
	result.arr = new char[result.size];

	for (int i = 0; i < result.size; i++)
		result.arr[i] = temp_arr[empty_cells + i];

	delete[] temp_arr;


}

void CNumber::absSub(const CNumber& bigger, const CNumber& smaller, CNumber& result)
{
	char* temp_arr = new char[bigger.size];
	char carry = 0;
	for (int i = 1; i <= bigger.size; i++)
	{
		temp_arr[bigger.size - i] = bigger.arr[bigger.size - i] - carry;
		temp_arr[bigger.size - i] -= (i <= smaller.size) ? smaller.arr[smaller.size - i] : 0;
		if (temp_arr[bigger.size - i] < 0)
		{
			temp_arr[bigger.size - i] += 10;
			carry = 1;
		}
		else
			carry = 0;

	}



	result.is_positive = bigger.is_positive;
	int empty_cells = 0;
	while (temp_arr[empty_cells] == 0 && empty_cells < bigger.size-1)
		empty_cells++;
	result.size = bigger.size - empty_cells;

	delete[] result.arr;
	result.arr = new char[result.size];

	for (int i = 0; i < result.size; i++)
		result.arr[i] = temp_arr[empty_cells + i];

	delete[] temp_arr;


}

string CNumber::sToStr()
{
	string result = "";
	if (!is_positive)
		result += "-";
	for (int i = 0; i < size; i++)
	{
		result = result + char(arr[i] + 48);
	}

	return result;
}

bool CNumber::isAbsGreater(const CNumber& pc1, const CNumber& pc2)
{
	if (pc1.size > pc2.size)
		return true;
	if (pc2.size > pc1.size)
		return false;

	for (int i = 0; i < pc1.size; i++)
	{
		if (pc1.arr[i] >=pc2.arr[i])
			return true;
		if (pc2.arr[i] > pc1.arr[i])
			return false;
	}
	return false;
}

void CNumber::printInfo() const
{
	if (!is_positive)
		std::cout << "-";
	for (int i = 0; i < size; i++)
		std::cout << int(arr[i])<<",";
	cout << endl <<"Size:"<< size << endl;
}

