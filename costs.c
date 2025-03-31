/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   costs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glugo-mu <glugo-mu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 01:09:53 by glugo-mu          #+#    #+#             */
/*   Updated: 2025/03/31 13:25:05 by glugo-mu         ###   ########.fr       */
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

void	calculate_ra_rra(t_cost *cost, int pos_a, int len_a)
{
	if (pos_a <= len_a / 2)
		cost->ra_cost = pos_a;
	else
		cost->ra_cost = 0;
	if (pos_a > len_a / 2)
		cost->rra_cost = len_a - pos_a;
	else
		cost->rra_cost = 0;
}

void	calculate_rb_rrb(t_cost *cost, int pos_b, int len_b)
{
	if (pos_b <= len_b / 2)
		cost->rb_cost = pos_b;
	else
		cost->rb_cost = 0;
	if (pos_b > len_b / 2)
		cost->rrb_cost = len_b - pos_b;
	else
		cost->rrb_cost = 0;
}

void	calculate_common_cost(t_cost *cost)
{
	int	common;

	cost->total = cost->ra_cost + cost->rra_cost;
	cost->total += cost->rb_cost + cost->rrb_cost;
	if (cost->ra_cost > 0 && cost->rb_cost > 0)
	{
		if (cost->ra_cost < cost->rb_cost)
			common = cost->ra_cost;
		else
			common = cost->rb_cost;
		cost->total -= common;
	}
	else if (cost->rra_cost > 0 && cost->rrb_cost > 0)
	{
		if (cost->rra_cost < cost->rrb_cost)
			common = cost->rra_cost;
		else
			common = cost->rrb_cost;
		cost->total -= common;
	}
}
