#include "searchable_tree_bag.hpp"

searchable_tree_bag& searchable_tree_bag::operator=(const searchable_tree_bag& other)
{
	if (this != &other)
		tree_bag::operator=(other);
	return *this;
}

bool searchable_tree_bag::has(int num) const
{
	node *temp = tree;
	while (temp)
	{
		if (temp->value == num) return true;
		if (num < temp->value) temp = temp->l;
		else temp = temp->r;
	}
	return false;
}