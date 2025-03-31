NAME	=	push_swap
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror
SRCS	=	push_swap.c validations.c stack.c sort.c turk_algorithm.c \
			utils_1.c utils_2.c utils_3.c utils_validations.c \
			operations_1.c operations_2.c operations_3.c
OBJS	= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

%.o: %.c push_swap.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
