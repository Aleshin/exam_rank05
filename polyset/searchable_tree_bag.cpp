#include "searchable_tree_bag.hpp"
#include <cstddef>

searchable_tree_bag::searchable_tree_bag() : tree_bag() {}

searchable_tree_bag::searchable_tree_bag(const searchable_tree_bag& src) : tree_bag(src) {}

searchable_tree_bag& searchable_tree_bag::operator=(const searchable_tree_bag& src) {
	if (this != &src) {
		tree_bag::operator=(src);
	}
	return *this;
}

searchable_tree_bag::~searchable_tree_bag() {}

bool searchable_tree_bag::has(int value) const {
	return search_node(tree, value);
}

bool searchable_tree_bag::search_node(node* current, int value) const {
	if (current == NULL) {
		return false;
	}
	if (current->value == value) {
		return true;
	}
	if (value < current->value) {
		return search_node(current->l, value);
	}
	return search_node(current->r, value);
}
