#include "set.hpp"
set::set(searchable_bag& bag)
{
	sbag = &bag;
}

set::set(const set& copy)
{
	sbag = copy.sbag;
}

set& set::operator=(const set& other)
{
	if (this != &other)
		sbag = other.sbag;
	return *this;
}

void set::insert(int num)
{
	if (!sbag->has(num))
		sbag->insert(num);
}

void set::insert(int *arr, int s)
{
	for (int i = 0; i < s; i++)
		sbag->insert(arr[i]);
}

void set::print() const
{
	sbag->print();
}

void set::clear()
{
	sbag->clear();
}

bool set::has(int num) const
{
	return sbag->has(num);
}

searchable_bag& set::get_bag()
{
	return *sbag;
}
