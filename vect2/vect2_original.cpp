#include "vect2.hpp"

vect2::vect2(const vect2& other): x(other.x), y(other.y) {}

vect2& vect2::operator=(const vect2& other)
{
	if (this != &other)
	{
		x = other.x;
		y = other.y;
	}
	return *this;
}

vect2::~vect2() {}

int vect2::operator[](int i)
{
	if (i == 0)
		return x;
	return y;
}

int vect2::operator[](int i) const
{
	if (i == 0)
		return x;
	return y;
}

vect2 vect2::operator*(int s) const
{
	return vect2(x * s, y * s);
}

vect2 operator*(int s, const vect2& v)
{
	return v * s;
}

std::ostream& operator<<(std::ostream& os, const vect2& v)
{
	os << "{" << v.x << ", " << v.y << "}";
	return os;
}
