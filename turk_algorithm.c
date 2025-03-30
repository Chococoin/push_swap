/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turk_algorithm.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glugo-mu <glugo-mu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 12:00:00 by glugo-mu          #+#    #+#             */
/*   Updated: 2025/03/30 19:03:11 by glugo-mu         ###   ########.fr       */
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

static void	calc_rot_costs(t_cost *c, int pos, int len)
{
	c->ra_cost = 0;
	c->rra_cost = 0;
	if (pos <= len / 2)
		c->ra_cost = pos;
	else
		c->rra_cost = len - pos;
}

static int	get_minimum(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

static void	adj_common_cost(t_cost *c)
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

t_cost	calc_cost(t_node *a, t_node *b, int val)
{
	t_cost	c;
	int		pos_a;
	int		pos_b;
	int		len_a;
	int		len_b;

	len_a = stack_length(a);
	len_b = stack_length(b);
	pos_a = get_position(a, val);
	pos_b = find_position_in_b(b, val);
	calc_rot_costs(&c, pos_a, len_a);
	calc_rot_costs(&c, pos_b, len_b);
	c.total = c.ra_cost + c.rra_cost + c.rb_cost + c.rrb_cost;
	adj_common_cost(&c);
	return (c);
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

static void	exec_common_rot(t_node **stack_a, t_node **stack_b, t_cost *cost)
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

static void	exec_single_rot(t_node **stack_a, t_node **stack_b, t_cost *cost)
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

void	execute_rotations(t_node **stack_a, t_node **stack_b, int value)
{
	t_cost	cost;

	cost = calc_cost(*stack_a, *stack_b, value);
	exec_common_rot(stack_a, stack_b, &cost);
	exec_single_rot(stack_a, stack_b, &cost);
}

static void	rotate_stack_b_to_max(t_node **stack_b)
{
	int	max_pos;
	int	len_b;
	int	max_value;

	max_value = get_max_value(*stack_b);
	max_pos = get_position(*stack_b, max_value);
	len_b = stack_length(*stack_b);
	if (max_pos <= len_b / 2)
	{
		while ((*stack_b)->value != max_value)
			rb(stack_b, 1);
	}
	else
	{
		while ((*stack_b)->value != max_value)
			rrb(stack_b, 1);
	}
}

void	turk_sort(t_node **stack_a, t_node **stack_b)
{
	int	cheapest_value;

	pb(stack_a, stack_b);
	pb(stack_a, stack_b);
	while (*stack_a)
	{
		cheapest_value = find_cheapest(*stack_a, *stack_b);
		execute_rotations(stack_a, stack_b, cheapest_value);
		pb(stack_a, stack_b);
	}
	rotate_stack_b_to_max(stack_b);
	while (*stack_b)
	{
		pa(stack_a, stack_b);
	}
}
