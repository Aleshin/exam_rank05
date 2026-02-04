#!/bin/bash

# Скрипт для тестирования решения

echo "=== КОМПИЛЯЦИЯ ==="
make clean
make

if [ ! -f bsq ]; then
    echo "Ошибка компиляции!"
    exit 1
fi

echo -e "\n=== ТЕСТ 1: Простая карта (5x5 все пусто) ==="
cat > test1.txt << 'EOF'
5 . o x
.....
.....
.....
.....
.....
EOF
./bsq test1.txt

echo -e "\n=== ТЕСТ 2: Карта с препятствием ==="
cat > test2.txt << 'EOF'
5 . o x
.....
.....
..o..
.....
.....
EOF
./bsq test2.txt

echo -e "\n=== ТЕСТ 3: Невалидная карта (разные символы) ==="
cat > test3.txt << 'EOF'
3 . . x
...
...
...
EOF
./bsq test3.txt 2>&1

echo -e "\n=== ТЕСТ 4: stdin ==="
cat test1.txt | ./bsq

echo -e "\n=== ТЕСТ 5: Ошибка в длине строк ==="
cat > test5.txt << 'EOF'
3 . o x
...
..
...
EOF
./bsq test5.txt 2>&1

echo -e "\n=== ОЧИСТКА ==="
rm -f test1.txt test2.txt test3.txt test5.txt

echo "Тесты завершены!"
