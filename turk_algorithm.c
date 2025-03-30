/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turk_algorithm.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glugo-mu <glugo-mu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   */
/*   Created: 2025/03/30 12:00:00 by glugo-mu          #+#    #+#             */
/*   Updated: 2025/03/30 23:45:38 by glugo-mu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	perform_rot_single(t_node **stack_a, t_node **stack_b, t_cost *cost)
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
	t_cost		cost;
	t_positions	positions;

	positions.len_a = stack_length(*stack_a);
	positions.len_b = stack_length(*stack_b);
	positions.pos_a = get_position(*stack_a, value);
	positions.pos_b = find_position_in_b(*stack_b, value);
	calculate_costs(&cost, &positions);
	perform_rotations(stack_a, stack_b, &cost);
}

void	align_stack_b(t_node **stack_b)
{
	int	max_pos;
	int	len_b;

	max_pos = get_position(*stack_b, get_max_value(*stack_b));
	len_b = stack_length(*stack_b);
	if (max_pos <= len_b / 2)
	{
		while ((*stack_b)->value != get_max_value(*stack_b))
			rb(stack_b, 1);
	}
	else
	{
		while ((*stack_b)->value != get_max_value(*stack_b))
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
	align_stack_b(stack_b);
	while (*stack_b)
		pa(stack_a, stack_b);
}
