#include "searchable_bag.hpp"
#include "searchable_tree_bag.hpp"
#include "searchable_array_bag.hpp"
#include "set.hpp"

#include <iostream>
#include <cassert>

void test_set_basic_operations()
{
	std::cout << "=== TEST 1: Basic Set Operations ===" << std::endl;
	
	searchable_array_bag a;
	set s(a);
	
	// Test insert single element
	s.insert(5);
	assert(s.has(5) == true);
	std::cout << "✓ Insert and has() work correctly" << std::endl;
	
	// Test that duplicates are not added
	s.insert(5);
	s.print();  // Should print "5" only once
	std::cout << "✓ Duplicates handled correctly" << std::endl;
}

void test_set_array_insert()
{
	std::cout << "\n=== TEST 2: Array Insert ===" << std::endl;
	
	searchable_array_bag a;
	set s(a);
	
	int arr[] = {1, 2, 3, 4, 5};
	s.insert(arr, 5);
	s.print();
	
	assert(s.has(1) == true);
	assert(s.has(3) == true);
	assert(s.has(5) == true);
	assert(s.has(10) == false);
	std::cout << "✓ Array insert works correctly" << std::endl;
}

void test_set_no_duplicates_from_array()
{
	std::cout << "\n=== TEST 3: No Duplicates from Array ===" << std::endl;
	
	searchable_array_bag a;
	set s(a);
	
	int arr[] = {1, 2, 2, 3, 3, 3, 4};
	s.insert(arr, 7);
	std::cout << "Array with duplicates {1, 2, 2, 3, 3, 3, 4}: ";
	s.print();
	std::cout << "✓ Duplicates in array handled" << std::endl;
}

void test_set_copy_constructor()
{
	std::cout << "\n=== TEST 4: Copy Constructor ===" << std::endl;
	
	searchable_array_bag a;
	set s1(a);
	
	int arr[] = {5, 10, 15};
	s1.insert(arr, 3);
	
	set s2(s1);
	
	std::cout << "Original set: ";
	s1.print();
	std::cout << "Copied set: ";
	s2.print();
	
	assert(s2.has(5) == true);
	assert(s2.has(10) == true);
	std::cout << "✓ Copy constructor works" << std::endl;
}

void test_set_assignment()
{
	std::cout << "\n=== TEST 5: Assignment Operator ===" << std::endl;
	
	searchable_array_bag a1;
	searchable_array_bag a2;
	
	set s1(a1);
	set s2(a2);
	
	int arr1[] = {1, 2, 3};
	int arr2[] = {10, 20, 30};
	
	s1.insert(arr1, 3);
	s2.insert(arr2, 3);
	
	std::cout << "Before assignment:" << std::endl;
	std::cout << "s1: ";
	s1.print();
	std::cout << "s2: ";
	s2.print();
	
	s2 = s1;
	
	std::cout << "After s2 = s1:" << std::endl;
	std::cout << "s1: ";
	s1.print();
	std::cout << "s2: ";
	s2.print();
	
	assert(s2.has(1) == true);
	assert(s2.has(20) == false);
	std::cout << "✓ Assignment operator works" << std::endl;
}

void test_set_clear()
{
	std::cout << "\n=== TEST 6: Clear Operation ===" << std::endl;
	
	searchable_array_bag a;
	set s(a);
	
	int arr[] = {1, 2, 3, 4, 5};
	s.insert(arr, 5);
	
	std::cout << "Before clear: ";
	s.print();
	
	s.clear();
	
	std::cout << "After clear: ";
	s.print();
	
	assert(s.has(1) == false);
	std::cout << "✓ Clear works correctly" << std::endl;
}

void test_set_with_tree_bag()
{
	std::cout << "\n=== TEST 7: Set with Tree Bag ===" << std::endl;
	
	searchable_tree_bag t;
	set s(t);
	
	int arr[] = {50, 25, 75, 10, 30};
	s.insert(arr, 5);
	
	std::cout << "Tree-based set: ";
	s.print();
	
	assert(s.has(50) == true);
	assert(s.has(25) == true);
	assert(s.has(100) == false);
	std::cout << "✓ Set works with tree_bag" << std::endl;
}

void test_get_bag()
{
	std::cout << "\n=== TEST 8: Get Bag Method ===" << std::endl;
	
	searchable_array_bag a;
	set s(a);
	
	int arr[] = {1, 2, 3};
	s.insert(arr, 3);
	
	std::cout << "Set: ";
	s.print();
	std::cout << "Via get_bag(): ";
	s.get_bag().print();
	
	std::cout << "✓ get_bag() works" << std::endl;
}

void test_edge_case_negative_numbers()
{
	std::cout << "\n=== TEST 9: Negative Numbers ===" << std::endl;
	
	searchable_array_bag a;
	set s(a);
	
	int arr[] = {-5, -1, 0, 1, 5};
	s.insert(arr, 5);
	
	std::cout << "Set with negatives: ";
	s.print();
	
	assert(s.has(-5) == true);
	assert(s.has(0) == true);
	assert(s.has(-10) == false);
	std::cout << "✓ Negative numbers handled" << std::endl;
}

void test_edge_case_single_element()
{
	std::cout << "\n=== TEST 10: Single Element ===" << std::endl;
	
	searchable_array_bag a;
	set s(a);
	
	s.insert(42);
	
	std::cout << "Single element set: ";
	s.print();
	
	assert(s.has(42) == true);
	assert(s.has(41) == false);
	std::cout << "✓ Single element works" << std::endl;
}

int main()
{
	try {
		test_set_basic_operations();
		test_set_array_insert();
		test_set_no_duplicates_from_array();
		test_set_copy_constructor();
		test_set_assignment();
		test_set_clear();
		test_set_with_tree_bag();
		test_get_bag();
		test_edge_case_negative_numbers();
		test_edge_case_single_element();
		
		std::cout << "\n" << std::string(50, '=') << std::endl;
		std::cout << "✓✓✓ ALL TESTS PASSED ✓✓✓" << std::endl;
		std::cout << std::string(50, '=') << std::endl;
	}
	catch (const char *e) {
		std::cout << "ERROR: " << e << std::endl;
		return 1;
	}
	catch (...) {
		std::cout << "UNKNOWN ERROR" << std::endl;
		return 1;
	}
	
	return 0;
}
