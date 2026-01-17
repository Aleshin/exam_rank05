#include "vect2.hpp"

vect2& vect2::operator=(const vect2& other)
{
	if (this != &other)
	{
		x = other.x;
		y = other.y;
	}
	return *this;
}

int vect2::operator[](int i)
{
	if (i == 0) return this->x;
	return this->y;
}

vect2 vect2::operator*(int s) const
{
	return vect2(x * s, y * s);
}

vect2 operator*(int s, const vect2& vect)
{
	return vect2(vect*s);
}

std::ostream& operator<<(std::ostream& os, const vect2& vect)
{
	os << "{" << vect.x << ", " << vect.y << "}";
	return os;
}
