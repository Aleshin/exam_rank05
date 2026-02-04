#pragma once
#include "searchable_bag.hpp"

class set
{
public:
	set() {}
	set(searchable_bag& sbag): bag(&sbag) {}
	set(const set& copy);
	set& operator=(const set& copy);
	~set() {}

	void insert(int);
	void insert(int *, int);
	void print() const;
	void clear();
	bool has(int) const;
	searchable_bag& get_bag();
private:
	searchable_bag *bag;
};