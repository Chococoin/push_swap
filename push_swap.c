/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glugo-mu <glugo-mu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 16:27:48 by glugo-mu          #+#    #+#             */
/*   Updated: 2025/03/09 18:01:03 by glugo-mu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_node
{
	int	value;
	struct	s_node	*prev;
	struct	s_node	*next;
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

int	atoi_validator(char *s)
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
	if (result == 0)
		return (-1);
	return (result * sign);
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

void	validate_no_characters(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (!(atoi_validator(argv[i])))
			print_error();
		i++;
	}
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
		new_node->value = atoi(argv[i]);
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

void sa(t_node **stack_a, int to_print)
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

void sb(t_node **stack_b, int to_print)
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

void	ss(t_node **stack_b, t_node **stack_a)
{
	sa(stack_a, 0);
	sa(stack_b, 0);
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

int stack_length(t_node *stack)
{
	int count;
	t_node *tmp;

	count = 0;
	tmp = stack;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

void	validate_args(char **argv)
{
	validate_no_clones(argv);
	validate_no_characters(argv);
}

void	stack_to_array(t_node *stack, int *arr)
{
	int		i;
	t_node	*tmp;

	i = 0;
	tmp = stack;
	while (tmp)
	{
		arr[i] = tmp->value;
		tmp = tmp->next;
		i++;
	}
}

void print_stacks(t_node *stack_a, t_node *stack_b)
{
	t_node *tmp_a;
	t_node *tmp_b;

	tmp_a = stack_a;
	tmp_b = stack_b;
	while (tmp_a && tmp_a->prev)
		tmp_a = tmp_a->prev;
	while (tmp_b && tmp_b->prev)
		tmp_b = tmp_b->prev;
	while (tmp_a || tmp_b)
	{
		if (tmp_a)
		{
			printf("%d ", tmp_a->value);
			tmp_a = tmp_a->next;
		}
		if (tmp_b)
		{
			printf("%d", tmp_b->value);
			tmp_b = tmp_b->next;
		}
		printf("\n");
	}
	printf("~~~\nA B\n");
}

int	main(int argc, char **argv)
{
	t_node	*stack_a;
	t_node	*stack_b;
	
	stack_a = NULL;
	stack_b = NULL;
	(void)stack_b;
	if (argc == 1)
		return (0);
	validate_args(argv);
	fill_stack_a(argv, &stack_a);
	print_stacks(stack_a, stack_b);
	sa(&stack_a, 1);
	print_stacks(stack_a, stack_b);
	pb(&stack_a, &stack_b);
	print_stacks(stack_a, stack_b);
	pb(&stack_a, &stack_b);
	print_stacks(stack_a, stack_b);
	ss(&stack_a, &stack_b);
	print_stacks(stack_a, stack_b);
	pa(&stack_a, &stack_b);
	print_stacks(stack_a, stack_b);
	return (0);
}
