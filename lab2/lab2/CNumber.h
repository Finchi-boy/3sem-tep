#pragma once
#include <iostream>
#include <algorithm>

class CNumber
{
public:
	char* arr;
	int size;
	int getIntLength(const int value);
	bool is_positive;
	bool isAbsGreater(const CNumber& pc1, const CNumber& pc2);
	void absAdd(const CNumber& bigger, const CNumber& smaller, CNumber& result);
	void absSub(const CNumber& bigger, const CNumber& smaller, CNumber& result);
	void mulByDigit(const CNumber& cnumber, const char digit, CNumber& result);
	void getAnotherDigit(CNumber& result, const int index);


public:
	CNumber();
	~CNumber();
	void operator=(const int value);
	void operator=(const CNumber& pcOther);
	CNumber operator+(const CNumber& pcOther);
	CNumber operator-(const CNumber& pcOther);
	CNumber operator*(const CNumber& pcOther);
	CNumber operator/(const CNumber& pcOther);
	

	void mulByTen(const CNumber& number, CNumber& result);

	
	CNumber castFragmentToCnumber(const CNumber& cnumber, int start, int length);

	
	
	std::string sToStr();
	void printInfo() const;


};


