#pragma once
#include <string>
#include <sstream>
#include <iostream>

class bigint
{
public:
	bigint(): bint("0") {}
	bigint(unsigned int n);
	bigint(const bigint& copy): bint(copy.bint) {}
	bigint& operator=(const bigint& other);
	~bigint() {}
	
	friend std::ostream& operator<<(std::ostream& os, const bigint& other);
	int toInt(const bigint& other) const;
	
	bigint operator+(const bigint& other) const;
	bigint& operator+=(const bigint& other);
	bigint& operator++();
	bigint operator++(int);

	bigint operator<<(int n) const;
	bigint& operator<<=(int n);
	bigint operator>>(int n) const;
	bigint& operator>>=(int n);
	bigint& operator>>=(const bigint& other);
	
	bool operator<(const bigint& other) const;
	bool operator>(const bigint& other) const;

private:
	std::string bint;
};
