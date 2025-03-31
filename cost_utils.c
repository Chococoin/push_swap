/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glugo-mu <glugo-mu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 19:12:23 by glugo-mu          #+#    #+#             */
/*   Updated: 2025/03/31 13:30:42 by glugo-mu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
