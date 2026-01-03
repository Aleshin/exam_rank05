#ifndef VECT2_HPP
#define VECT2_HPP

#include <ostream>

class vect2
{
private:
	int x,y;
public:
	vect2(): x(0), y(0) {}
	vect2(int x0, int y0): x(x0), y(y0) {}
	vect2(const vect2& other);
	vect2& operator=(const vect2& other);
	~vect2();
	int operator[](int i);
	int operator[](int i) const;
	vect2 operator*(int s) const;
	friend vect2 operator*(int s, const vect2& v);
	friend std::ostream& operator<<(std::ostream& os, const vect2& v);
};
#endif
