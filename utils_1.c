/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glugo-mu <glugo-mu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 19:12:23 by glugo-mu          #+#    #+#             */
/*   Updated: 2025/03/30 20:17:28 by glugo-mu         ###   ########.fr       */
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

void	calc_rot_costs(t_cost *c, int pos, int len)
{
	c->ra_cost = 0;
	c->rra_cost = 0;
	if (pos <= len / 2)
		c->ra_cost = pos;
	else
		c->rra_cost = len - pos;
}

int	get_minimum(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}
