#include "bigint.hpp"

bigint::bigint(unsigned long long n)
{
	std::ostringstream oss;
	oss << n;
	str = oss.str();
}

bigint::bigint(const std::string& s): str(s)
{
	str.erase(0, str.find_first_not_of('0'));
	if (str.empty()) str = "0";
}
std::ostream& operator<<(std::ostream& os, const bigint& num)
{
	os << num.str;
	return os;
}
bigint& bigint::operator=(const bigint& num)
{
	if (this != &num)
		str = num.str;
	return *this;
}
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

bool bigint::operator<(const bigint& num) const
{
	if (str.size() != num.str.size()) return (str.size() < num.str.size());
	return (str < num.str);
}

bigint bigint::operator<<(int n) const
{
	bigint res;
	if (str == "0" || n == 0) return *this;
	res = *this;
	res.str.append(n, '0');
	return res;
}

bigint bigint::operator>>(int n) const
{
	if (n <= 0) return *this;
	if (str.size() <= (size_t)n) return bigint(0);
	bigint res;
	res.str = str.substr(0, str.size() - n);
	return res;
}

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
	bigint tmp(*this);
	++(*this);
	return tmp;
}

bool bigint::operator<=(const bigint& other) const
{
	return !(other < *this);
}

bool bigint::operator>(const bigint& other) const
{
	return other < *this;
}

bool bigint::operator>=(const bigint& other) const
{
	return !(*this < other);
}

bool bigint::operator==(const bigint& other) const
{
	return str == other.str;
}

bool bigint::operator!=(const bigint& other) const
{
	return !(*this == other);
}

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
