/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   positions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glugo-mu <glugo-mu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 19:14:16 by glugo-mu          #+#    #+#             */
/*   Updated: 2025/03/31 13:42:57 by glugo-mu         ###   ########.fr       */
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
