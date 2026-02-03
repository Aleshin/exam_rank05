#include "set.hpp"

set(const set& copy)
{
	sbag = copy.sbag;
}

set& operator=(const set& other)
{
	if (this != &other)
		sbag = other.sbag;
	return *this;
}

void insert(int num)
{
	if (!sbag.has(num))
		sbag.insert(num);
}

void insert(int *arr, int size)
{
	for (int i = 0; i < size; i++)
		sbag.insert(arr[i]);
}

void print() const
{
	sbag.print();
}

void clear()
{
	sbag.clear();
}

bool has(int num) const
{
	return sbag.has(num);
}

set& get_bag()
{
	return *this;
}

