/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glugo-mu <glugo-mu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 19:14:16 by glugo-mu          #+#    #+#             */
/*   Updated: 2025/03/30 20:20:53 by glugo-mu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	adj_common_cost(t_cost *c)
{
	int	common;

	if (c->ra_cost > 0 && c->rb_cost > 0)
	{
		common = get_minimum(c->ra_cost, c->rb_cost);
		c->total -= common;
	}
	else if (c->rra_cost > 0 && c->rrb_cost > 0)
	{
		common = get_minimum(c->rra_cost, c->rrb_cost);
		c->total -= common;
	}
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

void	exec_common_rot(t_node **stack_a, t_node **stack_b, t_cost *cost)
{
	while (cost->ra_cost > 0 && cost->rb_cost > 0)
	{
		rr(stack_a, stack_b);
		cost->ra_cost--;
		cost->rb_cost--;
	}
	while (cost->rra_cost > 0 && cost->rrb_cost > 0)
	{
		rrr(stack_a, stack_b);
		cost->rra_cost--;
		cost->rrb_cost--;
	}
}

void	exec_single_rot(t_node **stack_a, t_node **stack_b, t_cost *cost)
{
	while (cost->ra_cost-- > 0)
		ra(stack_a, 1);
	while (cost->rra_cost-- > 0)
		rra(stack_a, 1);
	while (cost->rb_cost-- > 0)
		rb(stack_b, 1);
	while (cost->rrb_cost-- > 0)
		rrb(stack_b, 1);
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
