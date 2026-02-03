#pragma once
#include <string>
#include <sstream>
#include <iostream>

class bigint
{
public:
	bigint(): str("0") {}
	bigint(const unsigned int& num);
	bigint(std::string str0);
	bigint(const bigint& copy): str(copy.str) {}
	bigint& operator=(const bigint& other);
	~bigint() {}
	
	friend std::ostream& operator<<(std::ostream& os, const bigint& other);
	int toInt(const bigint& other) const;
	
	bigint operator+(const bigint& other) const;
	
	bigint operator<<(const int num) const;
	bigint operator<<(const bigint& other) const;
	bigint operator>>(const int num) const;
	bool operator<(const bigint& other) const;
private:
	std::string str;
};
