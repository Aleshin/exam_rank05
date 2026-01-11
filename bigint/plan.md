# Bigint — Поэтапная реализация

## Логика порядка этапов:

**Подготовительные (без них ничего не тестировать):**
1. Конструкторы — создать объект
2. operator<< вывода — увидеть результат

**Сложные (требуют запоминания алгоритма):**
3. operator+ — сложение строк с carry
4. operator< — сравнение (длина → лексикографически)

**Зависимые от сложных (нужны для сдвига с bigint):**
5. operator<<, >> с int — простая работа со строкой
6. toInt + сдвиг с bigint — конвертация и вызов предыдущего

**Технические (через уже написанное):**
7. +=, <<=, >>= — однострочники через базовые
8. ==, !=, >, <=, >= — через operator<

---

## Этап 1: Конструкторы (подготовка)

**HPP — минимум для теста:**
```cpp
#pragma once
#include <string>
#include <sstream>

class bigint {
private:
    std::string _str;
public:
    bigint();
    bigint(unsigned int n);
    bigint(const bigint& src);
    bigint& operator=(const bigint& src);
    ~bigint();
    
    std::string getStr() const;
};
```

**CPP:**
```cpp
#include "bigint.hpp"

bigint::bigint() : _str("0") {}

bigint::bigint(unsigned int n) {
    std::ostringstream oss;
    oss << n;
    _str = oss.str();
}

bigint::bigint(const bigint& src) : _str(src._str) {}

bigint& bigint::operator=(const bigint& src) {
    if (this != &src)
        _str = src._str;
    return *this;
}

bigint::~bigint() {}

std::string bigint::getStr() const { return _str; }
```

**Тест:**
```cpp
int main() {
    bigint a(42);
    bigint b;
    bigint c(a);
    std::cout << a.getStr() << " " << b.getStr() << " " << c.getStr() << std::endl;
    // Ожидаем: 42 0 42
}
```

---

## Этап 2: operator<< вывода (подготовка)

**Добавить в HPP:**
```cpp
std::ostream& operator<<(std::ostream& os, const bigint& obj);
```

**Добавить в CPP:**
```cpp
std::ostream& operator<<(std::ostream& os, const bigint& obj) {
    os << obj.getStr();
    return os;
}
```

**Тест:**
```cpp
bigint a(12345);
std::cout << "a = " << a << std::endl;
// Ожидаем: a = 12345
```

---

## Этап 3: operator+ сложение (СЛОЖНЫЙ)

**Алгоритм запомнить:**
- i, j — индексы с конца строк
- while пока есть цифры ИЛИ carry
- результат собирается задом наперёд → reverse

**Добавить в HPP:**
```cpp
bigint operator+(const bigint& r) const;
```

**Добавить в CPP:**
```cpp
bigint bigint::operator+(const bigint& r) const {
    std::string res;
    int carry = 0;
    int i = _str.size() - 1;
    int j = r._str.size() - 1;

    while (i >= 0 || j >= 0 || carry) {
        int sum = carry;
        if (i >= 0) sum += _str[i--] - '0';
        if (j >= 0) sum += r._str[j--] - '0';
        res.push_back(sum % 10 + '0');
        carry = sum / 10;
    }
    // reverse без <algorithm>:
    bigint result;
    result._str = std::string(res.rbegin(), res.rend());
    return result;
}
```

**Тест:**
```cpp
std::cout << bigint(999) + bigint(1) << std::endl;      // 1000
std::cout << bigint(12345) + bigint(67890) << std::endl; // 80235
std::cout << bigint(0) + bigint(42) << std::endl;        // 42
```

---

## Этап 4: operator< сравнение (СЛОЖНЫЙ)

**Алгоритм:** сначала длина, потом лексикографически

**Добавить в HPP:**
```cpp
bool operator<(const bigint& r) const;
```

**Добавить в CPP:**
```cpp
bool bigint::operator<(const bigint& r) const {
    if (_str.size() != r._str.size())
        return _str.size() < r._str.size();
    return _str < r._str;
}
```

**Тест:**
```cpp
std::cout << (bigint(42) < bigint(100)) << std::endl;  // 1 (true)
std::cout << (bigint(42) < bigint(99)) << std::endl;   // 1 (42 < 99)
std::cout << (bigint(99) < bigint(42)) << std::endl;   // 0 (false)
std::cout << (bigint(42) < bigint(42)) << std::endl;   // 0 (false)
```

---

## Этап 5: operator<<, >> сдвиг с int

**Добавить в HPP:**
```cpp
bigint operator<<(int n) const;
bigint operator>>(int n) const;
```

