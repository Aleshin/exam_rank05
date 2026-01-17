#ifndef VECT2_HPP
#define VECT2_HPP
#include <iostream>

class vect2
{
public:
	vect2(): x(0), y(0) {}
	vect2(int x0, int y0): x(x0), y(y0) {}
	vect2(const vect2& other): x(other.x), y(other.y) {}
	vect2& operator=(const vect2& other);
	~vect2() {}
	int operator[](int i);
	vect2 operator*(int s) const;
	friend std::ostream& operator<<(std::ostream& os, const vect2& vect);
	friend vect2 operator*(int s, const vect2& vect);
private:
	int x, y;
};

#endif
