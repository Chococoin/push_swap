/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glugo-mu <glugo-mu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 18:33:21 by glugo-mu          #+#    #+#             */
/*   Updated: 2025/03/15 16:57:13 by glugo-mu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sa(t_node **stack_a, int to_print, int *move_count)
{
	int	temp;

	if (!stack_a || !(*stack_a) || !(*stack_a)->next)
		return ;
	temp = (*stack_a)->value;
	(*stack_a)->value = (*stack_a)->next->value;
	(*stack_a)->next->value = temp;
	(*move_count)++;
	if (to_print)
		write(1, "sa\n", 3);
}

void	sb(t_node **stack_b, int to_print, int *move_count)
{
	int	temp;

	if (!stack_b || !(*stack_b) || !(*stack_b)->next)
		return ;
	temp = (*stack_b)->value;
	(*stack_b)->value = (*stack_b)->next->value;
	(*stack_b)->next->value = temp;
	(*move_count)++;
	if (to_print)
		write(1, "sb\n", 3);
}

void	ss(t_node **stack_a, t_node **stack_b, int *move_count)
{
	sa(stack_a, 0, move_count);
	sb(stack_b, 0, move_count);
	(*move_count)++;
	write(1, "ss\n", 3);
}

void	pa(t_node **stack_a, t_node **stack_b, int *move_count)
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
	(*move_count)++;
	write(1, "pa\n", 3);
}

void	pb(t_node **stack_a, t_node **stack_b, int *move_count)
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
	(*move_count)++;
	write(1, "pb\n", 3);
}

void	ra(t_node **stack_a, int to_print, int *move_count)
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
	(*move_count)++;
	if (to_print)
		write(1, "ra\n", 3);
}

void	rb(t_node **stack_b, int to_print, int *move_count)
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
	(*move_count)++;
	if (to_print)
		write(1, "rb\n", 3);
}

void	rr(t_node **stack_a, t_node **stack_b, int *move_count)
{
	ra(stack_a, 0, move_count);
	rb(stack_b, 0, move_count);
	(*move_count)++;
	write(1, "rr\n", 3);
}

void	rra(t_node **stack_a, int to_print, int *move_count)
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
	(*move_count)++;
	if (to_print)
		write(1, "rra\n", 4);
}

void	rrb(t_node **stack_b, int to_print, int *move_count)
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
	(*move_count)++;
	if (to_print)
		write(1, "rrb\n", 4);
}

void	rrr(t_node **stack_a, t_node **stack_b, int *move_count)
{
	rra(stack_a, 0, move_count);
	rrb(stack_b, 0, move_count);
	(*move_count)++;
	write(1, "rrr\n", 4);
}
