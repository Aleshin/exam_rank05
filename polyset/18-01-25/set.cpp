#include "set.hpp"

set::set(searchable_bag& bag) : _bag(&bag) {}

set::set(const set& src) : _bag(src._bag) {}

set& set::operator=(const set& src) {
	if (this != &src) {
		_bag = src._bag;
	}
	return *this;
}

set::~set() {}

void set::insert(int value) {
	if (!_bag->has(value)) {
		_bag->insert(value);
	}
}

void set::insert(int* arr, int size) {
	for (int i = 0; i < size; i++) {
		insert(arr[i]);
	}
}

bool set::has(int value) const {
	return _bag->has(value);
}

void set::print() const {
	_bag->print();
}

void set::clear() {
	_bag->clear();
}

searchable_bag& set::get_bag() const {
	return *_bag;
}
