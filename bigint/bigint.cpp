#include "bigint.hpp"

bigint::bigint(unsigned int n)
{
	std::ostringstream oss;
	oss << n;
	str = oss.str();
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
bigint bigint::operator<<(int n) const
{
	bigint res;
	if (str == '0' || n = 0) return this;
	res = this;
	res.str.append('0',n);
	return res;
}
	
