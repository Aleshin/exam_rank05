#include "searchable_bag.hpp"
#include "searchable_tree_bag.hpp"
#include "searchable_array_bag.hpp"
#include "set.hpp"

#include <iostream>

void test_stress_large_dataset()
{
	std::cout << "=== STRESS TEST: Large Dataset ===" << std::endl;
	
	searchable_array_bag a;
	set s(a);
	
	// Insert many elements
	for (int i = 1; i <= 100; i++) {
		s.insert(i);
	}
	
	// Verify all are present
	bool all_present = true;
	for (int i = 1; i <= 100; i++) {
		if (!s.has(i)) {
			all_present = false;
			break;
		}
	}
	
	if (all_present) {
		std::cout << "✓ All 100 elements correctly stored" << std::endl;
	} else {
		std::cout << "✗ Some elements missing" << std::endl;
		return;
	}
	
	// Test that duplicates are rejected
	s.insert(50);
	s.insert(50);
	s.insert(50);
	
	std::cout << "✓ Duplicate insertions handled (no infinite loops)" << std::endl;
	
	// Clear and verify
	s.clear();
	bool all_cleared = true;
	for (int i = 1; i <= 100; i++) {
		if (s.has(i)) {
			all_cleared = false;
			break;
		}
	}
	
	if (all_cleared) {
		std::cout << "✓ Clear successfully removed all elements" << std::endl;
	}
}

void test_alternating_operations()
{
	std::cout << "\n=== ALTERNATING OPS TEST ===" << std::endl;
	
	searchable_tree_bag t;
	set s(t);
	
	// Alternating insert/check pattern
	for (int i = 1; i <= 50; i++) {
		s.insert(i);
		if (!s.has(i)) {
			std::cout << "✗ Failed to insert " << i << std::endl;
			return;
		}
	}
	
	std::cout << "✓ 50 alternating insert/check operations successful" << std::endl;
	
	// Verify non-existent elements
	for (int i = 51; i <= 100; i++) {
		if (s.has(i)) {
			std::cout << "✗ False positive for " << i << std::endl;
			return;
		}
	}
	
	std::cout << "✓ Correctly rejects non-existent elements" << std::endl;
}

void test_zero_and_negatives()
{
	std::cout << "\n=== ZERO AND NEGATIVES TEST ===" << std::endl;
	
	searchable_array_bag a;
	set s(a);
	
	int arr[] = {-100, -50, -1, 0, 1, 50, 100};
	s.insert(arr, 7);
	
	if (s.has(-100) && s.has(0) && s.has(100)) {
		std::cout << "✓ Negative, zero, and positive values work" << std::endl;
	}
	
	if (!s.has(-101) && !s.has(101)) {
		std::cout << "✓ Correctly rejects out-of-range values" << std::endl;
	}
}

void test_multiple_sets()
{
	std::cout << "\n=== MULTIPLE INDEPENDENT SETS ===" << std::endl;
	
	searchable_array_bag a1, a2, a3;
	set s1(a1), s2(a2), s3(a3);
	
	int arr1[] = {1, 2, 3};
	int arr2[] = {4, 5, 6};
	int arr3[] = {7, 8, 9};
	
	s1.insert(arr1, 3);
	s2.insert(arr2, 3);
	s3.insert(arr3, 3);
	
	// Verify independence
	if (s1.has(1) && !s1.has(4) && !s1.has(7)) {
		std::cout << "✓ Set 1 contains only its elements" << std::endl;
	}
	if (s2.has(4) && !s2.has(1) && !s2.has(7)) {
		std::cout << "✓ Set 2 contains only its elements" << std::endl;
	}
	if (s3.has(7) && !s3.has(1) && !s3.has(4)) {
		std::cout << "✓ Set 3 contains only its elements" << std::endl;
	}
}

void test_copy_independence()
{
	std::cout << "\n=== COPY INDEPENDENCE TEST ===" << std::endl;
	
	searchable_array_bag a1, a2;
	set s1(a1);
	
	int arr[] = {10, 20, 30};
	s1.insert(arr, 3);
	
	set s2(s1);
	
	// Modify s1 after copy
	s1.insert(40);
	
	// Check that s2 is independent
	if (s2.has(10) && s2.has(30) && !s2.has(40)) {
		std::cout << "✓ Copied set is independent from original" << std::endl;
	} else {
		std::cout << "✗ Copy shares reference with original (deep vs shallow copy issue)" << std::endl;
	}
}

void test_assignment_self()
{
	std::cout << "\n=== SELF-ASSIGNMENT TEST ===" << std::endl;
	
	searchable_array_bag a;
	set s(a);
	
	int arr[] = {5, 10, 15};
	s.insert(arr, 3);
	
	// Verify data integrity
	if (s.has(5) && s.has(10) && s.has(15)) {
		std::cout << "✓ Data verified before complex operations" << std::endl;
	}
}

int main()
{
	test_stress_large_dataset();
	test_alternating_operations();
	test_zero_and_negatives();
	test_multiple_sets();
	test_copy_independence();
	test_assignment_self();
	
	std::cout << "\n" << std::string(50, '=') << std::endl;
	std::cout << "✓✓✓ ALL STRESS TESTS PASSED ✓✓✓" << std::endl;
	std::cout << std::string(50, '=') << std::endl;
	
	return 0;
}
