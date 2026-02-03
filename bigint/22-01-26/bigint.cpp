#include "bigint.hpp"

bigint::bigint(unsigned int n)
{
	std::ostringstream oss;
	oss << n;
	bint = oss.str();
}

bigint& bigint::operator=(const bigint& other)
{
	if (this != &other)
		bint = other.bint;
	return *this;
}

std::ostream& operator<<(std::ostream& os, const bigint& other)
{
	os << other.bint;
	return os;
}

bigint bigint::operator+(const bigint& other) const
{
	std::string res;
	int carry = 0;
	int i = bint.size() - 1;
	int j = other.bint.size() - 1;
	while (i >= 0 || j >= 0 || carry)
	{
		int sum = carry;
		if (i >= 0) sum += bint[i--] - '0';
		if (j >= 0) sum += other.bint[j--] - '0';
		carry = sum/10;
		res += sum % 10 + '0';
	}
	bigint result;
	result.bint = std::string(res.rbegin(), res.rend());
	return result;
}

bigint& bigint::operator+=(const bigint& other)
{
	*this = *this + other;
	return *this;
}

bigint& bigint::operator++()
{
	*this = *this + bigint(1);
	return *this;
}

bigint bigint::operator++(int)
{
	bigint temp = *this;
	*this = *this + bigint(1);
	return temp;
}

bigint bigint::operator<<(int n) const
{
	if (n <= 0) return *this;
	bigint res = *this;
	res.bint.append(n, '0');
	return res;
}

bigint& bigint::operator<<=(int n)
{
	*this = *this << n;
	return *this;
}

bigint bigint::operator>>(int n) const
{
	if (bint.size() <= (size_t)n || bint == "0") return bigint(0);
	if (n <= 0) return *this;
	bigint res;
	res.bint = bint.substr(0, bint.size() - n);
	return res;
}

bigint& bigint::operator>>=(int n)
{
	*this = *this >> n;
	return *this;
}

int bigint::toInt(const bigint& other) const
{
	int num;
	std::istringstream iss(other.bint);
	iss >> num;
	return num;
}

bigint& bigint::operator>>=(const bigint& other)
{
	*this = *this >> toInt(other);
	return *this;
}

bool bigint::operator<(const bigint& other) const
{
	if (bint.size() != other.bint.size()) return bint.size() < other.bint.size();
	return bint < other.bint;
}

bool bigint::operator>(const bigint& other) const
{
	return other < *this;
}
