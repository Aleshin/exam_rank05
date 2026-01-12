#0. Библиотеки
#include <string>
#include <sstream>
#include <ostream>
#include <iostream>

#1. Конструкторы
bigint::bigint(unsigned int n)
{
	std::ostringstream oss;
	oss << n;
	str = oss.str();
}

#2. Перегрузка << для печати
std::ostream& operator<<(std::ostream& os, const bigint& num)
{
	os << num.str;
	return os;
}

#3. Перегрузка =
bigint& bigint::operator=(const bigint& num)
{
	if (this != &num)
		str = num.str;
	return *this;
}

#4. Перегрузка +
bigint bigint::operator+(const bigint& num) const
{
	std::string res;
	int i = str.size() - 1;
	int j = num.str.size() - 1;
	int carry = 0;
	while (i >= 0 || j >= 0 || carry > 0)
	{
		int sum = carry;
		if (i >= 0)
			sum += str[i--] - '0';
		if (j >= 0)
			sum += num.str[j--] - '0';
		carry = sum/10;
		res += sum % 10 + '0';
	}
	bigint result;
	result.str = std::string(res.rbegin(), res.rend());
	return result;
}

#5. Перегрузка <
bool bigint::operator<(const bigint& num) const
{
	if (str.size() != num.str.size()) return (str.size() < num.str.size());
	return (str < num.str);
}

#6. Перегрузка << (сдвиг по int)
bigint bigint::operator<<(int n) const
{
	bigint res;
	if (str == "0" || n == 0) return *this;
	res = *this;
	res.str.append(n, '0');
	return res;
}

#7. Перегрузка >> (сдвиг по int)
bigint bigint::operator>>(int n) const
{
	if (str.size() <= (size_t)n) return bigint(0);
	if (n <= 0) return *this;
	bigint res;
	res.str = str.substr(0, str.size() - n);
	return res;
}

#8. Перегрузка << и >> (сдвиг по bigint)
int toInt(const bigint& num)
{
	int res;
	std::istringstream iss(num.str);
	iss >> res;
	return res;
}

bigint bigint::operator<<(const bigint& n) const
{
	return *this << toInt(n);
}

bigint bigint::operator>>(const bigint& n) const
{
	return *this >> toInt(n);
}

#9. Перегрузка >, <=, >=, ==, !=
bool bigint::operator>(const bigint& num) const
{
	return num < *this;
}

bool bigint::operator==(const bigint& num) const
{
	return str == num.str;
}

bool bigint::operator!=(const bigint& num) const
{
	return !(*this == num);
}

bool bigint::operator<=(const bigint& num) const
{
	return *this < num || *this == num;
}

bool bigint::operator>=(const bigint& num) const
{
	return *this > num || *this == num;
}

#10. Перегрузка <<=, >>= для int и для bigint
bigint& bigint::operator<<=(int n)
{
	*this = *this << n;
	return *this;
}

bigint& bigint::operator>>=(int n)
{
	*this = *this >> n;
	return *this;
}

bigint& bigint::operator<<=(const bigint& n)
{
	*this = *this << n;
	return *this;
}

bigint& bigint::operator>>=(const bigint& n)
{
	*this = *this >> n;
	return *this;
}

#11. Перегрузка ++, +=
bigint& bigint::operator++()
{
	*this = *this + bigint(1);
	return *this;
}

bigint bigint::operator++(int)
{
	bigint temp = *this;
	++(*this);
	return temp;
}

bigint& bigint::operator+=(const bigint& num)
{
	*this = *this + num;
	return *this;
}
