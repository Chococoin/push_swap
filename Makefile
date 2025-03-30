NAME    = push_swap
CC      = gcc
CFLAGS  = -Wall -Wextra -Werror -fprofile-arcs -ftest-coverage
SRCS    = push_swap.c validations.c stack.c operations.c sort.c turk_algorithm.c
OBJS    = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -ftest-coverage

%.o: %.c push_swap.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) *.gcno *.gcda *.gcov

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
