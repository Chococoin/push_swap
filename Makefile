NAME	=	push_swap
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -g
SRCS	=	push_swap.c validations.c sort_utils.c turk_algorithm.c \
			min_cost_utils.c positions.c costs.c validation_utils.c \
			operations_1.c operations_2.c operations_3.c rotations.c \
			stack_utils.c 
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
