/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glugo-mu <glugo-mu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 22:43:23 by glugo-mu          #+#    #+#             */
/*   Updated: 2025/04/03 20:16:26 by glugo-mu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	get_min_index(t_node *stack)
{
	int	min;
	int	index;
	int	min_index;

	min = stack->value;
	index = 0;
	min_index = 0;
	while (stack)
	{
		if (stack->value < min)
		{
			min = stack->value;
			min_index = index;
		}
		index++;
		stack = stack->next;
	}
	return (min_index);
}

int	get_max_value(t_node *stack)
{
	int	max;

	max = stack->value;
	while (stack)
	{
		if (stack->value > max)
			max = stack->value;
		stack = stack->next;
	}
	return (max);
}

void	push_min_to_b(t_node **stack_a, t_node **stack_b)
{
	int	min_index;
	int	len;
	int	moves;

	min_index = get_min_index(*stack_a);
	len = stack_length(*stack_a);
	if (min_index <= len / 2)
	{
		while (min_index-- > 0)
			ra(stack_a, 1);
	}
	else
	{
		moves = len - min_index;
		while (moves-- > 0)
			rra(stack_a, 1);
	}
	pb(stack_a, stack_b);
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
