/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turk_algorithm.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glugo-mu <glugo-mu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 12:00:00 by glugo-mu          #+#    #+#             */
/*   Updated: 2025/03/30 20:10:22 by glugo-mu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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

void	exec_rotations(t_node **stack_a, t_node **stack_b, int value)
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
		exec_rotations(stack_a, stack_b, cheapest_value);
		pb(stack_a, stack_b);
	}
	rotate_stack_b_to_max(stack_b);
	while (*stack_b)
	{
		pa(stack_a, stack_b);
	}
}
