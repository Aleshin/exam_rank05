#include "bigint.hpp"

bigint::bigint(const unsigned int& num)
{
	std::ostringstream oss;
	oss << num;
	str = oss.str();
}

bigint::bigint(std::string str0): str(str0)
{
	str.erase(0, str.find_first_not_of('0'));
	if (str.empty()) str = "0";
}

bigint& bigint::operator=(const bigint& other)
{
	if (this != &other)
		str = other.str;
	return *this;
}

std::ostream& operator<<(std::ostream& os, const bigint& other)
{
	os << other.str;
	return os;
}

bigint bigint::operator+(const bigint& other) const
{
	std::string res;
	int carry = 0;
	int i = str.size() - 1;
	int j = other.str.size() - 1;
	while (i >= 0 || j >= 0 || carry)
	{
		int sum = carry;
		if (i >= 0) sum += str[i--] - '0';
		if (j >= 0) sum += other.str[j--] - '0';
		carry = sum / 10;
		res += sum % 10 +'0';
	}
	bigint result;
	result.str = std::string(res.rbegin(), res.rend());
	return result;
}

int bigint::toInt(const bigint& other) const
{
	int num;
	std::istringstream iss(other.str);
	iss >> num;
	return num;
}

bigint bigint::operator<<(const int num) const
{
	if (str == "0" || num <= 0) return *this;
	bigint res = *this;
	return res.str.append(num, '0');
}

bigint bigint::operator<<(const bigint& other) const
{
	bigint res;
	res = *this << toInt(other);
	return res;
}

bigint bigint::operator>>(const int num) const
{
	if ((size_t)num >= str.size()) return bigint(0);
	if (str == "0" || num <= 0) return *this;
	bigint res;
	res.str.substr(0, str.size() - num);
	return res;
}
	
bool bigint::operator<(const bigint& other) const
{
	if (str.size() != other.str.size()) return str.size() < other.str.size();
	return str < other.str;
}

