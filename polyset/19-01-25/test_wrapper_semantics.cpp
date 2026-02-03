#include "searchable_bag.hpp"
#include "searchable_array_bag.hpp"
#include "set.hpp"
#include <iostream>

int main()
{
	std::cout << "=== АНАЛИЗ ЗАДАНИЯ POLYSET ===" << std::endl << std::endl;
	
	std::cout << "Из main.cpp видно:" << std::endl;
	std::cout << "1. searchable_bag *a = new searchable_array_bag;" << std::endl;
	std::cout << "2. set sa(*a);  // set ОБОРАЧИВАЕТ существующий bag" << std::endl;
	std::cout << "3. set st(*t);  // set ОБОРАЧИВАЕТ существующий bag" << std::endl;
	std::cout << std::endl;
	
	std::cout << "Ключевое наблюдение:" << std::endl;
	std::cout << "- set НЕ ВЛАДЕЕТ (doesn't own) searchable_bag" << std::endl;
	std::cout << "- set только ОБОРАЧИВАЕТ (wraps) существующий bag" << std::endl;
	std::cout << "- В задании сказано: 'wrap a searchable_bag'" << std::endl;
	std::cout << std::endl;
	
	std::cout << "Проверка концепции wrapper'а:" << std::endl;
	searchable_array_bag original_bag;
	original_bag.insert(10);
	original_bag.insert(20);
	
	set wrapper1(original_bag);
	std::cout << "wrapper1 после создания: ";
	wrapper1.print();
	std::cout << std::endl;
	
	// Добавляем через wrapper
	wrapper1.insert(30);
	
	std::cout << "original_bag после wrapper1.insert(30): ";
	original_bag.print();
	std::cout << "  ^ Видим 30, значит wrapper модифицирует исходный bag!" << std::endl;
	std::cout << std::endl;
	
	// Создаем второй wrapper на тот же bag
	set wrapper2(original_bag);
	std::cout << "wrapper2 (новый wrapper на тот же bag): ";
	wrapper2.print();
	std::cout << "  ^ Видим все элементы, включая 30!" << std::endl;
	std::cout << std::endl;
	
	std::cout << "=== ВЫВОД ===" << std::endl;
	std::cout << "Класс set - это WRAPPER (обертка), а не OWNER (владелец)." << std::endl;
	std::cout << "Поверхностное копирование (shallow copy) - это ПРАВИЛЬНО!" << std::endl;
	std::cout << std::endl;
	std::cout << "Причина:" << std::endl;
	std::cout << "- Множественные wrapper'ы могут ссылаться на один bag" << std::endl;
	std::cout << "- Время жизни bag управляется извне (в main: new/delete)" << std::endl;
	std::cout << "- set не должен удалять bag в деструкторе" << std::endl;
	std::cout << "- Копирование set просто создает новую ссылку на тот же bag" << std::endl;
	
	return 0;
}
