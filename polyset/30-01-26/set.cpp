#include "set.hpp"

set::set(const set& copy)
{
	*this = copy;
}

set& set::operator=(const set& copy)
{
	if (this != &copy)
		*this = copy;
	return *this;
}

void set::insert(int n)
{
	if (!bag->has(n))
		bag->insert(n);
}

void set::insert(int *a, int s)
{
	for (int i = 0; i < s; i++)
		bag->insert(a[i]);
}

void set::print() const
{
	bag->print();
}

void set::clear()
{
	bag->clear();
}

bool set::has(int n) const
{
	return bag->has(n);
}

searchable_bag& set::get_bag()
{
	return *bag;
}