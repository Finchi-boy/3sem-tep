#include "CNumber.h"

using namespace std;

CNumber::CNumber()
{
	len = DEFAULT_LEN;
	digits = new int[DEFAULT_LEN];
	for (int i = 0; i < len; i++)
		digits[i] = 0;
	is_positive = true;
}

CNumber::CNumber(int len)
{
	this->len = len;
	digits = new int[len];
	for (int i = 0; i < len; i++)
		digits[i] = 0;
	is_positive = true;
}

CNumber::CNumber(const CNumber& pcOther)
{
	len = pcOther.len;
	digits = new int[len];
	for (int i = 0; i < len; i++)
		digits[i] = pcOther.digits[i];
	is_positive = pcOther.is_positive;
}

CNumber::~CNumber()
{
	delete[] this->digits;
}

int CNumber::getIntLength(int value) const
{
	int l = 1;
	while (value / BASE != 0)
	{
		value /= BASE;
		l++;
	}
	return l;
}

bool CNumber::isZero() const
{
	for (int i = 0; i < len; i++)
		if (digits[i] != 0)
			return false;
	return true;
}

int CNumber::absCompare(const CNumber& other) const
{
	if (len > other.len)
		return 1;
	if (len < other.len)
		return -1;

	for (int i = 0; i < len; i++)
	{
		if (this->digitAtPosition(i) > other.digitAtPosition(i))
			return 1;
		if (other.digitAtPosition(i) > this->digitAtPosition(i))
			return -1;
	}
	return 0;
}

int CNumber::digitAtPosition(int pos) const
{
	return (pos < len && pos >= 0) ? (digits[pos]) : (0);
}

void CNumber::trim()
{
	if (len == 0)
		return;

	int empty_cells = 0;
	while (empty_cells < len && digits[empty_cells] == 0)
		empty_cells++;

	int new_len = len - empty_cells;
	if (new_len == 0)
	{
		delete[] digits;
		digits = new int[1];
		len = 1;
		digits[0] = 0;
		return;
	}

	int* new_digits = new int[new_len];
	for (int i = 0; i < new_len; i++)
	{
		new_digits[i] = digits[i + empty_cells];
	}
	delete[] digits;

	digits = new_digits;
	len = new_len;

}

void CNumber::shiftToLeft()
{
	if (this->isZero())
		return;
	int* new_digits = new int[len + 1];
	for (int i = 0; i <= len; i++)
		new_digits[i] = this->digitAtPosition(i);

	len += 1;
	delete[] digits;
	digits = new_digits;
}

void CNumber::mulByDigit(int value)
{
	if (value == 0 || this->isZero())
		return;

	int* new_digits = new int[len + 1];
	int carry = 0;
	for (int i = 1; i <= len; i++)
	{
		new_digits[len - i + 1] = digits[len - i] * value + carry;
		carry = new_digits[len - i + 1] / BASE;
		new_digits[len - i + 1] %= BASE;
	}
	new_digits[0] = carry;
	delete[] digits;
	digits = new_digits;
	len += 1;
	this->trim();

}

CNumber& CNumber::operator=(int val)
{
	is_positive = val >= 0;
	val = abs(val);
	len = getIntLength(val);
	delete[] digits;
	digits = new int[len];
	for (int i = len - 1; i >= 0; i--)
	{
		digits[i] = val % BASE;
		val /= BASE;
	}
	return *this;
}

CNumber& CNumber::operator=(const CNumber& other)
{
	if (this == &other)
		return *this;

	len = other.len;
	delete[] digits;
	digits = new int[len];
	for (int i = 0; i < len; i++)
	{
		digits[i] = other.digits[i];
	}
	this->is_positive = other.is_positive;
	return *this;


}

