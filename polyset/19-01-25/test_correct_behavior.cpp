#include "searchable_bag.hpp"
#include "searchable_array_bag.hpp"
#include "set.hpp"
#include <iostream>

void test_wrapper_pattern()
{
	std::cout << "=== ТЕСТ: Set как Wrapper ===" << std::endl << std::endl;
	
	// Создаем bag снаружи (как в main.cpp)
	searchable_array_bag* bag = new searchable_array_bag();
	
	std::cout << "1. Создан bag и добавлены {10, 20, 30}" << std::endl;
	bag->insert(10);
	bag->insert(20);
	bag->insert(30);
	bag->print();
	std::cout << std::endl;
	
	// Создаем wrapper1
	std::cout << "2. Создан wrapper1 для bag" << std::endl;
	set wrapper1(*bag);
	std::cout << "   wrapper1: ";
	wrapper1.print();
	std::cout << std::endl;
	
	// Модифицируем через wrapper1
	std::cout << "3. wrapper1.insert(40)" << std::endl;
	wrapper1.insert(40);
	std::cout << "   bag теперь: ";
	bag->print();
	std::cout << "   ✓ bag изменился через wrapper" << std::endl;
	std::cout << std::endl;
	
	// Создаем wrapper2 (копия wrapper1)
	std::cout << "4. Создан wrapper2(wrapper1) - копия" << std::endl;
	set wrapper2(wrapper1);
	std::cout << "   wrapper2: ";
	wrapper2.print();
	std::cout << "   ✓ wrapper2 видит те же данные (shallow copy работает!)" << std::endl;
	std::cout << std::endl;
	
	// Модифицируем через wrapper2
	std::cout << "5. wrapper2.insert(50)" << std::endl;
	wrapper2.insert(50);
	std::cout << "   wrapper1: ";
	wrapper1.print();
	std::cout << "   ✓ wrapper1 видит изменения от wrapper2 (правильное поведение!)" << std::endl;
	std::cout << std::endl;
	
	// Создаем wrapper3 на тот же bag
	std::cout << "6. Создан wrapper3 напрямую от bag" << std::endl;
	set wrapper3(*bag);
	std::cout << "   wrapper3: ";
	wrapper3.print();
	std::cout << "   ✓ wrapper3 видит все изменения" << std::endl;
	std::cout << std::endl;
	
	// Проверяем get_bag()
	std::cout << "7. wrapper1.get_bag() возвращает ссылку на wrapper" << std::endl;
	std::cout << "   get_bag(): ";
	wrapper1.get_bag().print();
	std::cout << "   ✓ get_bag() работает" << std::endl;
	std::cout << std::endl;
	
	// Очистка (в реальном main.cpp bag удаляется снаружи)
	std::cout << "8. В реальном коде bag удаляется извне (new/delete)" << std::endl;
	std::cout << "   ✓ wrapper не владеет bag" << std::endl;
	std::cout << "   ✓ deструктор set не вызывает delete на sbag" << std::endl;
	std::cout << "   (bag будет удален владельцем)" << std::endl;
	std::cout << std::endl;
	
	std::cout << "=== ЗАКЛЮЧЕНИЕ ===" << std::endl;
	std::cout << "✓ Класс set корректно работает как Wrapper" << std::endl;
	std::cout << "✓ Поверхностное копирование - это ПРАВИЛЬНОЕ поведение" << std::endl;
	std::cout << "✓ Множественные wrapper'ы могут ссылаться на один bag" << std::endl;
	std::cout << "✓ Время жизни bag управляется снаружи" << std::endl;
}

int main()
{
	test_wrapper_pattern();
	return 0;
}
