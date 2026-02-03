#pragma once
#include <string>
#include <sstream>
#include <iostream>

class bigint
{
public:
	bigint(): bint("0") {}
	bigint(unsigned int num);
	bigint(const std::string& str);
	bigint(const bigint& copy): bint(copy.bint) {}
	bigint& operator=(const bigint& other);
	~bigint() {}
	
	friend std::ostream& operator<<(std::ostream& os, const bigint& other);
	bigint operator+(const bigint& other) const;
	bigint& operator+=(const bigint& other);
	
	bigint operator++(int);
	bigint& operator++();

private:
	std::string bint;
};
