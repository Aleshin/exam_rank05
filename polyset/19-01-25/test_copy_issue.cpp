#include "searchable_bag.hpp"
#include "searchable_array_bag.hpp"
#include "set.hpp"

#include <iostream>

void demonstrate_copy_issue()
{
	std::cout << "=== ДЕМОНСТРАЦИЯ ПРОБЛЕМЫ КОПИРОВАНИЯ ===" << std::endl << std::endl;
	
	searchable_array_bag bag_storage;
	set s1(bag_storage);
	
	std::cout << "1. Создан s1 и добавлены элементы {10, 20, 30}" << std::endl;
	int arr1[] = {10, 20, 30};
	s1.insert(arr1, 3);
	std::cout << "   s1: ";
	s1.print();
	std::cout << std::endl;
	
	std::cout << "2. Создана копия s2(s1)" << std::endl;
	set s2(s1);
	std::cout << "   s2: ";
	s2.print();
	std::cout << std::endl;
	
	std::cout << "3. Добавляем элемент 40 в s1" << std::endl;
	s1.insert(40);
	std::cout << "   s1 после insert(40): ";
	s1.print();
	std::cout << std::endl;
	
	std::cout << "4. Проверяем s2 (должна быть {10, 20, 30})" << std::endl;
	std::cout << "   s2 СЕЙЧАС: ";
	s2.print();
	std::cout << std::endl;
	
	if (s2.has(40)) {
		std::cout << "❌ ПРОБЛЕМА: s2 содержит 40, хотя мы добавляли только в s1!" << std::endl;
		std::cout << "   Причина: s1 и s2 ссылаются на ОДИН и тот же searchable_bag" << std::endl;
		std::cout << "   Это поверхностная (shallow) копия, а не глубокая (deep copy)!" << std::endl;
	} else {
		std::cout << "✓ OK: s2 независима от s1" << std::endl;
	}
	
	std::cout << std::endl;
	std::cout << "5. Очищаем s1" << std::endl;
	s1.clear();
	std::cout << "   s1 после clear(): ";
	s1.print();
	std::cout << std::endl;
	
	std::cout << "6. Проверяем s2 (должна быть {10, 20, 30})" << std::endl;
	std::cout << "   s2 СЕЙЧАС: ";
	s2.print();
	std::cout << std::endl;
	
	if (!s2.has(10)) {
		std::cout << "❌ КРИТИЧЕСКАЯ ПРОБЛЕМА: s2 очищена, когда очистили s1!" << std::endl;
		std::cout << "   s2.has(10) = " << s2.has(10) << " (ожидалось 1)" << std::endl;
	}
}

int main()
{
	demonstrate_copy_issue();
	return 0;
}
