/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turk_algorithm.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glugo-mu <glugo-mu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 12:00:00 by glugo-mu          #+#    #+#             */
/*   Updated: 2025/03/30 17:44:04 by glugo-mu         ###   ########.fr       */
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

t_cost	calculate_cost(t_node *stack_a, t_node *stack_b, int value)
{
	t_cost	cost;
	int		pos_a;
	int		pos_b;
	int		len_a;
	int		len_b;

	len_a = stack_length(stack_a);
	len_b = stack_length(stack_b);
	pos_a = get_position(stack_a, value);
	pos_b = find_position_in_b(stack_b, value);
	if (pos_a <= len_a / 2)
		cost.ra_cost = pos_a;
	else
		cost.ra_cost = 0;
	if (pos_a > len_a / 2)
		cost.rra_cost = len_a - pos_a;
	else
		cost.rra_cost = 0;
	if (pos_b <= len_b / 2)
		cost.rb_cost = pos_b;
	else
		cost.rb_cost = 0;
	if (pos_b > len_b / 2)
		cost.rrb_cost = len_b - pos_b;
	else
		cost.rrb_cost = 0;
	cost.total = cost.ra_cost + cost.rra_cost + cost.rb_cost + cost.rrb_cost;
	if (cost.ra_cost > 0 && cost.rb_cost > 0)
	{
		int common = (cost.ra_cost < cost.rb_cost) ? cost.ra_cost : cost.rb_cost;
		cost.total -= common;
	}
	else if (cost.rra_cost > 0 && cost.rrb_cost > 0)
	{
		int common = (cost.rra_cost < cost.rrb_cost) ? cost.rra_cost : cost.rrb_cost;
		cost.total -= common;
	}
	return (cost);
}

int	find_cheapest_value(t_node *stack_a, t_node *stack_b)
{
	t_node	*current;
	t_cost	min_cost;
	t_cost	current_cost;
	int		cheapest_value;

	current = stack_a;
	min_cost.total = 2147483647;
	cheapest_value = current->value;

	while (current)
	{
		current_cost = calculate_cost(stack_a, stack_b, current->value);
		if (current_cost.total < min_cost.total)
		{
			min_cost = current_cost;
			cheapest_value = current->value;
		}
		current = current->next;
	}

	return (cheapest_value);
}

void	execute_rotations(t_node **stack_a, t_node **stack_b, int value, int *move_count)
{
	t_cost	cost;
	int		pos_a;
	int		pos_b;
	int		len_a;
	int		len_b;

	len_a = stack_length(*stack_a);
	len_b = stack_length(*stack_b);
	pos_a = get_position(*stack_a, value);
	pos_b = find_position_in_b(*stack_b, value);

	if (pos_a <= len_a / 2)
		cost.ra_cost = pos_a;
	else
		cost.ra_cost = 0;
	if (pos_a > len_a / 2)
		cost.rra_cost = len_a - pos_a;
	else
		cost.rra_cost = 0;
	if (pos_b <= len_b / 2)
		cost.rb_cost = pos_b;
	else
		cost.rb_cost = 0;
	if (pos_b > len_b / 2)
		cost.rrb_cost = len_b - pos_b;
	else
		cost.rrb_cost = 0;
	while (cost.ra_cost > 0 && cost.rb_cost > 0)
	{
		rr(stack_a, stack_b, move_count);
		cost.ra_cost--;
		cost.rb_cost--;
	}
	while (cost.rra_cost > 0 && cost.rrb_cost > 0)
	{
		rrr(stack_a, stack_b, move_count);
		cost.rra_cost--;
		cost.rrb_cost--;
	}
	while (cost.ra_cost-- > 0)
		ra(stack_a, 1, move_count);
	while (cost.rra_cost-- > 0)
		rra(stack_a, 1, move_count);
	while (cost.rb_cost-- > 0)
		rb(stack_b, 1, move_count);
	while (cost.rrb_cost-- > 0)
		rrb(stack_b, 1, move_count);
}

void	turk_sort(t_node **stack_a, t_node **stack_b, int *move_count)
{
	int	cheapest_value;

	pb(stack_a, stack_b, move_count);
	pb(stack_a, stack_b, move_count);
	while (*stack_a)
	{
		cheapest_value = find_cheapest_value(*stack_a, *stack_b);
		execute_rotations(stack_a, stack_b, cheapest_value, move_count);
		pb(stack_a, stack_b, move_count);
	}
	int	max_pos = get_position(*stack_b, get_max_value(*stack_b));
	int	len_b = stack_length(*stack_b);
	if (max_pos <= len_b / 2)
	{
		while ((*stack_b)->value != get_max_value(*stack_b))
			rb(stack_b, 1, move_count);
	}
	else
	{
		while ((*stack_b)->value != get_max_value(*stack_b))
			rrb(stack_b, 1, move_count);
	}
	while (*stack_b)
		pa(stack_a, stack_b, move_count);
}
