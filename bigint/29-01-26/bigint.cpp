#include "bigint.hpp"

bigint::bigint(unsigned int num)
{
	std::ostringstream os;
	os << num;
	bint = os.str();
}

bigint::bigint(const std::string& str)
{
	bint = str;
	bint.erase(0, bint.find_first_not_of('0'));
	if (bint.empty()) bint = "0";
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
	int carry = 0;
	std::string res;
	int i = bint.size() - 1;
	int j = other.bint.size() - 1;
	while (i >= 0 || j >= 0 || carry)
	{
		int sum = carry;
		if (i >= 0) sum += bint[i--] - '0';
		if (j >= 0) sum += other.bint[j--] - '0';
		carry = carry / 10;
		res += sum % 10 +'0';
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

bigint bigint::operator++(int)
{
	*this = *this + bigint(1);
	return *this;
}

bigint& bigint::operator++()
{
	return *this + bigint(1);
}

