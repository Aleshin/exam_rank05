CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = life
SRC = life.c

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)

clean:
	rm -f $(NAME)

fclean: clean

re: fclean all

test: $(NAME)
	@echo "\n=== Test 1: 3x3, 0 iterations ==="
	@echo 'dxss' | ./$(NAME) 3 3 0
	@echo "\n=== Test 2: 3x3, 1 iteration ==="
	@echo 'dxss' | ./$(NAME) 3 3 1
	@echo "\n=== Test 3: 3x3, 2 iterations ==="
	@echo 'dxss' | ./$(NAME) 3 3 2
	@echo "\n=== Test 4: 5x5, 0 iterations ==="
	@echo 'sdxddssaaww' | ./$(NAME) 5 5 0
	@echo "\n=== Test 5: 10x6, 0 iterations ==="
	@echo 'sdxssdswdxdddxsaddawxwdxwaa' | ./$(NAME) 10 6 0

.PHONY: all clean fclean re test
