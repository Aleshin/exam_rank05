#ifndef BIGINT_HPP
#define BIGINT_HPP
#include <string>
#include <sstream>
#include <ostream>
#include <iostream>

class bigint
{
public:
	bigint(): str("0") {}
	bigint(unsigned int n);
	bigint(const bigint& other): str(other.str) {}
	~bigint() {}
	
	bigint operator+(const bigint& other) const;
	bool operator<(const bigint& other) const;
	bigint operator<<(int n) const;
	bigint operator>>(int n) const;
	bigint operator<<(const bigint& n) const;
	bigint operator>>(const bigint& n) const;
	bigint& operator=(const bigint& other);
	friend std::ostream& operator<<(std::ostream& os, const bigint& num);
	friend int toInt(const bigint& num);
private:
	std::string str;
};

#endif
