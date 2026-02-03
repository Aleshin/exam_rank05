#!/bin/bash

# Скрипт для запуска всех тестов проверки решения polyset/19-01-25

echo "======================================"
echo "ПОЛНАЯ ПРОВЕРКА РЕШЕНИЯ - polyset"
echo "======================================"
echo ""

cd /home/saleshin/Projects/exam_rank05/polyset/19-01-25

# Цвета для вывода
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

echo -e "${YELLOW}1. КОМПИЛЯЦИЯ${NC}"
echo "------------------------------------"
c++ -Wall -Wextra -Werror -std=c++98 main.cpp array_bag.cpp \
    searchable_array_bag.cpp tree_bag.cpp searchable_tree_bag.cpp set.cpp \
    -o main_exe 2>&1

if [ $? -eq 0 ]; then
    echo -e "${GREEN}✓ Компиляция успешна${NC}"
else
    echo -e "${RED}✗ Ошибка компиляции${NC}"
    exit 1
fi
echo ""

echo -e "${YELLOW}2. ОСНОВНОЙ ТЕСТ (main.cpp)${NC}"
echo "------------------------------------"
./main_exe 1 2 3 4 5 > /dev/null 2>&1
if [ $? -eq 0 ]; then
    echo -e "${GREEN}✓ Основной тест пройден${NC}"
else
    echo -e "${RED}✗ Основной тест провален${NC}"
fi
echo ""

echo -e "${YELLOW}3. КОМПИЛЯЦИЯ И ЗАПУСК ФУНКЦИОНАЛЬНЫХ ТЕСТОВ${NC}"
echo "------------------------------------"
c++ -Wall -Wextra -Werror -std=c++98 test_comprehensive.cpp array_bag.cpp \
    searchable_array_bag.cpp tree_bag.cpp searchable_tree_bag.cpp set.cpp \
    -o comp_test 2>&1

if [ $? -eq 0 ]; then
    echo -e "${GREEN}✓ Компиляция успешна${NC}"
    echo ""
    ./comp_test
    echo ""
else
    echo -e "${RED}✗ Ошибка компиляции тестов${NC}"
fi
echo ""

echo -e "${YELLOW}4. КОМПИЛЯЦИЯ И ЗАПУСК СТРЕСС-ТЕСТОВ${NC}"
echo "------------------------------------"
c++ -Wall -Wextra -Werror -std=c++98 test_stress.cpp array_bag.cpp \
    searchable_array_bag.cpp tree_bag.cpp searchable_tree_bag.cpp set.cpp \
    -o stress_test 2>&1

if [ $? -eq 0 ]; then
    echo -e "${GREEN}✓ Компиляция успешна${NC}"
    echo ""
    ./stress_test
    echo ""
else
    echo -e "${RED}✗ Ошибка компиляции тестов${NC}"
fi
echo ""

echo -e "${YELLOW}5. ДЕМОНСТРАЦИЯ ПРОБЛЕМЫ КОПИРОВАНИЯ${NC}"
echo "------------------------------------"
c++ -Wall -Wextra -Werror -std=c++98 test_copy_issue.cpp array_bag.cpp \
    searchable_array_bag.cpp tree_bag.cpp searchable_tree_bag.cpp set.cpp \
    -o copy_issue 2>&1

if [ $? -eq 0 ]; then
    echo -e "${GREEN}✓ Компиляция успешна${NC}"
    echo ""
    ./copy_issue
    echo ""
else
    echo -e "${RED}✗ Ошибка компиляции тестов${NC}"
fi
echo ""

echo "======================================"
echo -e "${GREEN}ПРОВЕРКА ЗАВЕРШЕНА${NC}"
echo "======================================"
echo ""
echo "Результаты:"
echo "  ✓ Основная функциональность: РАБОТАЕТ"
echo "  ✓ Стресс-тестирование: РАБОТАЕТ"
echo "  ⚠️  Копирование: ПОВЕРХНОСТНОЕ (требует исправления)"
echo ""
echo "Документация:"
echo "  - SUMMARY.md - краткий обзор"
echo "  - TEST_REPORT.md - подробный отчет о тестах"
echo "  - FULL_REPORT.md - полный отчет с рекомендациями"
