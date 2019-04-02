#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;
void reverse(char s[])
{
	int i, j;
	char c;

	for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}
char* itoa_plus(int64_t n, char s[])
{
	int64_t i;
	i = 0;
	do {
		s[i++] = n % 10 + '0';  
	} while ((n /= 10) > 0);  
	s[i] = '\0';
	reverse(s);
	return s;
}

class BigInt
{
public:
	BigInt();
	BigInt(const BigInt& copied)
		: data(new char[copied.Size])
		, Size(copied.Size)
		, flag(copied.flag)
	{
		std::copy(copied.data, copied.data + Size, data);
	}
	BigInt(const int64_t& number)
	{
		if (number == 0)
		{
			this->Size = 1;
			this->flag = 0;
			this->data = new char[Size];
			this->data[0] = 0 + '0';
		}
		else
		{
			int64_t num = number;
			if (num > 0) flag = 0;
			else
			{
				flag = 1;
				num = -1 * number;
			}
			size_t count = 0;
			while (num) {
				num /= 10;
				count++;
			}
			if (flag == 1) num = -1 * number;
			else num = number;
			Size = count;
			char* ptr = new char[Size + 1];
			data = ptr;
			data = itoa_plus(num, ptr);
		}
	}
	~BigInt();
	BigInt& operator=(const BigInt& copied)
	{
		if (this == &copied)
			return *this;
		char* ptr = new char[copied.Size + 1];
		delete[]data;
		data = ptr;
		flag = copied.flag;
		Size = copied.Size;
		copy(copied.data, copied.data + Size, data);
		return *this;
	}
	BigInt& operator=(const int64_t& number)
	{
		int64_t num = number;
		if (number > 0) flag = 0;
		else
		{
			flag = 1;
			num = -1 * number;
		}
		size_t count = 0;
		while (num) {
			num /= 10;
			count++;
		}
		if (flag == 1) num = -1 * number;
		else num = number;
		Size = count;
		char* ptr = new char[Size + 1];
		delete[] data;
		data = ptr;
		data = itoa_plus(num, ptr);
		return *this;
	}
	friend std::ostream& operator<<(std::ostream &out, const BigInt &BigInt);
	bool operator>(const BigInt& other) const;
	bool operator<(const BigInt& other) const;
	bool operator<=(const BigInt& other) const;
	bool operator>=(const BigInt& other) const;
	bool operator==(const BigInt& other) const;
	bool operator!=(const BigInt& other) const;
	bool operator>(const int& other) const;
	bool operator<(const int& other) const;
	bool operator<=(const int& other) const;
	bool operator>=(const int& other) const;
	bool operator==(const int& other) const;
	bool operator!=(const int& other) const;
	BigInt operator-() const;
	BigInt operator+(const BigInt& other) const;
	BigInt operator-(const BigInt& other) const;
	BigInt operator+(const int& other) const;
	BigInt operator-(const int& other) const;
private:
	size_t Size;
	char* data;
	bool flag;
};

BigInt::BigInt()
{
	this->Size = 1;
	this->flag = 0;
	this->data = new char[Size];
	this->data[0] = 0 + '0';
}

BigInt::~BigInt()
{
}
std::ostream& operator<<(std::ostream &out, const BigInt &BigInt)
{
	if (BigInt.flag) out << "-";
	for (size_t i = 0; i < BigInt.Size; i++)
		out << BigInt.data[i];
	return out;
}
bool BigInt::operator>(const BigInt& other) const
{
	if (*this == other)
		return 0;
	if (this->flag > other.flag) return 0;
	if (this->flag < other.flag) return 1;
	if (this->Size > other.Size) return 1;
	if (this->Size < other.Size) return 0;
	for (size_t i = 0; i < this->Size; i++)
	{
		if (this->data[i] > other.data[i])
		{
			if (this->flag) return 0;
			else return 1;
		}
		else if (this->data[i] < other.data[i])
		{
			if (this->flag) return 1;
			else return 0;
		}
	}
	return 0;
}
bool BigInt::operator>(const int& number) const
{
	BigInt other = number;
	if (this->flag > other.flag) return 0;
	if (this->flag < other.flag) return 1;
	if (this->Size > other.Size) return 1;
	if (this->Size < other.Size) return 0;
	for (size_t i = 0; i < this->Size; i++)
	{
		if (this->data[i] > other.data[i]) return 1;
	}
	return 0;
}

