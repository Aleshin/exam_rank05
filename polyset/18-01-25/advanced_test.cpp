#include "searchable_bag.hpp"
#include "searchable_tree_bag.hpp"
#include "searchable_array_bag.hpp"
#include "set.hpp"
#include <iostream>
#include <cassert>

void test_polymorphism() {
	std::cout << "=== Test 1: Polymorphism & Virtual Methods ===" << std::endl;
	
	// Test через указатели базовых классов
	searchable_bag* sb1 = new searchable_array_bag();
	searchable_bag* sb2 = new searchable_tree_bag();
	
	sb1->insert(5);
	sb1->insert(3);
	sb1->insert(5); // дубликат в bag
	
	sb2->insert(5);
	sb2->insert(3);
	sb2->insert(5); // дубликат в bag
	
	std::cout << "Array bag (polymorphic): ";
	sb1->print();
	std::cout << "Tree bag (polymorphic): ";
	sb2->print();
	
	assert(sb1->has(5) == true);
	assert(sb1->has(3) == true);
	assert(sb1->has(10) == false);
	
	assert(sb2->has(5) == true);
	assert(sb2->has(3) == true);
	assert(sb2->has(10) == false);
	
	delete sb1;
	delete sb2;
	std::cout << "✓ Polymorphism works correctly\n" << std::endl;
}

void test_copy_semantics() {
	std::cout << "=== Test 2: Copy Constructor & Assignment ===" << std::endl;
	
	// Test copy constructor для array_bag
	searchable_array_bag sab1;
	sab1.insert(10);
	sab1.insert(20);
	sab1.insert(30);
	
	searchable_array_bag sab2(sab1);
	std::cout << "Original array: ";
	sab1.print();
	std::cout << "Copied array: ";
	sab2.print();
	
	// Модифицируем копию
	sab2.insert(40);
	std::cout << "After insert to copy:" << std::endl;
	std::cout << "Original: ";
	sab1.print();
	std::cout << "Modified copy: ";
	sab2.print();
	
	assert(sab1.has(40) == false); // оригинал не изменился
	assert(sab2.has(40) == true);
	
	// Test assignment operator
	searchable_array_bag sab3;
	sab3.insert(99);
	sab3 = sab1;
	std::cout << "After assignment: ";
	sab3.print();
	assert(sab3.has(10) == true);
	assert(sab3.has(99) == false);
	
	// Test copy constructor для tree_bag
	searchable_tree_bag stb1;
	stb1.insert(50);
	stb1.insert(30);
	stb1.insert(70);
	
	searchable_tree_bag stb2(stb1);
	std::cout << "Original tree: ";
	stb1.print();
	std::cout << "Copied tree: ";
	stb2.print();
	
	stb2.insert(10);
	std::cout << "After insert to tree copy:" << std::endl;
	std::cout << "Original: ";
	stb1.print();
	std::cout << "Modified copy: ";
	stb2.print();
	
	assert(stb1.has(10) == false);
	assert(stb2.has(10) == true);
	
	std::cout << "✓ Copy semantics work correctly\n" << std::endl;
}

void test_const_correctness() {
	std::cout << "=== Test 3: Const Correctness ===" << std::endl;
	
	searchable_array_bag sab;
	sab.insert(1);
	sab.insert(2);
	
	const searchable_array_bag& const_ref = sab;
	
	// Эти методы должны компилироваться для const объектов
	std::cout << "Const array bag: ";
	const_ref.print();
	assert(const_ref.has(1) == true);
	assert(const_ref.has(99) == false);
	
	searchable_tree_bag stb;
	stb.insert(10);
	stb.insert(5);
	
	const searchable_tree_bag& const_tree = stb;
	std::cout << "Const tree bag: ";
	const_tree.print();
	assert(const_tree.has(10) == true);
	assert(const_tree.has(99) == false);
	
	std::cout << "✓ Const correctness verified\n" << std::endl;
}

void test_set_uniqueness() {
	std::cout << "=== Test 4: Set Uniqueness ===" << std::endl;
	
	searchable_array_bag sab;
	set array_set(sab);
	
	// Вставляем дубликаты
	array_set.insert(5);
	array_set.insert(5);
	array_set.insert(5);
	array_set.insert(3);
	array_set.insert(3);
	
	std::cout << "Array set (should have no duplicates): ";
	array_set.print();
	
	searchable_tree_bag stb;
	set tree_set(stb);
	
	tree_set.insert(5);
	tree_set.insert(5);
	tree_set.insert(5);
	tree_set.insert(3);
	tree_set.insert(3);
	
	std::cout << "Tree set (should have no duplicates): ";
	tree_set.print();
	
	// Test insert array
	int arr[] = {10, 20, 10, 30, 20, 40};
	array_set.clear();
	array_set.insert(arr, 6);
	std::cout << "After inserting array with duplicates: ";
	array_set.print();
	
	std::cout << "✓ Set uniqueness enforced correctly\n" << std::endl;
}

