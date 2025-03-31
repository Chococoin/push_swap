/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glugo-mu <glugo-mu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 13:25:09 by glugo-mu          #+#    #+#             */
/*   Updated: 2025/03/31 13:25:27 by glugo-mu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