bool BigInt::operator<(const BigInt& other) const
{
	if (*this == other)
		return 0;
	if (this->flag > other.flag) return 1;
	if (this->flag < other.flag) return 0;
	if (this->Size > other.Size) return 0;
	if (this->Size < other.Size) return 1;
	for (size_t i = 0; i < this->Size; i++)
	{
		if (this->data[i] > other.data[i])
		{
			if (this->flag) return 1;
			else return 0;
		}
		else if (this->data[i] < other.data[i])
		{
			if (this->flag) return 0;
			else return 1;
		}
	}
	return 0;
}
bool BigInt::operator<(const int& number) const
{
	BigInt other = number;
	if (this->flag > other.flag) return 1;
	if (this->flag < other.flag) return 0;
	if (this->Size > other.Size) return 0;
	if (this->Size < other.Size) return 1;
	for (size_t i = 0; i < this->Size; i++)
	{
		if (this->data[i] < other.data[i]) return 1;
	}
	return 0;
}
bool BigInt::operator<=(const BigInt& other) const
{
	return !(*this > other);
}
bool BigInt::operator<=(const int& number) const
{
	BigInt other = number;
	return !(*this > other);
}
bool BigInt::operator>=(const BigInt& other) const
{
	return !(*this < other);
}
bool BigInt::operator>=(const int& number) const
{
	BigInt other = number;
	return !(*this < other);
}
bool BigInt::operator==(const BigInt& other) const
{
	if (this->flag != other.flag) return 0;
	if (this->Size != other.Size) return 0;
	for (size_t i = 0; i < this->Size; i++)
	{
		if (this->data[i] != other.data[i]) return 0;
	}
	return 1;
}
bool BigInt::operator==(const int& number) const
{
	BigInt other = number;
	if (this->flag != other.flag) return 0;
	if (this->Size != other.Size) return 0;
	for (size_t i = 0; i < this->Size; i++)
	{
		if (this->data[i] != other.data[i]) return 0;
	}
	return 1;
}
bool BigInt::operator!=(const BigInt& other) const
{
	return !(*this == other);
}
bool BigInt::operator!=(const int& number) const
{
	BigInt other = number;
	return !(*this == other);
}
BigInt BigInt:: operator-() const
{
	BigInt tmp(*this);
	if (this->data[0] == '0'  && this->Size == 1) return tmp;
	tmp.flag = !tmp.flag;
	return tmp;
}
BigInt BigInt::operator+(const BigInt& other) const
{

	BigInt result;
	if (this->flag != other.flag)
	{
		bool a = 0;
		if (this->Size > other.Size) a = 1;
		else if (this->Size < other.Size) a = 0;
		else {
			for (size_t i = 0; i < this->Size; i++)
			{
				if (this->data[i] > other.data[i])
				{
					a = 1;
					break;
				}
				else if (this->data[i] < other.data[i])
				{
					a = 0;
					break;
				}

			}
		}
		if (this->flag == 0 && other.flag == 1) {
			BigInt res = other;
			res.flag = 0;
			return (this->operator-(res));
		}
		if (this->flag == 1 && other.flag == 0)
		{
			BigInt result;
			if (a == 0)
			{
				BigInt a = *this;
				BigInt b = other;
				a.flag = 0;
				b.flag = 0;
				result = a - b;
				result.flag = 0;
			}
			else
			{
				BigInt a = *this;
				BigInt b = other;
				a.flag = 0;
				b.flag = 0;
				result = b - a;
				result.flag = 1;
			}
			return result;
		}


	}
	else
	{
		size_t size_res = fmax(this->Size, other.Size);
		size_t min = fmin(this->Size, other.Size);
		result.Size = size_res + 1;
		result.data = new char[size_res + 1];
		char* result_reverse = new char[size_res + 2];
		for (size_t i = 0; i < size_res + 1; i++) result.data[i] = '0';
		for (size_t i = 0; i < size_res + 1; i++) result_reverse[i] = '0';
		char* revers_this = new char[this->Size + 1];
		for (size_t i = 0; i < this->Size + 1; i++) revers_this[i] = '0';
		for (size_t i = 0; i < this->Size; ++i)
		{
			revers_this[i] = this->data[(this->Size - 1) - i];
		}
		char* revers_other = new char[other.Size];
		for (size_t i = 0; i < this->Size + 1; i++) revers_other[i] = '0';
		for (size_t i = 0; i < other.Size; ++i)
		{
			revers_other[i] = other.data[(other.Size - 1) - i];
		}
		for (size_t i = 0; i < this->Size; i++)
			result_reverse[i] = revers_this[i];
		char buffer = 0;
		for (size_t i = 0; i < size_res; i++)
		{
			buffer = revers_other[i] + result_reverse[i] - '0' + buffer;
			if (buffer - '0' > 9)
			{
				result_reverse[i] = buffer - 10 + 0;
				buffer = 1;
			}
			else
			{
				result_reverse[i] = buffer;
				buffer = 0;
			}
		}
		if ((buffer - 0) == 1) result_reverse[size_res] = '1';
		if ((buffer - 0) != 1) {
			size_res = size_res - 1;
			result.Size = size_res + 1;
		}
		for (size_t i = 0; i < size_res + 1; ++i)
		{
			result.data[i] = result_reverse[(size_res)-i];
		}
		result.flag = other.flag;
		return result;
	}
}
BigInt BigInt::operator-(const BigInt& other) const
{
	if (this->flag == 0 && other.flag == 1)
	{
		BigInt res = other;
		res.flag = 0;
		return (this->operator+(res));
	}
	if (this->flag == 1 && other.flag == 0)
	{
		BigInt res = other;
		res.flag = 1;
		return (this->operator+(res));
	}
	if (other.flag == 1 && this->flag == 1)
	{
		BigInt res = other;
		BigInt res2 = *this;
		res2.flag = 0;
		res.flag = 0;
		return (res - res2);
	}
	bool a = 0;
	if (this->Size > other.Size) a = 1;
	if (this->Size < other.Size) a = 0;
	for (size_t i = 0; i < fmin(this->Size, other.Size); i++)
	{
		if (this->data[i] > other.data[i]) a = 1;
		break;
	}
	BigInt result;
	if (a == 1) result.flag = this->flag;
	else result.flag = other.flag;
	size_t size_res = fmax(this->Size, other.Size);
	result.data = new char[size_res + 1];
	for (size_t i = 0; i < size_res + 1; i++) result.data[i] = '0';
	char* result_reverse = new char[size_res + 2];
	for (size_t i = 0; i < size_res; i++) result_reverse[i] = '0';
	result_reverse[size_res] = '1';
	char* revers_this = new char[size_res + 1];
	for (size_t i = 0; i < size_res + 1; i++) revers_this[i] = '0';
	for (size_t i = 0; i < this->Size; ++i)
	{
		revers_this[i] = this->data[(this->Size - 1) - i];
	}
	char* revers_other = new char[size_res + 1];
	for (size_t i = 0; i < size_res + 1; i++) revers_other[i] = '0';
	for (size_t i = 0; i < other.Size; ++i)
	{
		revers_other[i] = other.data[(other.Size - 1) - i];
	}
	char buffer = 0;
	for (size_t i = 0; i < size_res; i++)
	{
		buffer = revers_this[i] - revers_other[i] + result_reverse[i];
		if ((buffer - '0') < 0)
		{
			result_reverse[i] = buffer + 10 - 0;
			result_reverse[i + 1] = result_reverse[i + 1] - 1;
			buffer = 0;
		}
		else result_reverse[i] = buffer;
	}
	if (result_reverse[size_res] == 1 + '0')
	{
		result.flag = 0;
		for (size_t i = size_res - 1; i > 0; i--)
		{
			if (result_reverse[i] == 0 + '0')
			{
				size_res -= 1;
			}
			else break;
		}
		for (size_t i = 0; i < size_res; ++i)
		{
			result.data[i] = result_reverse[(size_res - 1) - i];
		}
		result.Size = size_res;
		return result;
	}
	else
	{
		result.flag = 1;
		char* arr = new char[size_res + 2];
		for (size_t i = 0; i < size_res; i++)
		{
			arr[i] = '0';
		}
		arr[size_res] = '1';
		char buffer1;
		for (size_t i = 0; i < size_res; i++)
		{
			buffer1 = arr[i] - result_reverse[i] + '0';
			if ((buffer1 - '0') < 0)
			{
				arr[i] = buffer1 + 10 - 0;
				arr[i + 1] = arr[i + 1] - 1;
				buffer1 = 0;
			}
			else arr[i] = buffer1;
		}
		for (size_t i = size_res - 1; i > 0; i--)
		{
			if (arr[i] == 0 + '0')
			{
				size_res -= 1;
			}
			else break;
		}
		for (size_t i = 0; i < size_res; ++i)
		{
			result.data[i] = arr[(size_res - 1) - i];
		}
		result.Size = size_res;
		return result;
	}
}
BigInt BigInt::operator+(const int& number) const
{
	BigInt other = number;
	return (*this + other);
}
BigInt BigInt::operator-(const int& number) const
{
	BigInt other = number;
	return (*this + other);
}
