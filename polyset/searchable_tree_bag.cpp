#include "searchable_tree_bag.hpp"

searchable_tree_bag::searchable_tree_bag() {}
searchable_tree_bag::searchable_tree_bag(const searchable_tree_bag& src) : tree_bag(src) {}
searchable_tree_bag& searchable_tree_bag::operator=(const searchable_tree_bag& src) {
	if (this != &src)
		tree_bag::operator=(src);
	return *this;
}
searchable_tree_bag::~searchable_tree_bag() {}

bool searchable_tree_bag::has(int value) const {
	node* n = tree;
	while (n) {
		if (n->value == value) return true;
		n = (value < n->value) ? n->l : n->r;
	}
	return false;
}
