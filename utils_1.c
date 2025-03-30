/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glugo-mu <glugo-mu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 19:12:23 by glugo-mu          #+#    #+#             */
/*   Updated: 2025/03/31 01:35:59 by glugo-mu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	get_position(t_node *stack, int value)
{
	int	pos;

	pos = 0;
	while (stack)
	{
		if (stack->value == value)
			return (pos);
		pos++;
		stack = stack->next;
	}
	return (-1);
}

int	get_min_value(t_node *stack)
{
	int	min;

	if (!stack)
		return (0);
	min = stack->value;
	while (stack)
	{
		if (stack->value < min)
			min = stack->value;
		stack = stack->next;
	}
	return (min);
}

int	find_position_in_b(t_node *stack_b, int value)
{
	int		pos;
	int		min;
	int		max;
	t_node	*current;

	if (!stack_b)
		return (0);
	min = get_min_value(stack_b);
	max = get_max_value(stack_b);
	if (value > max || value < min)
		return (get_position(stack_b, max));
	pos = 0;
	current = stack_b;
	while (current && current->next)
	{
		if (value < current->value && value > current->next->value)
			return (pos + 1);
		pos++;
		current = current->next;
	}
	return (0);
}

int	find_cheapest(t_node *a, t_node *b)
{
	t_node	*cur;
	t_cost	min_c;
	t_cost	cur_c;
	int		cheap_val;

	cur = a;
	min_c.total = 2147483647;
	cheap_val = cur->value;
	while (cur)
	{
		cur_c = calc_cost(a, b, cur->value);
		if (cur_c.total < min_c.total)
		{
			min_c = cur_c;
			cheap_val = cur->value;
		}
		cur = cur->next;
	}
	return (cheap_val);
}

void	push_min_to_b(t_node **stack_a, t_node **stack_b)
{
	int	min_index;
	int	len;
	int	moves;

	min_index = get_min_index(*stack_a);
	len = stack_length(*stack_a);
	if (min_index == 0)
		pb(stack_a, stack_b);
	else if (min_index <= len / 2)
	{
		while (min_index-- > 0)
			ra(stack_a, 1);
		pb(stack_a, stack_b);
	}
	else
	{
		moves = len - min_index;
		while (moves-- > 0)
			rra(stack_a, 1);
		pb(stack_a, stack_b);
	}
}
