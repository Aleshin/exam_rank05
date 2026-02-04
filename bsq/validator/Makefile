NAME = validator
CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRCS = validator.c

all: $(NAME)

$(NAME): $(SRCS)
	$(CC) $(CFLAGS) -o $(NAME) $(SRCS)

clean:
	rm -f $(NAME)

re: clean all