CNumber CNumber::operator+(const CNumber& other) const
{
	CNumber result;

	if (is_positive == other.is_positive)
	{
		result = absAdd(*this, other);
		result.is_positive = is_positive;
	}
	else
	{
		switch (absCompare(other))
		{
		case 1:
			result = absSub(*this, other);
			result.is_positive = is_positive;
			break;

		case -1:
			result = absSub(other, *this);
			result.is_positive = other.is_positive;
			break;

		}
	}
	return result;

}

CNumber CNumber::operator-(const CNumber& other) const
{
	CNumber opposite_cnumber = other;
	opposite_cnumber.is_positive = !opposite_cnumber.is_positive;
	return *this + opposite_cnumber;
}

CNumber CNumber::operator*(const CNumber& other) const
{
	if (this->isZero() || other.isZero())
		return CNumber();
	CNumber result(len);
	CNumber acc;
	for (int i = 0; i < other.len; i++)
	{
		result.shiftToLeft();
		acc = *this;
		acc.mulByDigit(other.digits[i]);
		result = result + acc;
	}
	result.trim();
	result.is_positive = (is_positive == other.is_positive);
	return result;

}

CNumber CNumber::operator/(const CNumber& other) const
{
	CNumber result(len);
	if (other.isZero())
	{
		//nie mozna dzielic przez 0
		result = -1;
		return result;
	}


	CNumber acc;
	int counter;
	for (int i = 0; i < len; i++)
	{
		acc.shiftToLeft();
		acc.digits[acc.len - 1] = digits[i];
		//acc.trim();
		counter = 0;
		while (acc.absCompare(other) != -1)
		{
			counter++;
			acc = absSub(acc, other);

		}
		result.shiftToLeft();
		result.digits[result.len - 1] = counter;

	}
	result.trim();
	result.is_positive = (this->is_positive == other.is_positive);
	return result;

}

CNumber CNumber::operator^(const CNumber& other) const
{
	int* temp_arr = new int[len];
	int new_length = 0;
	int i;
	for (i = 1; i <= len; i++)
	{

		//cout << digitAtPosition(len - i) << " - " << other.digitAtPosition(other.len - i) << endl;
		if (digits[len - i] != other.digitAtPosition(other.len - i) || i > other.len)
		{
			temp_arr[new_length] = digits[len - i];
			new_length++;
		}
	}
	CNumber result(new_length);
	for (int i = 1; i <= new_length; i++)
	{
		result.digits[new_length - i] = temp_arr[i - 1];
	}
	delete[] temp_arr;
	return result;



}




CNumber CNumber::absAdd(const CNumber& cn1, const CNumber& cn2) const
{
	CNumber result = CNumber(max(cn1.len, cn2.len) + 1);
	int carry = 0;
	for (int i = 1; i <= result.len; i++)
	{
		result.digits[result.len - i] = cn1.digitAtPosition(cn1.len - i) + cn2.digitAtPosition(cn2.len - i) + carry;
		carry = result.digits[result.len - i] / BASE;
		result.digits[result.len - i] %= BASE;
	}
	result.trim();
	return result;
}


CNumber CNumber::absSub(const CNumber& bigger, const CNumber& smaller) const
{
	CNumber result = CNumber(bigger.len);
	int carry = 0;
	for (int i = 1; i <= result.len; i++)
	{
		result.digits[result.len - i] = bigger.digitAtPosition(bigger.len - i) - smaller.digitAtPosition(smaller.len - i) - carry;
		if (result.digits[result.len - i] < 0)
		{
			result.digits[result.len - i] += BASE;
			carry = 1;
		}
		else
		{
			carry = 0;
		}

	}
	result.trim();
	return result;
}


string CNumber::sToStr() const
{
	string result = "";
	if (!is_positive)
		result += "-";
	for (int i = 0; i < len; i++)
	{
		result += char(digits[i] + 48);
	}

	return result;
}

void CNumber::printInfo() const
{
	if (!is_positive)
		std::cout << "-";
	for (int i = 0; i < len; i++)
		std::cout << digits[i];
	cout << endl << "Size:" << len << endl;
}