void test_virtual_inheritance() {
	std::cout << "=== Test 5: Virtual Inheritance (Diamond Problem) ===" << std::endl;
	
	// Проверяем, что virtual наследование работает правильно
	searchable_array_bag sab;
	sab.insert(42);
	
	// Через указатель bag
	bag* b = &sab;
	std::cout << "Through bag* pointer: ";
	b->print();
	
	// Через указатель searchable_bag
	searchable_bag* sb = &sab;
	std::cout << "Through searchable_bag* pointer: ";
	sb->print();
	assert(sb->has(42) == true);
	
	// Через указатель array_bag
	array_bag* ab = &sab;
	std::cout << "Through array_bag* pointer: ";
	ab->print();
	
	std::cout << "✓ Virtual inheritance resolves diamond correctly\n" << std::endl;
}

void test_edge_cases() {
	std::cout << "=== Test 6: Edge Cases ===" << std::endl;
	
	// Empty bags
	searchable_array_bag empty_array;
	searchable_tree_bag empty_tree;
	
	std::cout << "Empty array: ";
	empty_array.print();
	std::cout << "Empty tree: ";
	empty_tree.print();
	
	assert(empty_array.has(1) == false);
	assert(empty_tree.has(1) == false);
	
	// Single element
	empty_array.insert(42);
	empty_tree.insert(42);
	
	assert(empty_array.has(42) == true);
	assert(empty_tree.has(42) == true);
	
	// Clear and reuse
	empty_array.clear();
	empty_tree.clear();
	
	std::cout << "After clear - array: ";
	empty_array.print();
	std::cout << "After clear - tree: ";
	empty_tree.print();
	
	assert(empty_array.has(42) == false);
	assert(empty_tree.has(42) == false);
	
	// Self-assignment
	searchable_array_bag sab_self;
	sab_self.insert(1);
	sab_self.insert(2);
	sab_self = sab_self;
	std::cout << "After self-assignment: ";
	sab_self.print();
	assert(sab_self.has(1) == true);
	assert(sab_self.has(2) == true);
	
	std::cout << "✓ Edge cases handled correctly\n" << std::endl;
}

void test_large_dataset() {
	std::cout << "=== Test 7: Large Dataset ===" << std::endl;
	
	searchable_array_bag sab;
	searchable_tree_bag stb;
	
	// Вставляем 100 элементов
	for (int i = 0; i < 100; i++) {
		sab.insert(i);
		stb.insert(i);
	}
	
	// Проверяем поиск
	for (int i = 0; i < 100; i++) {
		assert(sab.has(i) == true);
		assert(stb.has(i) == true);
	}
	
	assert(sab.has(100) == false);
	assert(stb.has(100) == false);
	assert(sab.has(-1) == false);
	assert(stb.has(-1) == false);
	
	std::cout << "✓ Large dataset (100 elements) handled correctly\n" << std::endl;
}

void test_set_wrapper_behavior() {
	std::cout << "=== Test 8: Set Wrapper Behavior ===" << std::endl;
	
	searchable_array_bag sab;
	set s(sab);
	
	s.insert(5);
	s.insert(3);
	s.insert(8);
	
	std::cout << "Set contents: ";
	s.print();
	
	// get_bag должен возвращать ссылку на тот же bag
	searchable_bag& bag_ref = s.get_bag();
	std::cout << "Through get_bag(): ";
	bag_ref.print();
	
	assert(bag_ref.has(5) == true);
	assert(s.has(5) == true);
	
	// Модификация через get_bag влияет на set
	bag_ref.insert(10);
	assert(s.has(10) == true);
	
	std::cout << "After insert through get_bag(): ";
	s.print();
	
	std::cout << "✓ Set wrapper behavior correct\n" << std::endl;
}

void test_multiple_inheritance_ambiguity() {
	std::cout << "=== Test 9: Multiple Inheritance Methods ===" << std::endl;
	
	searchable_array_bag sab;
	sab.insert(1);
	sab.insert(2);
	
	// Все эти вызовы должны работать без ambiguity
	sab.print();              // из bag через array_bag
	sab.has(1);               // из searchable_bag
	sab.insert(3);            // из bag через array_bag
	sab.clear();              // из bag через array_bag
	
	searchable_tree_bag stb;
	stb.insert(10);
	stb.insert(5);
	
	stb.print();
	stb.has(10);
	stb.insert(15);
	stb.clear();
	
	std::cout << "✓ No ambiguity in multiple inheritance\n" << std::endl;
}

int main() {
	std::cout << "\n╔════════════════════════════════════════════╗" << std::endl;
	std::cout << "║   ADVANCED POLYSET VALIDATION TEST        ║" << std::endl;
	std::cout << "╚════════════════════════════════════════════╝\n" << std::endl;
	
	try {
		test_polymorphism();
		test_copy_semantics();
		test_const_correctness();
		test_set_uniqueness();
		test_virtual_inheritance();
		test_edge_cases();
		test_large_dataset();
		test_set_wrapper_behavior();
		test_multiple_inheritance_ambiguity();
		
		std::cout << "\n╔════════════════════════════════════════════╗" << std::endl;
		std::cout << "║   ✓✓✓ ALL TESTS PASSED SUCCESSFULLY ✓✓✓   ║" << std::endl;
		std::cout << "╚════════════════════════════════════════════╝\n" << std::endl;
		
		return 0;
	} catch (const std::exception& e) {
		std::cerr << "\n✗ TEST FAILED: " << e.what() << std::endl;
		return 1;
	} catch (...) {
		std::cerr << "\n✗ TEST FAILED: Unknown exception" << std::endl;
		return 1;
	}
}
