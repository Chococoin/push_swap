/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glugo-mu <glugo-mu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 18:34:19 by glugo-mu          #+#    #+#             */
/*   Updated: 2025/03/15 17:18:22 by glugo-mu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
	int	count;

	count = 0;
	while (stack)
	{
		count++;
		stack = stack->next;
	}
	return (count);
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

void	print_stacks(t_node *stack_a, t_node *stack_b)
{
	t_node	*tmp_a;
	t_node	*tmp_b;

	tmp_a = stack_a;
	tmp_b = stack_b;
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
