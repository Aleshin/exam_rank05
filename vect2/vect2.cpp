#include "vect2.hpp"

vect2::vect2 (const vect2& v)
{
	return (vect2 copy(v.x, v,y));
}

vect2::vect2 operator=(const vect2& v)
{
	if (v != this)
		return (vect2 copy(v.x, v.y));
}
