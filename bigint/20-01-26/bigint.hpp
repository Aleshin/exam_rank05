#pragma once
#include <string>
#include <iostream>
#include <sstream>

class bigint
{
	public:
		bigint(): bignum("0") {}
		bigint(unsigned int num);
		bigint(const bigint& copy): bignum(copy.bignum) {}
		bigint& operator=(const bigint& other);
		~bigint() {}
		
		friend std::ostream& operator<<(std::ostream& os, const bigint& str);
		
		bigint operator+(const bigint& other) const;
		bigint& operator+=(const bigint& other);
		bigint& operator++();
		bigint operator++(int);
		bigint operator<<(int) const;
		bigint& operator<<=(int);
		bigint operator>>(int) const;
		bigint& operator>>=(int);
	private:
		std::string bignum;
};
