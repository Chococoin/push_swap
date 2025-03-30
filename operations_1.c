/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glugo-mu <glugo-mu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 20:29:12 by glugo-mu          #+#    #+#             */
/*   Updated: 2025/03/30 20:39:01 by glugo-mu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sa(t_node **stack_a, int to_print)
{
	int	temp;

	if (!stack_a || !(*stack_a) || !(*stack_a)->next)
		return ;
	temp = (*stack_a)->value;
	(*stack_a)->value = (*stack_a)->next->value;
	(*stack_a)->next->value = temp;
	if (to_print)
		write(1, "sa\n", 3);
}

void	sb(t_node **stack_b, int to_print)
{
	int	temp;

	if (!stack_b || !(*stack_b) || !(*stack_b)->next)
		return ;
	temp = (*stack_b)->value;
	(*stack_b)->value = (*stack_b)->next->value;
	(*stack_b)->next->value = temp;
	if (to_print)
		write(1, "sb\n", 3);
}

void	ss(t_node **stack_a, t_node **stack_b)
{
	sa(stack_a, 0);
	sb(stack_b, 0);
	write(1, "ss\n", 3);
}

void	pa(t_node **stack_a, t_node **stack_b)
{
	t_node	*top_b;

	if (!stack_b || !(*stack_b))
		return ;
	top_b = *stack_b;
	*stack_b = top_b->next;
	if (*stack_b)
		(*stack_b)->prev = NULL;
	top_b->prev = NULL;
	top_b->next = *stack_a;
	if (*stack_a)
		(*stack_a)->prev = top_b;
	*stack_a = top_b;
	write(1, "pa\n", 3);
}

void	pb(t_node **stack_a, t_node **stack_b)
{
	t_node	*top_a;

	if (!stack_a || !(*stack_a))
		return ;
	top_a = *stack_a;
	*stack_a = top_a->next;
	if (*stack_a)
		(*stack_a)->prev = NULL;
	top_a->prev = NULL;
	top_a->next = *stack_b;
	if (*stack_b)
		(*stack_b)->prev = top_a;
	*stack_b = top_a;
	write(1, "pb\n", 3);
}
