#pragma once

#include "searchable_bag.hpp"

class set {
public:
	set(searchable_bag& bag);
	set(const set& src);
	set& operator=(const set& src);
	~set();

	void insert(int value);
	void insert(int* arr, int size);
	bool has(int value) const;
	void print() const;
	void clear();
	searchable_bag& get_bag() const;

private:
	searchable_bag* _bag;
};
