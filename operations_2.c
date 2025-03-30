/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glugo-mu <glugo-mu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 18:33:21 by glugo-mu          #+#    #+#             */
/*   Updated: 2025/03/30 20:40:24 by glugo-mu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ra(t_node **stack_a, int to_print)
{
	t_node	*head;
	t_node	*tail;

	if (!stack_a || !(*stack_a) || !(*stack_a)->next)
		return ;
	head = *stack_a;
	tail = head;
	while (tail->next)
		tail = tail->next;
	*stack_a = head->next;
	(*stack_a)->prev = NULL;
	head->next = NULL;
	head->prev = tail;
	tail->next = head;
	if (to_print)
		write(1, "ra\n", 3);
}

void	rb(t_node **stack_b, int to_print)
{
	t_node	*head;
	t_node	*tail;

	if (!stack_b || !(*stack_b) || !(*stack_b)->next)
		return ;
	head = *stack_b;
	tail = head;
	while (tail->next)
		tail = tail->next;
	*stack_b = head->next;
	(*stack_b)->prev = NULL;
	head->next = NULL;
	head->prev = tail;
	tail->next = head;
	if (to_print)
		write(1, "rb\n", 3);
}

void	rr(t_node **stack_a, t_node **stack_b)
{
	ra(stack_a, 0);
	rb(stack_b, 0);
	write(1, "rr\n", 3);
}

void	rra(t_node **stack_a, int to_print)
{
	t_node	*head;
	t_node	*tail;

	if (!stack_a || !(*stack_a) || !(*stack_a)->next)
		return ;
	head = *stack_a;
	tail = head;
	while (tail->next)
		tail = tail->next;
	tail->prev->next = NULL;
	tail->prev = NULL;
	tail->next = head;
	head->prev = tail;
	*stack_a = tail;
	if (to_print)
		write(1, "rra\n", 4);
}

void	rrb(t_node **stack_b, int to_print)
{
	t_node	*head;
	t_node	*tail;

	if (!stack_b || !(*stack_b) || !(*stack_b)->next)
		return ;
	head = *stack_b;
	tail = head;
	while (tail->next)
		tail = tail->next;
	tail->prev->next = NULL;
	tail->prev = NULL;
	tail->next = head;
	head->prev = tail;
	*stack_b = tail;
	if (to_print)
		write(1, "rrb\n", 4);
}
