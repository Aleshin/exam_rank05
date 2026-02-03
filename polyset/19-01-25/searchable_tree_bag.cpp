#include "searchable_tree_bag.hpp"

searchable_tree_bag& searchable_tree_bag::operator=(const searchable_tree_bag& other)
{
	if (this != &other)
		tree_bag::operator=(other);
	return *this;
}

bool searchable_tree_bag::has(int num) const
{
	node* n = tree;
	while(n)
	{
		if (n->value == num) return true;
		num < n->value ? n = n->l : n = n->r;
	}
	return false;
}