**Добавить в CPP:**
```cpp
bigint bigint::operator<<(int n) const {
    if (_str == "0" || n <= 0)
        return *this;
    bigint res;
    res._str = _str;
    res._str.append(n, '0');
    return res;
}

bigint bigint::operator>>(int n) const {
    if (n <= 0)
        return *this;
    if ((size_t)n >= _str.size())
        return bigint(0);
    bigint res;
    res._str = _str.substr(0, _str.size() - n);
    return res;
}
```

**Тест:**
```cpp
std::cout << (bigint(42) << 3) << std::endl;   // 42000
std::cout << (bigint(1337) >> 2) << std::endl; // 13
std::cout << (bigint(0) << 5) << std::endl;    // 0
std::cout << (bigint(42) >> 10) << std::endl;  // 0
```

---

## Этап 6: toInt + сдвиг с bigint

**Добавить в HPP:**
```cpp
bigint operator<<(const bigint& r) const;
bigint operator>>(const bigint& r) const;

int toInt(const bigint& obj);
```

**Добавить в CPP:**
```cpp
int toInt(const bigint& obj) {
    std::istringstream iss(obj.getStr());
    int res;
    iss >> res;
    return res;
}

bigint bigint::operator<<(const bigint& r) const {
    return *this << toInt(r);
}

bigint bigint::operator>>(const bigint& r) const {
    return *this >> toInt(r);
}
```

**Тест:**
```cpp
bigint shift(3);
std::cout << (bigint(42) << shift) << std::endl;  // 42000
std::cout << (bigint(1337) >> shift) << std::endl; // 1
```

---

## Этап 7: +=, <<=, >>= (технический)

**Добавить в HPP:**
```cpp
bigint& operator+=(const bigint& r);
bigint& operator<<=(int n);
bigint& operator>>=(int n);
bigint& operator<<=(const bigint& r);
bigint& operator>>=(const bigint& r);
bigint& operator++();
bigint operator++(int);
```

**Добавить в CPP (все однострочники):**
```cpp
bigint& bigint::operator+=(const bigint& r) { *this = *this + r; return *this; }
bigint& bigint::operator<<=(int n) { *this = *this << n; return *this; }
bigint& bigint::operator>>=(int n) { *this = *this >> n; return *this; }
bigint& bigint::operator<<=(const bigint& r) { *this = *this << r; return *this; }
bigint& bigint::operator>>=(const bigint& r) { *this = *this >> r; return *this; }
bigint& bigint::operator++() { *this = *this + bigint(1); return *this; }
bigint bigint::operator++(int) { bigint t = *this; ++(*this); return t; }
```

**Тест:**
```cpp
bigint a(10);
a += bigint(5);
std::cout << a << std::endl;  // 15
a <<= 2;
std::cout << a << std::endl;  // 1500
std::cout << ++a << std::endl; // 1501
std::cout << a++ << std::endl; // 1501
std::cout << a << std::endl;   // 1502
```

---

## Этап 8: ==, !=, >, <=, >= (технический)

**Добавить в HPP:**
```cpp
bool operator==(const bigint& r) const;
bool operator!=(const bigint& r) const;
bool operator>(const bigint& r) const;
bool operator<=(const bigint& r) const;
bool operator>=(const bigint& r) const;
```

**Добавить в CPP:**
```cpp
bool bigint::operator==(const bigint& r) const { return _str == r._str; }
bool bigint::operator!=(const bigint& r) const { return !(*this == r); }
bool bigint::operator>(const bigint& r) const { return r < *this; }
bool bigint::operator<=(const bigint& r) const { return !(r < *this); }
bool bigint::operator>=(const bigint& r) const { return !(*this < r); }
```

**ВАЖНО:** `>` это `r < *this`, НЕ `!(*this < r)`!

**Тест:**
```cpp
std::cout << (bigint(42) == bigint(42)) << std::endl; // 1
std::cout << (bigint(42) != bigint(43)) << std::endl; // 1
std::cout << (bigint(100) > bigint(42)) << std::endl; // 1
std::cout << (bigint(42) <= bigint(42)) << std::endl; // 1
std::cout << (bigint(42) >= bigint(42)) << std::endl; // 1
```

---

## Мнемоники:

1. **Конструктор из int:** `ostringstream oss; oss << n; _str = oss.str();`
2. **Сложение:** `while (i >= 0 || j >= 0 || carry)` + `std::string(res.rbegin(), res.rend())`
3. **Сравнение <:** длина → строка
4. **Сдвиг <<:** `append(n, '0')`
5. **Сдвиг >>:** `substr(0, size - n)`
6. **toInt:** `istringstream iss(str); iss >> res;`
7. **>:** `return r < *this;`

---

## Типичные ошибки:

1. Забыть `const` в операторах
2. `>` как `!(*this < r)` — сломает для равных!
3. Забыть проверку `_str == "0"` в `<<`
4. Забыть `return *this` в compound операторах