#pragma once
#include <iostream>
#include <algorithm>
#define BASE 10


class CNumber
{
private:
	int* digits;
	int len;
	bool is_positive;

	int getIntLength(int value) const;
	bool isZero() const;
	int absCompare(const CNumber& other) const; //1 - this>other, -1 - this<other, 0 - this=other
	int digitAtPosition(int pos) const;//position od najbardziej znaczacej cyfry
	void shiftToLeft();
	void mulByDigit(int value);
	CNumber absAdd(const CNumber& cn1, const CNumber& cn2) const;
	CNumber absSub(const CNumber& bigger, const CNumber& smaller) const;
	void trim();


public:
	static const int DEFAULT_LEN = 1;
	CNumber();
	CNumber(int len);
	CNumber(const CNumber& pcOther);
	~CNumber();
	CNumber& operator=(int value);
	CNumber& operator=(const CNumber& other);
	CNumber operator+(const CNumber& other) const;
	CNumber operator-(const CNumber& other) const;
	CNumber operator*(const CNumber& other) const;
	CNumber operator/(const CNumber& other) const;
	CNumber operator^(const CNumber& other) const;
	std::string sToStr() const;
	void printInfo() const;


};


