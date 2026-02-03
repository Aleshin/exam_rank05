#pragma once

#include "searchable_bag.hpp"

class set
{
public:
	set() {}
	set(searchable_bag& bag);
	set(const set& copy);
	set &operator=(const set& other);
	~set() {}

	void insert(int);
	void insert(int *, int);
	void print() const;
	void clear();
	
	bool has(int) const;
	searchable_bag& get_bag();
private:
	searchable_bag* sbag;
};
