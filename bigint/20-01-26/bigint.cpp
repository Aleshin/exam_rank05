#include "bigint.hpp"

bigint::bigint(unsigned int num)
{
	std::ostringstream oss;
	oss << num;
	bignum = oss.str();
}

bigint& bigint::operator=(const bigint& other)
{
	if (this != &other)
		bignum = other.bignum;
	return *this;
}

std::ostream& operator<<(std::ostream& os, const bigint& str)
{
	os << str.bignum;
	return os;
}

bigint bigint::operator+(const bigint& other) const
{
	std::string res;
	int carry = 0;
	int i = bignum.size() - 1;
	int j = other.bignum.size() - 1;
	while (i >= 0 || j >= 0 || carry)
	{
		int sum = carry;
		if (i >= 0) sum += bignum[i--] - '0';
		if (j >= 0) sum += other.bignum[j--] - '0';
		carry = sum/10;
		res += sum % 10 + '0';
	}
	bigint result;
	result.bignum = std::string(res.rbegin(), res.rend());
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
	bigint res = *this;
	res.bignum.append(n, '0');
	return res;
}

bigint& bigint::operator<<=(int n)
{
	*this = *this << n;
	return *this;
}

bigint bigint::operator>>(int n) const
{
	bigint res;
	res.bignum = bignum.substr(0, bignum.size() - n);
	return res;
}

bigint& bigint::operator>>=(int n)
{
	bignum.substr(0, bignum.size() - n);
	return *this;
}
