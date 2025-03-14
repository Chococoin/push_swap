/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glugo-mu <glugo-mu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 16:27:48 by glugo-mu          #+#    #+#             */
/*   Updated: 2025/03/14 21:46:09 by glugo-mu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_node
{
	int				value;
	struct s_node	*prev;
	struct s_node	*next;
}	t_node;

void	print_error(void)
{
	write(2, "Error\n", 6);
	exit(1);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

void	free_stack(t_node *stack)
{
	t_node	*tmp;

	while (stack)
	{
		tmp = stack;
		stack = stack->next;
		free(tmp);
	}
}

int	ft_atoi(char *s)
{
	int	sign;
	int	result;

	sign = 1;
	result = 0;
	while (*s == ' ' || *s == '\n' || *s == '\t' || *s == '\v')
		s++;
	if (*s == '+' || *s == '-')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	while (*s)
	{
		if (*s >= '0' && *s <= '9')
			result = result * 10 + (*s - '0');
		s++;
	}
	return (result * sign);
}

int	no_alpha_validator(char *s)
{
	while (*s)
	{
		if (!(*s >= '0' && *s <= '9') && *s != '-')
		{
			return (0);
		}
		s++;
	}
	return (1);
}

void	validate_no_clones(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = i + 1;
		while (argv[j])
		{
			if (ft_strcmp(argv[i], argv[j]) == 0)
				print_error();
			j++;
		}
		i++;
	}
}

void	validate_no_char(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (!(no_alpha_validator(argv[i])))
			print_error();
		i++;
	}
}

void	validate_args(char **argv)
{
	validate_no_clones(argv);
	validate_no_char(argv);
}

void	fill_stack_a(char **argv, t_node **stack_a)
{
	int		i;
	t_node	*new_node;
	t_node	*tail;

	i = 1;
	tail = NULL;
	while (argv[i])
	{
		new_node = malloc(sizeof(t_node));
		if (!new_node)
			print_error();
		new_node->value = ft_atoi(argv[i]);
		new_node->prev = tail;
		new_node->next = NULL;
		if (!*stack_a)
			*stack_a = new_node;
		else
			tail->next = new_node;
		tail = new_node;
		i++;
	}
}

int	stack_length(t_node *stack)
{
	int		count = 0;
	t_node	*tmp = stack;

	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

void	restore_values(t_node *stack, int *sorted_arr)
{
	while (stack)
	{
		int index = stack->value;
		stack->value = sorted_arr[index];
		stack = stack->next;
	}
}

void	print_stacks(t_node *stack_a, t_node *stack_b)
{
	t_node	*tmp_a = stack_a;
	t_node	*tmp_b = stack_b;

	while (tmp_a && tmp_a->prev)
		tmp_a = tmp_a->prev;
	while (tmp_b && tmp_b->prev)
		tmp_b = tmp_b->prev;

	write(1, "STACK_A STACK_B\n", 16);
	while (tmp_a || tmp_b)
	{
		if (tmp_a)
		{
			printf("%d ", tmp_a->value);
			tmp_a = tmp_a->next;
		}
		else
			printf("  ");
		printf("   ");
		if (tmp_b)
		{
			printf("%d", tmp_b->value);
			tmp_b = tmp_b->next;
		}
		printf("\n");
	}
	printf("--------\n");
}

void	sa(t_node **stack_a, int to_print)
{
	t_node	*head;
	int		temp;

	if (!stack_a || !(*stack_a) || !(*stack_a)->next)
		return;
	head = *stack_a;
	temp = head->value;
	head->value = head->next->value;
	head->next->value = temp;

	if (to_print)
		write(1, "sa\n", 3);
}

void	sb(t_node **stack_b, int to_print)
{
	t_node	*head;
	int		temp;

	if (!stack_b || !(*stack_b) || !(*stack_b)->next)
		return ;
	head = *stack_b;
	temp = head->value;
	head->value = head->next->value;
	head->next->value = temp;
	if(to_print)
		write(1, "sb\n", 3);
}

void	ss(t_node **stack_a, t_node **stack_b)
{
	sa(stack_a, 0);
	sb(stack_b, 0);
	write(1, "ss\n", 3);
}

void	pa(t_node **stack_a, t_node **stack_b)
{
	t_node *top_b;

	if (!stack_b || !(*stack_b))
		return;
	top_b = *stack_b;
	*stack_b = top_b->next;
	if (*stack_b)
		(*stack_b)->prev = NULL;
	top_b->prev = NULL;
	top_b->next = *stack_a;
	if (*stack_a)
		(*stack_a)->prev = top_b;
	*stack_a = top_b;
	write(1, "pa\n", 3);
}

void	pb(t_node **stack_a, t_node **stack_b)
{
	t_node	*top_a;

	if (!stack_a || !(*stack_a))
		return;
	top_a = *stack_a;
	*stack_a = top_a->next;
	if (*stack_a)
		(*stack_a)->prev = NULL;
	top_a->prev = NULL;
	top_a->next = *stack_b;
	if (*stack_b)
		(*stack_b)->prev = top_a;
	*stack_b = top_a;
	write(1, "pb\n", 3);
}

void	ra(t_node **stack_a, int to_print)
{
	t_node *head;
	t_node *tail;

	if (!stack_a || !(*stack_a) || !(*stack_a)->next)
		return ;
	head = *stack_a;
	tail = head;
	while (tail->next)
		tail = tail->next;
	*stack_a = head->next;
	(*stack_a)->prev = NULL;
	head->next = NULL;
	head->prev = tail;
	tail->next = head;
	if (to_print)
		write(1, "ra\n", 3);
}

void	rb(t_node **stack_b, int to_print)
{
	t_node *head;
	t_node *tail;

	if (!stack_b || !(*stack_b) || !(*stack_b)->next)
		return ;
	head = *stack_b;
	tail = head;
	while (tail->next)
		tail = tail->next;
	*stack_b = head->next;
	(*stack_b)->prev = NULL;
	head->next = NULL;
	head->prev = tail;
	tail->next = head;
	if (to_print)
		write(1, "rb\n", 3);
}

void	rr(t_node **stack_a, t_node **stack_b)
{
	ra(stack_a, 0);
	rb(stack_b, 0);
	write(1, "rr\n", 3);
}

void	rra(t_node **stack_a, int to_print)
{
	t_node *head;
	t_node *tail;

	if (!stack_a || !(*stack_a) || !(*stack_a)->next)
		return ;
	head = *stack_a;
	tail = head;
	while (tail->next)
		tail = tail->next;
	tail->prev->next = NULL;
	tail->prev = NULL;
	tail->next = head;
	head->prev = tail;
	*stack_a = tail;
	if (to_print)
		write(1, "rra\n", 4);
}

void	rrb(t_node **stack_b, int to_print)
{
	t_node *head;
	t_node *tail;

	if (!stack_b || !(*stack_b) || !(*stack_b)->next)
		return ;
	head = *stack_b;
	tail = head;
	while (tail->next)
		tail = tail->next;
	tail->prev->next = NULL;
	tail->prev = NULL;
	tail->next = head;
	head->prev = tail;
	*stack_b = tail;
	if (to_print)
		write(1, "rrb\n", 4);
}

void	rrr(t_node **stack_a, t_node **stack_b)
{
	rra(stack_a, 0);
	rrb(stack_b, 0);
	write(1, "rrr\n", 4);
}

int	*compress_values(t_node *stack, int size)
{
	int		*sorted_arr;
	int		*tmp_values;
	t_node	*cur;
	int		i;

	tmp_values = malloc(sizeof(int) * size);
	if (!tmp_values)
		return (NULL);
	cur = stack;
	i = 0;
	while (cur)
	{
		tmp_values[i++] = cur->value;
		cur = cur->next;
	}

	sorted_arr = malloc(sizeof(int) * size);
	if (!sorted_arr)
	{
		free(tmp_values);
		return (NULL);
	}
	for (int k = 0; k < size; k++)
		sorted_arr[k] = tmp_values[k];

	for (int a = 0; a < size - 1; a++)
	{
		for (int b = a + 1; b < size; b++)
		{
			if (sorted_arr[a] > sorted_arr[b])
			{
				int aux = sorted_arr[a];
				sorted_arr[a] = sorted_arr[b];
				sorted_arr[b] = aux;
			}
		}
	}

	cur = stack;
	while (cur)
	{
		int idx = 0;
		while (sorted_arr[idx] != cur->value)
			idx++;
		cur->value = idx;
		cur = cur->next;
	}

	free(tmp_values);
	return (sorted_arr);
}

int	get_max_bits(t_node *stack)
{
	int max = 0;
	t_node *tmp = stack;
	while (tmp)
	{
		if (tmp->value > max)
			max = tmp->value;
		tmp = tmp->next;
	}
	int bits = 0;
	while ((max >> bits) != 0)
		bits++;
	return bits;
}

void	radix_sort(t_node **stack_a, t_node **stack_b)
{
	int	bits = get_max_bits(*stack_a);
	int	size = stack_length(*stack_a);
	for (int i = 0; i < bits; i++)
	{
		int moves = size;
		while (moves--)
		{
			int top_val = (*stack_a)->value;
			if (((top_val >> i) & 1) == 0)
				pb(stack_a, stack_b);
			else
				ra(stack_a, 1);
		}
		while (*stack_b)
			pa(stack_a, stack_b);
	}
}

void push_swap(t_node **stack_a, t_node **stack_b)
{
    int size = stack_length(*stack_a);
    if (size <= 1)
        return;

    int *sorted_arr = compress_values(*stack_a, size);
    if (!sorted_arr)
        print_error();

    radix_sort(stack_a, stack_b);

    restore_values(*stack_a, sorted_arr);

    free(sorted_arr);
}

int	main(int argc, char **argv)
{
	t_node	*stack_a = NULL;
	t_node	*stack_b = NULL;

	if (argc == 1)
		return (0);

	validate_args(argv);

	fill_stack_a(argv, &stack_a);
	print_stacks(stack_a, stack_b);

	push_swap(&stack_a, &stack_b);

	print_stacks(stack_a, stack_b);

	free_stack(stack_a);
	free_stack(stack_b);
	return (0);
}
