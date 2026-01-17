# Polyset - Exam Rank 05

## Важно!

**НЕ исправляйте готовые файлы экзамена!** Даже если они содержат ошибки компиляции с `-std=c++98`.

## Структура задания

### Файлы, которые ДАЮТСЯ на экзамене (НЕ трогать):
- `main.cpp` - использует `atoi` без `#include <cstdlib>` 
- `bag.hpp` - базовый интерфейс
- `searchable_bag.hpp` - интерфейс для поиска
- `array_bag.hpp` и `array_bag.cpp` - реализация через массив (использует `nullptr`)
- `tree_bag.hpp` и `tree_bag.cpp` - реализация через дерево (использует `nullptr`)

### Файлы, которые ВЫ должны написать:
- `searchable_array_bag.hpp` и `searchable_array_bag.cpp` - наследник от `array_bag` и `searchable_bag`
- (или) `searchable_tree_bag.hpp` и `searchable_tree_bag.cpp` - наследник от `tree_bag` и `searchable_bag`

## Правильная компиляция

Экзамен компилирует с **C++11** (или выше), а не C++98:

```bash
c++ -Wall -Werror -Wextra -std=c++11 main.cpp searchable_array_bag.cpp array_bag.cpp
```

## Что нужно реализовать в searchable_array_bag

1. **Конструктор по умолчанию** - пустой, вызывает конструктор базового класса
2. **Копирующий конструктор** - вызывает копирующий конструктор `array_bag`
3. **Оператор присваивания** - вызывает оператор присваивания `array_bag`
4. **Деструктор** - пустой, базовый класс все очистит
5. **bool has(int value) const** - проверяет наличие элемента в массиве

### Пример реализации has():

```cpp
bool searchable_array_bag::has(int value) const {
    for(int i = 0; i < this->size; i++) {
        if(this->data[i] == value)
            return true;
    }
    return false;
}
```

## Тестирование

```bash
./a.out 1 2 3 4 5
# Выведет:
# 1 2 3 4 5          <- print()
# 1 0 1 1 1 1 1 1 1 1  <- результаты has() для каждого числа и числа-1
```

## Ключевые моменты

- ✅ Используйте **виртуальное наследование** (`virtual public`)
- ✅ Используйте `this->size` и `this->data` для доступа к protected полям
- ✅ Базовые классы делают всю работу с памятью - не дублируйте код
- ❌ **НЕ исправляйте** готовые файлы экзамена
- ❌ **НЕ используйте** `-std=c++98` для компиляции
