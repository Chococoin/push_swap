/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glugo-mu <glugo-mu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 01:09:53 by glugo-mu          #+#    #+#             */
/*   Updated: 2025/03/31 01:45:28 by glugo-mu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	calculate_costs(t_cost *cost, t_positions *positions)
{
	calculate_ra_rra(cost, positions->pos_a, positions->len_a);
	calculate_rb_rrb(cost, positions->pos_b, positions->len_b);
	calculate_common_cost(cost);
}

t_cost	calc_cost(t_node *stack_a, t_node *stack_b, int value)
{
	t_cost		cost;
	t_positions	positions;

	positions.len_a = stack_length(stack_a);
	positions.len_b = stack_length(stack_b);
	positions.pos_a = get_position(stack_a, value);
	positions.pos_b = find_position_in_b(stack_b, value);
	calculate_costs(&cost, &positions);
	return (cost);
}

void	perform_rotations_rr(t_node **stack_a, t_node **stack_b, t_cost *cost)
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

void	perform_rotations(t_node **stack_a, t_node **stack_b, t_cost *cost)
{
	perform_rotations_rr(stack_a, stack_b, cost);
	perform_rot_single(stack_a, stack_b, cost);
}
